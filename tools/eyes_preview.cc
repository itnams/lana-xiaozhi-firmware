// Native preview of the Lana 2.2.4 OLED UI: renders the same lana_ui.h / lana_eyes.h used on the robot.
// g++ -O2 -std=c++17 -I main/boards/lana-tim tools/eyes_preview.cc -o /tmp/eyes_preview && /tmp/eyes_preview OUTDIR
// writes OUTDIR/<scenario>.raw = frames of 128x64 bytes (1 = lit), 40 ms apart; tools/ui_preview.py makes PNG/GIF.
#include "lana_ui.h"
#include <cstdio>
#include <string>
using namespace lana_eyes;
using namespace lana_ui;

static std::string g_dir;

static void run(const std::string& name, Model m, int emotion, int ms, int step_ms = 40, int volume = -1) {
    Ui ui(777);
    ui.eyes().SetState(kStateIdle);
    ui.eyes().SetEmotion(kNeutral);
    for (int i = 0; i < 10; i++) ui.Step(40);
    ui.eyes().SetState(m.state);
    ui.eyes().SetEmotion(emotion);
    if (volume >= 0) ui.eyes().ShowVolume(volume, ms);
    ui.ResetScroll();
    FILE* f = fopen((g_dir + "/" + name + ".raw").c_str(), "wb");
    static uint8_t px[W * H];
    int sec0 = m.ss;
    for (int t = 0; t < ms; t += step_ms) {
        ui.Step(step_ms);
        int s = sec0 + t / 1000;
        m.ss = s % 60;
        if (m.screen == kScreenClock && s >= 60) { m.mm = (m.mm + 1) % 60; sec0 -= 60; }
        ui.Render(m, px);
        for (int k = 0; k < step_ms / 40; k++) fwrite(px, 1, sizeof(px), f);
    }
    fclose(f);
}

int main(int argc, char** argv) {
    g_dir = argc > 1 ? argv[1] : ".";
    Model idle; idle.rssi = -58;
    for (int e = 0; e < kEmotionCount; e++) {
        Model m = idle; m.state = kStateSpeaking; m.status = "Đang nói…";
        if (e == kAlarm) { m.screen = kScreenAlarm; m.hh = 6; m.mm = 30; m.subtitle = "Dậy đi ba ơi, 6 giờ 30 rồi!"; }
        run(std::string("emotion_") + kEmotionNames[e], m, e, 3000);
    }
    run("state_idle", idle, kNeutral, 6000);
    { Model m = idle; m.state = kStateListening; m.status = "Đang lắng nghe…"; run("state_listening", m, kNeutral, 3000); }
    { Model m = idle; m.state = kStateSpeaking; m.status = "Đang nói…"; m.subtitle = "Chào ba! Hôm nay trời Sài Gòn nắng đẹp, 31°C, ba nhớ uống nước nha.";
      run("state_speaking", m, kHappy, 6000); }
    { Model m = idle; m.rssi = 0; m.state = kStateConnecting; m.status = "Đang kết nối…"; run("state_connecting", m, kNeutral, 3000); }
    { Model m = idle; m.status = "Âm lượng 70"; run("volume_70", m, kNeutral, 2000, 40, 70); }
    { Model m = idle; m.screen = kScreenClock; m.hh = 21; m.mm = 7; m.ss = 56; m.wday = 6; m.mday = 25; m.mon = 10; run("clock_idle", m, kSleepy, 8000, 240); }
    { Model m = idle; m.screen = kScreenAlarm; m.hh = 6; m.mm = 30; m.subtitle = "Dậy đi ba ơi, 6 giờ 30 rồi!"; run("alarm", m, kAlarm, 4000); }
    { Model m; m.screen = kScreenWifiSetup; m.ssid = "Lana-made-by-Nael"; m.url = "http://192.168.4.1"; m.status = "Chế độ cấu hình Wi-Fi"; run("wifi_setup", m, kNeutral, 3200); }
    return 0;
}
