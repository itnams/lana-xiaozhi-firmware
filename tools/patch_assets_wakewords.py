#!/usr/bin/env python3
"""Rewrite the wake phrases inside an existing xiaozhi assets image (esp_mmap_assets format) without
touching the firmware: unpack, edit index.json -> multinet_model.commands, repack (same file order).

usage: patch_assets_wakewords.py IN_assets.bin OUT_assets.bin "hai la na=Hi Lana" "la na ei=Lana ơi" ...
       [--threshold 0.2] [--language cn]
Flash OUT at the assets partition offset (0x920000 on the xiaozhi.vn 16 MB layout)."""
import argparse, json, struct

def unpack(blob):
    n, csum, length = struct.unpack_from("<III", blob, 0)
    data = blob[12:12 + length]
    assert sum(data) & 0xFFFF == csum, "checksum mismatch - not an esp_mmap_assets image?"
    files, table = [], data[:n * 44]
    base = n * 44
    for i in range(n):
        name, size, off, w, h = struct.unpack_from("<32sIIHH", table, i * 44)
        name = name.split(b"\0")[0].decode()
        start = base + off
        assert data[start:start + 2] == b"\x5a\x5a", name
        files.append([name, data[start + 2:start + 2 + size], w, h])
    return files

def pack(files):
    merged, table = bytearray(), bytearray()
    for name, content, w, h in files:
        table += name.encode().ljust(32, b"\0")[:32] + struct.pack("<IIHH", len(content), len(merged), w, h)
        merged += b"\x5a\x5a" + content
    data = bytes(table + merged)
    return struct.pack("<III", len(files), sum(data) & 0xFFFF, len(data)) + data

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("inp"); ap.add_argument("out"); ap.add_argument("phrases", nargs="+")
    ap.add_argument("--threshold", type=float); ap.add_argument("--language")
    a = ap.parse_args()
    blob = open(a.inp, "rb").read()
    files = unpack(blob)
    idx = next(f for f in files if f[0] == "index.json")
    j = json.loads(idx[1].decode("utf-8"))
    mn = j.setdefault("multinet_model", {"language": "cn", "duration": 3000, "threshold": 0.2})
    if a.threshold is not None: mn["threshold"] = a.threshold
    if a.language: mn["language"] = a.language
    mn["commands"] = [{"command": p.split("=", 1)[0].strip(), "text": (p.split("=", 1) + [p])[1].strip(), "action": "wake"}
                      for p in a.phrases]
    idx[1] = (json.dumps(j, ensure_ascii=False, indent=4) + "\n").encode("utf-8")   # vendor file ends with \n
    out = pack(files)
    out += b"\xff" * (-len(out) % 4)   # keep the image size 4-byte aligned like the vendor's (flashers pad anyway)
    assert unpack(out)[0][0] == files[0][0]
    open(a.out, "wb").write(out)
    print("files:", len(files), "| size %d -> %d bytes" % (len(blob.rstrip(b"\xff")), len(out)))
    print(json.dumps(mn, ensure_ascii=False, indent=1))

if __name__ == "__main__":
    main()
