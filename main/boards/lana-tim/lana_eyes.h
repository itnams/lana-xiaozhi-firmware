// Lana eyes: portable 1-bit renderer for animated robot eyes (no ESP-IDF / LVGL dependency, so the same
// code renders on the robot and in the native preview tool tools/eyes_preview.cc).
//
// Each eye is a filled rounded rectangle shaped by parameters that ease toward per-emotion targets:
// size/radius, upper lid slant (sad = outer corner down, angry = inner corner down), lower "smile" cut
// (happy ^ ^ arcs) and per-eye offsets. On top: random blinks (sometimes double), saccades + idle drift,
// breathing, state motion (listening = bigger + steady, speaking = talk bounce, connecting = scanning) and
// extras (hearts, tears, Zzz, thinking dots, blush, sunglasses glint, kiss heart, volume bar).
#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>

namespace lana_eyes {

enum Emotion {
    kNeutral, kHappy, kLaughing, kFunny, kSad, kAngry, kCrying, kLoving, kEmbarrassed, kSurprised, kShocked,
    kThinking, kWinking, kCool, kRelaxed, kDelicious, kKissy, kConfident, kSleepy, kSilly, kConfused,
    kAlarm,   // Lana extra (not one of the 21 server emotions): ringing alarm / reminder
    kEmotionCount
};

static const char* const kEmotionNames[kEmotionCount] = {
    "neutral", "happy", "laughing", "funny", "sad", "angry", "crying", "loving", "embarrassed", "surprised",
    "shocked", "thinking", "winking", "cool", "relaxed", "delicious", "kissy", "confident", "sleepy", "silly", "confused",
    "alarm"};

inline int EmotionFromName(const char* name) {
    if (!name) return -1;
    if (strcmp(name, "anger") == 0) return kAngry;
    if (strcmp(name, "scare") == 0) return kShocked;
    if (strcmp(name, "staticstate") == 0) return kNeutral;
    for (int i = 0; i < kEmotionCount; i++)
        if (strcmp(kEmotionNames[i], name) == 0) return i;
    return -1;
}

enum State { kStateIdle, kStateListening, kStateSpeaking, kStateConnecting };

struct EyeShape {
    float w, h, r;          // size, corner radius
    float dx, dy;           // offset from the eye's home position
    float lid_out, lid_in;  // upper lid coverage at the outer / inner corner (0..1 of height)
    float smile;            // lower arc cut (0 = none .. 1 = thin ^ arc)
};

struct Face {
    EyeShape l, r;          // l = robot's left eye on screen (left side); lids are mirrored for r
    int anim;               // see Anim
    float gaze_x, gaze_y;   // fixed gaze bias
};

enum Anim { kAnimNone = 0, kAnimBounce = 1, kAnimTremble = 2, kAnimWobble = 4, kAnimHearts = 8, kAnimTears = 16,
            kAnimZzz = 32, kAnimDots = 64, kAnimBlush = 128, kAnimGlasses = 256, kAnimWinkR = 512, kAnimKiss = 1024,
            kAnimNoBlink = 2048, kAnimSlow = 4096, kAnimLookSwap = 8192, kAnimBell = 16384 };

inline const Face& FaceFor(int e) {
    //                  w    h    r   dx  dy  lidO lidI smile
    static const Face faces[kEmotionCount] = {
        /*neutral*/    {{26, 30,  9,  0,  0, 0.00f, 0.00f, 0.00f}, {26, 30,  9, 0, 0, 0.00f, 0.00f, 0.00f}, kAnimNone, 0, 0},
        /*happy*/      {{28, 28, 11,  0, -1, 0.00f, 0.00f, 0.75f}, {28, 28, 11, 0, -1, 0.00f, 0.00f, 0.75f}, kAnimNoBlink, 0, -1},
        /*laughing*/   {{30, 26, 12,  0, -2, 0.00f, 0.00f, 0.95f}, {30, 26, 12, 0, -2, 0.00f, 0.00f, 0.95f}, kAnimBounce | kAnimNoBlink, 0, -1},
        /*funny*/      {{30, 28, 12,  0, -1, 0.00f, 0.00f, 0.85f}, {24, 22, 10, 0, 1, 0.00f, 0.00f, 0.85f}, kAnimWobble | kAnimNoBlink, 0, 0},
        /*sad*/        {{26, 26,  9,  0,  3, 0.55f, 0.05f, 0.00f}, {26, 26,  9, 0, 3, 0.55f, 0.05f, 0.00f}, kAnimSlow, 0, 3},
        /*angry*/      {{28, 24,  6,  0,  1, 0.05f, 0.60f, 0.00f}, {28, 24,  6, 0, 1, 0.05f, 0.60f, 0.00f}, kAnimTremble, 0, 0},
        /*crying*/     {{26, 22,  9,  0, -3, 0.60f, 0.10f, 0.00f}, {26, 22,  9, 0, -3, 0.60f, 0.10f, 0.00f}, kAnimTears | kAnimSlow, 0, -2},
        /*loving*/     {{30, 28, 10,  0,  0, 0.00f, 0.00f, 0.00f}, {30, 28, 10, 0, 0, 0.00f, 0.00f, 0.00f}, kAnimHearts | kAnimNoBlink, 0, 0},
        /*embarrassed*/{{22, 22,  9,  0,  0, 0.25f, 0.25f, 0.30f}, {22, 22,  9, 0, 0, 0.25f, 0.25f, 0.30f}, kAnimBlush, 0, 1},
        /*surprised*/  {{32, 36, 16,  0, -1, 0.00f, 0.00f, 0.00f}, {32, 36, 16, 0, -1, 0.00f, 0.00f, 0.00f}, kAnimNone, 0, -1},
        /*shocked*/    {{22, 36, 11,  0, -1, 0.00f, 0.00f, 0.00f}, {22, 36, 11, 0, -1, 0.00f, 0.00f, 0.00f}, kAnimTremble | kAnimNoBlink, 0, -1},
        /*thinking*/   {{24, 26,  9,  0,  0, 0.30f, 0.30f, 0.00f}, {24, 20,  8, 0, 1, 0.45f, 0.20f, 0.00f}, kAnimDots, -9, -8},
        /*winking*/    {{28, 28, 11,  0, -1, 0.00f, 0.00f, 0.70f}, {28, 28, 11, 0, -1, 0.00f, 0.00f, 0.70f}, kAnimWinkR | kAnimNoBlink, 0, 0},
        /*cool*/       {{36, 14,  3,  0,  0, 0.00f, 0.00f, 0.00f}, {36, 14,  3, 0, 0, 0.00f, 0.00f, 0.00f}, kAnimGlasses | kAnimNoBlink, 0, 0},
        /*relaxed*/    {{28, 26, 11,  0,  2, 0.50f, 0.50f, 0.30f}, {28, 26, 11, 0, 2, 0.50f, 0.50f, 0.30f}, kAnimSlow | kAnimNoBlink, 0, 1},
        /*delicious*/  {{28, 28, 11,  0, -1, 0.00f, 0.00f, 0.85f}, {28, 28, 11, 0, -1, 0.00f, 0.00f, 0.85f}, kAnimBounce | kAnimNoBlink, 0, 0},
        /*kissy*/      {{28, 28, 11,  0,  0, 0.00f, 0.00f, 0.60f}, {28, 28, 11, 0, 0, 0.00f, 0.00f, 0.60f}, kAnimWinkR | kAnimKiss | kAnimNoBlink, 0, 0},
        /*confident*/  {{28, 26,  8,  0,  0, 0.38f, 0.38f, 0.15f}, {28, 26,  8, 0, 0, 0.50f, 0.42f, 0.15f}, kAnimNone, 2, 0},
        /*sleepy*/     {{28, 26, 10,  0,  4, 0.68f, 0.68f, 0.00f}, {28, 26, 10, 0, 4, 0.72f, 0.68f, 0.00f}, kAnimZzz | kAnimSlow | kAnimNoBlink, 0, 2},
        /*silly*/      {{32, 34, 15,  0, -1, 0.00f, 0.00f, 0.00f}, {20, 20,  9, 0, 3, 0.00f, 0.00f, 0.00f}, kAnimWobble, 0, 0},
        /*confused*/   {{24, 30,  9,  0, -1, 0.00f, 0.00f, 0.00f}, {26, 20,  8, 0, 3, 0.10f, 0.40f, 0.00f}, kAnimLookSwap, 4, 0},
        /*alarm*/      {{26, 26, 13,  0,  3, 0.00f, 0.00f, 0.00f}, {26, 26, 13, 0, 3, 0.00f, 0.00f, 0.00f}, kAnimTremble | kAnimNoBlink | kAnimBell, 0, 2},
    };
    if (e < 0 || e >= kEmotionCount) e = kNeutral;
    return faces[e];
}

class Renderer {
public:
    static constexpr int W = 128;
    static constexpr int H = 64;        // full 128x64 panel; the UI composer reserves strips via SetReservedBottom

    explicit Renderer(uint32_t seed = 12345) : rng_(seed ? seed : 1) {
        cur_[0] = cur_[1] = FaceFor(kNeutral).l;
        next_blink_ms_ = 1500;
        next_saccade_ms_ = 800;
    }

    void SetEmotion(int e) {
        if (e < 0 || e >= kEmotionCount) e = kNeutral;
        if (e != emotion_) { emotion_ = e; emotion_ms_ = 0; }
    }
    int emotion() const { return emotion_; }
    void SetState(State s) { if (s != state_) { state_ = s; state_ms_ = 0; } }
    // Leave room at the bottom for a subtitle line (eyes squeeze into the top part)
    void SetReservedBottom(int px) { reserved_bottom_ = px < 0 ? 0 : (px > 40 ? 40 : px); }
    void SetDrawBell(bool on) { draw_bell_ = on; }
    void ShowVolume(int volume, int duration_ms = 1500) { volume_ = volume; volume_ms_ = duration_ms; }

    // Advance time by dt milliseconds
    void Step(int dt) {
        t_ += dt; emotion_ms_ += dt; state_ms_ += dt;
        if (volume_ms_ > 0) volume_ms_ -= dt;
        const Face& f = FaceFor(emotion_);
        float k = 1.0f - std::exp(-dt / 70.0f);          // shape easing (~70 ms time constant)
        float kg = 1.0f - std::exp(-dt / 45.0f);         // gaze easing (fast saccades)

        // --- blink ---
        if (blink_ms_ > 0) {
            blink_ms_ -= dt;
            if (blink_ms_ <= 0) {
                if (double_blink_) { double_blink_ = false; blink_ms_ = -90; }   // short gap, then blink again
                else blink_ms_ = 0;
            }
        } else if (blink_ms_ < 0) {
            blink_ms_ += dt;
            if (blink_ms_ >= 0) blink_ms_ = kBlinkMs;
        } else if (!(f.anim & kAnimNoBlink) && t_ >= next_blink_ms_) {
            blink_ms_ = kBlinkMs;
            double_blink_ = Rand(100) < 18;
            next_blink_ms_ = t_ + 1800 + Rand(f.anim & kAnimSlow ? 5200 : 3800);
        }

        // --- gaze: saccades + slow drift ---
        bool steady = state_ == kStateListening;
        if (t_ >= next_saccade_ms_) {
            float range_x = steady ? 3 : 9, range_y = steady ? 2 : 4;
            if (state_ == kStateSpeaking) { range_x = 5; range_y = 2; }
            sacc_x_ = (Rand(1000) / 500.0f - 1.0f) * range_x;
            sacc_y_ = (Rand(1000) / 500.0f - 1.0f) * range_y;
            if (Rand(100) < 35) { sacc_x_ = 0; sacc_y_ = 0; }   // come back to centre often
            next_saccade_ms_ = t_ + (steady ? 1600 : 700) + Rand(steady ? 2200 : 2600);
        }
        float tx = f.gaze_x + sacc_x_, ty = f.gaze_y + sacc_y_;
        if (f.anim & kAnimLookSwap) tx = ((t_ / 1400) % 2 ? 1 : -1) * 6.0f;
        if (state_ == kStateConnecting) { tx = 10.0f * std::sin(t_ / 650.0f); ty = -1; }
        if (f.anim & kAnimDots) { tx = f.gaze_x + 1.5f * std::sin(t_ / 900.0f); ty = f.gaze_y; }
        gaze_x_ += (tx - gaze_x_) * kg;
        gaze_y_ += (ty - gaze_y_) * kg;

        // --- shape targets ---
        float scale = 1.0f;
        if (state_ == kStateListening) scale = 1.10f;
        else if (state_ == kStateConnecting) scale = 0.85f;
        const EyeShape* tg[2] = {&f.l, &f.r};
        for (int i = 0; i < 2; i++) {
            EyeShape t = *tg[i];
            t.w *= scale; t.h *= scale; t.r *= scale;
            if (state_ == kStateListening) { t.lid_out *= 0.4f; t.lid_in *= 0.4f; }
            cur_[i].w += (t.w - cur_[i].w) * k;
            cur_[i].h += (t.h - cur_[i].h) * k;
            cur_[i].r += (t.r - cur_[i].r) * k;
            cur_[i].dx += (t.dx - cur_[i].dx) * k;
            cur_[i].dy += (t.dy - cur_[i].dy) * k;
            cur_[i].lid_out += (t.lid_out - cur_[i].lid_out) * k;
            cur_[i].lid_in += (t.lid_in - cur_[i].lid_in) * k;
            cur_[i].smile += (t.smile - cur_[i].smile) * k;
        }

        // --- speaking: syllable-like bounce envelope ---
        if (state_ == kStateSpeaking) {
            syll_ms_ -= dt;
            if (syll_ms_ <= 0) { syll_ms_ = 110 + Rand(170); syll_amp_ = 0.6f + Rand(100) / 70.0f; }
        } else {
            syll_amp_ *= 0.85f;
        }
        talk_phase_ += dt * 0.028f;
    }

    // Render into a 1-byte-per-pixel buffer (W*H): 1 = lit, 0 = off
    void Render(uint8_t* px) const {
        memset(px, 0, W * H);
        const Face& f = FaceFor(emotion_);
        int area_h = H - reserved_bottom_;
        // 2.2.4: eyes grow to fill the free area (full 64 rows -> ~1.3x the 2.2.3 size), shrink with strips
        float vscale = area_h / 46.0f; if (vscale > 1.32f) vscale = 1.32f; if (vscale < 0.6f) vscale = 0.6f;
        float hscale = vscale > 1.0f ? 1.0f + (vscale - 1.0f) * 0.75f : 1.0f;
        float sep = 30.0f + (vscale > 1.0f ? (vscale - 1.0f) * 12.0f : 0.0f);
        float cy = area_h * 0.5f;
        float t = t_ / 1000.0f;

        float bob = 0, shake = 0;
        if (f.anim & kAnimBounce) bob += 2.0f * std::sin(t * 2 * 3.14159f * 3.0f);
        if (f.anim & kAnimTremble) shake = (((t_ / 45) % 2) ? 0.9f : -0.9f);
        bob += 0.6f * std::sin(t * 2 * 3.14159f * (f.anim & kAnimSlow ? 0.25f : 0.4f));   // breathing
        if (state_ == kStateSpeaking || syll_amp_ > 0.05f) bob -= syll_amp_ * std::fabs(std::sin(talk_phase_));

        float blink = BlinkFactor();
        for (int i = 0; i < 2; i++) {
            EyeShape e = cur_[i];
            float wob = (f.anim & kAnimWobble) ? 1.5f * std::sin(t * 6.0f + i * 3.14159f) : 0;
            float ex = (i == 0 ? 64 - sep : 64 + sep) + e.dx + gaze_x_ + shake;
            float ey = cy + (e.dy + gaze_y_ + bob + wob) * vscale;
            float h = e.h * vscale;
            float w = e.w * hscale;
            bool wink = (f.anim & kAnimWinkR) && i == 1;
            if (f.anim & kAnimHearts) {
                float s = 1.0f + 0.12f * std::sin(t * 2 * 3.14159f * 1.6f);
                DrawHeart(px, ex, ey, 15.0f * s * (vscale < 0.8f ? 0.8f : vscale > 1.15f ? 1.15f : vscale), area_h);
                continue;
            }
            if (wink) { DrawArc(px, ex, ey + 2, w * 0.5f, 5, area_h); continue; }
            float hh = h * blink;
            if (hh < 2.5f) { DrawHLine(px, ex - w / 2 + 2, ex + w / 2 - 2, ey, area_h); DrawHLine(px, ex - w / 2 + 3, ex + w / 2 - 3, ey + 1, area_h); continue; }
            DrawEye(px, ex, ey, w, hh, e.r * vscale * (hh < h ? hh / h : 1.0f), i == 0 ? e.lid_out : e.lid_in,
                    i == 0 ? e.lid_in : e.lid_out, e.smile, area_h);
            if (f.anim & kAnimGlasses) {
                if (i == 0) for (int x = (int)(ex + w / 2); x <= (int)(64 + sep - w / 2 + gaze_x_); x++) { Set(px, x, (int)(ey - h / 2 + 2), area_h); Set(px, x, (int)(ey - h / 2 + 3), area_h); }
                int g = (int)(t_ / 30) % 90 - 20;   // sweeping glint
                for (int d = 0; d < 3; d++)
                    for (int y = 0; y < (int)h; y++) Clear(px, (int)(ex - w / 2 + g + d - y / 2), (int)(ey - h / 2 + y), area_h);
            }
            if (f.anim & kAnimTears) {
                float phase = std::fmod(t * 0.8f + i * 0.45f, 1.0f);
                float tx = ex + (i == 0 ? -w * 0.30f : w * 0.30f);
                float ty = ey + h * 0.35f + phase * (area_h - (ey + h * 0.35f));
                DrawTear(px, tx, ty, area_h);
            }
            if (f.anim & kAnimBlush) {
                int by = (int)(ey + h / 2 + 4);
                for (int k = 0; k < 3; k++) {
                    int bx = (int)(ex - 7 + k * 6);
                    for (int d = 0; d < 4; d++) Set(px, bx + d, by + 3 - d, area_h);
                }
            }
        }
        if (f.anim & kAnimZzz) DrawZzz(px, area_h);
        if ((f.anim & kAnimBell) && draw_bell_) DrawBell(px, 64 + ((((t_ / 90) % 2) ? 2 : -2)), 9, (t_ / 180) % 2 == 0, area_h);
        if (f.anim & kAnimDots) {
            int n = (int)(t_ / 450) % 4;
            for (int k = 0; k < n; k++) FillCircle(px, 100 + k * 7, 8 - k * 1.5f, 1.6f + k * 0.4f, area_h);
        }
        if (f.anim & kAnimKiss) {
            float ph = std::fmod(t * 0.6f, 1.0f);
            DrawHeart(px, 98 + 8 * ph, area_h - 8 - ph * (area_h - 14), 5.5f, area_h);
        }
        if (volume_ms_ > 0) DrawVolume(px, area_h);
    }

    // Idle clock: big HH:MM on the left (rows 0..clock_h), a small sleeping face with drifting Zzz on the right.
    // Called at ~4 fps by the display task; t_ (advanced by Step) drives the slow breathing / Zzz animation.
    void RenderClock(uint8_t* px, int hh, int mm, int ss, int area_h) const {
        memset(px, 0, W * H);
        const int dh = 26, dw = 15, th = 3, y0 = 2;
        int x = 3;
        auto digit = [&](int d) { DrawDigit(px, x, y0, dw, dh, th, d, area_h); x += dw + 4; };
        digit(hh / 10); digit(hh % 10);
        if (ss % 2 == 0) {                                    // blinking colon
            FillRect(px, x, y0 + 7, 3, 3, area_h); FillRect(px, x, y0 + dh - 10, 3, 3, area_h);
        }
        x += 7;
        digit(mm / 10); digit(mm % 10);
        // sleeping face: closed eyes that slowly 'breathe' (rise and fall)
        float br = std::sin(t_ / 1000.0f * 2 * 3.14159f / 4.0f);   // 4 s breath
        float ey = 21 + br * 1.2f;
        DrawSleepEye(px, 100, ey, 6, area_h);
        DrawSleepEye(px, 119, ey, 6, area_h);
        // three z's drifting up and growing, one after the other
        for (int k = 0; k < 3; k++) {
            float ph = std::fmod(t_ / 3600.0f + k / 3.0f, 1.0f);
            int sz = 2 + (int)(ph * 4);
            int zx = 106 + (int)(ph * 12), zy = (int)(13 - ph * 12);
            if (zy < 0) continue;
            for (int i = 0; i <= sz; i++) { Set(px, zx + i, zy, area_h); Set(px, zx + i, zy + sz, area_h); Set(px, zx + sz - i, zy + i, area_h); }
        }
    }

    // Pack to the SSD1306-style 1bpp, row-major MSB-first (for previews / I1 images)
    static void Pack1bpp(const uint8_t* px, uint8_t* out) {
        for (int y = 0; y < H; y++)
            for (int xb = 0; xb < W / 8; xb++) {
                uint8_t b = 0;
                for (int k = 0; k < 8; k++) if (px[y * W + xb * 8 + k]) b |= 0x80 >> k;
                out[y * (W / 8) + xb] = b;
            }
    }

private:
    static constexpr int kBlinkMs = 140;
    uint32_t rng_;
    int emotion_ = kNeutral;
    State state_ = kStateIdle;
    uint32_t t_ = 0, emotion_ms_ = 0, state_ms_ = 0, next_blink_ms_ = 0, next_saccade_ms_ = 0;
    int blink_ms_ = 0;
    bool double_blink_ = false;
    float gaze_x_ = 0, gaze_y_ = 0, sacc_x_ = 0, sacc_y_ = 0;
    float syll_amp_ = 0, talk_phase_ = 0;
    int syll_ms_ = 0;
    int reserved_bottom_ = 0;
    bool draw_bell_ = true;
    int volume_ = 0, volume_ms_ = 0;
    EyeShape cur_[2];

    uint32_t Rand(uint32_t n) { rng_ ^= rng_ << 13; rng_ ^= rng_ >> 17; rng_ ^= rng_ << 5; return n ? rng_ % n : 0; }

    float BlinkFactor() const {
        if (blink_ms_ <= 0) return 1.0f;
        float p = 1.0f - blink_ms_ / (float)kBlinkMs;       // 0 -> 1 over the blink
        float c = p < 0.5f ? p * 2 : (1.0f - p) * 2;         // close then open
        return 1.0f - c * 0.95f;
    }

    static void Set(uint8_t* px, int x, int y, int area_h) { if (x >= 0 && x < W && y >= 0 && y < area_h) px[y * W + x] = 1; }
    static void Clear(uint8_t* px, int x, int y, int area_h) { if (x >= 0 && x < W && y >= 0 && y < area_h) px[y * W + x] = 0; }
    static void DrawHLine(uint8_t* px, float x0, float x1, float y, int area_h) { for (int x = (int)x0; x <= (int)x1; x++) Set(px, x, (int)y, area_h); }

    static void FillCircle(uint8_t* px, float cx, float cy, float r, int area_h) {
        for (int y = (int)(cy - r - 1); y <= (int)(cy + r + 1); y++)
            for (int x = (int)(cx - r - 1); x <= (int)(cx + r + 1); x++) {
                float dx = x + 0.5f - cx, dy = y + 0.5f - cy;
                if (dx * dx + dy * dy <= r * r) Set(px, x, y, area_h);
            }
    }

    // Rounded rect, minus the upper lid (line from outer to inner corner), minus the smile ellipse
    static void DrawEye(uint8_t* px, float cx, float cy, float w, float h, float r, float lid_left, float lid_right,
                        float smile, int area_h) {
        float x0 = cx - w / 2, x1 = cx + w / 2, y0 = cy - h / 2, y1 = cy + h / 2;
        if (r > w / 2) r = w / 2;
        if (r > h / 2) r = h / 2;
        float sy_c = cy + h * 0.62f, srx = w * 0.70f, sry = h * 0.62f * smile;
        for (int y = (int)std::floor(y0); y <= (int)std::ceil(y1); y++) {
            for (int x = (int)std::floor(x0); x <= (int)std::ceil(x1); x++) {
                float fx = x + 0.5f, fy = y + 0.5f;
                if (fx < x0 || fx > x1 || fy < y0 || fy > y1) continue;
                float qx = fx < x0 + r ? x0 + r - fx : (fx > x1 - r ? fx - (x1 - r) : 0);
                float qy = fy < y0 + r ? y0 + r - fy : (fy > y1 - r ? fy - (y1 - r) : 0);
                if (qx * qx + qy * qy > r * r) continue;
                float u = (fx - x0) / w;                               // 0 at left .. 1 at right
                float lid = (lid_left * (1 - u) + lid_right * u) * h;  // lid depth at this column
                if (fy < y0 + lid) continue;
                if (smile > 0.01f) {
                    float ex = (fx - cx) / srx, ey = (fy - sy_c) / (sry > 0.5f ? sry : 0.5f);
                    if (ex * ex + ey * ey < 1.0f) continue;
                }
                Set(px, x, y, area_h);
            }
        }
    }

    // Closed eye: a thick ^ arc
    static void DrawArc(uint8_t* px, float cx, float cy, float half_w, float rise, int area_h) {
        for (int x = (int)(cx - half_w); x <= (int)(cx + half_w); x++) {
            float u = (x - cx) / half_w;
            float y = cy - rise * (1 - u * u);
            Set(px, x, (int)y, area_h); Set(px, x, (int)y + 1, area_h); Set(px, x, (int)y + 2, area_h);
        }
    }

    static void DrawHeart(uint8_t* px, float cx, float cy, float s, int area_h) {
        for (int y = (int)(cy - s); y <= (int)(cy + s); y++)
            for (int x = (int)(cx - s * 1.2f); x <= (int)(cx + s * 1.2f); x++) {
                float u = (x + 0.5f - cx) / s * 1.15f, v = -(y + 0.5f - cy) / s * 1.15f + 0.25f;
                float a = u * u + v * v - 1;
                if (a * a * a - u * u * v * v * v <= 0) Set(px, x, y, area_h);
            }
    }

    static void DrawTear(uint8_t* px, float cx, float cy, int area_h) {
        FillCircle(px, cx, cy + 1.5f, 2.2f, area_h);
        Set(px, (int)cx, (int)(cy - 2), area_h); Set(px, (int)cx, (int)(cy - 1), area_h);
        Set(px, (int)cx - 1, (int)(cy - 0), area_h); Set(px, (int)cx + 1, (int)(cy - 0), area_h);
    }

    void DrawZzz(uint8_t* px, int area_h) const {
        for (int k = 0; k < 3; k++) {
            float ph = std::fmod(t_ / 2400.0f + k / 3.0f, 1.0f);
            int s = 3 + (int)(ph * 4);
            int zx = 104 + (int)(ph * 14) + k, zy = (int)(area_h - 10 - ph * (area_h - 6));
            for (int i = 0; i <= s; i++) { Set(px, zx + i, zy, area_h); Set(px, zx + i, zy + s, area_h); Set(px, zx + s - i, zy + i, area_h); }
        }
    }

    static void FillRect(uint8_t* px, int x, int y, int w, int h, int area_h) {
        for (int j = y; j < y + h; j++) for (int i = x; i < x + w; i++) Set(px, i, j, area_h);
    }

    // 7-segment digit with rounded (chamfered) segment ends
    static void DrawDigit(uint8_t* px, int x, int y, int w, int h, int t, int d, int area_h) {
        static const uint8_t seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // gfedcba
        uint8_t m = seg[d < 0 || d > 9 ? 8 : d];
        int hm = h / 2;
        auto hseg = [&](int yy) { FillRect(px, x + 1, yy, w - 2, t, area_h); Clear(px, x + 1, yy, area_h); Clear(px, x + w - 2, yy, area_h);
                                  Clear(px, x + 1, yy + t - 1, area_h); Clear(px, x + w - 2, yy + t - 1, area_h); };
        auto vseg = [&](int xx, int ya, int yb) { FillRect(px, xx, ya + 1, t, yb - ya - 1, area_h); };
        if (m & 0x01) hseg(y);
        if (m & 0x40) hseg(y + hm - t / 2);
        if (m & 0x08) hseg(y + h - t);
        if (m & 0x20) vseg(x, y + 1, y + hm);            // f
        if (m & 0x02) vseg(x + w - t, y + 1, y + hm);    // b
        if (m & 0x10) vseg(x, y + hm, y + h - 1);        // e
        if (m & 0x04) vseg(x + w - t, y + hm, y + h - 1);// c
    }

    // Closed sleeping eye: a gentle u-shaped lash line
    static void DrawSleepEye(uint8_t* px, float cx, float cy, float half_w, int area_h) {
        for (int x = (int)(cx - half_w); x <= (int)(cx + half_w); x++) {
            float u = (x - cx) / half_w;
            float y = cy + 2.5f * (1 - u * u);
            Set(px, x, (int)y, area_h); Set(px, x, (int)y + 1, area_h);
        }
    }

    // Alarm bell with ringing marks
    static void DrawBell(uint8_t* px, int cx, int cy, bool ring, int area_h) {
        for (int y = -6; y <= 4; y++) {
            float hw = y < -3 ? 2.0f + (y + 6) * 0.6f : 3.8f + (y + 3) * 0.45f;
            for (int x = (int)(-hw); x <= (int)hw; x++) Set(px, cx + x, cy + y, area_h);
        }
        FillRect(px, cx - 7, cy + 5, 15, 1, area_h);
        FillCircle(px, cx, cy + 7.5f, 1.6f, area_h);
        Set(px, cx, cy - 7, area_h);
        if (ring) for (int k = 0; k < 3; k++) { Set(px, cx - 9 - k, cy - 3 + k * 3, area_h); Set(px, cx + 9 + k, cy - 3 + k * 3, area_h); }
    }

    void DrawVolume(uint8_t* px, int area_h) const {
        int x0 = 14, x1 = 114, y0 = area_h - 9, y1 = area_h - 3;
        for (int y = y0 - 1; y <= y1 + 1; y++) for (int x = x0 - 2; x <= x1 + 2; x++) Clear(px, x, y, area_h);
        for (int x = x0; x <= x1; x++) { Set(px, x, y0, area_h); Set(px, x, y1, area_h); }
        for (int y = y0; y <= y1; y++) { Set(px, x0, y, area_h); Set(px, x1, y, area_h); }
        int fill = x0 + 2 + (x1 - x0 - 4) * (volume_ < 0 ? 0 : volume_ > 100 ? 100 : volume_) / 100;
        for (int y = y0 + 2; y <= y1 - 2; y++) for (int x = x0 + 2; x < fill; x++) Set(px, x, y, area_h);
    }
};

}  // namespace lana_eyes
