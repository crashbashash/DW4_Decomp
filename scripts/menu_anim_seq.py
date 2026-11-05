#!/usr/bin/env python3
"""Build the main menu's animation sequence for the port's `--ui-seq`.

The menu's animation is the engine regenerating its *additive* light-trail layer every frame: nothing
rotates, zooms or flows (angular and radial profiles over 1.4 s correlate 0.97-0.99), but the
additive draws change count per frame (384 / 850 / 808 in three consecutive captures) and almost none
survive from one frame to the next.  So it cannot be reproduced as a transform of one picture; it is
replayed here as a sequence of captured frames.

The input is a text file listing `.gs.zst` captures of consecutive menu frames, in order, one path per
line.  The ceiling is PCSX2's screenshot rate, ~190 ms per GS dump (measured 5.2 fps).

    python3 scripts/menu_anim_seq.py --frames frames.txt --out <out-dir>

Writes `<out>/uiNNN.tsv` (one full frame per capture, in draw order, perspective-correct `#stq` form)
and `<out>/tex/<TEX0>.rgba` (a shared texture set -- the textures are byte-identical across frames).
Run the port against it with `--ui-seq <out> --uitex <out>/tex --ui-seq-fps <capture rate>`.
"""
import argparse
import os
import shutil
import subprocess
import sys

ap = argparse.ArgumentParser()
ap.add_argument("--frames", required=True, help="a text file listing the .gs.zst captures, in order")
ap.add_argument("--out", required=True, help="where the sequence goes")
ap.add_argument("--gsui", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "gs_ui.py"))
a = ap.parse_args()

files = [l.strip() for l in open(a.frames) if l.strip()]
if not files:
    sys.exit("no frames in %s" % a.frames)
src = os.path.join(a.out, ".src")
shutil.rmtree(src, ignore_errors=True)
os.makedirs(src, exist_ok=True)
os.makedirs(os.path.join(a.out, "tex"), exist_ok=True)

for i, f in enumerate(files):
    d = os.path.join(src, "f%03d" % i)
    r = subprocess.run([sys.executable, a.gsui, "--dump", f, "--out", d, "--stq"],
                       capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit("frame %d (%s):\n%s" % (i, f, (r.stdout + r.stderr)[-500:]))
    rows = [l.rstrip("\n") for l in open(os.path.join(d, "ui.tsv")) if not l.startswith("#")]
    with open(os.path.join(a.out, "ui%03d.tsv" % i), "w") as o:
        o.write("#stq\n" + "\n".join(rows) + "\n")
    if i == 0:
        for p in os.listdir(d):
            if p.endswith(".rgba"):
                shutil.copy(os.path.join(d, p), os.path.join(a.out, "tex", p))
shutil.rmtree(src, ignore_errors=True)
print("wrote %d frames to %s (textures: %d)" % (len(files), a.out, len(os.listdir(os.path.join(a.out, "tex")))))
