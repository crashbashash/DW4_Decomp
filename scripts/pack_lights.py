#!/usr/bin/env python3
"""pack_lights.py — read a pack's `igLightAttr` records (the game's light rig).

`p2-lighting.md` recorded the light values as "not in the disc": the *runtime* globals
(`0x56AF40`, `0x56AF94`) are empty in a savestate because they are populated only during the render
pass.  But the **source** objects are ordinary `igLightAttr` records in the common packs -- a
scan of class *directories* finds 0 and misses them.  Every common
pack (179/187/195/203/210/218 ...) carries the same three lights, i.e. the engine's standard rig:

    lightType 0  ambient  (0.4, 0.4, 0.45)          -- the ambient term
    lightType 0  diffuse  (0.8, 0.8, 1.1)           -- bluish key, dir (0.2424, -0.8192, -0.5198)
    lightType 2  diffuse  (1, 1, 1)                 -- white overhead spot at (0, 90, 0), 30 deg

Write the lights (one SPEC per line) and the ambient value with `--emit`.

    python3 pack_lights.py --pack <roms>/NDMW.AFS:187 --list
    python3 pack_lights.py --pack <roms>/NDMW.AFS:187 --emit /tmp/rig.txt
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DECOMP = os.environ.get("DW4_DECOMP", os.path.join(os.path.dirname(HERE)))
sys.path.insert(0, os.path.join(DECOMP, "scripts"))
import igb_ids  # noqa: E402
import igb_pool  # noqa: E402

ig = igb_ids.igb_inst

TYPE = {0: "dir", 1: "point", 2: "spot", 3: "spot"}


def load(pack, decomp):
    afs, entry = pack.rsplit(":", 1)
    refl = ig.load_reflection(os.path.join(decomp, "data", "reflection.json"))
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * int(entry):12 + 8 * int(entry)], "little")
    P = igb_pool.load(afs, hex(off), refl)
    dirs, _ = ig.parse_directory(P["b"])
    return P, dirs, refl


def lights(P, dirs, refl):
    out = []
    for r in P["s2"]:
        if r["class"] != "igLightAttr":
            continue
        rr = ig.decode_record(P["b"], r["off"], dirs, refl)
        if rr:
            out.append({n: v for n, v, _t in rr["fields"]})
    return out


def spec(f):
    """A `--light` SPEC: type,pos xyz,dir xyz,diffuse rgb,specular rgb,range,shininess,falloff,cutoff."""
    t = TYPE.get(int(f.get("_lightType") or 0), "dir")
    p, d = f.get("_position") or [0, 0, 0], f.get("_direction") or [0, 0, 0]
    di, sp = f.get("_diffuse") or [0, 0, 0, 1], f.get("_specular") or [0, 0, 0, 1]
    v = ([p[0], p[1], p[2], d[0], d[1], d[2], di[0], di[1], di[2], sp[0], sp[1], sp[2]]
         + [0.0, float(f.get("_shininess") or 16.0), float(f.get("_falloff") or 0.0),
            float(f.get("_cutoff") or 0.0)])
    return t + "," + ",".join("%g" % x for x in v)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--pack", required=True, metavar="AFS:ENTRY")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--emit", metavar="FILE", help="write the lights to FILE")
    ap.add_argument("--decomp", default=DECOMP)
    a = ap.parse_args()

    P, dirs, refl = load(a.pack, a.decomp)
    ls = lights(P, dirs, refl)
    amb = [0.4, 0.4, 0.45]
    for f in ls:
        if (f.get("_diffuse") or [0, 0, 0])[:3] == [0.0, 0.0, 0.0]:
            amb = (f.get("_ambient") or amb)[:3]
    for f in ls:
        print("  type %s  amb %s  dif %s  spec %s  dir %s  pos %s  cutoff %s falloff %s"
              % (f.get("_lightType"), f.get("_ambient"), f.get("_diffuse"), f.get("_specular"),
                 f.get("_direction"), f.get("_position"), f.get("_cutoff"), f.get("_falloff")))
    print("  ambient (%g, %g, %g)   %d light(s)" % (amb[0], amb[1], amb[2], len(ls)))
    if a.emit:
        with open(a.emit, "w") as fh:
            fh.write("# the game's light rig, from the igLightAttr records of %s\n" % a.pack)
            fh.write("# --ambient %g,%g,%g\n" % (amb[0], amb[1], amb[2]))
            for f in ls:
                fh.write(spec(f) + "\n")
        print("  wrote", a.emit)
    return 0


if __name__ == "__main__":
    sys.exit(main())
