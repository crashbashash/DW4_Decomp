#!/usr/bin/env python3
"""compare_retail_frames.py -- measure the shop-window layout of port frames against retail captures.

The Digi-Lab, Data Keeper and Chip Shop screens were first compared with retail "by eye".  This tool
puts numbers on that comparison.  It never contains retail pixels: both directories are arguments.

    tools/compare_retail_frames.py RETAIL_DIR PORT_DIR [--pair NAME ...] [--json OUT] [--overlay DIR]
    tools/compare_retail_frames.py --self-test

RETAIL_DIR holds PCSX2 GS captures named `rc-<id>.png` (640x480: the 640x448 framebuffer scaled by
480/448).  PORT_DIR holds the frames `test_hublabo`, `test_hubtalk` and `test_hubshops` write
(`xdata-*.png` CPU, `gpu-*.png` GPU; 640x448).  Every port frame is resampled to 640x480 (bilinear),
so all coordinates below are in the retail capture's 640x480 space.  Pairs whose files are missing
are reported as skipped.

Masks (applied to both frames; a pixel masked in either is ignored):

* **backdrop**: the animated green `j_shback` backdrop and its drifting shapes differ in phase between
  any two frames.  A pixel is backdrop when green dominates: G >= 24, G > R + 16 and G > 1.6 * B.
  The navy window interiors (B > G), the cyan frames and white text never pass that test; window
  interiors are translucent but dark enough (G < 24) to stay unmasked.
* **data**: per-pair rectangles holding content that legitimately differs between the retail save
  (level-99 Susanomon "BigDaddy", 99999/9999 stats) and the port's test records: the player name,
  level and portrait, stat numbers, list rows, prices, the description text.  They are excluded from
  the chrome difference (`mad`) only; the geometry measures below use the whole region, since a
  frame line or a text row is at the same place whatever the text says.

Per region (a window, band or text block) the tool reports:

* `dx`, `dy`: the shift that best aligns the port's edge map with the retail one (normalised
  cross-correlation of Sobel magnitudes over +-8 px, refined to 0.1 px by a parabola).  Positive
  means the port content sits right of / below retail.  `ncc` is the peak correlation (1 = identical
  edges); a low peak means the region's content differs too much for the shift to be trusted.
* `edges`: the strongest horizontal and vertical frame lines (rows/columns whose edge sum is a
  local maximum above half the region's peak) in retail and port, which locates window borders
  and bands independently of the correlation.
* `rows`: text rows (runs of rows with bright, low-saturation pixels) in a text region, as
  top..bottom pairs, so baselines can be compared row by row.
* `mad`: mean absolute difference of luminance (0..255) over the region's chrome pixels (neither
  mask), after both regions are normalised to the same mean and spread, plus the same at the
  best shift (`mad@shift`).

`--overlay DIR` writes a retail/port blend per pair (for a private scratch directory, not the
repository).
"""
import argparse
import json
import os
import sys

try:
    import numpy as np
    from PIL import Image
except ImportError:
    np = None
    Image = None

W, H = 640, 480

# Shared chrome (all shop roots): compact player base, header, legend, bottom band.
TOP = [
    ("base", (8, 4, 212, 76), [(70, 10, 210, 72)]),           # name, level, portrait
    ("header", (212, 8, 445, 48), []),
    ("legend", (448, 8, 634, 74), []),
]
BAND = ("band", (0, 436, 640, 472), [(16, 440, 640, 468)])     # instruction text differs per state
# STATUS left panel used by the Data Keeper / Chip Shop roots and the lab's equipment check.
PANEL = [
    ("panel-name", (8, 76, 174, 104), [(14, 78, 170, 102)]),
    ("panel-hpmp", (8, 104, 174, 154), [(40, 106, 170, 152)]),
    ("panel-stats", (8, 154, 174, 360), [(110, 156, 170, 358)]),
    ("panel-bits", (8, 360, 174, 432), [(80, 362, 170, 430)]),
]
DESC = ("desc", (228, 372, 640, 440), [(236, 378, 640, 436)])

PAIRS = {
    # name: (retail id, port file, [(region, box, data rects)], [(text region, box)])
    "lab-menu": ("labf1", "xdata-labo-menu.png",
                 TOP + [("talk", (0, 326, 640, 472), [])],
                 [("talk-rows", (24, 340, 400, 440))]),
    "lab-back": ("q1", "gpu-labo-back.png",
                 TOP + [("talk", (0, 326, 640, 472), [])],
                 [("talk-rows", (24, 340, 400, 440))]),
    "lab-list": ("labg0", "xdata-labo-list.png",
                 TOP + [("list", (8, 108, 274, 310), [(20, 140, 268, 306)]),
                        ("details", (274, 156, 634, 374), [(380, 186, 456, 350), (520, 186, 630, 372)]),
                        DESC, BAND],
                 [("list-rows", (30, 140, 268, 306)), ("details-rows", (288, 186, 456, 372)),
                  ("desc-rows", (240, 376, 640, 440)), ("band-rows", (16, 444, 640, 470))]),
    "lab-same": ("labg1", "xdata-labo-same.png",
                 TOP + [("list", (8, 108, 274, 310), [(20, 140, 268, 306)]),
                        ("details", (274, 156, 634, 374), [(380, 186, 456, 350), (520, 186, 630, 372)]),
                        ("notice", (228, 372, 640, 440), [(600, 420, 630, 436)]), BAND],
                 [("notice-rows", (240, 376, 640, 418)), ("band-rows", (16, 444, 640, 470))]),
    "lab-check": ("lw0", "xdata-labo-check.png",
                  TOP + PANEL + [("slots", (206, 48, 330, 104), []), DESC, BAND],
                  [("slot-rows", (212, 52, 330, 104)), ("panel-rows", (12, 156, 110, 358)),
                   ("desc-rows", (240, 376, 640, 440)), ("band-rows", (16, 444, 640, 470))]),
    "chip-list": ("chipb0", "xdata-chip-list.png",
                  TOP + PANEL + [("chip-list", (172, 78, 412, 348), [(196, 100, 404, 344)]),
                                 ("chip-price", (408, 84, 560, 348), [(414, 100, 556, 344)]),
                                 ("chip-page", (480, 346, 560, 372), []), DESC, BAND],
                  [("chip-rows", (200, 100, 404, 344)), ("band-rows", (16, 444, 640, 470))]),
    "chip-list-m": ("chipm1", "xdata-chip-list.png",
                    TOP + PANEL + [("chip-list", (172, 78, 412, 348), [(196, 100, 404, 344)]),
                                   ("chip-price", (408, 84, 560, 348), [(414, 100, 556, 344)]),
                                   ("chip-page", (480, 346, 560, 372), []), BAND],
                    [("chip-rows", (200, 100, 404, 344))]),
    "chip-quote": ("v1", "xdata-chipquote.png",
                   TOP + PANEL + [("dk-list", (172, 76, 408, 348), [(180, 100, 404, 344)]),
                                  ("dk-data", (408, 76, 560, 348), [(414, 100, 556, 344)]),
                                  ("quote", (228, 372, 640, 440), [(236, 376, 640, 436)]), BAND],
                   [("quote-rows", (240, 376, 640, 436))]),
    "dk-chrome": ("dkm0", "xdata-stats.png",
                  TOP + PANEL, [("panel-rows", (12, 156, 110, 358))]),
}

MAX_SHIFT = 8


def load(path, scale):
    img = Image.open(path).convert("RGB")
    if img.size != (W, H):
        if not scale:
            raise SystemExit("%s is %dx%d, expected %dx%d" % (path, img.width, img.height, W, H))
        img = img.resize((W, H), Image.BILINEAR)
    return np.asarray(img).astype(np.float64)


def luminance(rgb):
    return rgb[..., 0] * 0.299 + rgb[..., 1] * 0.587 + rgb[..., 2] * 0.114


def backdrop_mask(rgb):
    r, g, b = rgb[..., 0], rgb[..., 1], rgb[..., 2]
    return (g >= 24) & (g > r + 16) & (g > 1.6 * b)


def text_mask(rgb):
    """Bright, low-saturation pixels: the white/grey glyphs of every shop font."""
    mx, mn = rgb.max(axis=2), rgb.min(axis=2)
    return (mx >= 150) & (mx - mn <= 70)


def sobel(lum):
    p = np.pad(lum, 1, mode="edge")
    gx = (p[:-2, 2:] + 2 * p[1:-1, 2:] + p[2:, 2:]) - (p[:-2, :-2] + 2 * p[1:-1, :-2] + p[2:, :-2])
    gy = (p[2:, :-2] + 2 * p[2:, 1:-1] + p[2:, 2:]) - (p[:-2, :-2] + 2 * p[:-2, 1:-1] + p[:-2, 2:])
    return np.abs(gx), np.abs(gy)


def crop(a, box, pad=0):
    x0, y0, x1, y1 = box
    return a[max(0, y0 - pad):min(H, y1 + pad), max(0, x0 - pad):min(W, x1 + pad)]


def parabola(m, c, p):
    d = m - 2 * c + p
    return 0.0 if d == 0 else 0.5 * (m - p) / d


def best_shift(ref, mov, box):
    """(dx, dy, ncc): shift of `mov` relative to `ref` inside `box` (both full-frame edge maps)."""
    x0, y0, x1, y1 = box
    r = ref[y0:y1, x0:x1]
    r = r - r.mean()
    rn = np.sqrt((r * r).sum())
    if rn == 0:
        return None
    s = MAX_SHIFT
    scores = np.full((2 * s + 1, 2 * s + 1), -1.0)
    for dy in range(-s, s + 1):
        for dx in range(-s, s + 1):
            ya, yb, xa, xb = y0 + dy, y1 + dy, x0 + dx, x1 + dx
            if ya < 0 or xa < 0 or yb > H or xb > W:
                continue
            m = mov[ya:yb, xa:xb]
            m = m - m.mean()
            mn = np.sqrt((m * m).sum())
            if mn:
                scores[dy + s, dx + s] = (r * m).sum() / (rn * mn)
    iy, ix = np.unravel_index(np.argmax(scores), scores.shape)
    fx = fy = 0.0
    if 0 < ix < 2 * s and scores[iy, ix - 1] > -1 and scores[iy, ix + 1] > -1:
        fx = parabola(scores[iy, ix - 1], scores[iy, ix], scores[iy, ix + 1])
    if 0 < iy < 2 * s and scores[iy - 1, ix] > -1 and scores[iy + 1, ix] > -1:
        fy = parabola(scores[iy - 1, ix], scores[iy, ix], scores[iy + 1, ix])
    return ix - s + fx, iy - s + fy, float(scores[iy, ix])


def lines(edge, box, axis):
    """Frame lines in `box`: rows (axis=1 sums along x) or columns (axis=0) with strong edge sums."""
    prof = crop(edge, box).sum(axis=axis)
    if prof.max() <= 0:
        return []
    thr = 0.5 * prof.max()
    out = []
    for i in range(len(prof)):
        if prof[i] >= thr and (i == 0 or prof[i] >= prof[i - 1]) and (i == len(prof) - 1 or prof[i] > prof[i + 1]):
            out.append(i + (box[1] if axis == 1 else box[0]))
    return out


def text_rows(mask, box, min_px=3, min_h=5):
    prof = crop(mask, box).sum(axis=1)
    rows, start = [], None
    for i, v in enumerate(list(prof) + [0]):
        if v >= min_px and start is None:
            start = i
        elif v < min_px and start is not None:
            if i - start >= min_h:
                rows.append((start + box[1], i - 1 + box[1]))
            start = None
    return rows


def norm(v):
    sd = v.std()
    return (v - v.mean()) / sd * 40.0 + 128.0 if sd else v - v.mean() + 128.0


def chrome_mad(rl, pl, keep, box, dx=0, dy=0):
    x0, y0, x1, y1 = box
    dxi, dyi = int(round(dx)), int(round(dy))
    if y0 + dyi < 0 or x0 + dxi < 0 or y1 + dyi > H or x1 + dxi > W:
        dxi = dyi = 0
    k = keep[y0:y1, x0:x1] & keep[y0 + dyi:y1 + dyi, x0 + dxi:x1 + dxi]
    if k.sum() < 50:
        return None
    a = rl[y0:y1, x0:x1][k]
    b = pl[y0 + dyi:y1 + dyi, x0 + dxi:x1 + dxi][k]
    return float(np.abs(norm(a) - norm(b)).mean())


def compare(retail, port, regions, texts):
    rl, pl = luminance(retail), luminance(port)
    green = backdrop_mask(retail) | backdrop_mask(port)
    rl_e = rl.copy()
    pl_e = pl.copy()
    # Flatten the backdrop to a constant so its animated shapes give no edges.
    rl_e[green] = 20.0
    pl_e[green] = 20.0
    rgx, rgy = sobel(rl_e)
    pgx, pgy = sobel(pl_e)
    redge, pedge = np.hypot(rgx, rgy), np.hypot(pgx, pgy)
    rtext, ptext = text_mask(retail) & ~green, text_mask(port) & ~green
    out = {"regions": {}, "text": {}}
    for name, box, data in regions:
        keep = ~green
        for d in data:
            keep[d[1]:d[3], d[0]:d[2]] = False
        sh = best_shift(redge, pedge, box)
        res = {"box": list(box), "chrome_px": int(crop(keep, box).sum())}
        if sh:
            res.update(dx=round(sh[0], 1), dy=round(sh[1], 1), ncc=round(sh[2], 3))
        res["mad"] = chrome_mad(rl, pl, keep, box)
        if sh:
            res["mad_at_shift"] = chrome_mad(rl, pl, keep, box, sh[0], sh[1])
        res["h_lines"] = {"retail": lines(rgy, box, 1), "port": lines(pgy, box, 1)}
        res["v_lines"] = {"retail": lines(rgx, box, 0), "port": lines(pgx, box, 0)}
        out["regions"][name] = res
    for name, box in texts:
        r, p = text_rows(rtext, box), text_rows(ptext, box)
        res = {"retail": r, "port": p}
        if r and len(r) == len(p):
            res["dtop"] = [b[0] - a[0] for a, b in zip(r, p)]
            res["dbottom"] = [b[1] - a[1] for a, b in zip(r, p)]
        out["text"][name] = res
    return out


def fmt(v):
    return "-" if v is None else ("%.1f" % v if isinstance(v, float) else str(v))


def report(name, rid, pfile, res):
    print("== %s: rc-%s.png vs %s" % (name, rid, pfile))
    print("  %-12s %6s %6s %6s %7s %9s" % ("region", "dx", "dy", "ncc", "mad", "mad@shift"))
    for rn, r in res["regions"].items():
        print("  %-12s %6s %6s %6s %7s %9s" % (rn, fmt(r.get("dx")), fmt(r.get("dy")), fmt(r.get("ncc")),
                                             fmt(r.get("mad")), fmt(r.get("mad_at_shift"))))
    for rn, r in res["regions"].items():
        hl, vl = r["h_lines"], r["v_lines"]
        print("  %-12s rows retail %s port %s | cols retail %s port %s"
              % (rn, hl["retail"][:6], hl["port"][:6], vl["retail"][:6], vl["port"][:6]))
    for tn, t in res["text"].items():
        print("  %-12s text rows retail %s" % (tn, t["retail"]))
        print("  %-12s text rows port   %s" % ("", t["port"]))
        if "dtop" in t:
            print("  %-12s dtop %s dbottom %s" % ("", t["dtop"], t["dbottom"]))


def overlay(retail, port, path):
    a = Image.fromarray(retail.astype(np.uint8))
    b = Image.fromarray(port.astype(np.uint8))
    Image.blend(a, b, 0.5).save(path)


def self_test():
    """A synthetic window shifted by a known offset must be measured at that offset."""
    rng = np.random.default_rng(1)
    base = np.zeros((H, W, 3))
    base[..., 1] = 50  # green backdrop
    def window(img, x, y):
        img[y:y + 120, x:x + 200] = (0, 8, 30)
        img[y:y + 2, x:x + 200] = (150, 200, 230)
        img[y + 118:y + 120, x:x + 200] = (150, 200, 230)
        img[y:y + 120, x:x + 2] = (150, 200, 230)
        for k in range(3):
            img[y + 20 + 25 * k:y + 32 + 25 * k, x + 20:x + 120:3] = 230
        return img
    ref = window(base.copy(), 100, 100)
    mov = window(base.copy(), 103, 98)
    mov[rng.integers(0, H, 400), rng.integers(0, W, 400), 1] = 90  # backdrop noise, masked away
    res = compare(ref, mov, [("w", (90, 90, 320, 240), [])], [("t", (110, 110, 300, 200))])
    r = res["regions"]["w"]
    assert abs(r["dx"] - 3) < 0.3 and abs(r["dy"] + 2) < 0.3, r
    t = res["text"]["t"]
    assert t["dtop"] == [-2, -2, -2], t
    print("compare_retail_frames: self-test passed")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("retail_dir", nargs="?")
    ap.add_argument("port_dir", nargs="?")
    ap.add_argument("--pair", action="append", choices=sorted(PAIRS), help="limit to these pairs")
    ap.add_argument("--json", help="write all measurements as JSON")
    ap.add_argument("--overlay", help="write retail/port blends to this (scratch) directory")
    ap.add_argument("--self-test", action="store_true")
    a = ap.parse_args()
    if np is None:
        print("compare_retail_frames: numpy/Pillow not available, skipped")
        return 0
    if a.self_test:
        self_test()
        return 0
    if not a.retail_dir or not a.port_dir:
        ap.error("RETAIL_DIR and PORT_DIR are required")
    allres = {}
    for name in a.pair or PAIRS:
        rid, pfile, regions, texts = PAIRS[name]
        rp, pp = os.path.join(a.retail_dir, "rc-%s.png" % rid), os.path.join(a.port_dir, pfile)
        if not (os.path.exists(rp) and os.path.exists(pp)):
            print("== %s: skipped (missing %s)" % (name, rp if not os.path.exists(rp) else pp))
            continue
        retail, port = load(rp, False), load(pp, True)
        res = compare(retail, port, regions, texts)
        report(name, rid, pfile, res)
        allres[name] = res
        if a.overlay:
            os.makedirs(a.overlay, exist_ok=True)
            overlay(retail, port, os.path.join(a.overlay, "blend-%s.png" % name))
    if a.json:
        with open(a.json, "w") as f:
            json.dump(allres, f, indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
