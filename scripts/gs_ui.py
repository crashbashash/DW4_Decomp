#!/usr/bin/env python3
"""gs_ui.py — export a GS dump's 2D UI draws (the HUD) as screen-space triangles + textures.

The port renders the 3D scene from the pack; the HUD and every other 2D overlay are drawn by the
engine's UI system straight to the GS in **screen space** and are not in the scene TSV, so the port
draws nothing there -- the largest single remaining error region in the Goblin Pass frame.

This tool reads those draws back out of a PCSX2 `.gs` dump.  The UI draws are the ones that are
**alpha-blended** (`PRIM.ABE`) and **unlit** (their per-vertex RGBA is one constant), and whose
surface stays inside the framebuffer -- the lit 3D draws fail all three, so the split is by
measurement rather than by a texture list.  Each strip/fan/list becomes plain screen-space triangles
`{x, y, u, v, r, g, b, a}` (the GS's `STQ` divided by `Q`, exactly as the sampler reads it), plus
each TEX0's texture decoded out of the dump's VRAM (PSMT8 + CT32 CLUT, `gsdump.texture_rgba`).  The
port's `--ui` path then draws them over the scene with the game's own alpha blend.

    python3 scripts/gs_ui.py --dump ../local/dumps/goblin_pass_ref.gs.zst --out /tmp/ui

Writes `<out>/ui.tsv` (one row per triangle: `TEX\tx0 y0 u0 v0 r g b a\tx1 ...\t...`, the RGBA the
same for all three) and `<out>/<TEX0>.rgba` (RGBA8888 with a 2-word width/height header -- the same
layout `dw4asset render --texdir` already reads).
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gsdump  # noqa: E402

OFX = 0x6c00 / 16.0
OFY = 0x7200 / 16.0


def ui_draws(d, stq=False):
    """[(tex0, prim, [(x, y, a, b, c, r, g, b, a)])] for the unlit, alpha-blended screen-space draws.

    Without `stq` the coords are the sampled `u, v` (the GS's `STQ/Q`, baked per vertex) and the
    draws are the *flat* ones -- a 2D overlay sits at a single Z.  With `stq` the raw `s, t, q` come
    through and the 3D draws stay in, so a caller can do the divide per pixel like the GS does.
    """
    out = []
    for dr in gsdump.draws(d):
        prim = dr["state"].get("PRIM_EFF", 0)
        abe = bool(prim & 0x40)
        if not abe and not stq:
            continue                             # the UI-only view is the blending passes
 
        rgba = dr["verts"][0]["RGBA"]
        if not stq and any(v["RGBA"] != rgba for v in dr["verts"]):
            continue                             # the UI-only view needs one colour per draw
        if not stq:
            zs = [v["XYZ"][2] for v in dr["verts"]]
            if max(zs) != min(zs):
                continue                         # a 3D draw, not UI: a 2D overlay is FLAT (one Z).
        #     measured on the menu frame: all 36 genuine UI draws share one Z, and all 1159 of the
        #     background dome's draws vary (190..162584) -- so this separates them exactly.
        textured = bool(prim & 0x10)              # PRIM.TME
        tex0 = dr["state"].get(6) if textured else None
        verts = []
        for v in dr["verts"]:
            x = v["XYZ"][0] / 16.0 - OFX
            y = v["XYZ"][1] / 16.0 - OFY
            if "ST" in v:
                s, t, q = v["ST"]
                if stq:
                    a, b, c = s, t, q
                else:
                    q = q if abs(q) > 1e-9 else 1e-9
                    a, b, c = s / q, t / q, 1.0
            else:
                a, b, c = 0.0, 0.0, 1.0          # an untextured overlay quad (RGBAXYZF2)
            verts.append((x, y, a, b, c, v["RGBA"]))
        else:
            # Keep it if the quad *overlaps* the viewport, not only if it sits wholly inside it:
            # the menu's logo is 13 px above the top edge, and dropping it lost the whole logo.
            # The rasteriser clips, so a partly-off-screen triangle is fine.
            xs = [q[0] for q in verts]
            ys = [q[1] for q in verts]
            if max(xs) < 0 or min(xs) > 640 or max(ys) < 0 or min(ys) > 448:
                continue                         # a world draw, not UI
            # blend: 0 opaque (ABE off), 1 alpha (ALPHA 0x44), 2 additive (ALPHA 0x48).  The opaque
            # passes matter for a frame: dropping them left the backdrop measurably dark.
            alpha = dr["state"].get(0x42, 0x44) or 0x44
            blend = 0 if not abe else (2 if alpha == 0x48 else 1)
            out.append((tex0, prim, verts, blend))
    return out


def triangles(prim, verts):
    """Screen-space triangles from a strip/fan/list."""
    ptype = prim & 7
    if ptype == 4:                               # TRISTRIP (winding does not matter for an overlay)
        for k in range(len(verts) - 2):
            yield (verts[k], verts[k + 1], verts[k + 2]) if k % 2 == 0 else \
                  (verts[k + 1], verts[k], verts[k + 2])
    elif ptype == 5:                             # TRIFAN
        for k in range(1, len(verts) - 1):
            yield (verts[0], verts[k], verts[k + 1])
    elif ptype == 3:                             # TRI (independent)
        for k in range(0, len(verts) - 2, 3):
            yield (verts[k], verts[k + 1], verts[k + 2])


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dump", required=True)
    ap.add_argument("--out", required=True, help="output directory (ui.tsv + <tex0>.rgba)")
    ap.add_argument("--stq", action="store_true",
                    help="emit raw STQ and keep the 3D draws (perspective-correct; the port divides "
                         "per pixel like the GS, which is what a background dome needs)")
    a = ap.parse_args()

    d = gsdump.read_dump(a.dump)
    draws = ui_draws(d, stq=a.stq)
    os.makedirs(a.out, exist_ok=True)

    tex0s = {}
    rows = []
    for tex0, prim, verts, alpha in draws:
        for tri in triangles(prim, verts):
            rows.append((tex0, tri, alpha))
            if tex0 is not None:
                tex0s[tex0] = None
    for tex0 in sorted(tex0s):
        try:
            rgba, w, h, _f = gsdump.texture_rgba(d, tex0)
        except SystemExit as e:
            print("  %#x: %s (skipped)" % (tex0, e))
            continue
        name = "%#x" % tex0
        with open(os.path.join(a.out, name + ".rgba"), "wb") as f:
            f.write(struct.pack("<II", w, h))
            f.write(rgba)
        tex0s[tex0] = name
        print("  texture %-14s %3dx%-3d TEX0 %#x" % (name, w, h, tex0))

    path = os.path.join(a.out, "ui.tsv")
    n = 0
    with open(path, "w") as f:
        if a.stq:
            f.write("#stq\n")
        for tex0, tri, alpha in rows:
            name = tex0s.get(tex0, "-" if tex0 is None else None)
            if name is None:
                continue
            cells = []
            for (x, y, ca1, cb1, cc1, rgba) in tri:
                if a.stq:                       # x y s t q + rgba (the port's perspective form)
                    cells.append("%.2f %.2f %.6f %.6f %.6f %d %d %d %d"
                                 % (x, y, ca1, cb1, cc1, rgba[0], rgba[1], rgba[2], rgba[3]))
                else:                           # x y u v + rgba, exactly the four the reader expects
                    cells.append("%.2f %.2f %.6f %.6f %d %d %d %d"
                                 % (x, y, ca1, cb1, rgba[0], rgba[1], rgba[2], rgba[3]))
            f.write("%s\t%s\t%d\n" % (name, "\t".join(cells), alpha))
            n += 1
    print("gs_ui: %d UI draws -> %d triangles, %d texture(s) -> %s"
          % (len(draws), n, len(tex0s), path))
    return 0


if __name__ == "__main__":
    sys.exit(main())
