#!/usr/bin/env python3
"""permdecl.py FUNCTION CANDIDATE "decl1|decl2|..." [--configs def,alt3,alt3p] [--random N] [--unit-objects FILE] [--extra-flags FLAGS]

Declaration-order search for register-colour near misses.

The ids that decide the graph colouring of function-level variables follow their declaration order
(docs/engine/register-allocation.md), and `regalloc.py` often cannot say which order is needed ("structural"). This tool
takes a candidate whose local declarations stand on consecutive lines of the function, compiles every permutation of those
lines (or N random shuffles when there are more than six) under the chosen profiles and reports the best ones. The first
exact `MATCH` is written to the scratch directory as `MATCH_<function>_<config>.<ext>`.

  def    default compiler, `-O3`
  alt3   pinned alternate compiler, `-O3`
  alt3p  pinned alternate compiler, `-O3,p`

The declaration lines must appear verbatim, one per line with four spaces of indentation, exactly as listed. Candidates
that need a unit-object overlay (callee compiled first in the same unit) pass `--unit-objects`.
"""
import argparse
import itertools
import os
import random
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ALT = "local/mwcps2/combat/mwccps2.exe"
CONFIGS = {"def": ("-O3 -Iinclude", []), "alt3": ("-O3 -Iinclude", ["--mwcc", ALT]),
           "alt3p": ("-O3,p -Iinclude", ["--mwcc", ALT])}


def address_of(name):
    for line in open(os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")):
        parts = line.split()
        if len(parts) >= 3 and parts[2] == name:
            return "0x" + parts[0]
    raise SystemExit("unknown function " + name)


def score(output):
    if output.startswith("MATCH"):
        return -1
    if output.startswith(("emitted object rejected", "compile failed")):
        return 9999
    return len(re.findall(r"^ *(?:!!)?\[", output, re.M))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("function")
    ap.add_argument("candidate")
    ap.add_argument("decls")
    ap.add_argument("--configs", default="def,alt3,alt3p")
    ap.add_argument("--random", type=int, default=0, help="N random shuffles instead of all permutations")
    ap.add_argument("--unit-objects", default=None)
    ap.add_argument("--extra-flags", default="", help="appended to every flag set, e.g. \"-Cpp_exceptions off\" for C++ units")
    ap.add_argument("--out", default=tempfile.gettempdir())
    a = ap.parse_args()
    decls = a.decls.split("|")
    text = open(a.candidate).read()
    block = "".join("    " + d + "\n" for d in decls)
    if block not in text:
        raise SystemExit("the declaration block must appear verbatim in the candidate")
    va = address_of(a.function)
    ext = os.path.splitext(a.candidate)[1]
    if a.random:
        rng = random.Random(1)
        orders = []
        for _ in range(a.random):
            order = decls[:]
            rng.shuffle(order)
            orders.append(tuple(order))
        orders = list(dict.fromkeys(orders))
    else:
        orders = itertools.permutations(decls)
    best = []
    scratch = os.path.join(a.out, "permdecl_%d%s" % (os.getpid(), ext))
    try:
        for order in orders:
            open(scratch, "w").write(text.replace(block, "".join("    " + d + "\n" for d in order)))
            for tag in a.configs.split(","):
                flags, extra = CONFIGS[tag]
                cmd = ["python3", "tools/verify.py", va, scratch, "--flags", (flags + " " + a.extra_flags).strip()] + extra
                if a.unit_objects:
                    cmd += ["--unit-objects", a.unit_objects]
                out = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT).stdout
                best.append((score(out), tag, order))
                if best[-1][0] == -1:
                    path = os.path.join(a.out, "MATCH_%s_%s%s" % (a.function, tag, ext))
                    os.replace(scratch, path)
                    print("MATCH", tag, order, "->", path)
                    return 0
    finally:
        if os.path.exists(scratch):
            os.remove(scratch)
    best.sort(key=lambda row: row[0])
    for row in best[:5]:
        print(row)
    return 1


if __name__ == "__main__":
    sys.exit(main())
