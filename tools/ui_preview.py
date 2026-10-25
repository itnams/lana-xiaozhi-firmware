#!/usr/bin/env python3
"""Turn eyes_preview .raw dumps (128x64, 1 byte/px, 40 ms/frame) into 1x and 4x PNG/GIF + a contact sheet.
Colour: rendered as a white SSD1306 (lit = #E8F4FF on black). usage: ui_preview.py RAWDIR OUTDIR"""
import sys, os, glob
from PIL import Image, ImageDraw
W, H, LIT, OFF = 128, 64, (232, 244, 255), (0, 0, 0)
src, out = sys.argv[1], sys.argv[2]
os.makedirs(out, exist_ok=True)
KEY = {"state_idle": 1200, "state_listening": 1500, "state_speaking": 2500, "state_connecting": 1500, "volume_70": 800,
       "clock_idle": 1000, "alarm": 300, "wifi_setup": 1300}
sheet = []
for raw in sorted(glob.glob(src + "/*.raw")):
    name = os.path.basename(raw)[:-4]
    data = open(raw, "rb").read()
    n = len(data) // (W * H)
    frames = []
    for i in range(0, n, 2):   # 80 ms GIF frames
        im = Image.frombytes("L", (W, H), data[i * W * H:(i + 1) * W * H]).point(lambda v: 255 if v else 0)
        frames.append(Image.merge("RGB", [im.point(lambda v, c=c: c if v else 0) for c in LIT]))
    key = frames[min(len(frames) - 1, KEY.get(name, 1500) // 80)]
    key.save(f"{out}/{name}_1x.png"); key.resize((W * 4, H * 4), Image.NEAREST).save(f"{out}/{name}_4x.png")
    frames[0].save(f"{out}/{name}_1x.gif", save_all=True, append_images=frames[1:], duration=80, loop=0)
    big = [f.resize((W * 4, H * 4), Image.NEAREST) for f in frames]
    big[0].save(f"{out}/{name}_4x.gif", save_all=True, append_images=big[1:], duration=80, loop=0)
    sheet.append((name, key))
order = ["state_idle", "state_listening", "state_speaking", "state_connecting", "clock_idle", "alarm", "wifi_setup", "volume_70"]
sheet.sort(key=lambda t: (order.index(t[0]) if t[0] in order else 99, t[0]))
cols, S, pad, lab = 4, 3, 10, 16
rows = (len(sheet) + cols - 1) // cols
cs = Image.new("RGB", (cols * (W * S + pad) + pad, rows * (H * S + pad + lab) + pad), (40, 40, 48))
d = ImageDraw.Draw(cs)
for i, (name, im) in enumerate(sheet):
    x = pad + (i % cols) * (W * S + pad); y = pad + (i // cols) * (H * S + pad + lab)
    d.text((x, y), name.replace("emotion_", "emotion: "), fill=(220, 220, 220))
    cs.paste(im.resize((W * S, H * S), Image.NEAREST), (x, y + lab))
cs.save(f"{out}/contact_sheet.png")
print(len(sheet), "scenarios ->", out)
