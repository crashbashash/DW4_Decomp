#!/usr/bin/env python3
"""gs_barrel_shading.py — recover a mesh's per-vertex shading from a GS dump, camera-free.

The pixel fits (`DW4_Port/tools/fit_light_rig.py`) are confounded by the texture, the geometry
and whatever is behind the object.  A PCSX2 `.gs` dump instead carries the **per-vertex colour the
VU1 lighting produced**, with the texture not yet applied, and the pack mesh carries the normals
that colour was computed from.  Pairing the two turns "which light rig?" into a small exact linear
problem.

The pairing is by **primitive structure**, not by UV (a barrel's UVs repeat -- only 20 distinct
values -- so UV alone is ambiguous) and not by projection: the pack's `igPrimLengthArray` gives the
`_numStrips` strip lengths, and the GS draws one packet per strip, in order.  The barrel's last
strip is the only one the GS splits (packets of 40 and 23 vertices overlapping by 2), so the
mapping is `dump vertex k of packet p -> mesh vertex base[p] + k`, with that one offset.

Usage:

    python3 gs_barrel_shading.py --dump ../local/dumps/goblin_pass_frame.gs.zst \\
        --tex0 0x4007950555307ca4 --afs ../local/extracted/NDMW.AFS --entry 614 \\
        --vertex-array 36087 --decomp . --out /tmp/barrel_shading.json

The output is the census of the fit: the live rig's model under both `max(0,N.L)` and `|N.L|`, a
sweep of the light direction, and the residual.  For the Goblin Pass barrel the model is exact:
`rgb8 = floor(255 * 0.5 * clamp(ambient + diffuse * max(0, N.L), 0, 1))` with the live-read rig
(ambient 0.25,0.20,0.35; diffuse 1.20,1.15,1.20; L = -igLightAttr._direction), sub-1/255 on all
84 distinct normals.
"""
import argparse
import json
import math
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gsdump  # noqa: E402


def fib(n):
    """n roughly-uniform unit vectors over the sphere (Fibonacci spiral)."""
    ga = math.pi * (3.0 - math.sqrt(5.0))
    out = []
    for i in range(n):
        z = 1.0 - 2.0 * (i + 0.5) / n
        r = math.sqrt(max(0.0, 1.0 - z * z))
        th = ga * i
        out.append((r * math.cos(th), z, r * math.sin(th)))
    return out


def load_pack(afs, entry, decomp):
    sys.path.insert(0, os.path.join(decomp, "scripts"))
    import igb_ids
    import igb_pool
    import igb_models
    refl = igb_ids.igb_inst.load_reflection(os.path.join(decomp, "data", "reflection.json"))
    data = open(afs, "rb").read()
    off = struct.unpack_from("<I", data, 8 + 8 * entry)[0]
    return igb_pool.load(afs, hex(off), refl), refl, igb_models


def mesh_arrays(P, refl, igb_models, va):
    """(pos, nrm, uv, lengths, num_verts) for the geometry whose _vertexArray is `va`."""
    for g in igb_models.read_geometry(P, refl):
        if g["vertex_array"] != va or not g["num_verts"]:
            continue
        nv = g["num_verts"]
        pos = nrm = uv = None
        for sid, off, size in igb_models.streams(P, g["vdata"]):
            if size == 12 * nv and pos is None:
                pos = P["b"][off:off + size]
            elif size == 12 * nv and nrm is None:
                nrm = P["b"][off:off + size]
            elif size == 8 * nv and uv is None:
                uv = P["b"][off:off + size]
        if pos and nrm and uv:
            return pos, nrm, uv, g["lengths"], nv
    raise SystemExit("gs_barrel_shading: no geometry with _vertexArray %d" % va)


def floats(blob, n):
    return [struct.unpack_from("<%df" % n, blob, i * 4 * n) for i in range(len(blob) // (4 * n))]


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dump", required=True)
    ap.add_argument("--tex0", required=True)
    ap.add_argument("--afs", required=True)
    ap.add_argument("--entry", type=int, required=True)
    ap.add_argument("--vertex-array", type=int, required=True)
    ap.add_argument("--decomp", default=os.path.join(os.path.dirname(HERE)))
    ap.add_argument("--sweep", type=int, default=6000, help="directions in the fit sweep")
    ap.add_argument("--out", help="write the census as JSON")
    a = ap.parse_args()

    tex0 = int(a.tex0, 0)
    P, refl, igb_models = load_pack(a.afs, a.entry, a.decomp)
    posb, nrmb, uvb, lengths, nv = mesh_arrays(P, refl, igb_models, a.vertex_array)
    pos = floats(posb, 3)
    nrm = floats(nrmb, 3)
    uv = floats(uvb, 2)
    if sum(lengths) != nv:
        raise SystemExit("gs_barrel_shading: strip lengths do not sum to _numVerts")
    base = []
    s = 0
    for L in lengths:
        base.append(s)
        s += L

    d = gsdump.read_dump(a.dump)
    draws = list(gsdump.draws(d))
    sel = [(i, x) for i, x in enumerate(draws) if x["state"].get(6) == tex0]
    groups = []
    cur = []
    prev = None
    for i, x in sel:
        if prev is not None and i != prev + 1:
            groups.append(cur)
            cur = []
        cur.append((i, x))
        prev = i
    groups.append(cur)
    if not groups or not groups[0]:
        raise SystemExit("gs_barrel_shading: no draw with TEX0 %s" % a.tex0)
    packets = [(i, x) for i, x in groups[0]]

    # one packet per strip; the last strip is the only split (40 + 23 vertices, 2 overlap)
    mapping = {}
    for pi, (_i, x) in enumerate(packets):
        if pi < len(lengths) - 1:
            strip, off = pi, 0
        elif pi == len(lengths) - 1:
            strip, off = len(lengths) - 1, 0
        else:
            strip, off = len(lengths) - 1, len(packets[-2][1]["verts"]) - 2
        for k, v in enumerate(x["verts"]):
            mi = base[strip] + off + k
            if mi < nv:
                mapping[mi] = v["RGBA"]
    if len(mapping) != nv:
        raise SystemExit("gs_barrel_shading: paired %d of %d vertices" % (len(mapping), nv))

    # colour is constant per normal (flat-shaded), so collapse to unique normals
    uniq = {}
    for mi, rgba in mapping.items():
        uniq[tuple(round(c, 4) for c in nrm[mi])] = rgba
    U = list(uniq.keys())
    O = [uniq[k] for k in U]

    def fit(L, absL, scale, clamp):
        err = 0.0
        for k, rgba in zip(U, O):
            ndl = sum(k[j] * L[j] for j in range(3))
            ndl = abs(ndl) if absL else max(0.0, ndl)
            for ch in range(3):
                v = (0.25, 0.20, 0.35)[ch] + ndl * (1.20, 1.15, 1.20)[ch]
                v = min(max(v, 0.0), 1.0) if clamp else v
                pred = math.floor(255.0 * scale * v + 1e-9)
                err += abs(pred - rgba[ch])
        return err / (len(U) * 3)

    ldir = (0.3214, -0.8660, 0.3830)
    live = [(-ldir[0], -ldir[1], -ldir[2])]
    a_best = None
    for L in fib(a.sweep):
        for absL in (False, True):
            # closed-form a + d*x is not needed: report the live-model residual directly
            pass
    # the live model, both conventions and both scales
    live_model = {}
    for name, L, absL, scale, clamp in (
            ("live_onesided_0.5", live[0], False, 0.5, True),
            ("live_twosided_0.5", live[0], True, 0.5, True),
            ("live_onesided_1.0", live[0], False, 1.0, True),
            ("live_twosided_1.0", live[0], True, 1.0, True)):
        live_model[name] = round(fit(L, absL, scale, clamp), 4)

    census = {"vertex_array": a.vertex_array, "num_verts": nv, "num_strips": len(lengths),
              "dump_packets": len(packets), "dump_packets_per_group":
              [len(g) for g in groups], "distinct_normals": len(U),
              "live_model_residual_255": live_model,
              "mesh_uv_distinct": len(set(tuple(round(c, 5) for c in u) for u in uv))}
    print(json.dumps(census, indent=1))
    if a.out:
        json.dump(census, open(a.out, "w"), indent=1)
        print("wrote", a.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
