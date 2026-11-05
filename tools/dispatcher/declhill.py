#!/usr/bin/env python3
"""declhill.py FUNCTION CANDIDATE [--config def|alt3|alt3p|alt4|alt4p] [--rounds N] [--jobs N]

Hill-climbing search over the order of the function-level local declarations (complement of permdecl.py).

permdecl.py compiles whole permutations, which is hopeless for the 15-20 locals of a 500-byte function. Every
near miss of this kind is usually one or two ids away from retail, so this tool starts from the order in the file
and, per round, compiles all single-element moves (take declaration i, insert it at position j; n * (n - 1) compiles,
8 in parallel), keeps the best order and repeats until nothing improves or an exact MATCH is found. The score is the
number of differing instruction words (a size mismatch adds 1000, a compile failure 9999).

The declarations are the lines between a `//DECL` line and a `//ENDDECL` line of the candidate, one declaration per
line (the markers are plain comments, so the file also compiles unchanged). The best text is written to the
scratch directory as `declhill_<function>.<ext>` (the markers stay in it); remove the two marker lines before banking.

  def    default compiler, `-O3`
  alt3   pinned alternate compiler, `-O3`
  alt3p  pinned alternate compiler, `-O3,p`   (alt4 / alt4p: `-O4` / `-O4,p`)

Typical use: run `regalloc.py` first; when its suggestion says "no permutation of the involved ids" because the
node is a temporary, the cheap fix is to add or rename locals (a separate variable for a volatile re-read, `ix` /
`dp` / `ob` temporaries for an indexed callback argument, a second variable for the second web of a counter) and
let this tool find the order of the new set.
"""
import argparse
import os
import subprocess
import sys
import tempfile
from multiprocessing.pool import ThreadPool

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ALT = "local/mwcps2/combat/mwccps2.exe"
CONFIGS = {
    "def": ("-O3 -Iinclude", []),
    "alt3": ("-O3 -Iinclude", ["--mwcc", ALT]),
    "alt3p": ("-O3,p -Iinclude", ["--mwcc", ALT]),
    "alt4": ("-O4 -Iinclude", ["--mwcc", ALT]),
    "alt4p": ("-O4,p -Iinclude", ["--mwcc", ALT]),
}


def address_of(name):
    for line in open(os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")):
        parts = line.split()
        if len(parts) >= 3 and parts[2] == name and not line.startswith("#"):
            return "0x" + parts[0]
    raise SystemExit("unknown function " + name)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("function")
    ap.add_argument("candidate")
    ap.add_argument("--config", default="alt3")
    ap.add_argument("--rounds", type=int, default=8)
    ap.add_argument("--jobs", type=int, default=8)
    args = ap.parse_args()
    va = address_of(args.function)
    flags, extra = CONFIGS[args.config]
    text = open(args.candidate).read()
    a = text.index("//DECL\n") + len("//DECL\n")
    b = text.index("//ENDDECL")
    decl = [l for l in text[a:b].split("\n") if l.strip()]
    ext = os.path.splitext(args.candidate)[1]
    cache = {}

    def score(order):
        order = tuple(order)
        if order in cache:
            return cache[order]
        body = text[:a] + "\n".join(decl[i] for i in order) + "\n" + text[b:]
        fd, path = tempfile.mkstemp(suffix=ext, prefix="declhill-", dir=tempfile.gettempdir())
        os.write(fd, body.encode())
        os.close(fd)
        try:
            r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "verify.py"), va, path, "--flags", flags] + extra,
                               capture_output=True, text=True, cwd=ROOT)
        finally:
            os.unlink(path)
        out = r.stdout.splitlines()
        n = len([x for x in out if x.strip().startswith("[") or x.strip().startswith("!![")])
        if out and out[0].startswith("MATCH"):
            n = -1
        elif out and out[0].startswith("compile"):
            n = 9999
        elif any("size:" in x for x in out[:2]):
            n += 1000
        cache[order] = (n, order, body)
        return cache[order]

    cur = score(range(len(decl)))
    print("start", cur[0], flush=True)
    for rnd in range(args.rounds):
        if cur[0] <= 0:
            break
        cands = []
        base = list(cur[1])
        for i in range(len(base)):
            for j in range(len(base)):
                if i != j:
                    p = base[:]
                    p.insert(j, p.pop(i))
                    cands.append(p)
        with ThreadPool(args.jobs) as pool:
            best = min(pool.map(score, cands), key=lambda r: r[0])
        print("round", rnd, best[0], best[1], flush=True)
        if best[0] >= cur[0]:
            break
        cur = best
    out_path = os.path.join(tempfile.gettempdir(), "declhill_%s%s" % (args.function, ext))
    open(out_path, "w").write(cur[2])
    print("best", cur[0], cur[1], "->", out_path)
    sys.exit(0 if cur[0] == -1 else 1)


if __name__ == "__main__":
    main()
