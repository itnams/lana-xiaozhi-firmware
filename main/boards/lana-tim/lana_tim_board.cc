#include "wifi_board.h"
#include "codecs/no_audio_codec.h"
#include "display/oled_display.h"
#include "lana_face_display.h"
#include "system_reset.h"
#include "application.h"
#include "button.h"
#include "config.h"
#include "mcp_server.h"
#include "led/single_led.h"
#include "assets/lang_config.h"

#include <wifi_station.h>
#include <esp_log.h>
#include <algorithm>
#include <string>
#include <driver/i2c_master.h>
#include <driver/gpio.h>
#include <driver/ledc.h>
#include <esp_timer.h>
#include <esp_lcd_io_i2c.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>

#ifdef SH1106
#include <esp_lcd_panel_sh1106.h>
#endif

#define TAG "LanaTimBoard"


// ---------------------------------------------------------------------------------------------
// Lana War Tank: two N20 motors through an L298 (Motor A = left, IN1/IN2 = GPIO39/40,
// Motor B = right, IN1/IN2 = GPIO43/44), same pins and MCP tool names as the vendor firmware.
// The pins are driven LOW as early as possible so the motors never twitch at boot.
// ---------------------------------------------------------------------------------------------
class TankDrive {
public:
    static void HoldPinsLow() {
        const gpio_num_t pins[] = {TANK_A_IN1_GPIO, TANK_A_IN2_GPIO, TANK_B_IN1_GPIO, TANK_B_IN2_GPIO};
        for (auto pin : pins) {
            gpio_reset_pin(pin);
            gpio_set_direction(pin, GPIO_MODE_OUTPUT);
            gpio_set_level(pin, 0);
        }
    }

    void Init() {
        ledc_timer_config_t timer = {};
        timer.speed_mode = LEDC_LOW_SPEED_MODE;
        timer.duty_resolution = LEDC_TIMER_10_BIT;
        timer.timer_num = LEDC_TIMER_1;
        timer.freq_hz = TANK_PWM_HZ;
        timer.clk_cfg = LEDC_AUTO_CLK;
        ESP_ERROR_CHECK(ledc_timer_config(&timer));
        const gpio_num_t pins[4] = {TANK_A_IN1_GPIO, TANK_A_IN2_GPIO, TANK_B_IN1_GPIO, TANK_B_IN2_GPIO};
        for (int i = 0; i < 4; i++) {
            ledc_channel_config_t ch = {};
            ch.gpio_num = pins[i];
            ch.speed_mode = LEDC_LOW_SPEED_MODE;
            ch.channel = (ledc_channel_t)(LEDC_CHANNEL_2 + i);
            ch.timer_sel = LEDC_TIMER_1;
            ch.duty = 0;
            ch.hpoint = 0;
            ESP_ERROR_CHECK(ledc_channel_config(&ch));
        }
        esp_timer_create_args_t args = {};
        args.callback = [](void* arg) { static_cast<TankDrive*>(arg)->Stop(); };
        args.arg = this;
        args.name = "tank_stop";
        ESP_ERROR_CHECK(esp_timer_create(&args, &stop_timer_));
        ESP_LOGI("TankDrive", "Tank drive ready (A: %d/%d, B: %d/%d)", TANK_A_IN1_GPIO, TANK_A_IN2_GPIO,
                 TANK_B_IN1_GPIO, TANK_B_IN2_GPIO);
    }

    // left/right: -100..100 (percent, sign = direction)
    void Drive(int left, int right, int duration_ms) {
        esp_timer_stop(stop_timer_);
        SetMotor(0, left);
        SetMotor(1, right);
        if (duration_ms > 0) {
            esp_timer_start_once(stop_timer_, (uint64_t)duration_ms * 1000);
        }
    }

    void Stop() {
        if (stop_timer_) esp_timer_stop(stop_timer_);
        SetMotor(0, 0);
        SetMotor(1, 0);
    }

private:
    esp_timer_handle_t stop_timer_ = nullptr;

    static void SetDuty(int channel, int percent) {
        uint32_t duty = (uint32_t)((1023 * percent) / 100);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)(LEDC_CHANNEL_2 + channel), duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)(LEDC_CHANNEL_2 + channel));
    }

    static void SetMotor(int motor, int speed) {
        if (speed > 100) speed = 100;
        if (speed < -100) speed = -100;
        int in1 = motor * 2, in2 = motor * 2 + 1;
        if (speed >= 0) {
            SetDuty(in2, 0);
            SetDuty(in1, speed);
        } else {
            SetDuty(in1, 0);
            SetDuty(in2, -speed);
        }
    }
};

class LanaTimBoard : public WifiBoard {
private:
    i2c_master_bus_handle_t display_i2c_bus_;
    esp_lcd_panel_io_handle_t panel_io_ = nullptr;
    esp_lcd_panel_handle_t panel_ = nullptr;
    Display* display_ = nullptr;
    LanaFaceDisplay* face_display_ = nullptr;
    Button boot_button_;
    Button touch_button_;
    Button volume_up_button_;
    Button volume_down_button_;
    TankDrive tank_;

    void InitializeDisplayI2c() {
        i2c_master_bus_config_t bus_config = {
            .i2c_port = (i2c_port_t)0,
            .sda_io_num = DISPLAY_SDA_PIN,
            .scl_io_num = DISPLAY_SCL_PIN,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .intr_priority = 0,
            .trans_queue_depth = 0,
            .flags = {
                .enable_internal_pullup = 1,
            },
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &display_i2c_bus_));
    }

    void InitializeSsd1306Display() {
        // SSD1306 config (0x3C on most modules, some use 0x3D)
        uint16_t oled_addr = 0x3C;
        if (i2c_master_probe(display_i2c_bus_, 0x3C, 100) != ESP_OK && i2c_master_probe(display_i2c_bus_, 0x3D, 100) == ESP_OK) {
            oled_addr = 0x3D;
        }
        ESP_LOGI(TAG, "SSD1306 at I2C addr 0x%02X", oled_addr);
        esp_lcd_panel_io_i2c_config_t io_config = {
            .dev_addr = oled_addr,
            .on_color_trans_done = nullptr,
            .user_ctx = nullptr,
            .control_phase_bytes = 1,
            .dc_bit_offset = 6,
            .lcd_cmd_bits = 8,
            .lcd_param_bits = 8,
            .flags = {
                .dc_low_on_data = 0,
                .disable_control_phase = 0,
            },
            .scl_speed_hz = 400 * 1000,
        };

        ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c_v2(display_i2c_bus_, &io_config, &panel_io_));

        ESP_LOGI(TAG, "Install SSD1306 driver");
        esp_lcd_panel_dev_config_t panel_config = {};
        panel_config.reset_gpio_num = -1;
        panel_config.bits_per_pixel = 1;

        esp_lcd_panel_ssd1306_config_t ssd1306_config = {
            .height = static_cast<uint8_t>(DISPLAY_HEIGHT),
        };
        panel_config.vendor_config = &ssd1306_config;

#ifdef SH1106
        ESP_ERROR_CHECK(esp_lcd_new_panel_sh1106(panel_io_, &panel_config, &panel_));
#else
        ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(panel_io_, &panel_config, &panel_));
#endif
        ESP_LOGI(TAG, "SSD1306 driver installed");

        // Reset the display
        ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_));
        if (esp_lcd_panel_init(panel_) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to initialize display");
            display_ = new NoDisplay();
            return;
        }
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_, false));

        // Set the display to on
        ESP_LOGI(TAG, "Turning display on");
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_, true));

        face_display_ = new LanaFaceDisplay(panel_io_, panel_, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y);
        display_ = face_display_;
    }

    void InitializeButtons() {
        boot_button_.OnClick([this]() {
            auto& app = Application::GetInstance();
            if (app.GetDeviceState() == kDeviceStateStarting && !WifiStation::GetInstance().IsConnected()) {
                ResetWifiConfiguration();
            }
            app.ToggleChatState();
        });
        touch_button_.OnPressDown([this]() {
            Application::GetInstance().StartListening();
        });
        touch_button_.OnPressUp([this]() {
            Application::GetInstance().StopListening();
        });

        // Volume buttons on GPIO18 (+) / GPIO17 (-): click = +/-10, long press (1 s) = max / mute
        volume_up_button_.OnClick([this]() { ChangeVolume(+10); });
        volume_up_button_.OnLongPress([this]() { SetVolume(100, Lang::Strings::MAX_VOLUME); });
        volume_down_button_.OnClick([this]() { ChangeVolume(-10); });
        volume_down_button_.OnLongPress([this]() { SetVolume(0, Lang::Strings::MUTED); });
    }

    void ChangeVolume(int delta) {
        int v = std::max(0, std::min(100, GetAudioCodec()->output_volume() + delta));
        SetVolume(v, nullptr);
    }

    void SetVolume(int v, const char* text) {
        GetAudioCodec()->SetOutputVolume(v);
        if (display_ == nullptr) return;
        if (text) display_->ShowNotification(text);
        else display_->ShowNotification(Lang::Strings::VOLUME + std::to_string(v));
        if (face_display_) face_display_->ShowVolume(v);
    }

    // 物联网初始化，逐步迁移到 MCP 协议
    void InitializeTools() {
        tank_.Init();
        auto& mcp = McpServer::GetInstance();
        auto props = []() {
            return PropertyList({
                Property("pace", kPropertyTypeString, "normal"),
                Property("speed", kPropertyTypeInteger, 70, 30, 100),
                Property("duration_ms", kPropertyTypeInteger, 1000, 100, 10000),
            });
        };
        auto pace_speed = [](const PropertyList& p) {
            std::string pace = p["pace"].value<std::string>();
            if (pace == "slow" || pace == "cham") return 45;
            if (pace == "fast" || pace == "nhanh") return 100;
            if (pace == "custom" || pace == "manual") return p["speed"].value<int>();
            return 70;
        };
        struct Move { const char* name; const char* desc; int l; int r; };
        static const Move moves[] = {
            {"self.tank.forward", "Lana War Tank: tiến thẳng. pace=normal|slow|fast|custom, speed khi custom (30-100), duration_ms (mặc định 1000).", 1, 1},
            {"self.tank.backward", "Lana War Tank: lùi thẳng. Tham số giống self.tank.forward.", -1, -1},
            {"self.tank.turn_left", "Lana War Tank: rẽ trái (bánh trái dừng, bánh phải tiến).", 0, 1},
            {"self.tank.turn_right", "Lana War Tank: rẽ phải (bánh phải dừng, bánh trái tiến).", 1, 0},
            {"self.tank.spin_left", "Lana War Tank: xoay trái tại chỗ (bánh trái lùi, bánh phải tiến).", -1, 1},
            {"self.tank.spin_right", "Lana War Tank: xoay phải tại chỗ (bánh trái tiến, bánh phải lùi).", 1, -1},
        };
        for (const auto& m : moves) {
            const Move* mv = &m;
            mcp.AddTool(mv->name, mv->desc, props(), [this, mv, pace_speed](const PropertyList& p) -> ReturnValue {
                int sp = pace_speed(p);
                tank_.Drive(mv->l * sp, mv->r * sp, p["duration_ms"].value<int>());
                return true;
            });
        }
        mcp.AddTool("self.tank.stop", "Lana War Tank: dừng cả hai motor N20 (Motor A trái, Motor B phải).", PropertyList(),
            [this](const PropertyList&) -> ReturnValue {
                tank_.Stop();
                return true;
            });
    }

public:
    LanaTimBoard() :
        boot_button_(BOOT_BUTTON_GPIO),
        touch_button_(TOUCH_BUTTON_GPIO),
        volume_up_button_(VOLUME_UP_BUTTON_GPIO, false, 1000),
        volume_down_button_(VOLUME_DOWN_BUTTON_GPIO, false, 1000) {
        TankDrive::HoldPinsLow();
        InitializeDisplayI2c();
        InitializeSsd1306Display();
        InitializeButtons();
        InitializeTools();
    }

    // 2.2.4: the app turns modem sleep on whenever the audio channel closes; Lana is mains powered and needs a
    // responsive radio for pushes / low-latency UDP, so every request is mapped to WIFI_PS_NONE.
    virtual void SetPowerSaveMode(bool enabled) override {
        (void)enabled;
        WifiBoard::SetPowerSaveMode(false);
    }

    virtual Led* GetLed() override {
        static SingleLed led(BUILTIN_LED_GPIO);
        return &led;
    }

    virtual AudioCodec* GetAudioCodec() override {
#ifdef AUDIO_I2S_METHOD_SIMPLEX
        static NoAudioCodecSimplex audio_codec(AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_SPK_GPIO_BCLK, AUDIO_I2S_SPK_GPIO_LRCK, AUDIO_I2S_SPK_GPIO_DOUT, AUDIO_I2S_MIC_GPIO_SCK, AUDIO_I2S_MIC_GPIO_WS, AUDIO_I2S_MIC_GPIO_DIN);
#else
        static NoAudioCodecDuplex audio_codec(AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_BCLK, AUDIO_I2S_GPIO_WS, AUDIO_I2S_GPIO_DOUT, AUDIO_I2S_GPIO_DIN);
#endif
        return &audio_codec;
    }

    virtual Display* GetDisplay() override {
        return display_;
    }
};

DECLARE_BOARD(LanaTimBoard);
