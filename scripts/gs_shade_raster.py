#!/usr/bin/env python3
"""gs_shade_raster.py — depth-buffered rasterisation of a GS draw's own vertices.

Builds a draw (by TEX0) as triangles in GS screen space and rasterises them with the **GS's own Z**
(`ZTST=2 GEQUAL`, so the larger Z wins) to produce three independent maps for the same pixels:

  * `shade`  — the per-vertex **RGBA** the GS receives, Gouraud-interpolated **affinely** (the GS
               has no Q on the colour), on-screen scale `Cv/128` (`(Cv*Ct)>>7` with a full texel)
  * `texel`  — the GS's own **VRAM texture** sampled through the GS's own **STQ** (S,T,Q
               interpolated affinely, then divided) with bilinear filtering
  * `frame`  — the dump's **framebuffer** decoded out of VRAM (PSMCT32, the `CTXT0.FRAME` register)

The three together separate the two halves of the pixel pipeline: `shade` is what the VU1 lighting
produced, `texel` is what the sampler read, and `frame` is the result.

Usage:

    python3 scripts/gs_shade_raster.py --dump <dump>.gs.zst \
        --tex0 0x40060805e1312fc0 --tex0 0x40063405dd30b160 --out-dir /tmp/raster

Writes `shade.npy`/`shade.png`, `texel.npy`/`texel.png`, `frame.npy`/`frame.png` and prints the
region means.
"""
import argparse
import math
import os
import sys

import numpy as np
from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gsdump  # noqa: E402

W, H = 640, 448
OFX = 0x6c00 / 16.0        # XYOFFSET freeze 0x720000006c00
OFY = 0x7200 / 16.0

BOXES = [("floor", (260, 330, 420, 420)), ("wall", (120, 60, 250, 110)),
         ("barrel", (135, 120, 225, 245)), ("crate", (210, 120, 300, 240)),
         ("whole", (0, 0, W, H))]


# A PSMCT32 page is 64 x 32 pixels (2048 words) built of 8 x 4 blocks of 8 x 8 pixels (64 words),
# and the blocks are **not** in row-major order -- the GS's page-block table (`_BLOCK8`, the same
# table the 8-bit texture swizzle uses) interleaves them.  Taking the blocks row-major instead puts
# every 8x8 block in the wrong place: the decoded frame is the right picture with each block
# displaced, which reads as an 8-pixel "checkerboard" scramble and cost a session of per-pixel
# analysis. Within each block, GS columnTable32 interleaves
# two rows at a time; row-major words also scramble the pixels.
_BLOCK32 = [[0, 1, 4, 5, 16, 17, 20, 21], [2, 3, 6, 7, 18, 19, 22, 23],
            [8, 9, 12, 13, 24, 25, 28, 29], [10, 11, 14, 15, 26, 27, 30, 31]]


def frame_pixels(vram, fbp=0, fbw=10):
    """The framebuffer the GS displayed, out of the dump's VRAM (PSMCT32, FBW 640, FBP 0).

    `fbp`/`fbw` come from the `CTXT0.FRAME` register (FBP is in units of a 2048-word page, FBW in
    pages of 64 pixels). FRAME can name a partly drawn back buffer: do not assume
    it is the displayed buffer or that the double-buffered twin is identical."""
    u32 = np.frombuffer(vram, dtype="<u4")
    out = np.zeros((H, W, 3), np.float32)
    for y in range(H):
        row = fbp + (y >> 5) * fbw
        for x in range(W):
            page = row + (x >> 6)
            col, r = x & 63, y & 31
            inner=(col&1)+((r&1)<<1)+((col&6)<<1)+((r&6)<<3)
            a = page * 2048 + _BLOCK32[(r >> 3)][(col >> 3)] * 64 + inner
            v = int(u32[a])
            out[y, x] = (v & 0xff, (v >> 8) & 0xff, (v >> 16) & 0xff)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dump", required=True)
    ap.add_argument("--tex0", type=lambda s: int(s, 0), action="append", required=True)
    ap.add_argument("--out-dir", default="/tmp/raster")
    a = ap.parse_args()

    d = gsdump.read_dump(a.dump)
    draws = list(gsdump.draws(d))
    tex0s = set(a.tex0)

    texcache = {}

    def gstex(t0):
        if t0 not in texcache:
            rgba, w, h, _f = gsdump.texture_rgba(d, t0)
            texcache[t0] = np.frombuffer(rgba, dtype=np.uint8).reshape(h, w, 4)[:, :, :3].astype(np.float32)
        return texcache[t0]

    tris = []
    for x in draws:
        t0 = x["state"].get(6)
        if t0 not in tex0s:
            continue
        vs = x["verts"]
        pt = x["state"].get("PRIM_EFF", 0) & 7

        def V(v):
            s, t, q = v["ST"]
            return (v["XYZ"][0] / 16.0 - OFX, v["XYZ"][1] / 16.0 - OFY, v["XYZ"][2], s, t, q,
                    v["RGBA"][0] * 2.0, v["RGBA"][1] * 2.0, v["RGBA"][2] * 2.0)
        if pt == 5:
            for k in range(len(vs) - 2):
                tris.append((V(vs[0]), V(vs[k + 1]), V(vs[k + 2]), t0))
        else:
            for k in range(len(vs) - 2):
                if k % 2 == 0:
                    tris.append((V(vs[k]), V(vs[k + 1]), V(vs[k + 2]), t0))
                else:
                    tris.append((V(vs[k + 1]), V(vs[k]), V(vs[k + 2]), t0))
    print("triangles:", len(tris))

    shade = np.zeros((H, W, 3), np.float32)
    texel = np.zeros((H, W, 3), np.float32)
    zbuf = np.zeros((H, W), np.int64)          # GEQUAL: the first fragment (z >= 0) always passes
    for (p, q, r, t0) in tris:
        ax, ay = p[0], p[1]
        bx, by = q[0], q[1]
        cx, cy = r[0], r[1]
        det = (bx - ax) * (cy - ay) - (cx - ax) * (by - ay)
        if abs(det) < 1e-9:
            continue
        x0 = max(0, int(math.floor(min(ax, bx, cx))))
        x1 = min(W - 1, int(math.ceil(max(ax, bx, cx))))
        y0 = max(0, int(math.floor(min(ay, by, cy))))
        y1 = min(H - 1, int(math.ceil(max(ay, by, cy))))
        if x1 < x0 or y1 < y0:
            continue
        PX, PY = np.meshgrid(np.arange(x0, x1 + 1) + 0.5, np.arange(y0, y1 + 1) + 0.5)
        # Barycentric weights with their vertex: `wa` is p's (first), `wb` q's, `wc` r's.  The
        # cross-product form puts the *third* vertex's weight in the first expression, so the
        # three must be paired back as (wa, wb, wc) = (w2, w1, w0); pairing `w0` with `p` instead
        # swaps the first and third corners, which mirrors every interpolated attribute (finding
        #).
        wc = ((bx - ax) * (PY - ay) - (PX - ax) * (by - ay)) / det
        wb = ((PX - ax) * (cy - ay) - (cx - ax) * (PY - ay)) / det
        wa = 1.0 - wc - wb
        m = (wa >= -0.002) & (wb >= -0.002) & (wc >= -0.002)
        if not m.any():
            continue
        z = wa * p[2] + wb * q[2] + wc * r[2]
        sub = zbuf[y0:y1 + 1, x0:x1 + 1]
        upd = m & (z >= sub)
        if not upd.any():
            continue
        for ch in range(3):
            shade[y0:y1 + 1, x0:x1 + 1, ch][upd] = (wa * p[6 + ch] + wb * q[6 + ch] + wc * r[6 + ch])[upd]
        S = wa * p[3] + wb * q[3] + wc * r[3]
        T = wa * p[4] + wb * q[4] + wc * r[4]
        Q = wa * p[5] + wb * q[5] + wc * r[5]
        Q = np.where(np.abs(Q) < 1e-9, 1e-9, Q)
        tex = gstex(t0)
        ht, wt = tex.shape[:2]
        fx = np.clip((S / Q) * wt - 0.5, 0, wt - 1)
        fy = np.clip((T / Q) * ht - 0.5, 0, ht - 1)
        ix0 = np.floor(fx).astype(int)
        iy0 = np.floor(fy).astype(int)
        fax = (fx - ix0)[..., None]
        fay = (fy - iy0)[..., None]
        ix1 = np.minimum(ix0 + 1, wt - 1)
        iy1 = np.minimum(iy0 + 1, ht - 1)
        col = (tex[iy0, ix0] * (1 - fax) * (1 - fay) + tex[iy0, ix1] * fax * (1 - fay)
               + tex[iy1, ix0] * (1 - fax) * fay + tex[iy1, ix1] * fax * fay)
        for ch in range(3):
            texel[y0:y1 + 1, x0:x1 + 1, ch][upd] = col[:, :, ch][upd]
        sub[upd] = z[upd]

    os.makedirs(a.out_dir, exist_ok=True)
    frame = frame_pixels(gsdump.read_state(d)["VRAM"])
    for name, arr in (("shade", shade), ("texel", texel), ("frame", frame)):
        np.save(os.path.join(a.out_dir, name + ".npy"), arr)
        Image.fromarray(np.clip(arr, 0, 255).astype(np.uint8)).save(
            os.path.join(a.out_dir, name + ".png"))

    print("region    shade(2Cv)            texel                   frame")
    for nm, (x0, y0, x1, y1) in BOXES:
        sl = (slice(y0, y1), slice(x0, x1))
        mm = texel[sl].mean(axis=2) > 10
        def mo(arr):
            v = arr[sl][mm] if mm.any() else arr[sl].reshape(-1, 3)
            return " ".join("%5.1f" % c for c in v.mean(axis=0))
        print("%-8s  %-20s  %-20s  %-20s" % (nm, mo(shade), mo(texel), mo(frame)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
