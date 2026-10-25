// Lana robot face for the 0.96" SSD1306 128x64 monochrome OLED (2.2.4 redesign).
// The whole panel is one 128x64 L8 LVGL image composed by lana_ui.h (eyes, status strip, subtitle, idle clock,
// alarm and Wi-Fi setup screens, Vietnamese bitmap font); the stock OLED layout is hidden. Only the font-awesome
// icon for non-face emotions (boot chip, errors...) is still an LVGL label drawn over the frame.
//
// Threading: a separate low-priority FreeRTOS task (priority 1, ~25 fps; 4 fps in clock mode) steps + renders the
// frame into a scratch buffer WITHOUT holding the LVGL lock, then takes the lock briefly (20 ms max) to copy it
// and invalidate the image only when it changed. The I2C flush runs in the esp_lvgl_port task, never on audio.
#pragma once

#include "display/oled_display.h"
#include "assets/lang_config.h"
#include "lana_ui.h"
#include "board.h"
#include <font_awesome.h>
#include <esp_random.h>
#include <esp_log.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_heap_caps.h>
#include <cstring>
#include <string>
#include <mutex>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <sys/time.h>
#include <esp_timer.h>

LV_FONT_DECLARE(font_awesome_30_1);

class LanaFaceDisplay : public OledDisplay {
public:
    static constexpr int kW = lana_ui::W;
    static constexpr int kH = lana_ui::H;
    static constexpr int kFrameMs = 40;   // 25 fps
    static constexpr int kClockFrameMs = 250;

    LanaFaceDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel, int width, int height,
                    bool mirror_x, bool mirror_y)
        : OledDisplay(panel_io, panel, width, height, mirror_x, mirror_y) {
        if (height != 64 || container_ == nullptr) {
            return;  // stock layout for anything else
        }
        ui_ = new lana_ui::Ui(esp_random());
        frame_ = (uint8_t*)heap_caps_malloc(kW * kH, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
        scratch_ = (uint8_t*)heap_caps_malloc(kW * kH, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
        if (ui_ == nullptr || frame_ == nullptr || scratch_ == nullptr) {
            ESP_LOGE("LanaFace", "no memory for the UI frame, keeping stock layout");
            return;
        }
        memset(frame_, 0xFF, kW * kH);   // 0xFF = pixel off (black = lit on this monochrome port)

        DisplayLockGuard lock(this);
        lv_obj_add_flag(container_, LV_OBJ_FLAG_HIDDEN);   // stock status bar + chat area: replaced by our frame

        face_ = lv_obj_create(lv_screen_active());
        lv_obj_set_size(face_, kW, kH);
        lv_obj_set_pos(face_, 0, 0);
        lv_obj_set_style_pad_all(face_, 0, 0);
        lv_obj_set_style_border_width(face_, 0, 0);
        lv_obj_set_style_radius(face_, 0, 0);
        lv_obj_set_scrollbar_mode(face_, LV_SCROLLBAR_MODE_OFF);
        lv_obj_remove_flag(face_, LV_OBJ_FLAG_SCROLLABLE);

        memset(&dsc_, 0, sizeof(dsc_));
        dsc_.header.magic = LV_IMAGE_HEADER_MAGIC;
        dsc_.header.cf = LV_COLOR_FORMAT_L8;
        dsc_.header.w = kW;
        dsc_.header.h = kH;
        dsc_.header.stride = kW;
        dsc_.data_size = kW * kH;
        dsc_.data = frame_;
        image_ = lv_image_create(face_);
        lv_image_set_src(image_, &dsc_);
        lv_obj_set_pos(image_, 0, 0);

        icon_ = lv_label_create(face_);
        lv_obj_set_style_text_font(icon_, &font_awesome_30_1, 0);
        lv_obj_align(icon_, LV_ALIGN_CENTER, 0, 6);
        lv_obj_add_flag(icon_, LV_OBJ_FLAG_HIDDEN);
        last_activity_us_ = esp_timer_get_time();

        xTaskCreatePinnedToCore([](void* arg) { static_cast<LanaFaceDisplay*>(arg)->RenderLoop(); },
                                "lana_eyes", 8192, this, 1, &task_, 1);
    }

    virtual void SetEmotion(const char* emotion) override {
        if (face_ == nullptr) {
            OledDisplay::SetEmotion(emotion);
            return;
        }
        int e = lana_eyes::EmotionFromName(emotion ? emotion : "neutral");
        if (e != lana_eyes::kNeutral) Touch();
        if (e >= 0) {
            {
                std::lock_guard<std::mutex> g(mutex_);
                ui_->eyes().SetEmotion(e);
                show_icon_ = false;
                alarm_ = (e == lana_eyes::kAlarm);
            }
            DisplayLockGuard lock(this);
            lv_obj_add_flag(icon_, LV_OBJ_FLAG_HIDDEN);
        } else {
            // not a face (boot chip, wifi/link/error icons...): font-awesome icon over the frame, strip keeps the text
            const char* utf8 = font_awesome_get_utf8(emotion ? emotion : "");
            {
                std::lock_guard<std::mutex> g(mutex_);
                show_icon_ = true;
                alarm_ = false;
            }
            DisplayLockGuard lock(this);
            lv_label_set_text(icon_, utf8 ? utf8 : FONT_AWESOME_MICROCHIP_AI);
            lv_obj_remove_flag(icon_, LV_OBJ_FLAG_HIDDEN);
        }
    }

    virtual void SetStatus(const char* status) override {
        OledDisplay::SetStatus(status);
        if (face_ == nullptr || status == nullptr) return;
        lana_eyes::State s = lana_eyes::kStateIdle;
        if (strcmp(status, Lang::Strings::LISTENING) == 0) s = lana_eyes::kStateListening;
        else if (strcmp(status, Lang::Strings::SPEAKING) == 0) s = lana_eyes::kStateSpeaking;
        else if (strcmp(status, Lang::Strings::CONNECTING) == 0 || strcmp(status, Lang::Strings::LOADING_PROTOCOL) == 0 ||
                 strcmp(status, Lang::Strings::REGISTERING_NETWORK) == 0 || strcmp(status, Lang::Strings::CHECKING_NEW_VERSION) == 0 ||
                 strcmp(status, Lang::Strings::UPGRADING) == 0)
            s = lana_eyes::kStateConnecting;
        // the idle status bar shows the time ("21:07") every second: that is still standby, not activity
        bool is_clock = strlen(status) == 5 && status[2] == ':' && isdigit((unsigned char)status[0]) && isdigit((unsigned char)status[4]);
        if (is_clock) return;
        {
            std::lock_guard<std::mutex> g(mutex_);
            ui_->eyes().SetState(s);
            model_.state = s;
            idle_ = (s == lana_eyes::kStateIdle && strcmp(status, Lang::Strings::STANDBY) == 0);
            model_.status = idle_ ? std::string() : Ellipsis(status);
            if (strcmp(status, Lang::Strings::WIFI_CONFIG_MODE) == 0) wifi_setup_ = true;
        }
        if (last_status_ != status) { last_status_ = status; Touch(); }
    }

    virtual void ShowNotification(const char* notification, int duration_ms = 3000) override {
        if (face_ == nullptr) { OledDisplay::ShowNotification(notification, duration_ms); return; }
        std::lock_guard<std::mutex> g(mutex_);
        notif_ = notification ? Ellipsis(notification) : std::string();
        notif_until_us_ = esp_timer_get_time() + (int64_t)duration_ms * 1000;
        last_activity_us_ = esp_timer_get_time();
    }
    virtual void ShowNotification(const std::string& notification, int duration_ms = 3000) override {
        ShowNotification(notification.c_str(), duration_ms);
    }

    virtual void SetChatMessage(const char* role, const char* content) override {
        if (face_ == nullptr) {
            OledDisplay::SetChatMessage(role, content);
            return;
        }
        std::string s = content ? content : "";
        std::replace(s.begin(), s.end(), '\n', ' ');
        if (!s.empty()) Touch();
        std::lock_guard<std::mutex> g(mutex_);
        // Wi-Fi setup hint: "<CONNECT_TO_HOTSPOT><ssid><ACCESS_VIA_BROWSER><url>" -> dedicated setup screen
        const std::string hot = Lang::Strings::CONNECT_TO_HOTSPOT, via = Lang::Strings::ACCESS_VIA_BROWSER;
        size_t a = s.find(hot), b = s.find(via);
        if (a != std::string::npos && b != std::string::npos && b > a) {
            model_.ssid = s.substr(a + hot.size(), b - a - hot.size());
            model_.url = s.substr(b + via.size());
            wifi_setup_ = true;
            return;
        }
        if (s != model_.subtitle) { model_.subtitle = s; ui_->ResetScroll(); }
    }

    virtual void LanaShowVolume(int volume) override { ShowVolume(volume); }
    // Weather pushed by the server about every 15 min; hidden again when older than 2 h
    virtual void LanaSetWeather(int temp_c, int icon) override {
        std::lock_guard<std::mutex> g(mutex_);
        model_.temp = temp_c; model_.wx = icon;
        weather_us_ = esp_timer_get_time();
    }

    // Volume buttons: bar drawn under the eyes for 1.5 s (the strip shows the text notification)
    void ShowVolume(int volume) {
        if (face_ == nullptr) return;
        Touch();
        std::lock_guard<std::mutex> g(mutex_);
        ui_->eyes().ShowVolume(volume, 1500);
    }

    // Idle clock after this many minutes of standby without activity (0 = never)
    virtual void SetIdleClockMinutes(int minutes) override { idle_clock_min_ = minutes < 0 ? 0 : (minutes > 120 ? 120 : minutes); }
    // Any user/robot activity: leave the clock immediately
    void Touch() { last_activity_us_ = esp_timer_get_time(); }

private:
    static std::string Ellipsis(const char* s) {   // "Đang nói..." -> "Đang nói…" (narrower, one glyph)
        std::string r = s;
        size_t p;
        while ((p = r.find("...")) != std::string::npos) r.replace(p, 3, "…");
        return r;
    }

    bool WantClock(const struct tm& tmv) {
        if (!idle_ || idle_clock_min_ <= 0 || show_icon_ || alarm_) return false;
        if (tmv.tm_year + 1900 < 2025) return false;
        return esp_timer_get_time() - last_activity_us_ >= (int64_t)idle_clock_min_ * 60 * 1000000;
    }

    void RenderLoop() {
        TickType_t last = xTaskGetTickCount();
        int64_t next_rssi_us = 0;
        while (true) {
            int64_t now_us = esp_timer_get_time();
            if (now_us >= next_rssi_us) {   // Wi-Fi bars: poll the AP info every 5 s (cheap, no lock)
                next_rssi_us = now_us + 5000000;
                wifi_ap_record_t ap = {};
                rssi_ = (esp_wifi_sta_get_ap_info(&ap) == ESP_OK) ? ap.rssi : 0;
                int lvl = 0; bool chg = false, dis = false;   // boards without battery sense return false -> hidden
                if (Board::GetInstance().GetBatteryLevel(lvl, chg, dis)) { battery_ = lvl; charging_ = chg; }
                else battery_ = -1;
            }
            time_t now = time(nullptr);
            struct tm tmv;
            localtime_r(&now, &tmv);
            bool clock = WantClock(tmv);
            int frame_ms = clock ? kClockFrameMs : kFrameMs;    // 4 fps in clock mode: low CPU
            {
                std::lock_guard<std::mutex> g(mutex_);
                lana_ui::Model m = model_;
                m.rssi = rssi_;
                m.battery = battery_; m.charging = charging_;
                if (m.wx > 0 && now_us - weather_us_ > 2LL * 3600 * 1000000) m.wx = 0;
                m.hh = tmv.tm_hour; m.mm = tmv.tm_min; m.ss = tmv.tm_sec;
                m.wday = tmv.tm_wday; m.mday = tmv.tm_mday; m.mon = tmv.tm_mon + 1;
                if (!notif_.empty() && now_us < notif_until_us_) m.status = notif_;
                if (wifi_setup_) m.screen = lana_ui::kScreenWifiSetup;
                else if (alarm_) m.screen = lana_ui::kScreenAlarm;
                else if (clock) m.screen = lana_ui::kScreenClock;
                else if (show_icon_) m.screen = lana_ui::kScreenIcon;
                else m.screen = lana_ui::kScreenFace;
                ui_->Step(frame_ms);
                ui_->Render(m, scratch_);
            }
            if (clock != clock_on_) {
                clock_on_ = clock;
                ESP_LOGI("LanaFace", "clock %s, eyes stack free %u", clock ? "on" : "off",
                         (unsigned)uxTaskGetStackHighWaterMark(nullptr));
            }
            // 1 = lit -> L8 0x00 (black = lit pixel), 0 -> 0xFF
            for (int i = 0; i < kW * kH; i++) scratch_[i] = scratch_[i] ? 0x00 : 0xFF;
            if (memcmp(scratch_, frame_, kW * kH) != 0 && Lock(20)) {
                memcpy(frame_, scratch_, kW * kH);
                lv_image_cache_drop(&dsc_);
                lv_obj_invalidate(image_);
                Unlock();
            }
            vTaskDelayUntil(&last, pdMS_TO_TICKS(frame_ms));
        }
    }

    lana_ui::Ui* ui_ = nullptr;
    lana_ui::Model model_;
    int64_t weather_us_ = 0;
    std::mutex mutex_;
    bool show_icon_ = false;
    bool alarm_ = false;
    bool wifi_setup_ = false;
    std::string notif_;
    int64_t notif_until_us_ = 0;
    volatile int rssi_ = 0;
    volatile int battery_ = -1;
    volatile bool charging_ = false;
    uint8_t* frame_ = nullptr;
    uint8_t* scratch_ = nullptr;
    lv_image_dsc_t dsc_;
    lv_obj_t* face_ = nullptr;
    lv_obj_t* image_ = nullptr;
    lv_obj_t* icon_ = nullptr;
    TaskHandle_t task_ = nullptr;
    volatile bool idle_ = false;
    volatile bool clock_on_ = false;
    volatile int idle_clock_min_ = 2;
    volatile int64_t last_activity_us_ = 0;
    std::string last_status_;
};
