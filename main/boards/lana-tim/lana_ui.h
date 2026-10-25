// Lana 2.2.4 UI for the 0.96" SSD1306 128x64 monochrome OLED: one full-screen 1-bit frame composed in plain C++
// (no LVGL), so the robot and tools/eyes_preview.cc render identical pixels.
//
// Screens (high contrast, black background, nothing drawn that does not carry information):
//   face   : eyes fill all 64 rows when idle; a 12 px status strip (icon + short Vietnamese text + Wi-Fi bars) appears
//            only while listening / speaking / connecting or for a notification; subtitle = 13 px scrolling line.
//   clock  : idle standby -> big 7-segment HH:MM (38 px) + short date "T7 · 25/10"; 1 px burn-in drift each minute.
//   alarm  : flashing inverted header (bell, "Báo thức", HH:MM) + trembling alarm eyes + reminder text.
//   wifi   : setup steps with the hotspot SSID and portal address (192.168.4.1) in bold.
#pragma once
#include "lana_eyes.h"
#include "lana_font_vi.h"
#include <cstdint>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <string>

namespace lana_ui {

static constexpr int W = 128, H = 64;
static constexpr int kStripH = 13, kSubH = 13;

enum Screen { kScreenFace, kScreenClock, kScreenAlarm, kScreenWifiSetup, kScreenIcon };

struct Model {
    Screen screen = kScreenFace;
    lana_eyes::State state = lana_eyes::kStateIdle;
    std::string status;        // strip text ("" = no strip unless state needs one)
    std::string subtitle;      // bottom line ("" = none)
    std::string ssid, url;     // wifi setup
    int hh = 0, mm = 0, ss = 0, wday = 0, mday = 1, mon = 1;
    int rssi = 0;              // dBm, 0 = unknown / not connected
    int battery = -1;          // %, -1 = no battery sense (indicator hidden)
    bool charging = false;
    int temp = 0;              // °C, shown on the clock when wx > 0
    int wx = 0;                // 0 none, 1 sun, 2 partly cloudy, 3 cloud, 4 rain, 5 storm
};

// ---- text ------------------------------------------------------------------------------------------------------
inline uint32_t NextCp(const char*& p) {
    uint8_t c = (uint8_t)*p;
    if (!c) return 0;
    uint32_t cp; int n;
    if (c < 0x80) { cp = c; n = 0; } else if ((c >> 5) == 6) { cp = c & 0x1F; n = 1; }
    else if ((c >> 4) == 14) { cp = c & 0x0F; n = 2; } else if ((c >> 3) == 30) { cp = c & 0x07; n = 3; } else { p++; return '?'; }
    p++;
    while (n-- > 0 && ((uint8_t)*p >> 6) == 2) cp = (cp << 6) | ((uint8_t)*p++ & 0x3F);
    return cp;
}

inline const lana_font::Glyph* FindGlyph(uint32_t cp) {
    int lo = 0, hi = lana_font::kGlyphCount - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        uint32_t c = lana_font::kGlyphs[mid].cp;
        if (c == cp) return &lana_font::kGlyphs[mid];
        if (c < cp) lo = mid + 1; else hi = mid - 1;
    }
    return nullptr;
}

inline const lana_font::Glyph* GlyphOrFallback(uint32_t cp) {
    const lana_font::Glyph* g = FindGlyph(cp);
    if (!g && cp == 0x2026) g = FindGlyph('.');
    return g ? g : FindGlyph('?');
}

inline int TextWidth(const std::string& s, bool bold = false) {
    int w = 0;
    for (const char* p = s.c_str(); *p;) { auto g = GlyphOrFallback(NextCp(p)); if (g) w += g->adv + (bold ? 1 : 0); }
    return w > 0 ? w - 1 : 0;
}

class Canvas {
public:
    explicit Canvas(uint8_t* px) : px_(px) {}
    void Clear() { memset(px_, 0, W * H); }
    void Set(int x, int y, uint8_t v = 1) { if (x >= 0 && x < W && y >= clip0_ && y < clip1_) px_[y * W + x] = v; }
    void Fill(int x, int y, int w, int h, uint8_t v = 1) { for (int j = y; j < y + h; j++) for (int i = x; i < x + w; i++) Set(i, j, v); }
    void HLine(int x0, int x1, int y, uint8_t v = 1) { for (int x = x0; x <= x1; x++) Set(x, y, v); }
    void Invert(int x, int y, int w, int h) { for (int j = y; j < y + h; j++) for (int i = x; i < x + w; i++) if (i >= 0 && i < W && j >= 0 && j < H) px_[j * W + i] ^= 1; }
    void SetClip(int y0, int y1) { clip0_ = y0; clip1_ = y1; }
    void ResetClip() { clip0_ = 0; clip1_ = H; }
    // draws the 13 px cell with its top at y; returns the pen x after the text
    int Text(int x, int y, const std::string& s, bool bold = false, uint8_t v = 1) {
        for (const char* p = s.c_str(); *p;) {
            const lana_font::Glyph* g = GlyphOrFallback(NextCp(p));
            if (!g) continue;
            for (int r = 0; r < lana_font::kCellH; r++)
                for (int k = 0; k < g->w; k++)
                    if (g->rows[r] >> (15 - k) & 1) { Set(x + g->x0 + k, y + r, v); if (bold) Set(x + g->x0 + k + 1, y + r, v); }
            x += g->adv + (bold ? 1 : 0);
        }
        return x;
    }
    int TextCentered(int y, const std::string& s, bool bold = false) { int w = TextWidth(s, bold); return Text((W - w) / 2, y, s, bold); }
    uint8_t* px() { return px_; }
private:
    uint8_t* px_;
    int clip0_ = 0, clip1_ = H;
};

// ---- icons (pixel art, 9 px tall) --------------------------------------------------------------------------------
inline void Art(Canvas& c, int x, int y, const char* const* rows, int n, uint8_t v = 1) {
    for (int j = 0; j < n; j++) for (int i = 0; rows[j][i]; i++) if (rows[j][i] == 'X') c.Set(x + i, y + j, v);
}
inline void IconMic(Canvas& c, int x, int y) {
    static const char* const a[] = {"..XXX..", "..XXX..", "..XXX..", "X.XXX.X", "X.XXX.X", ".X...X.", "..XXX..", "...X...", ".XXXXX."};
    Art(c, x, y, a, 9);
}
inline void IconSpeaker(Canvas& c, int x, int y, int phase) {
    static const char* const a[] = {"...X", "..XX", "XXXX", "XXXX", "XXXX", "XXXX", "XXXX", "..XX", "...X"};
    Art(c, x, y, a, 9);
    for (int k = 0; k < 2; k++) {   // sound waves, animated
        if (((phase + k) & 3) == 3) continue;
        int r = 3 + k * 3;
        for (int j = -r + 1; j <= r - 1; j++) c.Set(x + 4 + r - (j * j) / (2 * r) - 1, y + 4 + j);
    }
}
inline void IconWifi(Canvas& c, int x, int y, int bars) {   // 4 rising bars, unlit bars as dots
    for (int b = 0; b < 4; b++) {
        int h = 2 + b * 2, bx = x + b * 3;
        if (b < bars) c.Fill(bx, y + 8 - h, 2, h); else c.Set(bx, y + 7), c.Set(bx + 1, y + 7);
    }
}
inline void IconBell(Canvas& c, int x, int y, uint8_t v = 1) {
    static const char* const a[] = {"....X....", "..XXXXX..", ".XXXXXXX.", ".XXXXXXX.", ".XXXXXXX.", "XXXXXXXXX", "XXXXXXXXX", "....X....", "...XXX..."};
    Art(c, x, y, a, 9, v);
}
inline void IconSpinner(Canvas& c, int x, int y, int phase) {   // three bouncing dots
    for (int k = 0; k < 3; k++) c.Fill(x + k * 4, y + (phase % 3 == k ? 3 : 5), 3, 3);
}
// 11x7 battery outline + fill; charging = bolt cut-out; returns width drawn
inline int IconBattery(Canvas& c, int x, int y, int pct, bool charging) {
    c.HLine(x, x + 9, y); c.HLine(x, x + 9, y + 6);
    for (int j = y; j <= y + 6; j++) { c.Set(x, j); c.Set(x + 9, j); }
    c.Fill(x + 10, y + 2, 1, 3);
    int f = (pct * 8 + 50) / 100; if (pct > 0 && f == 0) f = 1;
    c.Fill(x + 1, y + 1, f, 5);
    if (charging) { c.Set(x + 5, y + 1, 0); c.Set(x + 4, y + 2, 0); c.Fill(x + 3, y + 3, 4, 1, 0); c.Set(x + 5, y + 4, 0); c.Set(x + 4, y + 5, 0);
                    c.Set(x + 5, y + 1, 1 - (f > 4)); }
    return 11;
}
// 11x9 weather icons for the clock screen
inline void IconWeather(Canvas& c, int x, int y, int wx) {
    static const char* const sun[] = {"X....X....X", ".X.......X.", "....XXX....", "...XXXXX...", "XX.XXXXX.XX", "...XXXXX...", "....XXX....", ".X.......X.", "X....X....X"};
    static const char* const partly[] = {"......X..X.", "........XX.", ".......XXXX", "...XXX.XXX.", ".XX...XXX..", "X.......X..", "X........X.", ".X.......X.", "..XXXXXXX.."};
    static const char* const cloud[] = {"...........", "....XXX....", "...X...X...", ".XX.....XX.", "X.........X", "X.........X", "X.........X", ".XXXXXXXXX.", "..........."};
    static const char* const rain[] = {"....XXX....", "..XX...XX..", ".X.......X.", "X.........X", ".XXXXXXXXX.", "...........", ".X..X..X...", "X..X..X....", "..........."};
    static const char* const storm[] = {"....XXX....", "..XX...XX..", ".X.......X.", "X.........X", ".XXXX.XXXX.", ".....X.....", "....XXX....", "......X....", ".....X....."};
    const char* const* a = wx == 1 ? sun : wx == 2 ? partly : wx == 3 ? cloud : wx == 4 ? rain : storm;
    Art(c, x, y, a, 9);
}
inline bool BatteryLow(const Model& m) { return m.battery >= 0 && m.battery < 15 && !m.charging; }

inline int RssiBars(int rssi) { return rssi == 0 ? 0 : rssi >= -55 ? 4 : rssi >= -65 ? 3 : rssi >= -75 ? 2 : 1; }

// ---- 7-segment digits with chamfered ends (clock) ----------------------------------------------------------------
inline void Digit(Canvas& c, int x, int y, int w, int h, int t, int d) {
    static const uint8_t seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    uint8_t m = seg[d < 0 || d > 9 ? 8 : d];
    int hm = h / 2;
    auto hs = [&](int yy) { for (int j = 0; j < t; j++) { int in = j < t / 2 ? t / 2 - j : j - t / 2; c.HLine(x + 1 + in, x + w - 2 - in, yy + j); } };
    auto vs = [&](int xx, int ya, int yb) { for (int i = 0; i < t; i++) { int in = i < t / 2 ? t / 2 - i : i - t / 2; for (int yy = ya + 1 + in; yy <= yb - 1 - in; yy++) c.Set(xx + i, yy); } };
    if (m & 0x01) hs(y);
    if (m & 0x40) hs(y + hm - t / 2);
    if (m & 0x08) hs(y + h - t);
    if (m & 0x20) vs(x, y + 1, y + hm + 1);
    if (m & 0x02) vs(x + w - t, y + 1, y + hm + 1);
    if (m & 0x10) vs(x, y + hm - 1, y + h - 1);
    if (m & 0x04) vs(x + w - t, y + hm - 1, y + h - 1);
}

inline std::string ShortDate(int wday, int mday, int mon) {
    static const char* const kD[7] = {"CN", "T2", "T3", "T4", "T5", "T6", "T7"};
    char b[24]; snprintf(b, sizeof(b), "%s · %02d/%02d", kD[wday % 7], mday, mon);
    return b;
}

// ---- composer ----------------------------------------------------------------------------------------------------
class Ui {
public:
    explicit Ui(uint32_t seed = 1) : eyes_(seed) {}
    lana_eyes::Renderer& eyes() { return eyes_; }
    void Step(int dt) { t_ += dt; eyes_.Step(dt); if (scroll_hold_ > 0) scroll_hold_ -= dt; else scroll_px_ += dt * 0.035f; }
    void ResetScroll() { scroll_px_ = 0; scroll_hold_ = 900; }

    // px: W*H bytes, 1 = lit
    void Render(const Model& m, uint8_t* px) {
        Canvas c(px);
        c.Clear();
        switch (m.screen) {
            case kScreenClock: RenderClock(c, m); break;
            case kScreenAlarm: RenderAlarm(c, m); break;
            case kScreenWifiSetup: RenderWifi(c, m); break;
            case kScreenIcon: Strip(c, m, true); break;   // LVGL draws the font-awesome icon over the middle
            default: RenderFace(c, m); break;
        }
    }

    static std::string StripText(const Model& m) {
        if (!m.status.empty()) return m.status;
        return "";
    }

private:
    lana_eyes::Renderer eyes_;
    uint32_t t_ = 0;
    float scroll_px_ = 0;
    int scroll_hold_ = 900;
    uint8_t eye_px_[W * H];

    bool NeedStrip(const Model& m) const { return !m.status.empty(); }

    // battery: in the strip (icon + %), or alone in the top-right corner when low (<15 %, blinking)
    int Battery(Canvas& c, const Model& m, int right, int y, bool with_pct) {
        if (m.battery < 0) return right;
        if (BatteryLow(m) && (t_ / 500) % 2) return right - 12;
        char b[16]; snprintf(b, sizeof(b), "%d%%", m.battery);
        int x = right - 11;
        IconBattery(c, x, y + 1, m.battery, m.charging);
        if (with_pct) { int w = TextWidth(b); c.SetClip(0, kStripH); c.Text(x - 2 - w, y - 2, b); c.ResetClip(); x -= 2 + w; }
        return x - 2;
    }

    void Eyes(Canvas& c, int top, int bottom_reserved) {
        int area = H - top - bottom_reserved;
        eyes_.SetReservedBottom(H - area);
        eyes_.Render(eye_px_);
        for (int y = 0; y < area; y++) memcpy(c.px() + (top + y) * W, eye_px_ + y * W, W);
    }

    static bool s_has_room(const Model& m) { return TextWidth(m.status) < 62; }

    void Strip(Canvas& c, const Model& m, bool force) {
        if (!force && !NeedStrip(m)) return;
        int x = 1, ph = (int)(t_ / 150);
        if (m.state == lana_eyes::kStateListening) { IconMic(c, x, 1); x += 10; }
        else if (m.state == lana_eyes::kStateSpeaking) { IconSpeaker(c, x, 1, ph); x += 14; }
        else if (m.state == lana_eyes::kStateConnecting) { IconSpinner(c, x, 1, ph); x += 14; }
        int bars = RssiBars(m.rssi);
        int right = bars ? W - 13 : W;
        right = Battery(c, m, right - 1, 1, s_has_room(m)) ;
        std::string s = StripText(m);
        c.SetClip(0, kStripH);
        // text cell starts 1 row above the strip (row 0 of the cell only holds the tone of a stacked capital)
        if (x + TextWidth(s) <= right - 1) c.Text(x, -1, s);
        else { c.Text(x, -1, s); c.Fill(right - 9, 0, 9 + 13, kStripH, 0); c.Text(right - 8, -1, "…"); }
        c.ResetClip();
        if (bars) IconWifi(c, W - 12, 1, bars);
        c.HLine(0, W - 1, kStripH - 1, 0);
        for (int x2 = 0; x2 < W; x2 += 2) c.Set(x2, kStripH - 1);   // dotted divider
    }

    void Subtitle(Canvas& c, const std::string& s, int y) {
        int w = TextWidth(s);
        c.SetClip(y, H);
        if (w <= W) c.TextCentered(y, s);
        else {
            int period = w + 24, off = ((int)scroll_px_) % period;
            c.Text(-off, y, s); c.Text(-off + period, y, s);
        }
        c.ResetClip();
    }

    void RenderFace(Canvas& c, const Model& m) {
        eyes_.SetDrawBell(true);
        bool strip = NeedStrip(m), sub = !m.subtitle.empty();
        Eyes(c, strip ? kStripH : 0, sub ? kSubH : 0);
        Strip(c, m, false);
        if (!strip && BatteryLow(m)) { c.Fill(W - 24, 0, 24, 9, 0); Battery(c, m, W - 1, 0, false); c.Text(W - 23, -3, "!"); }
        if (sub) Subtitle(c, m.subtitle, H - kSubH);
    }

    // ---- 2.2.6 idle clock: rounded capsule 7-segment digits, tidy info row, optional tiny sleeping face ----------
    static void Capsule(Canvas& c, float ax, float ay, float bx, float by, float r) {
        int x0 = (int)std::floor(std::min(ax, bx) - r), x1 = (int)std::ceil(std::max(ax, bx) + r);
        int y0 = (int)std::floor(std::min(ay, by) - r), y1 = (int)std::ceil(std::max(ay, by) + r);
        float dx = bx - ax, dy = by - ay, l2 = dx * dx + dy * dy;
        for (int y = y0; y <= y1; y++) for (int x = x0; x <= x1; x++) {
            float px = x + 0.5f - ax, py = y + 0.5f - ay;
            float t = l2 > 0 ? (px * dx + py * dy) / l2 : 0; t = t < 0 ? 0 : t > 1 ? 1 : t;
            float qx = px - t * dx, qy = py - t * dy;
            if (qx * qx + qy * qy <= r * r) c.Set(x, y);
        }
    }
    static void RoundDigit(Canvas& c, int x, int y, int w, int h, float th, int d) {
        static const uint8_t seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
        uint8_t m = seg[d < 0 || d > 9 ? 8 : d];
        float r = th / 2, g = r + 1.2f;                       // capsule radius, gap at the joints
        float L = x + r, R = x + w - r, T = y + r, B = y + h - r, M = y + h / 2.0f;
        if (d == 1) R = x + w * 0.62f;   // centre-ish the 1 so '21:48' has no hole
        if (m & 0x01) Capsule(c, L + g, T, R - g, T, r);
        if (m & 0x40) Capsule(c, L + g, M, R - g, M, r);
        if (m & 0x08) Capsule(c, L + g, B, R - g, B, r);
        if (m & 0x20) Capsule(c, L, T + g, L, M - g, r);
        if (m & 0x02) Capsule(c, R, T + g, R, M - g, r);
        if (m & 0x10) Capsule(c, L, M + g, L, B - g, r);
        if (m & 0x04) Capsule(c, R, M + g, R, B - g, r);
    }
    static void Dot(Canvas& c, float cx, float cy, float r) { Capsule(c, cx, cy, cx, cy, r); }
    // HH:MM centred in [x0, x0+span); colon = two round dots, solid on even seconds, small on odd (soft pulse)
    void ClockDigits(Canvas& c, const Model& m, int x0, int span, int y0, int dw, int dh, float th, int gap, int colon) {
        int total = dw * 4 + gap * 2 + colon, x = x0 + (span - total) / 2;
        RoundDigit(c, x, y0, dw, dh, th, m.hh / 10); x += dw + gap;
        RoundDigit(c, x, y0, dw, dh, th, m.hh % 10); x += dw;
        float cr = th * 0.5f;
        if (m.ss % 2 == 0) { Dot(c, x + colon / 2.0f, y0 + dh * 0.32f, cr); Dot(c, x + colon / 2.0f, y0 + dh * 0.70f, cr); }
        x += colon;
        RoundDigit(c, x, y0, dw, dh, th, m.mm / 10); x += dw + gap;
        RoundDigit(c, x, y0, dw, dh, th, m.mm % 10);
    }
    void Dotted(Canvas& c, int x0, int x1, int y) { for (int x = x0; x <= x1; x += 3) c.Set(x, y); }
    // bottom info row at y: date (left) + weather/battery (right)
    void InfoRow(Canvas& c, const Model& m, int x0, int x1, int y) {
        std::string d = ShortDate(m.wday, m.mday, m.mon);
        int right = x1;
        if (m.battery >= 0) { IconBattery(c, right - 10, y + 4, m.battery, m.charging); right -= 15; }
        if (m.wx > 0) {
            char t[12]; snprintf(t, sizeof(t), "%d°", m.temp);
            int tx = right - TextWidth(t); c.Text(tx, y, t); IconWeather(c, tx - 13, y + 3, m.wx); right = tx - 16;
        }
        if (x0 + TextWidth(d) <= right) c.Text(x0, y, d);
    }
    void SleepFace(Canvas& c, int cx, int cy) {   // tiny dozing face: closed eyes + small mouth, slow breath, Zzz
        int br = ((t_ / 1000) % 4) < 2 ? 0 : 1;
        for (int k = -1; k <= 1; k += 2) for (int i = -4; i <= 4; i++) { int yy = cy + br + 2 - (i * i) / 8; c.Set(cx + k * 8 + i, yy); c.Set(cx + k * 8 + i, yy + 1); }
        c.Fill(cx - 1, cy + 8 + br, 3, 3); c.Set(cx - 1, cy + 8 + br, 0); c.Set(cx + 1, cy + 8 + br, 0); c.Set(cx - 1, cy + 10 + br, 0); c.Set(cx + 1, cy + 10 + br, 0);
        float ph = (t_ % 3000) / 3000.0f;
        int zs = 2 + (int)(ph * 3), zx = cx + 12 + (int)(ph * 4), zy = cy - 5 - (int)(ph * 8);
        for (int i = 0; i <= zs; i++) { c.Set(zx + i, zy); c.Set(zx + i, zy + zs); c.Set(zx + zs - i, zy + i); }
    }
public:
    void SetClockStyle(int s) { clock_style_ = s; }
private:
    int clock_style_ = 1;   // B: clock + dozing face (chosen Oct 25)

    void RenderClock(Canvas& c, const Model& m) {
        // burn-in care: the whole screen drifts by 1 px in a 4-minute cycle
        static const int kdx[4] = {0, 1, 1, 0}, kdy[4] = {0, 0, 1, 1};
        int dx = kdx[m.mm % 4], dy = kdy[m.mm % 4];
        if (clock_style_ == 1) {          // B: clock left + date under it, dozing face + weather on the right
            ClockDigits(c, m, 0 + dx, 84, 4 + dy, 15, 30, 3.6f, 3, 8);
            c.Text(4 + dx, 40 + dy, ShortDate(m.wday, m.mday, m.mon));
            for (int y = 6; y < 58; y += 3) c.Set(86 + dx, y + dy);
            SleepFace(c, 106 + dx, 18 + dy);
            if (m.wx > 0) { char t[12]; snprintf(t, sizeof(t), "%d°", m.temp);
                int w = 13 + TextWidth(t), x = 107 - w / 2 + dx; IconWeather(c, x, 44 + dy, m.wx); c.Text(x + 13, 41 + dy, t); }
            if (m.battery >= 0) IconBattery(c, W - 13 + dx, 56 + dy, m.battery, m.charging);
            return;
        }
        if (clock_style_ == 2) {          // C: big clock, minute progress line, info row
            ClockDigits(c, m, dx, W, 2 + dy, 24, 38, 5.0f, 5, 12);
            int len = 8 + (W - 18) * m.ss / 59;
            c.HLine(4 + dx, 4 + len + dx, 45 + dy);
            InfoRow(c, m, 3 + dx, W - 3 + dx, 49 + dy);
            return;
        }
        // A (default): big rounded clock, dotted separator, date left / weather right
        ClockDigits(c, m, dx, W, 3 + dy, 24, 37, 5.0f, 5, 12);
        Dotted(c, 4 + dx, W - 5 + dx, 46 + dy);
        InfoRow(c, m, 3 + dx, W - 3 + dx, 49 + dy);
    }

    void RenderAlarm(Canvas& c, const Model& m) {
        eyes_.SetDrawBell(false);
        bool sub = !m.subtitle.empty();
        Eyes(c, 15, sub ? kSubH : 0);
        bool on = (t_ / 400) % 2 == 0;
        int shake = on ? 1 : -1;
        c.Fill(0, 0, W, 14);                               // header bar (inverted)
        IconBell(c, 3 + shake, 2, 0);
        c.Text(15, -1, "Báo thức", true, 0);
        char hm[8]; snprintf(hm, sizeof(hm), "%02d:%02d", m.hh, m.mm);
        c.Text(W - 2 - TextWidth(hm, true), -1, hm, true, 0);
        if (!on) c.Invert(0, 0, W, 14);                     // flash 1.25 Hz
        if (sub) Subtitle(c, m.subtitle, H - kSubH);
    }

    void RenderWifi(Canvas& c, const Model& m) {
        c.Fill(0, 0, W, 13);
        static const char* const kWifi[] = {"..XXXXX..", ".X.....X.", "X..XXX..X", "..X...X..", "....X....", "...XXX..."};
        Art(c, 4, 4, kWifi, 6, 0);
        c.Text(18, -1, "Cài đặt Wi-Fi", true, 0);
        c.Text(1, 13, "1. Kết nối Wi-Fi:");
        std::string ssid = m.ssid.empty() ? "Lana-made-by-Nael" : m.ssid;
        bool bold = TextWidth(ssid, true) <= W - 2;
        int w = TextWidth(ssid, bold);
        c.Text((W - w) / 2, 25, ssid, bold);
        c.Text(1, 38, "2. Mở trình duyệt:");
        std::string url = m.url.empty() ? "192.168.4.1" : m.url;
        if (url.rfind("http://", 0) == 0) url = url.substr(7);
        if (!url.empty() && url.back() == '/') url.pop_back();
        bool b2 = TextWidth(url, true) <= W - 2;
        c.Text((W - TextWidth(url, b2)) / 2, 50, url, b2);
    }
};

}  // namespace lana_ui
