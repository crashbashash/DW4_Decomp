#!/usr/bin/env python3
"""verify_fog.py — pin the GS fog stage on the port's scene path (findings #603/#604).

The engine's stage fog is a FOG_LINEAR program in view-space depth, near 60 / far 300, lerping
toward FOGCOL 0xE5CCE5 (recovered from the same-instant GS dump: the per-vertex F in the packed
`XYZF2` 4th dword is linear in the view depth to 0.22/255, and the framebuffer is
`out = C*(F/255) + FOGCOL*(1 - F/255)`).  The port now applies it by default on a scene render.

What is verified here, when the artifacts are on disk (all skipped otherwise, so `make check` stays
green on a machine without them):

  1. the scene render accepts the default fog and `--no-fog` and produces a different frame;
  2. the fogged frame is *better* against the captured native framebuffer at `--blur 1.2` -- the
     whole-frame mean |delta| must drop (the pre-fog baseline was 14.7 on this capture), which is
     the ship criterion the finding carries.

Set DW4_LIVEDUMP to the 31 MB EE dump; DW4_FOG_TSV / DW4_FOG_TEXDIR to the scene capture and the
inline prop textures; DW4_FOG_REF to the native reference frame.
"""
import os
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
WS = os.path.dirname(os.path.dirname(PORT))

DUMP = os.environ.get("DW4_LIVEDUMP", "")
TSV = os.environ.get("DW4_FOG_TSV",
                     os.path.join(WS, "local", "captures", "dw4-port", "live-camera",
                                  "pose-solved-20261002", "cam.tsv"))
TEXDIR = os.environ.get("DW4_FOG_TEXDIR", "/tmp/proptex")
REF = os.environ.get("DW4_FOG_REF",
                     os.path.join(PORT, "build", "pose-solve", "regen-artifacts",
                                  "combat-fb-frame.png"))
ROMS = os.environ.get("DW4_ROMS", os.path.join(WS, "local/extracted"))
POSE_ARTS = os.environ.get("DW4_POSE_ARTIFACTS", os.path.join(PORT, "build", "pose-solve"))
# the pre-fog whole-frame baseline this check must beat, and the headroom bound the fog achieves.
# (This check renders without the HUD overlay, so the baseline is 15.90 here; on the full render the
# overlay-carrying baseline is 14.70 and the fog takes it to 10.96 -- both shown in the finding.)
WHOLE_PRE_FOG = 15.90
WHOLE_BOUND = 12.50

VIEW = ("0.5 0.495845 0.710027 0 0 0.819868 -0.572552 0 -0.866025 0.286276 "
        "0.409934 0 -115.58885 -299.804123 -223.409985 1")


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True)


def whole(frame):
    m = run([sys.executable, os.path.join(HERE, "frame_metric.py"),
             "--ref", REF, "--blur", "1.2", frame])
    lines = [l.split() for l in m.stdout.strip().splitlines() if l.strip()]
    return float(dict(zip(lines[0][1:], lines[-1][1:]))["whole"])


def render(extra, outdir):
    return run([os.path.join(PORT, "build", "dw4asset"), "render", "--stage", ROMS,
                "stag0101.igb", "--ref", "1", "--scene", TSV, "--livedump", DUMP,
                "--pack2", os.path.join(ROMS, "NDMW.AFS:861"), "--texdir", TEXDIR,
                "--view", VIEW, "--fov", "0.6912", "--aspect", "1.0",
                "--w", "640", "--h", "448", "--out-dir", outdir,
                "--pose-select", "0", "--pose-palette", "0x1b753b0",
                "--pose-count", "24", "--pose-node", "0x16de170"] + extra)


def main():
    tool = os.path.join(PORT, "build", "dw4asset")
    if not os.path.exists(tool):
        print("  fog: build first (make), skipped")
        return 0
    if not (DUMP and os.path.exists(DUMP)):
        print("  fog: no DW4_LIVEDUMP, skipped")
        return 0
    for p in (TSV, REF):
        if not os.path.exists(p):
            print("  fog: %s missing, skipped" % p)
            return 0
    if not os.path.exists(os.path.join(TEXDIR, "g_woodencasez01.rgba")):
        print("  fog: no inline prop textures in %s, skipped" % TEXDIR)
        return 0
    with tempfile.TemporaryDirectory() as tmp:
        d_on = os.path.join(tmp, "on")
        d_off = os.path.join(tmp, "off")
        os.makedirs(d_on)
        os.makedirs(d_off)
        r_on = render([], d_on)
        r_off = render(["--no-fog"], d_off)
        if r_on.returncode or r_off.returncode:
            print("  fog: render failed:\n%s%s%s%s"
                  % (r_on.stdout, r_on.stderr, r_off.stdout, r_off.stderr))
            return 1
        f_on = os.path.join(d_on, "frame_0000.png")
        f_off = os.path.join(d_off, "frame_0000.png")
        if not (os.path.exists(f_on) and os.path.exists(f_off)):
            print("  fog: no frame written")
            return 1
        differs = open(f_on, "rb").read() != open(f_off, "rb").read()
        w_on = whole(f_on)
        w_off = whole(f_off)
        ok = differs and w_on < w_off and w_on <= WHOLE_BOUND and w_off > WHOLE_BOUND
        print("  fog: whole %0.2f with fog vs %0.2f without (pre-fog baseline %.2f, bound %.1f);"
              " frames differ: %s  %s"
              % (w_on, w_off, WHOLE_PRE_FOG, WHOLE_BOUND, "yes" if differs else "NO",
                 "ok" if ok else "BAD"))
        return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
