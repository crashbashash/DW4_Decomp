#!/usr/bin/env python3
"""verify_pose.py — pin the P4.1 player-pose chain (the per-bone VU palette).

The chain (findings #596/#599): the player's skin is drawn from a per-bone matrix
palette staged in the VU/DMA packet area (goblin-pass combat instant: 0x1b753b0,
24 matrices, indexed by the raw per-vertex bone byte — identity mapping, no
igBlendMatrixSelect indirection).  Shape0 (354 verts) is NOT drawn in that frame;
the visible draw is Skin0Shape1 (3580 verts) + Skin0Shape2 (2018).  Shape1 fits the
native GS draw at median 0.0057 model units single-bone; shape2 at ~0.03 (its
residuals are sub-pixel at this camera and its blend structure is unresolved —
do not "fix" it silently).

What is verified here, when the artifacts are on disk (all skipped otherwise, so
`make check` stays green on a machine without them):

  1. the C render accepts select=0 (identity) + the per-bone palette and skins
     both shapes;
  2. the character metric box stays under its regression bound (it was 27.1 in
     the bind pose, 29.2 with the wrong shape0+old palette; the pose chain gets
     ~23 and the box's remaining error is reference-side contamination — the
     striped/overlaid game fb — not geometry).

Set DW4_LIVEDUMP to the 31 MB EE dump and DW4_POSE_ARTIFACTS to the directory
holding gs_char_model2.npy + char_runs.pkl (the scratch/pose-solve staging) to
enable; DW4_POSE_REF names the ground-truth frame png.
"""
import os
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)

DUMP = os.environ.get("DW4_LIVEDUMP", "")
ARTS = os.environ.get("DW4_POSE_ARTIFACTS",
                      os.path.join(PORT, "..", "scratch", "pose-solve"))
REF = os.environ.get("DW4_POSE_REF",
                     os.path.join(ARTS, "regen-artifacts", "combat-fb-frame.png"))
ROMS = os.environ.get("DW4_ROMS", os.path.join(PORT, "..", "..", "local/extracted"))
CHAR_BOUND = 26.0     # regression bound; the measured value is ~22.8-23.1
BIND_PAST = 27.1      # the bind-pose value this chain had to beat

VIEW = ("0.5 0.495845 0.710027 0 0 0.819868 -0.572552 0 -0.866025 0.286276 "
        "0.409934 0 -115.58885 -299.804123 -223.409985 1")


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True)


def main():
    tool = os.path.join(PORT, "build", "dw4asset")
    if not os.path.exists(tool):
        print("  pose: build first (make), skipped")
        return 0
    if not (DUMP and os.path.exists(DUMP)):
        print("  pose: no DW4_LIVEDUMP, skipped")
        return 0
    stage = os.path.join(ROMS, "NDMW.AFS")
    if not os.path.exists(stage):
        print("  pose: no local/extracted, skipped")
        return 0

    # the scene tsv the render consumes: regenerate it (camera_match, ~5 min) or
    # take the staged copy the last measurement left
    tsv = os.environ.get("DW4_POSE_TSV", "/tmp/pose_check_cam.tsv")
    if not os.path.exists(tsv):
        cm = run([sys.executable, os.path.join(PORT, "..", "scripts", "camera_match.py"),
                  "--from", DUMP, "--pack", os.path.join(ROMS, "NDMW.AFS:614"),
                  "--target", "421.83", "72", "-110.07", "--character", "P_susanoo_Skin0",
                  "--character-pack", os.path.join(ROMS, "NDMW.AFS:861"),
                  "--character-tex", "P_susanoo01.png",
                  "--prop", "M_BK17v1_barrelsShape@0x14df9d0",
                  "--prop", "M_BK19a0_boxShape@0x130a858",
                  "--prop-tex", "g_bbarrelsz01@M_BK17v1_barrelsShape",
                  "--prop-tex", "g_woodencasez01@M_BK19a0_boxShape",
                  "--texdir", "/tmp/proptex", "--tsv", tsv, "--textures", "--stage-material"])
        if cm.returncode != 0:
            print("  pose: camera_match failed:\n%s" % cm.stderr)
            return 1
        # shape0 is not drawn in this frame (finding #599); drop its id from the row
        rows = open(tsv).read().replace("5475,5485,5882", "5485,5882")
        open(tsv, "w").write(rows)

    with tempfile.TemporaryDirectory() as tmp:
        r = run([tool, "render", "--stage", ROMS, "stag0101.igb", "--ref", "1",
                 "--scene", tsv, "--livedump", DUMP, "--pack2",
                 os.path.join(ROMS, "NDMW.AFS:861"), "--texdir", "/tmp/proptex",
                 "--view", VIEW, "--fov", "0.6912", "--aspect", "1.0",
                 "--w", "640", "--h", "448", "--out-dir", tmp,
                 "--pose-select", "0", "--pose-palette", "0x1b753b0",
                 "--pose-count", "24", "--pose-node", "0x16de170"])
        if r.returncode != 0:
            print("  pose: the C render failed:\n%s%s" % (r.stdout, r.stderr))
            return 1
        if "2 mesh(es) skinned" not in r.stdout:
            print("  pose: the render did not skin the character:\n%s" % r.stdout)
            return 1
        frame = os.path.join(tmp, "frame_0000.png")
        if not os.path.exists(frame):
            print("  pose: no frame written")
            return 1
        if not os.path.exists(REF):
            print("  pose: skinned ok, no reference frame (%s), metric skipped" % REF)
            return 0
        m = run([sys.executable, os.path.join(HERE, "frame_metric.py"),
                 "--ref", REF, "--blur", "1.2", frame])
        if m.returncode != 0:
            print("  pose: frame_metric failed:\n%s%s" % (m.stdout, m.stderr))
            return 1
        vals = {}
        for line in m.stdout.splitlines():
            f = line.split()
            if f and f[0].endswith(".png") or f and f[0].startswith("frame"):
                vals = dict(zip(f[0::1], []))  # fall through to the header parse below
        # frame_metric prints a header row then one row per frame; parse the last row
        lines = [l.split() for l in m.stdout.strip().splitlines() if l.strip()]
        header = lines[0][1:]
        last = lines[-1]
        vals = dict(zip(header, last[1:]))
        char = float(vals["character"])
        print("  pose: char-box metric %.2f (bind was %.1f, bound %.1f)"
              % (char, BIND_PAST, CHAR_BOUND))
        if char >= CHAR_BOUND:
            print("  pose: REGRESSED above the bound")
            return 1
        return 0


if __name__ == "__main__":
    sys.exit(main())
