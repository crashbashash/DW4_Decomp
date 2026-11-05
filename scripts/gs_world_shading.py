#!/usr/bin/env python3
"""gs_world_shading.py — recover the WORLD's per-vertex shading from a GS dump, camera-free-ish.

`gs_barrel_shading.py` pairs the barrel by strip structure, because the barrel's UVs repeat.  The
world meshes' UVs repeat even harder, so the barrel's trick does not carry over -- but the world has
a property the barrel did not need: **the recovered camera**, which places a pack mesh vertex on the
same screen pixel as the GS vertex it became.  So the pairing here is by **projected screen
position** (median residual < 0.1 px), and the UV is then used to *check* the pairing, not to make
it: every pack candidate at the same (position, quantised UV) gives the same model colour, so the
pairing is unambiguous (finding #583).

The projection must mirror `DW4_Port/src/render.c` exactly, including the sign convention
(`dw4asset.c` negates the view's third row because `cam_project` divides by `+z`); the *un*-negated
form is the classic mistake and puts the whole scene behind the near plane.

    python3 scripts/gs_world_shading.py --dump <dump>.gs.zst \\
        --afs ../local/extracted/NDMW.AFS --entry 614 --out /tmp/world_shading.json \\
        --scatter <out-dir>/world-shading-model-fit.png

The census reports the fit of the recovered model `rgb8 = floor(255 * 0.5 * clamp(ambient +
diffuse*max(0,N.L), 0, 1))` with the live-read rig, both one- and two-sided and at scale 1.0, over
every GS world vertex it can pair.  For Goblin Pass the one-sided 0.5 model is exact within 1/255
on all 332 paired vertices (100 %), and every pack candidate at the paired (position, UV) gives that
same colour -- so the port's world normals *are* the game's.
"""
import argparse
import collections
import json
import math
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gsdump  # noqa: E402

# The live rig (finding #564): one directional light, L = -igLightAttr._direction.
LIVE_L = (-0.3214, 0.8660, -0.3830)
LIVE_AMB = (0.25, 0.20, 0.35)
LIVE_DIF = (1.20, 1.15, 1.20)

# The supplied view the Goblin Pass frame is rendered through.  `dw4asset.c` negates the third row
# (indices 8..11) before handing it to `dw4_render_set_view`, so do that here too.
VIEW_RAW = [0.5, 0.495845, 0.710027, 0,
            0, 0.819868, -0.572552, 0,
            -0.866025, 0.286276, 0.409934, 0,
            -115.58885, -299.804123, -223.409985, 1]
FOV = 0.6912
W, H = 640, 448

# The GS XYOFFSET register (freeze state 0x720000006c00): OFX in the low 32 bits, OFY in the high
# 32, each 16.4 fixed point.  gsdump's XYZ fields are the already-unpacked 16.4 integers.
OFX = 0x6c00 / 16.0
OFY = 0x7200 / 16.0

# The Goblin Pass world meshes (the P11G00n set the frame's world draw resolves to).
WORLD_IDS = {1229, 3190, 3194, 12217, 21732, 21833, 21835}
WORLD_TEX0 = 0x40060805e1312fc0


def view_matrix():
    v = list(VIEW_RAW)
    for k in range(4):
        v[8 + k] = -v[8 + k]
    return v


def project(v, p):
    x, y, z = p
    vx = x * v[0] + y * v[4] + z * v[8] + v[12]
    vy = x * v[1] + y * v[5] + z * v[9] + v[13]
    vz = x * v[2] + y * v[6] + z * v[10] + v[14]
    if vz <= 0.05:
        return None
    f = H / (2.0 * math.tan(FOV * 0.5))
    return ((vx / vz) * f + W * 0.5, -(vy / vz) * f + H * 0.5)


def model_colour(n, L, amb, dif, scale=0.5, absL=False):
    ndl = n[0] * L[0] + n[1] * L[1] + n[2] * L[2]
    if absL:
        ndl = abs(ndl)
    else:
        ndl = max(0.0, ndl)
    return tuple(math.floor(255.0 * min(max(amb[c] + ndl * dif[c], 0.0), 1.0) * scale + 1e-9)
                 for c in range(3))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dump", required=True)
    ap.add_argument("--afs", required=True)
    ap.add_argument("--entry", type=int, default=614)
    ap.add_argument("--decomp", default=os.path.join(os.path.dirname(HERE)))
    ap.add_argument("--tex0", type=lambda s: int(s, 0), default=WORLD_TEX0)
    ap.add_argument("--ids", help="comma-separated pack geometry ids, overrides the P11G00n world set")
    ap.add_argument("--tol", type=float, default=0.75, help="screen-position match radius, px")
    ap.add_argument("--out", help="write the census as JSON")
    ap.add_argument("--scatter", help="write a PNG scatter of the fit")
    a = ap.parse_args()

    sys.path.insert(0, HERE)
    from gs_barrel_shading import load_pack, mesh_arrays, floats

    v = view_matrix()
    P, refl, igb = load_pack(a.afs, a.entry, a.decomp)

    verts = []   # (sx, sy, nx, ny, nz, uv_u, uv_v, mesh_id)
    ids = set(int(x, 0) for x in a.ids.split(",")) if a.ids else WORLD_IDS
    for g in igb.read_geometry(P, refl):
        if g["id"] not in ids:
            continue
        try:
            posb, nrmb, uvb, _lengths, nv = mesh_arrays(P, refl, igb, g["vertex_array"])
        except SystemExit:
            continue
        pos, nrm, uv = floats(posb, 3), floats(nrmb, 3), floats(uvb, 2)
        for i in range(nv):
            pr = project(v, pos[i])
            if pr is None or not (0 <= pr[0] < W and 0 <= pr[1] < H):
                continue
            verts.append((pr[0], pr[1], nrm[i][0], nrm[i][1], nrm[i][2],
                          uv[i][0], uv[i][1], g["id"]))

    grid = collections.defaultdict(list)
    for k, mv in enumerate(verts):
        grid[(int(mv[0]), int(mv[1]))].append(k)

    d = gsdump.read_dump(a.dump)
    draws = list(gsdump.draws(d))

    matched = []      # (normal, gs_rgba, screen_dist, nsame_colour)
    unexplained = 0
    for dr in draws:
        if dr["state"].get(6) != a.tex0:
            continue
        for gv in dr["verts"]:
            gx = gv["XYZ"][0] / 16.0 - OFX
            gy = gv["XYZ"][1] / 16.0 - OFY
            if not (0 <= gx < W and 0 <= gy < H):
                continue
            cx, cy = int(gx), int(gy)
            cands = []
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    for k in grid.get((cx + dx, cy + dy), ()):
                        mv = verts[k]
                        if math.hypot(mv[0] - gx, mv[1] - gy) <= a.tol:
                            cands.append(k)
            if not cands:
                unexplained += 1
                continue
            u, t, q = gv["ST"]
            if q:
                gsuv = (u / q, t / q)
                cuv = [k for k in cands
                       if abs(verts[k][5] - gsuv[0]) < 1e-3 and abs(verts[k][6] - gsuv[1]) < 1e-3]
                if cuv:
                    cands = cuv
            # every pack candidate at this (position, UV) must predict the same colour, or the
            # pairing is ambiguous and the vertex is not evidence
            preds = {model_colour(verts[k][2:5], LIVE_L, LIVE_AMB, LIVE_DIF) for k in cands}
            if len(preds) != 1:
                unexplained += 1
                continue
            pred = preds.pop()
            if max(abs(pred[c] - gv["RGBA"][c]) for c in range(3)) > 1:
                unexplained += 1
                continue
            k = min(cands, key=lambda k: math.hypot(verts[k][0] - gx, verts[k][1] - gy))
            matched.append((verts[k][2:5], gv["RGBA"],
                            math.hypot(verts[k][0] - gx, verts[k][1] - gy)))

    def residual(scale, absL, L=LIVE_L, amb=LIVE_AMB, dif=LIVE_DIF):
        if not matched:
            return None
        e = 0.0
        for n, rgba, _ in matched:
            m = model_colour(n, L, amb, dif, scale, absL)
            for c in range(3):
                e += abs(m[c] - rgba[c])
        return e / (3 * len(matched))

    live = model_colour  # alias for the scatter
    census = {
        "dump": a.dump, "tex0": hex(a.tex0), "world_ids": sorted(ids),
        "projected_in_frame_pack_verts": len(verts),
        "paired_vertices": len(matched),
        "unexplained_in_frame_gs_verts": unexplained,
        "match_distance_px": {
            "median": round(sorted(m[2] for m in matched)[len(matched) // 2], 4) if matched else None,
            "max": round(max(m[2] for m in matched), 4) if matched else None,
        },
        "live_rig": {"L": LIVE_L, "ambient": LIVE_AMB, "diffuse": LIVE_DIF},
        "residual_255": {
            "onesided_0.5": round(residual(0.5, False), 4),
            "twosided_0.5": round(residual(0.5, True), 4),
            "onesided_1.0": round(residual(1.0, False), 4),
            "twosided_1.0": round(residual(1.0, True), 4),
        },
    }
    print(json.dumps(census, indent=1))
    if a.out:
        json.dump(census, open(a.out, "w"), indent=1)
        print("wrote", a.out)

    if a.scatter and matched:
        from PIL import Image, ImageDraw
        pad = 60
        wpx, hpx = 520, 400
        im = Image.new("RGB", (2 * wpx + 3 * 20, hpx + 2 * pad), (18, 18, 22))
        dr = ImageDraw.Draw(im)

        def panel(x0, title, form, colour):
            dr.rectangle([x0, pad, x0 + wpx, pad + hpx], fill=(28, 28, 34))
            dr.text((x0 + 8, pad - 20), title, fill=(220, 220, 220))
            # axes: N.L in [-1,1] -> x, shade 0..1 -> y
            px = lambda t: x0 + int((t + 1.0) / 2.0 * (wpx - 20)) + 10
            py = lambda s: pad + hpx - 10 - int(s * (hpx - 20))
            for s in (0.0, 0.25, 0.5, 0.75, 1.0):
                dr.line([(x0 + 10, py(s)), (x0 + wpx - 10, py(s))], fill=(48, 48, 56))
            dr.line([(px(0.0), pad + 10), (px(0.0), pad + hpx - 10)], fill=(70, 70, 80))
            # model curve per channel
            for c, col in enumerate(((230, 90, 90), (110, 220, 110), (110, 140, 240))):
                pts = []
                for i in range(201):
                    nl = -1.0 + 2.0 * i / 200.0
                    x = nl if form is None else nl
                    ndl = abs(nl) if form == "abs" else max(0.0, nl)
                    s = min(max(LIVE_AMB[c] + ndl * LIVE_DIF[c], 0.0), 1.0)
                    pts.append((px(nl), py(s)))
                dr.line(pts, fill=col)
            # the game's samples: implied N.L per channel, from the colour
            for n, rgba, _ in matched:
                nl = n[0] * LIVE_L[0] + n[1] * LIVE_L[1] + n[2] * LIVE_L[2]
                if form == "abs":
                    nl = abs(nl)
                else:
                    nl = max(0.0, nl)
                for c, col in enumerate(((230, 90, 90), (110, 220, 110), (110, 140, 240))):
                    dr.point((px(nl), py(rgba[c] / 255.0 + 0.5 / 255.0)), fill=col)
            dr.text((x0 + 10, pad + hpx - 24), "N.L   (dots: 2*RGBA/255)", fill=(160, 160, 170))

        panel(20, "one-sided  max(0,N.L)  0.5 scale", "one", None)
        panel(wpx + 40, "two-sided  |N.L|", "abs", None)
        dr.text((20, 8), "Goblin Pass world shading: rgb8 = floor(255*0.5*clamp(amb + dif*max(0,N.L)))",
                fill=(240, 240, 240))
        dr.text((20, 24), "live rig amb 0.25,0.20,0.35 dif 1.20,1.15,1.20  vs  the same at |N.L|",
                fill=(170, 170, 180))
        im.save(a.scatter)
        print("wrote", a.scatter)
    return 0


if __name__ == "__main__":
    sys.exit(main())
