// Lana robot face for the 128x64 SSD1306: animated eyes from lana_eyes.h (21 emotions, blinks, saccades,
// listening/speaking/connecting motion, volume bar) drawn into a 128x48 L8 LVGL image under the stock
// 16 px status bar, with the subtitle as one scrolling line at the bottom.
//
// Threading: a separate low-priority FreeRTOS task (priority 1, ~25 fps) steps + renders the eyes into a
// scratch buffer WITHOUT holding the LVGL lock, then takes the lock briefly (non-blocking-ish, 20 ms max)
// to copy the frame and invalidate the image only when it changed. The actual I2C flush happens in the
// esp_lvgl_port task (also priority 1), so nothing here ever runs on the audio path.
#pragma once

#include "display/oled_display.h"
#include "assets/lang_config.h"
#include "lana_eyes.h"
#include <font_awesome.h>
#include <esp_random.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_heap_caps.h>
#include <cstring>
#include <string>
#include <mutex>
#include <algorithm>

LV_FONT_DECLARE(font_awesome_30_1);

class LanaFaceDisplay : public OledDisplay {
public:
    static constexpr int kW = lana_eyes::Renderer::W;
    static constexpr int kH = lana_eyes::Renderer::H;
    static constexpr int kSubtitleH = 18;
    static constexpr int kFrameMs = 40;   // 25 fps

    LanaFaceDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel, int width, int height,
                    bool mirror_x, bool mirror_y)
        : OledDisplay(panel_io, panel, width, height, mirror_x, mirror_y), eyes_(esp_random()) {
        if (height != 64 || container_ == nullptr || content_ == nullptr) {
            return;  // stock layout for anything else
        }
        frame_ = (uint8_t*)heap_caps_malloc(kW * kH, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
        scratch_ = (uint8_t*)heap_caps_malloc(kW * kH, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
        if (frame_ == nullptr || scratch_ == nullptr) {
            ESP_LOGE("LanaFace", "no memory for the eye frame, keeping stock layout");
            return;
        }
        memset(frame_, 0xFF, kW * kH);   // 0xFF = pixel off (black = lit on this monochrome port)

        DisplayLockGuard lock(this);
        lv_obj_add_flag(content_, LV_OBJ_FLAG_HIDDEN);  // flex layout skips hidden children

        face_ = lv_obj_create(container_);
        lv_obj_set_width(face_, LV_HOR_RES);
        lv_obj_set_flex_grow(face_, 1);
        lv_obj_set_style_pad_all(face_, 0, 0);
        lv_obj_set_style_border_width(face_, 0, 0);
        lv_obj_set_style_radius(face_, 0, 0);
        lv_obj_set_scrollbar_mode(face_, LV_SCROLLBAR_MODE_OFF);
        lv_obj_remove_flag(face_, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_layout(face_, LV_LAYOUT_NONE, 0);

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
        lv_obj_align(icon_, LV_ALIGN_TOP_MID, 0, 6);
        lv_obj_add_flag(icon_, LV_OBJ_FLAG_HIDDEN);

        subtitle_ = lv_label_create(face_);
        lv_obj_set_width(subtitle_, LV_HOR_RES);
        lv_label_set_long_mode(subtitle_, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_style_text_align(subtitle_, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(subtitle_, LV_ALIGN_BOTTOM_MID, 0, 0);
        lv_label_set_text(subtitle_, "");
        lv_obj_add_flag(subtitle_, LV_OBJ_FLAG_HIDDEN);

        xTaskCreatePinnedToCore([](void* arg) { static_cast<LanaFaceDisplay*>(arg)->RenderLoop(); },
                                "lana_eyes", 3072, this, 1, &task_, 1);
    }

    virtual void SetEmotion(const char* emotion) override {
        if (face_ == nullptr) {
            OledDisplay::SetEmotion(emotion);
            return;
        }
        int e = lana_eyes::EmotionFromName(emotion ? emotion : "neutral");
        if (e >= 0) {
            {
                std::lock_guard<std::mutex> g(eyes_mutex_);
                eyes_.SetEmotion(e);
                show_icon_ = false;
            }
            DisplayLockGuard lock(this);
            lv_obj_add_flag(icon_, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(image_, LV_OBJ_FLAG_HIDDEN);
        } else {
            // not a face (boot chip, wifi/link/error icons...): show the font-awesome icon instead of the eyes
            const char* utf8 = font_awesome_get_utf8(emotion ? emotion : "");
            {
                std::lock_guard<std::mutex> g(eyes_mutex_);
                show_icon_ = true;
            }
            DisplayLockGuard lock(this);
            lv_label_set_text(icon_, utf8 ? utf8 : FONT_AWESOME_MICROCHIP_AI);
            lv_obj_remove_flag(icon_, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(image_, LV_OBJ_FLAG_HIDDEN);
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
        std::lock_guard<std::mutex> g(eyes_mutex_);
        eyes_.SetState(s);
    }

    virtual void SetChatMessage(const char* role, const char* content) override {
        if (face_ == nullptr) {
            OledDisplay::SetChatMessage(role, content);
            return;
        }
        std::string s = content ? content : "";
        std::replace(s.begin(), s.end(), '\n', ' ');
        {
            std::lock_guard<std::mutex> g(eyes_mutex_);
            eyes_.SetReservedBottom(s.empty() ? 0 : kSubtitleH);
        }
        DisplayLockGuard lock(this);
        if (s.empty()) {
            lv_obj_add_flag(subtitle_, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_label_set_text(subtitle_, s.c_str());
            lv_obj_remove_flag(subtitle_, LV_OBJ_FLAG_HIDDEN);
        }
    }

    // Volume buttons: bar drawn under the eyes for 1.5 s (the status bar shows the text notification)
    void ShowVolume(int volume) {
        if (face_ == nullptr) return;
        std::lock_guard<std::mutex> g(eyes_mutex_);
        eyes_.ShowVolume(volume, 1500);
    }

private:
    void RenderLoop() {
        TickType_t last = xTaskGetTickCount();
        while (true) {
            bool icon;
            {
                std::lock_guard<std::mutex> g(eyes_mutex_);
                eyes_.Step(kFrameMs);
                icon = show_icon_;
                if (!icon) eyes_.Render(scratch_);
            }
            if (!icon) {
                // 1 = lit -> L8 0x00 (black = lit pixel), 0 -> 0xFF
                for (int i = 0; i < kW * kH; i++) scratch_[i] = scratch_[i] ? 0x00 : 0xFF;
                if (memcmp(scratch_, frame_, kW * kH) != 0 && Lock(20)) {
                    memcpy(frame_, scratch_, kW * kH);
                    lv_image_cache_drop(&dsc_);
                    lv_obj_invalidate(image_);
                    Unlock();
                }
            }
            vTaskDelayUntil(&last, pdMS_TO_TICKS(kFrameMs));
        }
    }

    lana_eyes::Renderer eyes_;
    std::mutex eyes_mutex_;
    bool show_icon_ = false;
    uint8_t* frame_ = nullptr;
    uint8_t* scratch_ = nullptr;
    lv_image_dsc_t dsc_;
    lv_obj_t* face_ = nullptr;
    lv_obj_t* image_ = nullptr;
    lv_obj_t* icon_ = nullptr;
    lv_obj_t* subtitle_ = nullptr;
    TaskHandle_t task_ = nullptr;
};
