#!/usr/bin/env python3
"""fit_light_rig.py — fit the port's light rig against a game frame.

The rig is a **fit, not a decode**: `docs/engine/p2-lighting.md` records that the values the game
feeds `p2lighting` are written into runtime descriptors from the scene at load time, are absent from
every pack, and are empty in every savestate.  So the port carries a baked default and this tool
fits it by driving `build/dw4asset render` as a black box and minimising the mean absolute
difference against a reference frame.

**Use `tools/frame_metric.py`'s rescaling** (finding #573): the reference is a 640x480 PCSX2
screenshot of a 640x448 framebuffer, so it is resampled to the frame's size before comparing.  The
rig that was fitted without that correction came out degenerate -- it was driven by the floor and
wall, whose normals barely vary, and the up-facing facets of the flat-shaded props clipped to white.

    # one frame, the boxes the P4.4 table reports, nine parameters
    tools/fit_light_rig.py --ref <reference>.png \\
        --cmd './build/dw4asset render --stage ~/local/extracted stag0101.igb --ref 1 \\
               --scene /tmp/cam.tsv --livedump <ee-dump>.bin \\
               --pack2 ~/local/extracted/NDMW.AFS:861 --texdir /tmp/proptex \\
               --view "0.5 0.495845 0.710027 0 0 0.819868 -0.572552 0 -0.866025 0.286276 \\
                       0.409934 0 -115.58885 -299.804123 -223.409985 1" \\
               --fov 0.6912 --aspect 1.0 --w 640 --h 448 {rig} --out /tmp/fit/f.png'

`{rig}` expands to `--light dir,0,0,0,dx,dy,dz,dr,dg,db --amb ar,ag,ab`.  `--keys` selects the boxes
in the objective (repeat a name to weight it); `--wide` frees the three diffuse channels instead of
scaling one key colour.  The result prints as a SPEC plus the default rig's source values.
"""
import argparse
import math
import os
import subprocess
import sys
import tempfile

try:
    import numpy as np
    from PIL import Image
except ImportError:
    np = None


def phrase(spec, amb):
    """'--light SPEC --amb R,G,B', shell-quoted for the template."""
    return "--light %s --amb %s" % (spec, amb)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ref", required=True, help="the reference screenshot (any size)")
    ap.add_argument("--cmd", required=True, help="the render command, with a {rig} placeholder")
    ap.add_argument("--keys", default="whole,floor,wall,barrel,crate",
                    help="boxes in the objective, comma separated (repeat to weight)")
    ap.add_argument("--wide", action="store_true", help="free the diffuse channels (9 params)")
    ap.add_argument("--start", default="60,90,1.15,0.25,0.20,0.35",
                    help="start point: elev,azim,diffuse,amb_r,amb_g,amb_b (scalar form)")
    ap.add_argument("--maxiter", type=int, default=1200)
    ap.add_argument("--out", help="write the fitted rig as a SPEC/ambient pair")
    a = ap.parse_args()

    if np is None:
        print("fit_light_rig: needs numpy and Pillow")
        return 2
    from PIL import Image as I

    here = os.path.dirname(os.path.abspath(__file__))
    port = os.path.dirname(here)
    work = tempfile.mkdtemp(prefix="fit_rig_")
    # `{out}` is a directory: the render's scene path writes `frame_0000.png` into `--out-dir`.  A
    # single-model render, which takes `--out FILE`, lands in the same place if pointed at it.
    cmd = a.cmd.replace("{out}", work)

    def frame_path():
        for cand in (os.path.join(work, "frame_0000.png"), os.path.join(work, "f.png")):
            if os.path.exists(cand):
                return cand
        return None

    # the boxes tools/frame_metric.py uses, so the two tools agree
    sys.path.insert(0, here)
    import frame_metric
    boxes = dict(frame_metric.BOXES)

    ref_img = I.open(a.ref).convert("RGB")
    state = {"size": None, "ref": None, "calls": 0}

    def render(p):
        elev, azim, dr, dg, db, ar, ag, ab = p
        e, az = math.radians(elev), math.radians(azim)
        stl = (math.cos(e) * math.cos(az), math.sin(e), math.cos(e) * math.sin(az))
        spec = "dir,0,0,0,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f" % (
            -stl[0], -stl[1], -stl[2], dr, dg, db)
        amb = "%.5f,%.5f,%.5f" % (ar, ag, ab)
        full = cmd.replace("{rig}", phrase(spec, amb))
        r = subprocess.run(full, shell=True, cwd=port, capture_output=True, text=True)
        fp = frame_path()
        if not fp:
            raise SystemExit("fit_light_rig: the render produced no frame\n%s\n%s"
                             % (r.stdout[-2000:], r.stderr[-2000:]))
        state["calls"] += 1
        return np.asarray(I.open(fp).convert("RGB")).astype(np.float64)

    def objective(p):
        img = render(p)
        if state["size"] is None:
            state["size"] = (img.shape[1], img.shape[0])
            state["ref"] = np.asarray(
                frame_metric.resample(ref_img, state["size"])).astype(np.float64)
        d = np.abs(state["ref"] - img).mean(2)
        vals = []
        for k in a.keys.split(","):
            x0, y0, x1, y1 = boxes[k]
            vals.append(d[y0:y1, x0:x1].mean())
        return float(np.mean(vals))

    from scipy.optimize import minimize
    start = [float(v) for v in a.start.split(",")]
    if a.wide and len(start) == 6:          # a scalar key colour expands to three channels
        start = start[:2] + [start[2], start[2] * 0.96, start[2] * 1.05] + start[3:]
    if len(start) != (8 if a.wide else 6):
        raise SystemExit("fit_light_rig: --start wants 6 values (scalar) or 8 with --wide")
    print("start objective %.3f" % objective(start))
    res = minimize(objective, np.array(start, float), method="Nelder-Mead",
                   options={"maxiter": a.maxiter, "maxfev": a.maxiter + 400,
                            "xatol": 0.004, "fatol": 0.004})
    p = res.x
    if not a.wide:
        p = list(p[:2]) + [p[2], p[2] * 0.96, p[2] * 1.05] + list(p[3:])
    img = render(p)
    size = (img.shape[1], img.shape[0])
    ref = np.asarray(frame_metric.resample(ref_img, size)).astype(np.float64)
    d = np.abs(ref - img).mean(2)
    print("evals %d  objective %.3f" % (state["calls"], res.fun))
    for k in ("whole", "floor", "wall", "barrel", "crate"):
        x0, y0, x1, y1 = boxes[k]
        print("  %-7s %.2f" % (k, d[y0:y1, x0:x1].mean()))
    e, az = math.radians(p[0]), math.radians(p[1])
    stl = (math.cos(e) * math.cos(az), math.sin(e), math.cos(e) * math.sin(az))
    spec = "dir,0,0,0,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f" % (
        -stl[0], -stl[1], -stl[2], p[2], p[3], p[4])
    amb = "%.4f,%.4f,%.4f" % (p[5], p[6], p[7])
    print("SPEC %s\nAMB  %s" % (spec, amb))
    print("(elev %.1f deg, azim %.1f deg)" % (p[0], p[1]))
    if a.out:
        with open(a.out, "w") as f:
            f.write("# fitted by tools/fit_light_rig.py, keys %s, reference %s\n" % (a.keys, a.ref))
            f.write("# %s\n# %s\n" % (spec, amb))
        print("wrote", a.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
