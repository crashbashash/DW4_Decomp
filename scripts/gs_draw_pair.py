#!/usr/bin/env python3
"""gs_draw_pair.py — pair a GS draw to a pack mesh by strip structure and compare attributes.

Reuses `gs_barrel_shading.py`'s pairing (the pack's `igPrimLengthArray` strip lengths vs the GS's
one-packet-per-strip draws, in order) but keeps the whole vertex record, so it can answer, for a
draw: are the mesh's **UVs** the ST the GS sampled, or was a texture matrix (UV offset/scale)
applied?  Are the positions the same?  Is the colour the fit?

    python3 scripts/gs_draw_pair.py --dump <dump>.gs.zst \\
        --tex0 0x4007950555307ca4 --afs ../local/extracted/NDMW.AFS --entry 614 \\
        --vertex-array 36087
"""
import argparse
import math
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gsdump  # noqa: E402
from gs_barrel_shading import load_pack, mesh_arrays, floats  # noqa: E402


def base_offsets(lengths):
    base, s = [], 0
    for L in lengths:
        base.append(s)
        s += L
    return base


def pairing_plan(len_lengths, packets):
    """per packet index -> (strip index, offset into the strip).  The last strip is the one the GS
    splits; extra packets continue it at verts[-2] (the strip's 2-vertex overlap)."""
    plan = []
    for pi in range(len(packets)):
        if pi < len_lengths - 1:
            plan.append((pi, 0))
        elif pi == len_lengths - 1:
            plan.append((len_lengths - 1, 0))
        else:
            plan.append((len_lengths - 1, len(packets[-2]["verts"]) - 2))
    return plan


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dump", required=True)
    ap.add_argument("--tex0", required=True)
    ap.add_argument("--afs", required=True)
    ap.add_argument("--entry", type=int, required=True)
    ap.add_argument("--vertex-array", type=int, required=True)
    ap.add_argument("--decomp", default=os.path.join(os.path.dirname(HERE)))
    ap.add_argument("--group", type=int, default=0, help="which coincident group to use")
    a = ap.parse_args()

    tex0 = int(a.tex0, 0)
    P, refl, igb_models = load_pack(a.afs, a.entry, a.decomp)
    posb, nrmb, uvb, lengths, nv = mesh_arrays(P, refl, igb_models, a.vertex_array)
    pos, nrm, uv = floats(posb, 3), floats(nrmb, 3), floats(uvb, 2)
    base = base_offsets(lengths)

    d = gsdump.read_dump(a.dump)
    draws = list(gsdump.draws(d))
    # gsdump.draws yields in stream order; a "group" is a maximal run of consecutive selected draws
    idx = [i for i, x in enumerate(draws) if x["state"].get(6) == tex0]
    runs, run = [], []
    for i in idx:
        if run and i != run[-1] + 1:
            runs.append(run)
            run = []
        run.append(i)
    if run:
        runs.append(run)
    if not runs or a.group >= len(runs):
        raise SystemExit("gs_draw_pair: no draw group %d for TEX0 %s" % (a.group, a.tex0))
    packets = [draws[i] for i in runs[a.group]]

    plan = pairing_plan(len(lengths), packets)
    mapping = {}
    for pi, x in enumerate(packets):
        strip, off = plan[pi]
        for k, v in enumerate(x["verts"]):
            mi = base[strip] + off + k
            if mi < nv and mi not in mapping:
                mapping[mi] = v
    if len(mapping) != nv:
        print("WARNING: paired %d of %d vertices" % (len(mapping), nv))

    # ---- ST vs mesh UV ----
    pairs = {}
    for mi, v in mapping.items():
        st = v["ST"]
        s, t, q = st
        if q == 0.0:
            continue
        pairs.setdefault((round(uv[mi][0], 5), round(uv[mi][1], 5)), set()).add(
            (round(s / q, 5), round(t / q, 5), round(q, 5)))
    print("distinct mesh UV: %d ; distinct GS (S/T/Q) per UV:" % len(pairs))
    for k in sorted(pairs):
        vals = pair_vals = sorted(pairs[k])
        tag = "" if len(vals) == 1 else "  <-- UV maps to %d different ST!" % len(vals)
        print("   uv(%.5f, %.5f) -> st %s%s" % (k[0], k[1], vals[:4], tag))

    # ---- affine fit st = A*uv + b (a texture matrix would show as A != I, b != 0) ----
    pts = []
    for mi, v in mapping.items():
        s, t, q = v["ST"]
        if q:
            pts.append((uv[mi][0], uv[mi][1], s / q, t / q))
    if len(pts) >= 3:
        # normal equations for the 2x3 affine (per component)
        import itertools
        n = len(pts)
        sx = sum(p[0] for p in pts); sy = sum(p[1] for p in pts)
        sxx = sum(p[0] * p[0] for p in pts); syy = sum(p[1] * p[1] for p in pts)
        sxy = sum(p[0] * p[1] for p in pts)
        M = [[n, sx, sy], [sx, sxx, sxy], [sy, sxy, syy]]
        def solve(rhs):
            A = [row[:] + [rhs[i]] for i, row in enumerate(M)]
            for c in range(3):
                p = max(range(c, 3), key=lambda r: abs(A[r][c]))
                A[c], A[p] = A[p], A[c]
                for r in range(3):
                    if r != c and A[c][c]:
                        f = A[r][c] / A[c][c]
                        for k in range(c, 4):
                            A[r][k] -= f * A[c][k]
            return [A[i][3] / A[i][i] for i in range(3)]
        cs = solve([sum(p[2] for p in pts), sum(p[0] * p[2] for p in pts), sum(p[1] * p[2] for p in pts)])
        ct = solve([sum(p[3] for p in pts), sum(p[0] * p[3] for p in pts), sum(p[1] * p[3] for p in pts)])
        err = 0.0
        for x, y, s, t in pts:
            ps = cs[0] + cs[1] * x + cs[2] * y
            pt = ct[0] + ct[1] * x + ct[2] * y
            err += abs(ps - s) + abs(pt - t)
        print("affine st = A*uv + b :  S = %.5f + %.5f*u + %.5f*v" % tuple(cs))
        print("                        T = %.5f + %.5f*u + %.5f*v" % tuple(ct))
        print("   mean |residual| per component = %.6f  (0 => mesh UV *is* the GS ST)" % (err / (2 * n)))

    # ---- position + colour census ----
    mu = sorted(set(tuple(round(c, 4) for c in nrm[mi]) for mi in mapping))
    rgba_by_n = {}
    for mi, v in mapping.items():
        rgba_by_n.setdefault(tuple(round(c, 4) for c in nrm[mi]), set()).add(v["RGBA"])
    multi = sum(1 for k in rgba_by_n if len(rgba_by_n[k]) > 1)
    print("positions: %d ; distinct normals: %d ; normals with >1 colour: %d"
          % (len(mapping), len(mu), multi))
    return 0


if __name__ == "__main__":
    sys.exit(main())
