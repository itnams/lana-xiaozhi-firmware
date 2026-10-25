# Lana firmware (fork of 78/xiaozhi-esp32 v2.0.5)

Board `lana-tim`: robot Lana = mạch tím ESP32-S3-WROOM-1 N16R8 (xiaozhi.vn, vendor board `mach-tim-wartank`).

| Part | GPIO |
|---|---|
| INMP441 mic | WS 4, SCK 5, SD 6 |
| MAX98357A amp | DIN 7, BCLK 15, LRC 16 |
| SSD1306 128x64 (I2C 0x3C/0x3D) | SDA 41, SCL 42 |
| Buttons | BOOT 0, Wake 47 (hold to talk) |
| LED | 48 |
| Tank motors (L298) | A (left) 39/40, B (right) 43/44 — held LOW at boot, MCP `self.tank.*` |

The xiaozhi.vn wiring sheet puts Vol-/Vol+ on 39/40; on this robot those pins drive the motors, so there are no
volume buttons. GPIO43/44 are UART0, so the console is USB-Serial-JTAG.

Changes vs upstream v2.0.5:
- several custom wake phrases (`CONFIG_CUSTOM_WAKE_WORD` / `_DISPLAY` separated by `;`, also written to the assets
  `index.json`), MultiNet7 Chinese pinyin like the vendor firmware:
  `hai la na` (Hi Lana), `hei la na` (Hey Lana), `ha lou la na` (Hello Lana), `la na ei` (Lana ơi), `jiao la na` (Chào Lana)
- animated eyes on the OLED that follow the server's `llm` emotion (blink, bounce, brows), subtitle as one scrolling line
- full Vietnamese 1-bpp font (Be Vietnam Pro 12 px) compiled in
- partition table identical to the xiaozhi.vn 2.0.5.x layout (`partitions/v2/16m_lana.csv`): NVS (Wi-Fi, OTA URL) and
  offsets are kept; DIO 80 MHz like the vendor image
- `CONFIG_OTA_URL` defaults to the Lana server; a URL saved in NVS (`wifi/ota_url`) still wins
- `tools/patch_assets_wakewords.py`: change the wake phrases inside an existing assets image (e.g. the vendor one)

## Build (ESP-IDF v5.5.1)

```bash
. ~/esp/esp-idf-v5.5/export.sh
export SDKCONFIG_DEFAULTS="sdkconfig.defaults;sdkconfig.defaults.esp32s3;main/boards/lana-tim/sdkconfig.lana"
idf.py set-target esp32s3 && idf.py build
```

## Flash (keeps Wi-Fi/NVS)

```bash
python -m esptool --chip esp32s3 -b 460800 write_flash --flash_mode dio --flash_size 16MB --flash_freq 80m \
  0x0 bootloader.bin 0x8000 partition-table.bin 0xd000 ota_data_initial.bin 0x20000 xiaozhi.bin 0x920000 generated_assets.bin
```

A merged image written at 0x0 also overwrites NVS (0x9000) with 0xFF: Wi-Fi has to be set up again.
Never commit `.bin` files, `sdkconfig`, Wi-Fi credentials or device tokens.

## 2.1.0-lana

* **Eyes** (`main/boards/lana-tim/lana_eyes.h`, portable renderer): rounded-rect eyes, random (double) blinks,
  saccades/idle drift/breathing, a distinct face for each of the 21 emotions (hearts, tears, Zzz, thinking dots,
  blush, sunglasses glint, wink, kiss), listening = bigger/steady, speaking = syllable bounce, connecting = scan.
  `LanaFaceDisplay` renders it in its own task (prio 1, 25 fps) into a 128x48 L8 LVGL image; the LVGL lock is
  only held for a 6 KB memcpy. Previews: `g++ -O2 -std=c++17 -I main/boards/lana-tim tools/eyes_preview.cc -o
  /tmp/eyes_preview && /tmp/eyes_preview /tmp/raw && python3 tools/eyes_preview_render.py /tmp/raw out/`.
* **Volume buttons**: Vol+ = GPIO18, Vol- = GPIO17 (left header). Button between GPIO and GND, internal
  pull-up. Click = +/-10, hold 1 s = 100 / mute. Shown in the status bar + bar under the eyes.
* **OTA**: version `2.1.0-lana`; the OTA reply may contain `"assets": {"version","url"}` -> queued in
  Settings("assets"), device reboots and downloads it, stores `version` (or `fail_version`, no retry loop).

## 2.2.0-lana
- **Server push** (`{"type":"lana",...}` over MQTT, forwarded by the gateway's `/lana/ctl` link):
  - `say {id,text,alarm}`: when idle, opens a channel and sends listen-detect `lana_push:<id>`; the server (robotsay.py) then plays that exact text. If already listening/speaking it does nothing (the server plays in-session). `alarm` shows the alarm face (trembling eyes + bell) and rings 3x.
  - `config {clock_idle_min}`: persisted in NVS `lana/clock_idle_min`.
  - `stop`: ends an alarm / the session.
- **Idle clock**: after `clock_idle_min` (default 2, 0 = off) minutes idle in standby, the OLED shows 7-segment HH:MM, sleeping eyes and Zzz, plus the Vietnamese date line; renders at 4 fps. Wake word, button, or server push brings the normal face back. Time comes from SNTP pool.ntp.org with TZ ICT-7; for lana-tim the OTA `server_time` is taken as true UTC (no extra offset added).
- **Wake words (Vietnamese pronunciation)**, threshold 0.15: `hai la na; hei la na; hai lan na; ha lou la na; la na ei; la na wei; la na ai; zhao la na; jiao la na; chao la na; la na la na`.
- Previews: `tools/eyes_preview.cc` scenarios `clock_idle` and `emotion_alarm`.

## 2.2.1-lana
- **Easier wake (lana-tim only)**: an AFE front end (single mic, WebRTC AGC +12 dB to -3 dBFS, WebRTC VAD, no NS/AEC/wakenet) now runs before MultiNet in its own task (core 1, prio 5). MultiNet is reset only after >= 600 ms of VAD silence (the 6 s timeout is a fallback), so a phrase can no longer be cut by the old blind 3 s reset. Crash guard: NVS `lana/afe_fail`; two AFE starts that do not survive 20 s fall back to direct MultiNet.
- **Wake words (20 commands, threshold 0.12)**: `hai la na; hei la na; hai lan na; ha lou la na; ai la na; ei la na; e la na; a la na; la na ei; la na wei; la na ai; la na e; lan na ei; la na ya; la na a; zhao la na; jiao la na; chao la na; xin chao la na; la na la na`.
- The wake detect message now carries `lana_cmd` (pinyin command) and `prob`; the OTA request carries `lana_reset` (esp_reset_reason) for diagnostics.
- Clock-mode fix: the `lana_eyes` task stack goes from 3 KB to 8 KB (localtime_r + snprintf + lv_label in clock mode could overflow; suspected cause of reboots/hangs a few minutes after a conversation on 2.2.0). Logs the stack high-water mark when the clock toggles.
- Server push `{"type":"lana","action":"reboot"}` (only when idle), e.g. to pick up an OTA offer.
- Wi-Fi config hotspot SSID is `Lana-made-by-Nael` (no suffix); the portal is still http://192.168.4.1.

## 2.2.2-lana
- **No mic-off dead window while waiting for a reply (lana-tim only)**: the robot stays Listening (mic on) after you stop talking. The first reply audio packet itself switches it to Speaking. Packets that arrive before the main loop has switched are buffered in order (up to 120) and flushed after the decoder reset, so the start of the reply is not lost. The server therefore no longer needs to send an early `tts start` (server key `fw_buffers_audio_min`). Audio that arrives within 400 ms after a `tts stop` is dropped as a leftover from the previous reply. Guard: if Speaking was started by audio alone and neither `tts start` nor `tts stop` follows, the robot returns to Listening after 2.5 s without audio once playback is idle.
- **UDP warm-up**: right after the audio channel opens, the robot sends one empty encrypted packet (payload_len 0, next sequence number). The MQTT+UDP gateway then learns the robot's address immediately instead of waiting for the first mic packet. The server ignores empty frames.
- Assets unchanged from 2.2.1 (OTA ships the app only).

## 2.2.3-lana
- **Long replies no longer overflow the audio queue (lana-tim only)**: the server sends 20 ms Opus packets, so the stock limit of 2400/60 = 40 packets meant only 0.8 s of audio. With the server's 0.6 s lead plus Wi-Fi bursts, the queue overflowed and the extra packets were silently dropped, which is the stutter heard in long answers. The limit is now 120 packets (2.4 s); the server uses a bigger cushion (1.5 s lead, 600 ms prebuffer) only for 2.2.3 or newer (`fw_big_queue_min`).
- **Hang recovery**: `CONFIG_ESP_TASK_WDT_PANIC=y`. A task that starves the CPU or deadlocks now panics and reboots after 10 s (reset reason TASK_WDT, reported to the server as `lana_reset`) instead of freezing until someone power-cycles the robot.
- **Harder to wake from TV/background noise**: threshold 0.12 -> 0.15. The false-prone vowel-onset phrases `ai la na`, `e la na` and `a la na` are dropped (every logged wake with no speech afterwards came from them). Pre-wake AGC gain goes from +12 to +9 dB. The remaining 17 phrases are: `hai la na; hei la na; hai lan na; ha lou la na; ei la na; la na ei; la na wei; la na ai; la na e; lan na ei; la na ya; la na a; zhao la na; jiao la na; chao la na; xin chao la na; la na la na`.

## 2.2.4-lana — Wi-Fi power save off + 0.96" OLED UI redesign

**Wi-Fi.** The stock app sets `WIFI_PS_MIN_MODEM` at boot (IDF default) and again every time the audio channel
closes, so while idle the radio only wakes on DTIM beacons (LAN ping ~120 ms, bursty UDP, late pushes). lana-tim now
maps every `SetPowerSaveMode()` call to `WIFI_PS_NONE` and forces it right after the station connects
(`wifi_board.cc`, guarded by `CONFIG_BOARD_TYPE_LANA_TIM`). The boot log prints
`Lana Wi-Fi: rssi <dBm>, channel <n>, power save off`. The server logs `rssi=/ch=` from the OTA body.

**Display: SSD1306 128x64 monochrome, I2C SDA41/SCL42** (`CONFIG_OLED_SSD1306_128X64`). The whole panel is now one
128x64 frame composed by `lana_ui.h` (plain C++, no LVGL); the stock top bar and chat area are hidden.
- Face: the eyes fill all 64 rows when idle (about 1.3x the 2.2.3 size). A 13 px status strip (mic / speaker / dots icon,
  short Vietnamese text, Wi-Fi bars) appears only while listening / speaking / connecting or for a notification.
  The subtitle is one 13 px line that scrolls when it is long.
- Idle clock: 38 px 7-segment HH:MM, blinking colon, short date `T7 · 25/10`, 1 px burn-in drift per minute, 4 fps.
- Alarm: flashing inverted header (bell, `Báo thức`, HH:MM), trembling alarm eyes, reminder text below.
- Wi-Fi setup: steps with the hotspot `Lana-made-by-Nael` and `192.168.4.1` (bold), parsed from the stock hint.
- Font: `lana_font_vi.h`, 245 glyphs in a 13 px cell (ASCII + all Vietnamese letters). The base glyphs come from
  DejaVu Sans 10 rasterised 1-bit, and the tone/vowel marks are hand-drawn pixel art composed via NFD
  (`tools/gen_vi_font.py`), because outline fonts lose the marks at this size.
- Previews: `g++ -O2 -std=c++17 -I main/boards/lana-tim tools/eyes_preview.cc -o /tmp/eyes_preview && /tmp/eyes_preview RAW`
  then `tools/ui_preview.py RAW OUT` (1x/4x PNG + GIF, contact_sheet.png).

### 2.2.4-lana (rebuild): server pushes for volume / face, battery-ready UI
- Push `{"type":"lana","action":"volume","volume":0-100}`: speaker volume (saved) + volume bar.
- Push `{"type":"lana","action":"emotion","emotion":"happy","hold_s":30}`: shows the face; with hold_s>0 reply
  emotions are ignored until it ends, then neutral; hold_s=0 lasts until the next reply.
- Battery: status-strip icon + %, clock corner %, blinking low-battery icon <15 %. Hidden: this robot has no battery
  sense. To enable, fit a 100k/100k divider BAT+ -> GPIO1 (ADC1_CH0) -> GND (+100 nF), optional TP4056 CHRG -> GPIO2,
  then uncomment LANA_BATTERY_ADC_GPIO / LANA_BATTERY_CHARGE_GPIO in config.h. The level is also sent in the OTA board JSON.

## 2.2.4-lana trim (Oct 25)
- lana-tim build drops ml307/dual-network boards, ESP32 camera, LCD/emote displays and JPEG encoder sources
  (main/CMakeLists.txt filter) and unused LVGL widgets/decoders (sdkconfig.lana). Kept: label, image, flex,
  default theme, imgfont (xiaozhi-fonts emoji), 16-bit colour (esp_lvgl_port SSD1306 mono path).
- App 2,619,072 -> 2,439,104 B (-176 KB); DIRAM used 155,759 -> 145,347 B (+10.4 KB free).
