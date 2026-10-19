// Lana robot face for the 128x64 SSD1306: two animated eyes (blink, bounce, look around) that follow the
// emotion the server sends ({"type":"llm","emotion":...}), with the subtitle as one scrolling line below.
// Replaces the stock 32 px font-awesome emotion icon of OledDisplay::SetupUI_128x64 (top status bar kept).
#pragma once

#include "display/oled_display.h"
#include <font_awesome.h>
#include <esp_random.h>
#include <cstring>
#include <string>
#include <algorithm>

LV_FONT_DECLARE(font_awesome_30_1);

class LanaFaceDisplay : public OledDisplay {
public:
    LanaFaceDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel, int width, int height,
                    bool mirror_x, bool mirror_y)
        : OledDisplay(panel_io, panel, width, height, mirror_x, mirror_y) {
        if (height != 64 || container_ == nullptr || content_ == nullptr) {
            return;  // stock layout for anything else
        }
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

        for (int i = 0; i < 2; i++) {
            eye_[i] = MakeRect(face_, true);
            cover_[i] = MakeRect(face_, false);
            brow_[i] = lv_line_create(face_);
            lv_obj_set_style_line_width(brow_[i], 2, 0);
            lv_obj_set_style_line_color(brow_[i], lv_color_black(), 0);
            lv_obj_set_style_line_rounded(brow_[i], true, 0);
        }
        icon_ = lv_label_create(face_);
        lv_obj_set_style_text_font(icon_, &font_awesome_30_1, 0);
        lv_obj_add_flag(icon_, LV_OBJ_FLAG_HIDDEN);

        subtitle_ = lv_label_create(face_);
        lv_obj_set_width(subtitle_, LV_HOR_RES);
        lv_label_set_long_mode(subtitle_, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_style_text_align(subtitle_, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(subtitle_, LV_ALIGN_BOTTOM_MID, 0, 0);
        lv_label_set_text(subtitle_, "");
        lv_obj_add_flag(subtitle_, LV_OBJ_FLAG_HIDDEN);

        face_kind_ = FindFace("neutral");
        Apply();
        timer_ = lv_timer_create([](lv_timer_t* t) {
            static_cast<LanaFaceDisplay*>(lv_timer_get_user_data(t))->Tick();
        }, 50, this);
    }

    virtual void SetEmotion(const char* emotion) override {
        if (face_ == nullptr) {
            OledDisplay::SetEmotion(emotion);
            return;
        }
        DisplayLockGuard lock(this);
        int k = FindFace(emotion ? emotion : "neutral");
        if (k >= 0) {
            face_kind_ = k;
            lv_obj_add_flag(icon_, LV_OBJ_FLAG_HIDDEN);
        } else {
            // not a face (boot chip, wifi/link/error icons...): show the font-awesome icon instead of the eyes
            const char* utf8 = font_awesome_get_utf8(emotion ? emotion : "");
            face_kind_ = -1;
            lv_label_set_text(icon_, utf8 ? utf8 : FONT_AWESOME_MICROCHIP_AI);
            lv_obj_remove_flag(icon_, LV_OBJ_FLAG_HIDDEN);
        }
        phase_ = 0;
        Apply();
    }

    virtual void SetChatMessage(const char* role, const char* content) override {
        if (face_ == nullptr) {
            OledDisplay::SetChatMessage(role, content);
            return;
        }
        DisplayLockGuard lock(this);
        std::string s = content ? content : "";
        std::replace(s.begin(), s.end(), '\n', ' ');
        if (s.empty()) {
            lv_obj_add_flag(subtitle_, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_label_set_text(subtitle_, s.c_str());
            lv_obj_remove_flag(subtitle_, LV_OBJ_FLAG_HIDDEN);
        }
        Apply();
    }

private:
    // brow: 0 none, 1 sad (inner ends up), 2 angry (inner ends down), 3 raised flat, 4 left raised only
    // cover: 0 none, 1 smile (lower arc covered -> ^ ^), 2 lid from top (fraction 1/2), 3 lid 2/3 (sleepy)
    // anim: 0 none, 1 bounce (laugh), 2 look around (thinking), 3 shake (angry/shocked), 4 wink right eye
    struct Face { const char* name; int w, h, r; int lw_scale, rw_scale; int look_x, look_y; int brow, cover, anim; bool blink; };
    static const Face* Faces() {
        static const Face f[] = {
            {"neutral",     20, 24, 7, 100, 100,  0,  0, 0, 0, 0, true},
            {"happy",       22, 22, 9, 100, 100,  0, -1, 0, 1, 0, false},
            {"laughing",    22, 20, 9, 100, 100,  0, -2, 0, 1, 1, false},
            {"funny",       22, 20, 9, 100, 100,  0, -2, 0, 1, 1, false},
            {"sad",         20, 20, 7, 100, 100,  0,  3, 1, 0, 0, true},
            {"crying",      20, 18, 7, 100, 100,  0,  3, 1, 2, 3, false},
            {"angry",       22, 18, 4, 100, 100,  0,  2, 2, 0, 3, false},
            {"loving",      22, 22, 11, 100, 100, 0, -1, 0, 1, 1, false},
            {"embarrassed", 16, 16, 7, 100, 100,  0,  5, 1, 2, 0, true},
            {"surprised",   24, 28, 12, 100, 100, 0, -1, 3, 0, 0, true},
            {"shocked",     18, 28, 9, 100, 100,  0, -2, 3, 0, 3, false},
            {"thinking",    18, 22, 7, 100, 100,  6, -4, 4, 0, 2, true},
            {"winking",     22, 22, 9, 100, 100,  0,  0, 0, 1, 4, false},
            {"cool",        26, 10, 2, 100, 100,  0,  0, 0, 0, 0, false},
            {"relaxed",     22, 20, 9, 100, 100,  0,  2, 0, 2, 0, false},
            {"delicious",   22, 22, 9, 100, 100,  0, -1, 0, 1, 1, false},
            {"kissy",       22, 22, 9, 100, 100,  0,  0, 0, 1, 4, false},
            {"confident",   22, 20, 5, 100, 100,  0,  0, 0, 2, 0, true},
            {"sleepy",      22, 22, 9, 100, 100,  0,  4, 0, 3, 0, false},
            {"silly",       22, 24, 11, 120, 70,  0,  0, 0, 0, 1, true},
            {"confused",    18, 22, 8, 100, 85, -5, -2, 4, 0, 2, true},
        };
        return f;
    }
    static constexpr int kFaces = 21;

    static int FindFace(const char* name) {
        if (strcmp(name, "anger") == 0) name = "angry";
        if (strcmp(name, "scare") == 0) name = "shocked";
        for (int i = 0; i < kFaces; i++) {
            if (strcmp(Faces()[i].name, name) == 0) return i;
        }
        return -1;
    }

    static lv_obj_t* MakeRect(lv_obj_t* parent, bool lit) {
        lv_obj_t* o = lv_obj_create(parent);
        lv_obj_set_style_border_width(o, 0, 0);
        lv_obj_set_style_pad_all(o, 0, 0);
        lv_obj_set_style_bg_opa(o, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(o, lit ? lv_color_black() : lv_color_white(), 0);  // black = lit pixel on this OLED
        lv_obj_remove_flag(o, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(o, LV_SCROLLBAR_MODE_OFF);
        return o;
    }

    void Tick() {
        tick_++;
        if (face_kind_ < 0) return;
        const Face& f = Faces()[face_kind_];
        bool changed = false;
        // blink: every 2.5-6 s, 150 ms closed
        if (blink_left_ > 0) {
            if (--blink_left_ == 0) changed = true;
        } else if (f.blink && tick_ >= next_blink_) {
            blink_left_ = 3;
            next_blink_ = tick_ + 50 + (esp_random() % 70);
            changed = true;
        }
        if (f.anim != 0 && (tick_ % 4) == 0) {  // 200 ms animation step
            phase_++;
            changed = true;
        }
        if (changed) Apply();
    }

    void Apply() {
        if (face_ == nullptr) return;
        bool sub = !lv_obj_has_flag(subtitle_, LV_OBJ_FLAG_HIDDEN);
        int area_h = 48;
        int cy = sub ? 15 : 24;        // eye centre line inside the face area
        int max_h = sub ? 24 : 34;
        if (face_kind_ < 0) {
            for (int i = 0; i < 2; i++) {
                lv_obj_add_flag(eye_[i], LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(cover_[i], LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(brow_[i], LV_OBJ_FLAG_HIDDEN);
            }
            lv_obj_align(icon_, LV_ALIGN_TOP_MID, 0, cy - 15);
            return;
        }
        const Face& f = Faces()[face_kind_];
        int dx = f.look_x, dy = f.look_y;
        switch (f.anim) {
            case 1: dy += (phase_ % 2) ? -2 : 1; break;                                   // bounce
            case 2: { static const int lx[4] = {0, 3, 0, -3}; dx += lx[(phase_ / 4) % 4]; break; }  // look around slowly
            case 3: dx += (phase_ % 2) ? 1 : -1; break;                                   // tremble
            default: break;
        }
        bool closed = blink_left_ > 0;
        for (int i = 0; i < 2; i++) {
            int scale = i == 0 ? f.lw_scale : f.rw_scale;
            int w = f.w * scale / 100;
            int h = std::min(max_h, f.h * scale / 100 * (sub ? 85 : 115) / 100);
            bool wink = (f.anim == 4 && i == 1);
            if (closed || wink) h = 3;
            int x = (i == 0 ? 38 : 90) + dx - w / 2;
            int y = cy + dy - h / 2;
            y = std::max(0, std::min(area_h - h, y));
            lv_obj_remove_flag(eye_[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_pos(eye_[i], x, y);
            lv_obj_set_size(eye_[i], w, h);
            lv_obj_set_style_radius(eye_[i], (closed || wink) ? 1 : std::min(f.r, std::min(w, h) / 2), 0);

            // eyelid / smile cover (unlit shape drawn over the eye)
            int cover = (closed || wink) ? 0 : f.cover;
            if (cover == 1) {         // ^ ^ : cover the lower part with a wider unlit ellipse
                lv_obj_set_pos(cover_[i], x - 3, y + h * 45 / 100);
                lv_obj_set_size(cover_[i], w + 6, h);
                lv_obj_set_style_radius(cover_[i], LV_RADIUS_CIRCLE, 0);
            } else if (cover == 2 || cover == 3) {   // flat upper lid
                int lid = cover == 2 ? h / 2 : h * 2 / 3;
                lv_obj_set_pos(cover_[i], x - 1, y - 1);
                lv_obj_set_size(cover_[i], w + 2, lid + 1);
                lv_obj_set_style_radius(cover_[i], 0, 0);
            }
            if (cover) lv_obj_remove_flag(cover_[i], LV_OBJ_FLAG_HIDDEN);
            else lv_obj_add_flag(cover_[i], LV_OBJ_FLAG_HIDDEN);

            // eyebrows
            int brow = f.brow;
            if (brow == 4) brow = (i == 0) ? 3 : 0;
            if (brow == 0 || sub) {   // no room for brows above the eyes while a subtitle is shown
                lv_obj_add_flag(brow_[i], LV_OBJ_FLAG_HIDDEN);
            } else {
                int bx0 = x - 2, bx1 = x + w + 2, by = std::max(1, y - 5);
                int outer_y = by, inner_y = by;
                if (brow == 1) inner_y = by - 3;          // sad: inner end raised
                else if (brow == 2) inner_y = by + 3;     // angry: inner end lowered
                else if (brow == 3) { outer_y = by - 2; inner_y = by - 2; }
                outer_y = std::max(0, outer_y); inner_y = std::max(0, inner_y);
                // left eye: outer = left end; right eye: outer = right end
                brow_pts_[i][0] = {(lv_value_precise_t)bx0, (lv_value_precise_t)(i == 0 ? outer_y : inner_y)};
                brow_pts_[i][1] = {(lv_value_precise_t)bx1, (lv_value_precise_t)(i == 0 ? inner_y : outer_y)};
                lv_line_set_points(brow_[i], brow_pts_[i], 2);
                lv_obj_set_pos(brow_[i], 0, 0);
                lv_obj_remove_flag(brow_[i], LV_OBJ_FLAG_HIDDEN);
            }
        }
        if (f.name[0] == 'c' && strcmp(f.name, "cool") == 0) {
            // sunglasses bridge: reuse the right brow as a line between the lenses
            int y = cy + dy - 1;
            brow_pts_[1][0] = {(lv_value_precise_t)(38 + dx + 13), (lv_value_precise_t)y};
            brow_pts_[1][1] = {(lv_value_precise_t)(90 + dx - 13), (lv_value_precise_t)y};
            lv_line_set_points(brow_[1], brow_pts_[1], 2);
            lv_obj_remove_flag(brow_[1], LV_OBJ_FLAG_HIDDEN);
        }
    }

    lv_obj_t* face_ = nullptr;
    lv_obj_t* eye_[2] = {nullptr, nullptr};
    lv_obj_t* cover_[2] = {nullptr, nullptr};
    lv_obj_t* brow_[2] = {nullptr, nullptr};
    lv_point_precise_t brow_pts_[2][2] = {};
    lv_obj_t* icon_ = nullptr;
    lv_obj_t* subtitle_ = nullptr;
    lv_timer_t* timer_ = nullptr;
    int face_kind_ = 0;
    uint32_t tick_ = 0, next_blink_ = 60, phase_ = 0;
    int blink_left_ = 0;
};
