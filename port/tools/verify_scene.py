#!/usr/bin/env python3
"""verify_scene.py — the scene loader against the file reader and the repository's decoder.

`dw4asset scene` is not a second reader: it is the *loader*.  It walks a pack's id table, places
every id's payload in one arena and records a 32-bit handle for it, then reads the geometry back
through those handles — which is what the engine's own loader does.  So three
things have to hold, and this is where they are checked:

1. **the arena is the file.**  `scene --check` asserts that every id is placed in order, exactly
   once, and that its payload is byte-for-byte the file's bytes for that id, and that every mesh
   handle resolves — 50,497 ids for the model pack;
2. **the route is the game's.**  The same pack is opened the way the game reaches it —
   `stag0102.igb`'s own `[0.621]` reference, not an archive index — and that is
   what the OBJ comparison uses;
3. **the references are the pack's ids.**  Every `igObjectRef`/`igMemoryRef` value is rewritten
   from its id into a handle — the id -> pointer pass — with the kind taken from the
   value's own descriptor (type 0 is always an object id or NULL and type 7 always a
   pool-block id or NULL).  The loader counts this on the pack it loaded and the count must show
   **0 NEITHER**, which is the C-side check of that finding;
4. **the meshes are the extractor's.**  `scene --out-dir` and `models --out-dir` and
   `DW4_Decomp/scripts/igb_models.py --out-dir` write the same files, byte for byte (the filenames
   carry the DCC shape names, so those are compared too).

  tools/verify_scene.py [--tool build/dw4asset] [--roms <dir>] [--repo <DW4_Decomp>]
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_ROMS = os.path.join(PORT, "..", "..", "local/extracted")
DEFAULT_REPO = os.path.join(PORT, "..")
STAGE = "stag0102.igb"
REF = 1                      # stag0102.igb's [0.621] -- the model pack
ENTRY = 621


def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def diff_dirs(a, b, label):
    ca, cb = sorted(os.listdir(a)), sorted(os.listdir(b))
    if ca != cb:
        only_a = [n for n in ca if n not in cb][:4]
        only_b = [n for n in cb if n not in ca][:4]
        return "%s: %d vs %d files (only in scene: %s; only in the other: %s)" % (
            label, len(ca), len(cb), only_a, only_b)
    for n in ca:
        if open(os.path.join(a, n), "rb").read() != open(os.path.join(b, n), "rb").read():
            return "%s: %s differs" % (label, n)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4asset"))
    ap.add_argument("--roms", default=DEFAULT_ROMS)
    ap.add_argument("--repo", default=DEFAULT_REPO)
    ap.add_argument("--entry", type=int, default=ENTRY)
    ap.add_argument("--ref", type=int, default=REF)
    args = ap.parse_args()
    py = os.path.join(args.repo, "scripts", "igb_models.py")
    afs = os.path.join(args.roms, "NDMW.AFS")
    for p in (args.tool, py, afs):
        if not os.path.exists(p):
            print("  missing %s" % p)
            return 2

    bad = 0
    # 1 + 2: the loader's own contract, reached the way the game reaches its pack
    c = run([args.tool, "scene", "--stage", args.roms, STAGE, "--ref", str(args.ref),
             "--check"])
    line = [l for l in c.stdout.splitlines() if l.startswith("scene ")]
    chk = [l for l in c.stdout.splitlines() if l.strip().startswith("check:")]
    ref = [l for l in c.stdout.splitlines() if l.strip().startswith("id->pointer:")]
    if c.returncode != 0 or not chk or " 0 payload(s) differ from the file" not in chk[0] \
            or " 0 mesh handle(s) broken" not in chk[0] or " 0 id(s) placed in order" in chk[0]:
        print("  the scene loader's own check failed")
        print(c.stdout + c.stderr)
        return 1
    print("  %s" % (line[0] if line else ""))
    print("  %s" % chk[0].strip())
    # the id -> pointer pass: reference-typed values become handles, and no
    # value of a reference type is ever outside the id space
    if not ref or " 0 NEITHER" not in ref[0] or " 0 reference(s) rewritten" in ref[0]:
        print("  the id -> pointer pass did not report cleanly: %s" % (ref or "no line"))
        return 1
    print("  %s" % ref[0].strip())
    # the check line reports "N id(s) placed in order" only when nothing was out of order, so it
    # is the "0 out of order" assertion; fail loudly if the wording ever changes
    if "placed in order" not in chk[0]:
        print("  the check line does not report in-order placement any more")
        bad += 1

    with tempfile.TemporaryDirectory() as tmp:
        sd, md, pd = (os.path.join(tmp, n) for n in ("scene", "models", "python"))
        for d in (sd, md, pd):
            os.mkdir(d)
        runs = [
            (run([args.tool, "scene", "--stage", args.roms, STAGE, "--ref", str(args.ref),
                  "--out-dir", sd]), sd, "scene"),
            (run([args.tool, "models", "--afs", afs, "--entry", str(args.entry),
                  "--out-dir", md]), md, "models"),
            (run([sys.executable, py, "--afs", afs, "--entry", str(args.entry),
                  "--out-dir", pd]), pd, "python"),
        ]
        for r, _d, name in runs:
            if r.returncode != 0:
                print("  %s failed:\n%s%s" % (name, r.stdout, r.stderr))
                bad += 1
        # the OBJ directories collapse a repeated name to one file, so the *counts* are compared
        # separately; both sides must place the same number of meshes
        counts = {}
        m = re.search(r"extracted (\d+), skipped", runs[1][0].stdout)
        if m:
            counts["models"] = int(m.group(1))
        m = re.search(r"(\d+) mesh\(es\)", line[0] if line else "")
        if m:
            counts["scene"] = int(m.group(1))
        if len(set(counts.values())) > 1:
            print("  mesh counts differ: %s" % counts)
            bad += 1
        if not bad:
            for other, label in ((md, "models"), (pd, "python")):
                why = diff_dirs(sd, other, label)
                if why:
                    print("  %s" % why)
                    bad += 1
            if not bad:
                print("  %s meshes, %d distinct name(s), OBJ bytes identical across"
                      " scene / models / python" % (counts.get("scene", "?"), len(os.listdir(sd))))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
