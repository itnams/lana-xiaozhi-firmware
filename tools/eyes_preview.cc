// Native preview of the Lana OLED eyes: renders the same lana_eyes.h used on the robot.
// g++ -O2 -std=c++17 -I main/boards/lana-tim tools/eyes_preview.cc -o /tmp/eyes_preview && /tmp/eyes_preview OUTDIR
// writes OUTDIR/<scenario>.raw = frames of 128x48 bytes (1 = lit), 40 ms apart
#include "lana_eyes.h"
#include <cstdio>
#include <string>
using namespace lana_eyes;

static void run(const std::string& dir, const std::string& name, int emotion, State st, int ms, int reserved = 0,
                int volume = -1) {
    Renderer r(777);
    r.SetState(kStateIdle);
    r.SetEmotion(kNeutral);
    for (int i = 0; i < 10; i++) r.Step(40);           // settle on neutral first
    r.SetState(st);
    r.SetEmotion(emotion);
    r.SetReservedBottom(reserved);
    if (volume >= 0) r.ShowVolume(volume, ms);
    FILE* f = fopen((dir + "/" + name + ".raw").c_str(), "wb");
    static uint8_t px[Renderer::W * Renderer::H];
    for (int t = 0; t < ms; t += 40) {
        r.Step(40);
        r.Render(px);
        fwrite(px, 1, sizeof(px), f);
    }
    fclose(f);
}

int main(int argc, char** argv) {
    std::string dir = argc > 1 ? argv[1] : ".";
    for (int e = 0; e < kEmotionCount; e++) run(dir, std::string("emotion_") + kEmotionNames[e], e, kStateSpeaking, 4000);
    run(dir, "state_idle", kNeutral, kStateIdle, 8000);
    run(dir, "state_listening", kNeutral, kStateListening, 4000);
    run(dir, "state_speaking", kNeutral, kStateSpeaking, 4000, 18);
    run(dir, "state_connecting", kNeutral, kStateConnecting, 4000);
    run(dir, "volume_70", kNeutral, kStateIdle, 2000, 0, 70);
    return 0;
}
