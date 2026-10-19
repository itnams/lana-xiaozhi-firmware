#!/usr/bin/env python3
"""Turn eyes_preview .raw frames into OLED-looking GIFs and a contact sheet PNG.
usage: eyes_preview_render.py RAWDIR OUTDIR"""
import os, sys
from PIL import Image, ImageDraw, ImageFont
W, H, TOP, S = 128, 48, 16, 4
FONT = "/usr/share/fonts/truetype/sand-box/google/Be Vietnam Pro/BeVietnamPro-Medium.ttf"
STATUS = {"state_idle": "Chờ", "state_listening": "Đang lắng nghe...", "state_connecting": "Đang kết nối...",
          "volume_70": "Âm lượng 70"}
ON, OFF = (150, 225, 255), (4, 6, 10)

def frame(raw, status, subtitle=None):
    im = Image.new("RGB", (W, 64), OFF); d = ImageDraw.Draw(im)
    f = ImageFont.truetype(FONT, 11)
    d.text((64, 1), status, fill=ON, font=f, anchor="ma")
    for y in range(H):
        row = raw[y * W:(y + 1) * W]
        for x in range(W):
            if row[x]: im.putpixel((x, TOP + y), ON)
    if subtitle: d.text((64, 64 - 15), subtitle, fill=ON, font=f, anchor="ma")
    im = im.resize((W * S, 64 * S), Image.NEAREST)
    g = ImageDraw.Draw(im)
    for y in range(0, 64 * S, S): g.line([(0, y), (W * S, y)], fill=(0, 0, 0))    # pixel grid look
    for x in range(0, W * S, S): g.line([(x, 0), (x, 64 * S)], fill=(0, 0, 0))
    return im

def main():
    src, out = sys.argv[1], sys.argv[2]; os.makedirs(out, exist_ok=True)
    thumbs = []
    for fn in sorted(os.listdir(src)):
        name = fn[:-4]; data = open(os.path.join(src, fn), "rb").read()
        n = len(data) // (W * H)
        status = STATUS.get(name, "Đang nói...")
        sub = "Dạ con nghe nè ba!" if name in ("state_speaking",) else None
        frames = [frame(data[i * W * H:(i + 1) * W * H], status, sub) for i in range(0, n, 1)]
        frames[0].save(os.path.join(out, name + ".gif"), save_all=True, append_images=frames[1:], duration=40, loop=0)
        if name.startswith("emotion_"):
            thumbs.append((name[8:], frames[min(n - 1, 40)]))
    cols, tw, th = 4, W * 2, 64 * 2
    rows = (len(thumbs) + cols - 1) // cols
    sheet = Image.new("RGB", (cols * (tw + 10) + 10, rows * (th + 26) + 10), (30, 30, 34))
    d = ImageDraw.Draw(sheet); f = ImageFont.truetype(FONT, 14)
    for i, (n, im) in enumerate(thumbs):
        x, y = 10 + (i % cols) * (tw + 10), 10 + (i // cols) * (th + 26)
        sheet.paste(im.resize((tw, th), Image.LANCZOS), (x, y + 20)); d.text((x, y), n, fill=(230, 230, 230), font=f)
    sheet.save(os.path.join(out, "all_emotions.png"))
    print("wrote", len(os.listdir(out)), "files to", out)

main()
