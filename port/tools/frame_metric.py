#!/usr/bin/env python3
"""frame_metric.py — score a rendered frame against a reference, at the reference's true scale.

The port renders the PS2's 640x448 framebuffer; a PCSX2 savestate screenshot of it is **640x480**,
because the screenshot is the 448-line image scaled by 480/448.  Comparing the screenshot's top 448
rows against the port's 448 rows therefore mixes two vertical scales: it inflates every number and
it moves features (finding #573 measured the whole-frame mean |delta| falling 24.73 -> 19.26, and
the floor 20.51 -> 9.45, once the reference is rescaled).  So this tool always **resamples the
reference to the frame's size** before comparing -- a no-op for a reference that is already 640x448.

    tools/frame_metric.py --ref ../local/captures/.../real-goblin-pass.png FRAME.png [FRAME2.png ...]
    tools/frame_metric.py --ref REF --json out.json FRAME.png
    tools/frame_metric.py --self-test          # no game data needed; runs in `make check`

A metric is the mean absolute per-channel difference over a box (0..255, lower is better).  The
named boxes are the ones the tracker's P4.4 table uses, in the reference's own pixel space.
"""
import argparse
import json
import sys

try:
    import numpy as np
    from PIL import Image
except ImportError:  # the tool is optional; `make check` skips it without Pillow
    np = None
    Image = None

# The regions the P4.4 table reports, in the reference frame's coordinates (640x448).
BOXES = [
    ("whole", (0, 0, 640, 448)),
    ("floor", (260, 330, 420, 420)),
    ("wall", (120, 60, 250, 110)),
    ("barrel", (135, 120, 225, 245)),
    ("crate", (210, 120, 300, 240)),
    ("character", (264, 122, 366, 236)),
]


def resample(img, size):
    """The reference resampled to `size` -- see the module docstring.  A no-op when it matches."""
    return img if img.size == size else img.resize(size, Image.BILINEAR)


def load_reference(path, size):
    return np.asarray(resample(Image.open(path).convert("RGB"), size)).astype(np.float64)


def load_frame(path, size):
    img = Image.open(path).convert("RGB")
    if img.size != size:
        raise SystemExit("frame_metric: %s is %dx%d, expected %dx%d -- the port renders the "
                         "framebuffer, so a differently-sized frame is not comparable"
                         % (path, img.width, img.height, size[0], size[1]))
    return np.asarray(img).astype(np.float64)


def blur(img, sigma):
    """Gaussian blur both sides of a comparison, so the metric scores the scale the shading lives
    at.  The game's framebuffer carries a +-4 ordered dither (finding #588) and the port's render
    does not, so a pixel-exact |d| against the native framebuffer is dominated by that dither; a
    known-good fallback is scipy, and without it the blur is skipped rather than faked."""
    if not sigma:
        return img
    try:
        from scipy.ndimage import gaussian_filter
    except ImportError:
        return img
    return gaussian_filter(img, (sigma, sigma, 0.0))


def score(ref, frame):
    d = np.abs(ref - frame).mean(2)
    out = {}
    for name, (x0, y0, x1, y1) in BOXES:
        if x1 > d.shape[1] or y1 > d.shape[0]:
            continue
        out[name] = float(d[y0:y1, x0:x1].mean())
    return out


def self_test():
    """The rescale is the whole point, so check it: a 640x480 reference that is a 448-line image
    stretched by 480/448 must score ~0 against that 448-line image once resampled."""
    base = np.zeros((448, 640, 3), np.uint8)
    for y in range(448):
        base[y, :, :] = (y * 255) // 447           # a vertical ramp: any scale error shows up
    small = Image.fromarray(base)
    stretched = small.resize((640, 480), Image.BILINEAR)
    ref = resample(stretched, (640, 448))
    d = np.abs(np.asarray(ref).astype(np.float64) - base.astype(np.float64)).mean()
    # Without the rescale the same pair differs by a lot, which is what #573 was.
    naive = np.abs(np.asarray(stretched)[:448].astype(np.float64) - base).mean()
    ok = d < 1.0 and naive > 5.0
    print("  self-test: resampled %.3f, raw-top-448 %.3f -> %s" % (d, naive, "ok" if ok else "BAD"))
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("frames", nargs="*", help="rendered frame(s), 640x448")
    ap.add_argument("--ref", help="the reference screenshot (any size; resampled to the frame's); "
                                   "a native 640x448 frame -- e.g. gs_shade_raster.py's frame.png -- "
                                   "is used as-is, which is the better ground truth")
    ap.add_argument("--blur", type=float, default=0.0,
                    help="gaussian sigma applied to the reference and every frame (finding #591: "
                         "~1.2 px removes the framebuffer's dither; 0 keeps the raw pixel metric)")
    ap.add_argument("--json", help="write the table as JSON to this path")
    ap.add_argument("--self-test", action="store_true")
    a = ap.parse_args()

    if np is None or Image is None:
        if a.self_test:
            print("  metrics: numpy/Pillow not available, skipped")
            return 0
        print("frame_metric: needs numpy and Pillow")
        return 2
    if a.self_test:
        return self_test()
    if not a.ref or not a.frames:
        ap.error("--ref and at least one frame are required")

    f0 = Image.open(a.frames[0])
    size = f0.size
    ref = blur(load_reference(a.ref, size), a.blur)
    rows = []
    print("%-42s %s" % ("frame", " ".join("%7s" % n for n, _ in BOXES)))
    for path in a.frames:
        frame = blur(load_frame(path, size), a.blur)
        m = score(ref, frame)
        rows.append({"frame": path, "metrics": m})
        print("%-42s %s" % (path.rsplit("/", 1)[-1],
              " ".join("%7.2f" % m.get(n, float("nan")) for n, _ in BOXES)))
    if a.json:
        with open(a.json, "w") as f:
            json.dump({"reference": a.ref, "size": list(size), "boxes": BOXES, "rows": rows},
                      f, indent=1)
        print("wrote", a.json)
    return 0


if __name__ == "__main__":
    sys.exit(main())
