#!/usr/bin/env python3
"""verify_models.py — diff the C model reader against the repository's Python decoder.

The port's `dw4asset models` and DW4_Decomp/scripts/igb_models.py implement the same rules
(the geometry chain of finding #477 and the 4-byte pool alignment of finding #478), so they
must agree on every geometry attribute of a model pack: the stream ids, the counts and the
OBJ bytes (positions, UVs and triangles).  This is the model half of `make check`, and the
OBJ diff is what makes it strong -- a wrong stream offset or a triangle rule shows up as
different text, not as a count that happens to match.

  tools/verify_models.py [--tool build/dw4asset] [--afs <NDMW.AFS>] [entries...]
"""
import argparse
import os
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_AFS = os.path.join(PORT, "..", "..", "local/extracted", "NDMW.AFS")
DEFAULT_REPO = os.path.join(PORT, "..")
ENTRIES = [621, 179, 642, 861]   # model packs: stag0102, another stage, stag0201, and the
                                 # player's character pack (entry 861, the odd-alignment case)


def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def diff_dirs(a, b):
    ca = sorted(os.listdir(a))
    cb = sorted(os.listdir(b))
    if ca != cb:
        return "%d files vs %d" % (len(ca), len(cb))
    for n in ca:
        if open(os.path.join(a, n), "rb").read() != open(os.path.join(b, n), "rb").read():
            return "%s differs" % n
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4asset"))
    ap.add_argument("--afs", default=DEFAULT_AFS)
    ap.add_argument("--repo", default=DEFAULT_REPO)
    ap.add_argument("entries", nargs="*", type=int)
    args = ap.parse_args()
    entries = args.entries or ENTRIES
    py = os.path.join(args.repo, "scripts", "igb_models.py")
    if not os.path.exists(py):
        print("  set --repo to the decompilation checkout")
        return 2

    bad = 0
    for entry in entries:
        c_head = run([args.tool, "models", "--afs", args.afs, "--entry", str(entry),
                      "--tsv"])
        p_head = run([sys.executable, py, "--afs", args.afs, "--entry", str(entry), "--tsv"])
        if c_head.returncode != 0 or p_head.returncode != 0:
            print("  entry %d: C exit %d, python exit %d" % (entry, c_head.returncode,
                                                             p_head.returncode))
            print(c_head.stderr + p_head.stderr)
            bad += 1
            continue
        cl, pl = c_head.stdout.splitlines(), p_head.stdout.splitlines()
        # the two summary lines (pool accounting and attribute count) and then the rows
        if cl[:2] != pl[:2]:
            print("  entry %d: summary differs\n    C: %s\n    P: %s"
                  % (entry, cl[:2], pl[:2]))
            bad += 1
            continue
        crows, prows = cl[2:], pl[2:]
        if crows != prows:
            n = next(i for i in range(max(len(crows), len(prows)))
                     if crows[i:i + 1] != prows[i:i + 1])
            print("  entry %d: row %d differs\n    C: %s\n    P: %s"
                  % (entry, n, crows[n:n + 1], prows[n:n + 1]))
            bad += 1
            continue
        with tempfile.TemporaryDirectory() as tmp:
            cd, pd = os.path.join(tmp, "c"), os.path.join(tmp, "p")
            os.mkdir(cd)
            os.mkdir(pd)
            for tool, out in ((run([args.tool, "models", "--afs", args.afs, "--entry",
                                    str(entry), "--out-dir", cd]), cd),
                              (run([sys.executable, py, "--afs", args.afs, "--entry",
                                    str(entry), "--out-dir", pd]), pd)):
                if tool.returncode != 0:
                    print("  entry %d: extractor failed: %s" % (entry, tool.stderr))
                    bad += 1
            if not bad:
                why = diff_dirs(cd, pd)
                if why:
                    print("  entry %d: OBJ output differs: %s" % (entry, why))
                    bad += 1
                else:
                    print("  entry %-4d %s, %d models, OBJ bytes identical  ok"
                          % (entry, cl[0].strip(), len(crows)))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
