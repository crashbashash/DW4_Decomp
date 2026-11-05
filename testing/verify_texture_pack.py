#!/usr/bin/env python3
"""verify_texture_pack.py -- live regression check for the texture-pack decode.

Decodes every texture of NDMW.AFS entry 625 through the recovered rules and compares
the RGB against the live-extracted PNGs in ../local/evidence/screenshots/dw4-textures.  This is the check
that *pins the rules to real data*: the pool layout and the texture -> palette pairing are
both predictions, and 26/26 exact RGB is what makes them facts.

The rules applied (findings #472/#473, #476):

  * a block's pool offset is `pool_base + sum(_memSize of MEM ids below it)`, with
    `pool_base = EOF - 1 - hdr[6] + 4*nclut`; a clut block is 1024 bytes, an image `W*H`
    and its grid starts one byte into the block;
  * an igImage's `_pClut` is an id in the pack's id space, not a block id: the id->class
    table says which class it is, its rank among the ids of that class is its position in
    the loader's creation order (= file order), and the r-th igClut record's `_pData` is
    the palette block.

The offline fixture lives in the repo (docs/engine/texture-pack-625-{layout,textures}.tsv,
re-checked by scripts/verify_texpack_layout.py); this file is the part that
needs private live evidence, while the verifier itself lives in testing/ in the shared repo.
"""
import os
import struct
import sys
import zlib
_PATH_HERE = os.path.dirname(os.path.abspath(__file__))
_PATH_REPO = os.path.dirname(_PATH_HERE)
_PATH_WS = os.path.dirname(_PATH_REPO)

AFS = os.path.join(_PATH_WS, "local/extracted/NDMW.AFS")
ENTRY = 625
PNGDIR = os.path.join(_PATH_WS, "local/evidence/screenshots/dw4-textures")
REPO_SCRIPTS = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                            "..", "scripts")
sys.path.insert(0, REPO_SCRIPTS)
import igb_texpack as TP  # noqa: E402


def png_pixels(path):
    d = open(path, "rb").read()
    i, W, H, idat = 8, None, None, b""
    while i < len(d):
        ln = struct.unpack(">I", d[i:i + 4])[0]
        typ = d[i + 4:i + 8]
        body = d[i + 8:i + 8 + ln]
        i += 12 + ln
        if typ == b"IHDR":
            W, H = struct.unpack(">II", body[:8])
        elif typ == b"IDAT":
            idat += body
        elif typ == b"IEND":
            break
    raw = zlib.decompress(idat)
    stride = W * 4
    out = bytearray()
    prev = bytearray(stride)
    p = 0
    for _ in range(H):
        f = raw[p]
        p += 1
        line = bytearray(raw[p:p + stride])
        p += stride
        for x in range(stride):
            a = line[x - 4] if x >= 4 else 0
            b = prev[x]
            c = prev[x - 4] if x >= 4 else 0
            if f == 1:
                line[x] = (line[x] + a) & 255
            elif f == 2:
                line[x] = (line[x] + b) & 255
            elif f == 3:
                line[x] = (line[x] + (a + b) // 2) & 255
            elif f == 4:
                pp = a + b - c
                pa, pb, pc = abs(pp - a), abs(pp - b), abs(pp - c)
                pr = a if (pa <= pb and pa <= pc) else (b if pb <= pc else c)
                line[x] = (line[x] + pr) & 255
        out += line
        prev = line
    return W, H, bytes(out)


def main():
    data = open(AFS, "rb").read()
    off, pack_size = struct.unpack_from("<II", data, 8 + 8 * ENTRY)
    b = data[off:off + pack_size]
    recs = TP.find_records(b)
    info = TP.header_layout(b, recs)
    if info is None:
        print("FAILED: the header does not describe this pool")
        return 1
    base, npad, _total, _nclut = info
    pads = set(TP.choose_pads(b, recs, base, npad))
    layout, _, end = TP.build_layout(b, recs, base, pads)
    print("pool 0x%06x .. 0x%06x  (pack 0x%06x, %d blocks)" % (base, end, pack_size, len(layout)))

    pal = TP.resolve_palettes(b, recs)
    if pal is None:
        print("FAILED: no validated id->class table / palette pairing")
        return 1

    live = {}
    for fn in sorted(os.listdir(PNGDIR)):
        try:
            W, H, px = png_pixels(os.path.join(PNGDIR, fn))
        except Exception:
            continue
        live.setdefault(fn.split(".")[0], []).append((W, H, px))

    ok = missed = 0
    for d in TP.image_records(b):
        stem = d["name"].split(".")[0]
        cid = pal.get(d["image"])
        if cid is None:
            print("  %-12s no palette resolved" % stem)
            missed += 1
            continue
        dec = TP.decode_rgba(b, layout, d["image"], cid)
        cand = [pp for W, H, pp in live.get(stem, []) if (W, H) == (d["w"], d["h"])]
        if not cand:
            print("  %-12s %3dx%-3d (no live png at this size)" % (stem, d["w"], d["h"]))
            continue
        px = cand[0]
        exact = any(dec[2][k * 4:k * 4 + 3] == px[k * 4:k * 4 + 3]
                    for k in range(0, 1)) and all(
            dec[2][k * 4:k * 4 + 3] == px[k * 4:k * 4 + 3] for k in range(d["w"] * d["h"]))
        print("  %-12s %3dx%-3d image id %-3d palette id %-3d  %s"
              % (stem, d["w"], d["h"], d["image"], cid, "exact" if exact else "MISMATCH"))
        ok += exact
        missed += not exact
    print("textures reproduced exactly: %d, failures: %d" % (ok, missed))
    return 0 if missed == 0 and ok >= 26 else 1


if __name__ == "__main__":
    sys.exit(main())
