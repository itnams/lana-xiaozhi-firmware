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
