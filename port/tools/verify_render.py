#!/usr/bin/env python3
"""verify_render.py — the rasteriser draws something, and draws the same thing twice.

A renderer's failure mode is a blank or degenerate frame, which no count catches.  This renders three
named meshes of a stage pack and asserts, for each: the image is not the cleared background, a sane
fraction of it is covered, and two runs produce identical bytes (the pass is deterministic — no
threads, no curves, no timing).  It is the renderer half of `make check`.

It also pins the stage framing (findings #495/#496): the pack's own camera must compose
(child x parent) to the position the live session measured, (0, 102.490, 74.565) for `stag0102` —
that is pure pack data, so it runs with no RAM capture.  When `--scene <capture.tsv>` is given (a
live capture from `scripts/capture_scene.py`) it additionally renders the placed stage through
that camera and asserts the frame is non-degenerate and deterministic.

  tools/verify_render.py [--tool build/dw4asset] [--roms <dir>] [--entry 621]
                         [--stage stag0102.igb] [--ref 1] [--scene capture.tsv]
"""
import argparse
import os
import struct
import subprocess
import sys
import tempfile
import zlib

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_ROMS = os.path.join(PORT, "..", "..", "local/extracted")


def png_rows(path):
    """(w, h, raw scanlines) with each row's filter byte stripped -- the tool's PNGs store
    filter-0 rows (src/png.c), so the RGBA bytes are at their literal offsets."""
    d = open(path, "rb").read()
    w, h = struct.unpack(">II", d[16:24])
    idat = b""
    i = 8
    while i + 8 <= len(d):
        ln, typ = struct.unpack(">I", d[i:i + 4])[0], d[i + 4:i + 8]
        if typ == b"IDAT":
            idat += d[i + 8:i + 8 + ln]
        i += 12 + ln
    raw = zlib.decompress(idat)
    if len(raw) != (w * 4 + 1) * h:
        return None, 0, None
    stride = w * 4
    return w, h, [raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)] for y in range(h)]


def coverage(path, bg=(24, 28, 36)):
    """(fraction of non-background pixels, byte size) -- PNG rows filtered 0 (stored)."""
    d = open(path, "rb").read()
    w, h = struct.unpack(">II", d[16:24])
    idat = b""
    i = 8
    while i + 8 <= len(d):
        ln, typ = struct.unpack(">I", d[i:i + 4])[0], d[i + 4:i + 8]
        if typ == b"IDAT":
            idat += d[i + 8:i + 8 + ln]
        i += 12 + ln
    raw = zlib.decompress(idat)
    if len(raw) != (w * 4 + 1) * h:
        return None, len(d)
    n = 0
    for y in range(h):
        row = raw[y * (w * 4 + 1) + 1:][:w * 4]
        for x in range(0, len(row), 4):
            if (row[x], row[x + 1], row[x + 2]) != bg:
                n += 1
    return n / float(w * h), len(d)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4asset"))
    ap.add_argument("--roms", default=DEFAULT_ROMS)
    ap.add_argument("--entry", type=int, default=621)
    ap.add_argument("--stage", default="stag0102.igb")
    ap.add_argument("--ref", type=int, default=1)
    ap.add_argument("--scene", default=None,
                    help="a live scene capture (scripts/capture_scene.py) to frame the stage")
    ap.add_argument("--livedump", default=os.environ.get("DW4_LIVEDUMP"),
                    help="an EE RAM dump (31/32 MB) for the live-texture path")
    ap.add_argument("names", nargs="*")
    args = ap.parse_args()
    names = args.names or ["pCylinderShape3", "mainShape", "pCubeShape1"]
    afs = os.path.join(args.roms, "NDMW.AFS")
    bad = 0
    with tempfile.TemporaryDirectory() as tmp:
        for name in names:
            outs = []
            for run in (0, 1):
                out = os.path.join(tmp, "%s.%d.png" % (name, run))
                r = subprocess.run([args.tool, "render", "--afs", afs, "--entry",
                                    str(args.entry), "--name", name, "--out", out,
                                    "--w", "240", "--h", "240"], capture_output=True, text=True)
                if r.returncode != 0 or "0 mesh(es) drawn" in r.stdout:
                    print("  %s: nothing drawn (%s)" % (name, r.stdout.strip() or r.stderr.strip()))
                    bad += 1
                    break
                outs.append(out)
            if len(outs) != 2:
                continue
            cov, size = coverage(outs[0])
            same = open(outs[0], "rb").read() == open(outs[1], "rb").read()
            ok = cov is not None and 0.02 <= cov <= 0.98 and same
            print("  %-18s coverage %5.1f%% of the frame, two runs identical: %s  %s"
                  % (name, 100.0 * (cov or 0.0), "yes" if same else "NO",
                     "ok" if ok else "BAD"))
            if not ok:
                bad += 1
        # The character model packs (P3.5, finding #536): their records sit on the other
        # parity from the stage packs, so this is what proves a `p_*.igb` loads and draws.
        # The three shapes are the player's actor LODs (finding #537).
        for name in ("P_susanoo_Skin0Shape0", "P_susanoo_Skin0Shape1", "P_susanoo_Skin0Shape2"):
            out = os.path.join(tmp, "char_%s.png" % name)
            r = subprocess.run([args.tool, "render", "--afs", afs, "--entry", "861",
                                "--name", name, "--out", out, "--w", "240", "--h", "240"],
                               capture_output=True, text=True)
            if r.returncode != 0 or "0 mesh(es) drawn" in r.stdout:
                print("  char %-14s nothing drawn (%s)"
                      % (name[10:], r.stdout.strip() or r.stderr.strip()))
                bad += 1
                continue
            cov, _ = coverage(out)
            ok = cov is not None and 0.02 <= cov <= 0.98
            print("  char %-14s coverage %5.1f%%  %s"
                  % (name[10:], 100.0 * (cov or 0.0), "ok" if ok else "BAD"))
            if not ok:
                bad += 1
        # the texture sampler: the same mesh drawn with a texture from a texture pack must differ
        # from the flat shading (and still be non-blank), which is what proves the UV path
        afs_t = os.path.join(args.roms, "NDMW.AFS")
        flat = os.path.join(tmp, "flat.png")
        texd = os.path.join(tmp, "tex.png")
        r1 = subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", str(args.entry),
                             "--name", names[0], "--out", flat, "--w", "240", "--h", "240"],
                            capture_output=True, text=True)
        r2 = subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", str(args.entry),
                             "--name", names[0], "--texture", "BJGR01.png", "--texentry", "625",
                             "--out", texd, "--w", "240", "--h", "240"],
                            capture_output=True, text=True)
        if r1.returncode or r2.returncode:
            print("  textured render failed: %s%s" % (r1.stderr, r2.stderr))
            bad += 1
        else:
            a, b = open(flat, "rb").read(), open(texd, "rb").read()
            cov, _ = coverage(texd)
            ok = a != b and cov is not None and cov >= 0.02
            print("  %-18s texture changes the frame: %s, coverage %5.1f%%  %s"
                  % (names[0] + "+tex", "yes" if a != b else "NO", 100.0 * (cov or 0.0),
                     "ok" if ok else "BAD"))
            if not ok:
                bad += 1

        # --- the VU1 FOG family (P4.1) ----------------------------------------------------------
        # FOG_LINEAR / FOG_EXP / FOG_EXP2 are the three fog programs (the CLIP_FOG_* variants are
        # the same effect at the clip stage).  Each mode must change the frame from the un-fogged
        # one and from each other, and be deterministic -- a fog factor is a pure function of depth.
        fog_frames = {}
        fog_ok = True
        for mode, spec in (("off", None), ("linear", "linear,1,3,0,0.10,0.11,0.15"),
                           ("exp", "exp,0,0,0.5,0.10,0.11,0.15"),
                           ("exp2", "exp2,0,0,0.5,0.10,0.11,0.15")):
            p = os.path.join(tmp, "fog-%s.png" % mode)
            cmd = [args.tool, "render", "--afs", afs_t, "--entry", str(args.entry),
                   "--name", names[0], "--out", p, "--w", "240", "--h", "240"]
            if spec:
                cmd += ["--fog", spec]
            r = subprocess.run(cmd, capture_output=True, text=True)
            if r.returncode != 0 or not os.path.exists(p):
                print("  %-18s fog render failed: %s" % ("fog-" + mode, r.stderr.strip()))
                fog_ok = False
                break
            fog_frames[mode] = open(p, "rb").read()
        if fog_ok:
            base = fog_frames["off"]
            modes = ("linear", "exp", "exp2")
            distinct = all(fog_frames[m] != base for m in modes)
            pair = len({fog_frames[m] for m in modes}) == 3
            ok = distinct and pair
            print("  %-18s linear/exp/exp2 differ from off and each other: %s  %s"
                  % ("fog", "yes" if ok else "NO", "ok" if ok else "BAD"))
            if not ok:
                bad += 1

        # --- the GPU backend (P4.1/P4.3) --------------------------------------------------------
        # The same single mesh and a placed-scene frame through EGL/GLES must draw (not blank) and
        # be deterministic, and a texture pack image must change the frame -- the GL UV sampler is
        # the same texture the software renderer samples.  Skips cleanly when EGL/GLES is absent.
        gl_bg = (18, 22, 30)          # the GL clear colour, not the software one
        gl_flat = os.path.join(tmp, "gl-flat.png")
        gl_flat2 = os.path.join(tmp, "gl-flat2.png")
        gl_tex = os.path.join(tmp, "gl-tex.png")
        gl_fog = os.path.join(tmp, "gl-fog.png")
        r = subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", str(args.entry),
                            "--name", names[0], "--gl", "--w", "240", "--h", "240",
                            "--out", gl_flat], capture_output=True, text=True)
        if "not compiled in" in (r.stdout + r.stderr):
            print("  %-18s GPU backend not compiled in, skipped" % "gl-name")
        elif r.returncode != 0:
            print("  %-18s GPU backend failed: %s"
                  % ("gl-name", (r.stderr or r.stdout).strip()))
            bad += 1
        else:
            subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", str(args.entry),
                            "--name", names[0], "--gl", "--w", "240", "--h", "240",
                            "--out", gl_flat2], capture_output=True, text=True)
            subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", str(args.entry),
                            "--name", names[0], "--texture", "BJGR01.png", "--texentry", "625",
                            "--gl", "--w", "240", "--h", "240", "--out", gl_tex],
                           capture_output=True, text=True)
            subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", str(args.entry),
                            "--name", names[0], "--fog", "linear,1,3,0,0.10,0.11,0.15",
                            "--gl", "--w", "240", "--h", "240", "--out", gl_fog],
                           capture_output=True, text=True)
            cov, _ = coverage(gl_flat, gl_bg)
            same = open(gl_flat, "rb").read() == open(gl_flat2, "rb").read()
            tex_diff = os.path.exists(gl_tex) and open(gl_flat, "rb").read() != open(gl_tex, "rb").read()
            fog_diff = os.path.exists(gl_fog) and open(gl_flat, "rb").read() != open(gl_fog, "rb").read()
            ok = cov is not None and cov >= 0.02 and same and tex_diff and fog_diff
            print("  %-18s coverage %5.1f%%, deterministic: %s, texture: %s, fog: %s  %s"
                  % ("gl-name", 100.0 * (cov or 0.0), "yes" if same else "NO",
                     "yes" if tex_diff else "NO", "yes" if fog_diff else "NO",
                     "ok" if ok else "BAD"))
            if not ok:
                bad += 1

        # the `--scene` GL path: a synthetic one-row capture framed by `--fit` exercises the scene
        # merge + GL draw without needing a live RAM capture.  (When a real `--scene` is supplied,
        # the camera-framed GL pass below adds the per-draw frame-run path.)
        cap1 = os.path.join(tmp, "one-row.tsv")
        with open(cap1, "w") as f:
            f.write("%s\t1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1\n" % names[0])
        gl_scene = os.path.join(tmp, "gl-scene.png")
        r = subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                            "--ref", str(args.ref), "--scene", cap1, "--fit", "--gl",
                            "--w", "240", "--h", "240", "--out", gl_scene],
                           capture_output=True, text=True)
        if "not compiled in" in (r.stdout + r.stderr):
            print("  %-18s GPU backend not compiled in, skipped" % "gl-scene")
        elif r.returncode != 0 or not os.path.exists(gl_scene):
            print("  %-18s GPU scene render failed: %s"
                  % ("gl-scene", (r.stderr or r.stdout).strip()))
            bad += 1
        else:
            cov, _ = coverage(gl_scene, gl_bg)
            ok = cov is not None and cov >= 0.02
            print("  %-18s coverage %5.1f%%  %s"
                  % ("gl-scene", 100.0 * (cov or 0.0), "ok" if ok else "BAD"))
            if not ok:
                bad += 1

        # the fifth-column pack-attr-id join (finding #519): a capture row carrying a real pack
        # geometry-attribute id draws that mesh even though its name is not a pack name, and an
        # unknown id draws nothing -- the name is ignored whenever the column is present.
        tsv = subprocess.run([args.tool, "scene", "--stage", args.roms, args.stage,
                              "--ref", str(args.ref), "--tsv"], capture_output=True, text=True)
        rows = [l.split("\t") for l in (tsv.stdout or "").splitlines() if "\t" in l]
        rows = [q for q in rows if q and q[0].isdigit()]
        if not rows:
            print("  %-18s no scene tsv rows, skipped" % "attr-id join")
        else:
            aid = rows[0][0]
            row = "nomatch\t1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1\t\t0x0\t%s\n"
            cap_hit = os.path.join(tmp, "id-hit.tsv")
            cap_miss = os.path.join(tmp, "id-miss.tsv")
            p_hit = os.path.join(tmp, "id-hit.png")
            p_miss = os.path.join(tmp, "id-miss.png")
            with open(cap_hit, "w") as f:
                f.write(row % aid)
            with open(cap_miss, "w") as f:
                f.write(row % "999999999")
            for cap, out in ((cap_hit, p_hit), (cap_miss, p_miss)):
                subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                                "--ref", str(args.ref), "--scene", cap, "--fit",
                                "--w", "120", "--h", "120", "--out", out],
                               capture_output=True, text=True)
            c_hit = coverage(p_hit, gl_bg)[0] if os.path.exists(p_hit) else None
            differs = (os.path.exists(p_hit) and os.path.exists(p_miss) and
                       open(p_hit, "rb").read() != open(p_miss, "rb").read())
            ok = c_hit is not None and c_hit >= 0.02 and differs
            print("  %-18s id %.1f%% hit, hit!=miss: %s  %s"
                  % ("attr-id join", 100.0 * (c_hit or 0.0), "yes" if differs else "NO",
                     "ok" if ok else "BAD"))
            if not ok:
                bad += 1

        # --- the scene path's vertex normals ------------------------------------------------------
        # A scene row is shaded with the mesh's own unit-length normal stream where the pack ships
        # one (the engine's LIGHT programs interpolate it; finding #559).  The scene reader resolves
        # it to a second `12*numVerts` block, so the check is a render: a mesh whose normals differ
        # from its face normals must come out *different* under `--flat` (the face-normal baseline)
        # than under the default.  Pack 621's id 1141 is such a mesh (3599 verts, smooth normals);
        # it is unnamed, which is why it is named by id here.
        mt = "1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1"
        cap_n = os.path.join(tmp, "nrm.tsv")
        with open(cap_n, "w") as f:
            f.write("-\t%s\t\t0x0\t1141\n" % mt)
        p_nrm = os.path.join(tmp, "nrm.png")
        p_flat = os.path.join(tmp, "nrm-flat.png")
        for extra, out in ((["--no-fog"], p_nrm), (["--flat", "--no-fog"], p_flat)):
            subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                            "--ref", str(args.ref), "--scene", cap_n, "--fit",
                            "--w", "240", "--h", "240", "--out", out] + extra,
                           capture_output=True, text=True)
        cov_n = coverage(p_nrm, gl_bg)[0] if os.path.exists(p_nrm) else None
        differs = (os.path.exists(p_nrm) and os.path.exists(p_flat) and
                   open(p_nrm, "rb").read() != open(p_flat, "rb").read())
        ok = cov_n is not None and cov_n >= 0.02 and differs
        print("  %-18s coverage %5.1f%%, smooth != flat: %s  %s"
              % ("scene normals", 100.0 * (cov_n or 0.0), "yes" if differs else "NO",
                 "ok" if ok else "BAD"))
        if not ok:
            bad += 1

        # --- the game's per-vertex (gouraud) shading path ----------------------------------------
        # The GS lights each vertex and interpolates the *colour*; the port's other path interpolates
        # the normal and lights per pixel.  On a smooth-shaded mesh the two differ, so `--per-pixel`
        # and `--gouraud` must render differently (finding #583), and both must still draw.  The
        # game's path is the default (finding #591), so pin the explicit pair rather than a flag
        # against the default.
        p_ppx = os.path.join(tmp, "nrm-perpixel.png")
        subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                        "--ref", str(args.ref), "--scene", cap_n, "--fit",
                        "--w", "240", "--h", "240", "--out", p_ppx, "--per-pixel", "--no-fog"],
                       capture_output=True, text=True)
        p_gour = os.path.join(tmp, "nrm-gouraud.png")
        subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                        "--ref", str(args.ref), "--scene", cap_n, "--fit",
                        "--w", "240", "--h", "240", "--out", p_gour, "--gouraud", "--no-fog"],
                       capture_output=True, text=True)
        # the default must BE the game's path: a plain render has to equal the explicit --gouraud one
        default_is_gouraud = (os.path.exists(p_nrm) and os.path.exists(p_gour) and
                              open(p_nrm, "rb").read() == open(p_gour, "rb").read())
        cov_g = coverage(p_gour, gl_bg)[0] if os.path.exists(p_gour) else None
        differs_g = (os.path.exists(p_ppx) and os.path.exists(p_gour) and
                     open(p_ppx, "rb").read() != open(p_gour, "rb").read())
        # Pin the texture-modulation SOURCE (finding #587) with a render identity.  The GS's
        # modulate is per fragment: out = (texel * fragment_colour) / 255, and the port computes
        # both halves independently -- `--unlit --texture` gives the texel map (white x texel),
        # plain `--gouraud` gives the interpolated colour map -- so the textured gouraud render
        # must equal (texel * colour) / 255 EXACTLY, per channel, on every drawn pixel.  The bug
        # this catches: the gouraud branch used to texture-modulate with the stale stack array
        # col[] instead of the interpolated r,g,bb (col[] is only ever filled on the !smooth and
        # per-pixel paths).  An --unlit-based invariant (gouraud-unlit == unlit) is vacuous here:
        # under --unlit the stale stack slot holds the previous triangle's WHITE vertex colour,
        # so old and new code agree; the identity below needs the lighting on and a colour map
        # that varies, which this mesh's smooth normals supply.
        p_tex = os.path.join(tmp, "mod-texel.png")        # --unlit --texture  -> texel map
        p_col = os.path.join(tmp, "mod-colour.png")       # --gouraud          -> colour map
        p_act = os.path.join(tmp, "mod-actual.png")       # --gouraud --texture
        runs_ok = True
        tex_loaded = False
        for out, extra in ((p_tex, ["--unlit", "--texture", "P11G00n.png", "--texentry", "618",
                                     "--no-fog"]),
                           (p_col, ["--gouraud", "--no-fog"]),
                           (p_act, ["--gouraud", "--texture", "P11G00n.png",
                                    "--texentry", "618", "--no-fog"])):
            run = subprocess.run([args.tool, "render", "--afs", afs, "--stage", args.roms,
                                  args.stage, "--ref", str(args.ref), "--scene", cap_n,
                                  "--fit", "--w", "240", "--h", "240", "--out", out] + extra,
                                 capture_output=True, text=True)
            runs_ok = runs_ok and run.returncode == 0
            tex_loaded = tex_loaded or ("texture P11G00n.png:" in run.stdout)
            if run.returncode:
                print("  modulate render failed: %s" % (run.stderr or run.stdout).strip())
        mism = -1
        if runs_ok and tex_loaded and all(os.path.exists(p) for p in (p_tex, p_col, p_act)):
            wt, ht, rt = png_rows(p_tex)
            wc, hc, rc = png_rows(p_col)
            wa, ha, ra = png_rows(p_act)
            if wt and wt == wc == wa and ht == hc == ha:
                bg = (ra[0][0], ra[0][1], ra[0][2])
                mism = 0
                drawn = 0
                for y in range(ht):
                    at, ac, aa = rt[y], rc[y], ra[y]
                    for x in range(wt):
                        o = x * 4
                        tr_, tg_, tb_ = at[o], at[o + 1], at[o + 2]
                        cr, cg, cb = ac[o], ac[o + 1], ac[o + 2]
                        ar, ag, ab = aa[o], aa[o + 1], aa[o + 2]
                        if (tr_, tg_, tb_) == bg or (cr, cg, cb) == bg:
                            continue        # background is not a drawn pixel
                        drawn += 1
                        if ((tr_ * cr) // 255 != ar or (tg_ * cg) // 255 != ag
                                or (tb_ * cb) // 255 != ab):
                            mism += 1
                print("  %-18s drawn %d, texel*colour/255 mismatches: %d  %s"
                      % ("gouraud modulate", drawn, mism, "ok" if mism == 0 else "BAD"))
        if mism < 0:
            print("  %-18s could not run (texture loaded: %s)  BAD"
                  % ("gouraud modulate", "yes" if tex_loaded else "NO"))
        ok = cov_g is not None and cov_g >= 0.02 and differs_g and mism == 0
        print("  %-18s coverage %5.1f%%, per-pixel != gouraud: %s, default == gouraud: %s  %s"
              % ("gouraud path", 100.0 * (cov_g or 0.0), "yes" if differs_g else "NO",
                 "yes" if default_is_gouraud else "NO",
                 "ok" if ok else "BAD"))
        if not ok:
            bad += 1
        if not default_is_gouraud:
            print("  %-18s the default render is not the game's per-vertex path (finding #591)  BAD"
                  % "gouraud default")
            bad += 1

        # --- the game's own stage fog (the GS fog stage, findings #603/#604) ---------------------
        # The scene path now defaults to the engine's recovered fog: FOG_LINEAR, near 60 / far 300,
        # lerping toward FOGCOL 0xE5CCE5.  The port previously left fog off, so the two things to
        # pin are that the default actually applies it (a scene render differs from --no-fog) and
        # that it does not break the frame (both draw).
        p_fog = os.path.join(tmp, "scene-fog.png")
        p_nofog = os.path.join(tmp, "scene-nofog.png")
        for out, extra in ((p_nofog, ["--no-fog"]), (p_fog, [])):
            subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                            "--ref", str(args.ref), "--scene", cap_n, "--fit",
                            "--w", "240", "--h", "240", "--out", out] + extra,
                           capture_output=True, text=True)
        cov_fog = coverage(p_fog, gl_bg)[0] if os.path.exists(p_fog) else None
        differs = (os.path.exists(p_fog) and os.path.exists(p_nofog) and
                   open(p_fog, "rb").read() != open(p_nofog, "rb").read())
        ok = cov_fog is not None and cov_fog >= 0.02 and differs
        print("  %-18s coverage %5.1f%%, default fog != --no-fog: %s  %s"
              % ("scene fog", 100.0 * (cov_fog or 0.0), "yes" if differs else "NO",
                 "ok" if ok else "BAD"))
        if not ok:
            bad += 1

        # --- the scene TSV's texture column (item 3) ----------------------------------------------
        # A capture row may carry a sixth column naming a live texture (`texture_map.py`).  The
        # per-draw frame-run path must sample it, so a row drawn with the column must differ from the
        # same row without it -- and both must still draw.  The row is the scene's largest mesh, so
        # it is visible through the stage camera (a small mesh can render behind the stage).
        big = max(rows, key=lambda q: int(q[3]) if len(q) > 3 and q[3].isdigit() else 0) \
            if rows else None
        if big is None:
            print("  %-18s no scene tsv rows, skipped" % "scene texture")
        else:
            tid = big[0]
            mt = "1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1"
            cap_t = os.path.join(tmp, "tex-col.tsv")
            cap_u = os.path.join(tmp, "tex-col-none.tsv")
            with open(cap_t, "w") as f:
                f.write("nomatch\t%s\t\t0x0\t%s\tP11G00n.png\n" % (mt, tid))
            with open(cap_u, "w") as f:
                f.write("nomatch\t%s\t\t0x0\t%s\n" % (mt, tid))
            dt = os.path.join(tmp, "tex-col")
            du = os.path.join(tmp, "tex-col-none")
            os.makedirs(dt, exist_ok=True)
            os.makedirs(du, exist_ok=True)
            for cap, d in ((cap_t, dt), (cap_u, du)):
                subprocess.run([args.tool, "render", "--afs", afs_t, "--stage", args.roms,
                                args.stage, "--ref", str(args.ref), "--scene", cap,
                                "--camera", "--frames", "2", "--texentry", "618",
                                "--w", "240", "--h", "168", "--out-dir", d],
                               capture_output=True, text=True)
            pt = os.path.join(dt, "frame_0000.png")
            pu = os.path.join(du, "frame_0000.png")
            if not (os.path.exists(pt) and os.path.exists(pu)):
                print("  %-18s render failed" % "scene texture")
                bad += 1
            else:
                ct, _ = coverage(pt)
                cu, _ = coverage(pu)
                differs = open(pt, "rb").read() != open(pu, "rb").read()
                ok = differs and ct is not None and ct >= 0.02 and (cu or 0) >= 0.02
                print("  %-18s mesh %s textured != flat: %s (coverage %4.1f%% vs %4.1f%%)  %s"
                      % ("scene texture", tid, "yes" if differs else "NO",
                         100.0 * (ct or 0.0), 100.0 * (cu or 0.0), "ok" if ok else "BAD"))
                if not ok:
                    bad += 1

            # --- the texture filter -------------------------------------------------------------
            # The game's own `igTextureAttr` records ask for linear magnification and minification
            # (`_magFilter`/`_minFilter` = 1) on every material that carries a texture -- the crate's
            # `g_woodencasez01`, the barrels, the cave, the floor -- with 0 only on a handful of
            # internal records, and the GS filters accordingly (finding #562).  The port sampled
            # nearest, so the check is a render of that same textured row: `--nearest` must differ
            # from the default and both must still draw.
            fl = os.path.join(tmp, "filt-linear")
            fn = os.path.join(tmp, "filt-nearest")
            os.makedirs(fl, exist_ok=True)
            os.makedirs(fn, exist_ok=True)
            for d, extra in ((fl, []), (fn, ["--nearest"])):
                subprocess.run([args.tool, "render", "--afs", afs_t, "--stage", args.roms,
                                args.stage, "--ref", str(args.ref), "--scene", cap_t,
                                "--camera", "--frames", "2", "--texentry", "618",
                                "--w", "240", "--h", "168", "--out-dir", d] + extra,
                               capture_output=True, text=True)
            pf = os.path.join(fl, "frame_0000.png")
            pn = os.path.join(fn, "frame_0000.png")
            cov_f = coverage(pf)[0] if os.path.exists(pf) else None
            differs = (os.path.exists(pf) and os.path.exists(pn) and
                       open(pf, "rb").read() != open(pn, "rb").read())
            ok = cov_f is not None and cov_f >= 0.02 and differs
            print("  %-18s coverage %5.1f%%, linear != nearest: %s  %s"
                  % ("tex filter", 100.0 * (cov_f or 0.0), "yes" if differs else "NO",
                     "ok" if ok else "BAD"))
            if not ok:
                bad += 1

            # --- the stage-material fallback (`--default-tex`, finding #544) -------------------
            # A scene row the material walk cannot name (the cave shell is RamData/packet-drawn)
            # gets the stage's own material via --default-tex, split by the mesh's mean normal; that
            # must differ from the same row left flat.
            dd = os.path.join(tmp, "tex-default")
            os.makedirs(dd, exist_ok=True)
            subprocess.run([args.tool, "render", "--afs", afs_t, "--stage", args.roms,
                            args.stage, "--ref", str(args.ref), "--scene", cap_u,
                            "--default-tex", "P11G00n.png", "--camera", "--frames", "2",
                            "--texentry", "618", "--w", "240", "--h", "168", "--out-dir", dd],
                           capture_output=True, text=True)
            pd = os.path.join(dd, "frame_0000.png")
            if not os.path.exists(pd):
                print("  %-18s render failed" % "default-tex")
                bad += 1
            else:
                differs = open(pd, "rb").read() != open(pu, "rb").read()
                print("  %-18s --default-tex changes a textureless row: %s  %s"
                      % ("default-tex", "yes" if differs else "NO", "ok" if differs else "BAD"))
                if not differs:
                    bad += 1

        # --- near-plane clipping (finding #544 follow-up) -----------------------------------------
        # The camera sits *inside* a stage's cave, so a triangle straddling the near plane is the
        # common case; dropping it (the old behaviour) left the frame's "gaps".  Render pack 614's
        # 21721 -- a cave shell the recovered Goblin Pass camera is inside -- and require the frame
        # to be covered.  Without the clip this mesh draws nothing at all.
        npl = os.path.join(tmp, "nearplane")
        os.makedirs(npl, exist_ok=True)
        cap_np = os.path.join(tmp, "nearplane.tsv")
        with open(cap_np, "w") as f:
            f.write("-\t1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1\t\t0x0\t21721\tP11G00s.png\n")
        npv = ("0.5 0.495845 0.710027 0 0 0.819868 -0.572552 0 "
               "-0.866025 0.286276 0.409934 0 -115.58885 -299.804123 -223.409985 1")
        r = subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", "614",
                            "--scene", cap_np, "--view", npv, "--fov", "0.6912",
                            "--aspect", "1.0", "--w", "160", "--h", "112", "--out-dir", npl],
                           capture_output=True, text=True)
        pnp = os.path.join(npl, "frame_0000.png")
        if not os.path.exists(pnp):
            print("  %-18s render failed (%s)"
                  % ("near-plane", r.stdout.strip() or r.stderr.strip()))
            bad += 1
        else:
            cnp, _ = coverage(pnp)
            ok = cnp is not None and cnp >= 0.5
            print("  %-18s a camera inside the cave covers the frame: %5.1f%%  %s"
                  % ("near-plane", 100.0 * (cnp or 0.0), "ok" if ok else "BAD"))
            if not ok:
                bad += 1

        # --- the 2D UI overlay (`--ui`, scripts/gs_ui.py) --------------------------------------
        # The port has no UI system, so the HUD is replayed from the draws a `.gs` dump recorded.
        # This check is about the plumbing and the blend only: a hand-made UI TSV with one textured
        # quad and one half-alpha untextured quad over a known area must land where the coordinates
        # say (screen space, no transform), the textured quad must come out red (its texture is red,
        # alpha 128, vertex colour 127 -> modulate ~= identity) and a half-alpha WHITE quad must
        # lighten what is under it (the GS's (Cs-Cd)*As+Cd with As=64/128).
        uis = os.path.join(tmp, "ui")
        os.makedirs(uis, exist_ok=True)
        with open(os.path.join(uis, "REDTEX.rgba"), "wb") as f:
            f.write(struct.pack("<II", 2, 2))
            f.write(bytes([255, 0, 0, 128]) * 4)
        ui_tsv = os.path.join(uis, "ui.tsv")

        def _row(name, x, y, r, g, b, a):
            return ("%s\t%d %d 0 0 %d %d %d %d\t%d %d 1 0 %d %d %d %d\t%d %d 0 1 %d %d %d %d\n"
                    % (name, x, y, r, g, b, a, x + 40, y, r, g, b, a, x, y + 40, r, g, b, a))

        with open(ui_tsv, "w") as f:
            f.write(_row("REDTEX", 40, 40, 127, 127, 127, 128))     # opaque red, sampled at (50,55)
            f.write(_row("-", 100, 40, 127, 127, 127, 64))          # half-alpha white, (110,55)
        uip = os.path.join(tmp, "ui-out")
        uib = os.path.join(tmp, "ui-base")
        os.makedirs(uip, exist_ok=True)
        os.makedirs(uib, exist_ok=True)
        for d, extra in ((uib, []), (uip, ["--ui", ui_tsv, "--uitex", uis])):
            subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", "614",
                            "--scene", cap_np, "--view", npv, "--fov", "0.6912",
                            "--aspect", "1.0", "--w", "160", "--h", "112", "--out-dir", d] + extra,
                           capture_output=True, text=True)
        pui = os.path.join(uip, "frame_0000.png")
        pui_base = os.path.join(uib, "frame_0000.png")
        if not (os.path.exists(pui) and os.path.exists(pui_base)):
            print("  %-18s render failed" % "ui overlay")
            bad += 1
        else:
            try:
                from PIL import Image
                a = Image.open(pui_base).convert("RGB").load()
                b = Image.open(pui).convert("RGB").load()
                drawn = any(b[x, y] != a[x, y] for y in range(45, 80) for x in range(45, 80))
                rr, gg, bb = b[50, 55]
                red_ok = rr > gg + 40 and rr > bb + 40
                # the background under it is mid-grey in the near-plane scene, so a half-alpha
                # WHITE quad must move the pixel by a lot in either direction
                dark_ok = abs(sum(b[110, 55]) - sum(a[110, 55])) >= 10
                ok = drawn and red_ok and dark_ok
                print("  %-18s drawn %s, red (r=%d g=%d b=%d), half-alpha blends (%d -> %d) %s  %s"
                      % ("ui overlay", "yes" if drawn else "NO", rr, gg, bb,
                         sum(a[110, 55]), sum(b[110, 55]), "yes" if dark_ok else "NO",
                         "ok" if ok else "BAD"))
                if not ok:
                    bad += 1
            except ImportError:
                print("  %-18s skipped (no Pillow)" % "ui overlay")

        # --- the perspective-correct form (`#stq`: the GS's raw STQ, divide per pixel) -------------
        # A triangle whose q differs per vertex.  Dividing per *vertex* (the affine form) and per
        # *pixel* (the GS's own `u = s/q`) put different texture coordinates on the interior, so the
        # two forms must not draw the same pixels -- that is the whole reason the second exists.
        with open(os.path.join(uis, "QUADTEX.rgba"), "wb") as f:
            f.write(struct.pack("<II", 2, 2))
            for px in ((255, 0, 0, 255), (0, 255, 0, 255), (0, 0, 255, 255), (255, 255, 255, 255)):
                f.write(bytes(px))
        stq_tsv = os.path.join(uis, "stq.tsv")
        apx_tsv = os.path.join(uis, "stq-affine.tsv")
        # the same three corners either way: (s,t,q) raw, and the same thing pre-divided per vertex
        corners = [(20, 20, 0.0, 0.0, 1.0), (90, 20, 1.0, 0.0, 0.5), (20, 90, 0.0, 1.0, 2.0)]
        with open(stq_tsv, "w") as f:
            f.write("#stq\n")
            f.write("QUADTEX\t%s\n" % "\t".join(
                "%d %d %.6f %.6f %.6f 127 127 127 128" % c for c in corners))
        with open(apx_tsv, "w") as f:
            f.write("QUADTEX\t%s\n" % "\t".join(
                "%d %d %.6f %.6f 127 127 127 128" % (x, y, s / q, t / q) for (x, y, s, t, q) in corners))
        p_stq = os.path.join(tmp, "stq-out")
        p_apx = os.path.join(tmp, "stq-affine-out")
        for d, tsv in ((p_stq, stq_tsv), (p_apx, apx_tsv)):
            os.makedirs(d, exist_ok=True)
            subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", "614",
                            "--scene", cap_np, "--view", npv, "--fov", "0.6912",
                            "--aspect", "1.0", "--w", "160", "--h", "112", "--out-dir", d,
                            "--ui", tsv, "--uitex", uis], capture_output=True, text=True)
        if not (os.path.exists(os.path.join(p_stq, "frame_0000.png"))
                and os.path.exists(os.path.join(p_apx, "frame_0000.png"))):
            print("  %-18s render failed" % "ui perspective")
            bad += 1
        else:
            try:
                from PIL import Image
                a = Image.open(os.path.join(p_apx, "frame_0000.png")).convert("RGB").load()
                b = Image.open(os.path.join(p_stq, "frame_0000.png")).convert("RGB").load()
                n = sum(1 for y in range(20, 90) for x in range(20, 90) if a[x, y] != b[x, y])
                ok = n > 100                       # the interior really is sampled differently
                print("  %-18s per-pixel STQ differs from per-vertex on %d px  %s"
                      % ("ui perspective", n, "ok" if ok else "BAD"))
                if not ok:
                    bad += 1
            except ImportError:
                print("  %-18s skipped (no Pillow)" % "ui perspective")

        # --- the on-frame readout (`--fps` / `--osd-text`) ---------------------------------------
        # The counter must land in the top-left band and leave the rest of the frame alone, and the
        # glyphs must actually be the string asked for: two different strings cannot render alike,
        # and a longer string cannot be the same width.  (`--fps` itself is timing-dependent, so the
        # fixed-string form is what a check can pin.)
        readouts = {}
        for label, text in (("a", "60 fps"), ("b", "144 fps"), ("c", "0.0 fps")):
            d = os.path.join(tmp, "osd-" + label)
            os.makedirs(d, exist_ok=True)
            subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", "614",
                            "--scene", cap_np, "--view", npv, "--fov", "0.6912", "--aspect", "1.0",
                            "--w", "160", "--h", "112", "--out-dir", d, "--osd-text", text],
                           capture_output=True, text=True)
            p = os.path.join(d, "frame_0000.png")
            readouts[label] = p if os.path.exists(p) else None
        if not all(readouts.values()):
            print("  %-18s render failed" % "osd readout")
            bad += 1
        else:
            try:
                from PIL import Image
                img = {k: Image.open(v).convert("RGB").load() for k, v in readouts.items()}
                # the glyphs are white; the plate only darkens, so white is the readout's own ink
                ink = sum(1 for y in range(0, 26) for x in range(0, 90) if img["a"][x, y][0] > 200)
                band = sum(1 for y in range(0, 26) for x in range(0, 90))
                # outside the top-left band the frame must be untouched by the readout
                base = os.path.join(tmp, "osd-none")
                os.makedirs(base, exist_ok=True)
                subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", "614",
                                "--scene", cap_np, "--view", npv, "--fov", "0.6912",
                                "--aspect", "1.0", "--w", "160", "--h", "112", "--out-dir", base],
                               capture_output=True, text=True)
                ref = Image.open(os.path.join(base, "frame_0000.png")).convert("RGB").load()
                outside = sum(1 for y in range(26, 112) for x in range(0, 160)
                              if img["a"][x, y] != ref[x, y])
                differs = sum(1 for y in range(0, 26) for x in range(0, 160)
                              if img["a"][x, y] != img["b"][x, y])
                ok = ink > 20 and outside == 0 and differs > 20
                print("  %-18s ink %d/%d px top-left, %d px changed outside it, two strings differ "
                      "on %d px  %s" % ("osd readout", ink, band, outside, differs,
                                        "ok" if ok else "BAD"))
                if not ok:
                    bad += 1
            except ImportError:
                print("  %-18s skipped (no Pillow)" % "osd readout")

        # --- the replay's threads must not change a pixel -----------------------------------------
        # The draws have to stay in order (the blends compose), so parallelism splits the frame's rows
        # and every band replays the whole list.  A draw only writes inside its own bbox, so the bands
        # write exactly what the serial pass wrote -- asserted here, because a mistake would be a
        # subtle seam rather than a crash.  Large, overlapping, blended triangles spanning many rows
        # exercise both the banding and the overlaps.
        big = os.path.join(tmp, "ui-big.tsv")
        with open(big, "w") as f:
            f.write("#stq\n")
            for i in range(12):                       # diagonal bands of blended, overlapping tris
                o = i * 9
                f.write("REDTEX\t%d %d 0 0.02\t%d %d 40 0.02\t%d %d 0 40 0.02\t1\n"
                        % (o, 0, o + 120, 0, o, 112))
            for i in range(12):                       # and additive ones over them
                o = i * 7
                f.write("-\t%d %d 0 0\t%d %d 1 0\t%d %d 0 1\t2\n"
                        % (o + 20, 10, o + 90, 10, o + 20, 70))
        th = {}
        for n in (1, 8):
            d = os.path.join(tmp, "ui-th%d" % n)
            os.makedirs(d, exist_ok=True)
            subprocess.run([args.tool, "render", "--afs", afs_t, "--entry", "614",
                            "--scene", cap_np, "--view", npv, "--fov", "0.6912", "--aspect", "1.0",
                            "--w", "160", "--h", "112", "--out-dir", d,
                            "--ui", big, "--uitex", uis, "--ui-threads", str(n)],
                           capture_output=True, text=True)
            th[n] = os.path.join(d, "frame_0000.png")
        if not (os.path.exists(th[1]) and os.path.exists(th[8])):
            print("  %-18s render failed" % "ui threads")
            bad += 1
        else:
            try:
                from PIL import Image
                one = Image.open(th[1]).convert("RGB")
                many = Image.open(th[8]).convert("RGB")
                differing = sum(1 for p, q in zip(one.getdata(), many.getdata()) if p != q)
                ok = differing == 0 and one.size[1] >= 64
                print("  %-18s 1 thread vs 8: %d px differ over %d  %s"
                      % ("ui threads", differing, one.size[0] * one.size[1], "ok" if ok else "BAD"))
                if not ok:
                    bad += 1
            except ImportError:
                print("  %-18s skipped (no Pillow)" % "ui threads")

        # --- live textures from a RAM dump (`--livedump`, P4.1's material residual) ---------------
        # A stage pack's texture list does not carry every material: the character's texture is an
        # `igPsx2Image` reachable only through the live object graph (finding #525's residual).
        # With a dump, `livetex` must find them and the scene renderer must sample the one a row
        # names, so a row textured from the dump differs from the same row untextured.
        if not args.livedump or not os.path.exists(args.livedump):
            print("  %-18s no --livedump, skipped" % "live texture")
        else:
            r = subprocess.run([args.tool, "livetex", args.livedump, "--list"],
                               capture_output=True, text=True)
            found = [l.strip() for l in r.stdout.splitlines()]
            name = "E_ogre01.png" if any("E_ogre01.png" == f for f in found) else None
            if name is None or len(found) < 20:
                print("  %-18s livetex found %d names, %s missing  BAD"
                      % ("live texture", len(found), "E_ogre01.png"))
                bad += 1
            else:
                dl = os.path.join(tmp, "live-tex")
                du = os.path.join(tmp, "live-tex-none")
                os.makedirs(dl, exist_ok=True)
                os.makedirs(du, exist_ok=True)
                mt = "1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1"
                cap_l = os.path.join(tmp, "live-tex.tsv")
                cap_u = os.path.join(tmp, "live-tex-none.tsv")
                with open(cap_l, "w") as f:
                    f.write("nomatch\t%s\t\t0x0\t%s\t%s\n" % (mt, tid, name))
                with open(cap_u, "w") as f:
                    f.write("nomatch\t%s\t\t0x0\t%s\n" % (mt, tid))
                for cap, d in ((cap_l, dl), (cap_u, du)):
                    subprocess.run([args.tool, "render", "--afs", afs_t, "--stage", args.roms,
                                    args.stage, "--ref", str(args.ref), "--scene", cap,
                                    "--camera", "--frames", "2", "--livedump", args.livedump,
                                    "--w", "240", "--h", "168", "--out-dir", d],
                                   capture_output=True, text=True)
                pl = os.path.join(dl, "frame_0000.png")
                pu = os.path.join(du, "frame_0000.png")
                if not (os.path.exists(pl) and os.path.exists(pu)):
                    print("  %-18s render failed" % "live texture")
                    bad += 1
                else:
                    cl, _ = coverage(pl)
                    cu, _ = coverage(pu)
                    differs = open(pl, "rb").read() != open(pu, "rb").read()
                    ok = differs and (cl or 0) >= 0.02 and (cu or 0) >= 0.02
                    print("  %-18s %d name(s); dump-textured != flat: %s"
                          " (coverage %4.1f%% vs %4.1f%%)  %s"
                          % ("live texture", len(found), "yes" if differs else "NO",
                             100.0 * (cl or 0.0), 100.0 * (cu or 0.0), "ok" if ok else "BAD"))
                    if not ok:
                        bad += 1

        # --- the stage camera (findings #495/#496) ---------------------------------------------
        # The pack's own camera node composes child x parent into a world matrix; its translation is
        # the measured (0, 102.490, 74.565).  This is pure pack data: if the composition breaks (a
        # parent link lost, the multiply order flipped, the chain truncated) the number moves, which
        # is what the identity-camera confusion at the last handoff was.
        r = subprocess.run([args.tool, "scene", "--stage", args.roms, args.stage,
                            "--ref", str(args.ref), "--cam"], capture_output=True, text=True)
        line = next((l for l in r.stdout.splitlines() if l.startswith("stage camera:")), "")
        want = (0.0, 102.490, 74.565)
        got = None
        if "world pos (" in line:
            try:
                vals = line.split("world pos (", 1)[1].rstrip(") ").split()
                got = tuple(float(v) for v in vals[:3])
            except ValueError:
                got = None
        ok = got is not None and all(abs(got[i] - want[i]) < 0.05 for i in range(3))
        print("  %-18s stage camera %s at %s (want %.3f %.3f %.3f)  %s"
              % (args.stage, "node" if got else "MISSING",
                 ("(%.3f %.3f %.3f)" % got) if got else "-", want[0], want[1], want[2],
                 "ok" if ok else "BAD"))
        if not ok:
            print("     %s" % line.strip())
            bad += 1

        # the whole-stage framing: render the placed stage through that camera, twice, and require
        # a non-degenerate deterministic frame.  Needs the live capture (placement is not in the
        # pack, finding #484), so it is skipped rather than faked when no capture was supplied.
        if args.scene and os.path.exists(args.scene):
            outs = []
            for run in (0, 1):
                d = os.path.join(tmp, "stage%d" % run)
                os.makedirs(d, exist_ok=True)
                r = subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                                    "--ref", str(args.ref), "--scene", args.scene, "--camera",
                                    "--w", "320", "--h", "224", "--out-dir", d],
                                   capture_output=True, text=True)
                if r.returncode != 0:
                    print("  stage framing render failed: %s" % (r.stderr.strip() or r.stdout.strip()))
                    bad += 1
                    break
                outs.append(os.path.join(d, "frame_0000.png"))
            if len(outs) == 2:
                cov, _ = coverage(outs[0])
                same = open(outs[0], "rb").read() == open(outs[1], "rb").read()
                # the measured camera fills the frame (389 of 702 placements on screen, #496), so
                # the frame must be substantially covered -- a floor well above a dot.  (An
                # interior stage legitimately covers ~everything; the floor is what catches the
                # 'auto-fit zoomed to one cluster' failure.)
                ok = cov is not None and cov >= 0.10 and same
                print("  %-18s stage frame through the pack camera: coverage %5.1f%%, "
                      "two runs identical: %s  %s"
                      % (args.stage, 100.0 * (cov or 0.0), "yes" if same else "NO",
                         "ok" if ok else "BAD"))
                if not ok:
                    bad += 1
                # the same placed stage through the GPU backend, same camera (P4.1)
                gd = os.path.join(tmp, "stagegl")
                os.makedirs(gd, exist_ok=True)
                rg = subprocess.run([args.tool, "render", "--stage", args.roms, args.stage,
                                     "--ref", str(args.ref), "--scene", args.scene, "--camera",
                                     "--gl", "--w", "320", "--h", "224", "--out-dir", gd],
                                    capture_output=True, text=True)
                if "not compiled in" in (rg.stdout + rg.stderr):
                    print("  %-18s GPU backend not compiled in, skipped" % "stage+gl")
                elif rg.returncode != 0:
                    print("  %-18s GPU stage render failed: %s"
                          % ("stage+gl", (rg.stderr or rg.stdout).strip()))
                    bad += 1
                else:
                    gcov, _ = coverage(os.path.join(gd, "frame_0000.png"), (18, 22, 30))
                    gok = gcov is not None and gcov >= 0.10
                    print("  %-18s stage frame through the pack camera (GPU): coverage %5.1f%%  %s"
                          % (args.stage, 100.0 * (gcov or 0.0), "ok" if gok else "BAD"))
                    if not gok:
                        bad += 1
        elif args.scene:
            print("  stage framing: capture %s not found, skipped" % args.scene)
        else:
            print("  stage framing: no capture supplied (pass --scene capture.tsv to render it)")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
