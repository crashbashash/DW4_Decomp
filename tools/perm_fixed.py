#!/usr/bin/env python3
"""perm_fixed.py — permute the drafts that only became compilable after fix_compile.py.

permuter_one.build() regenerates its base.c from m2c, so it cannot see
build/m2c_fixed/. This builds the project (for target.o/compile.sh), then replaces
base.c with the fixed source before searching.

  python3 build/perm_fixed.py <worklist.tsv> [--budget 40]
worklist columns: name \t va
"""
import argparse, json, os, sys, time
from multiprocessing import Pool

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT + "/tools")
import automatch as am            # noqa: E402
import permuter_one as P          # noqa: E402
import verify as vfy              # noqa: E402

SYMBOLS = ROOT + "/config/symbols.txt"
ELF = ROOT + "/orig/SLUS-20836/SLUS_208.36"
FIXED = [ROOT + "/build/m2c_fixed", ROOT + "/build/m2c_autofix"]
_T = {}


def table():
    if "t" not in _T:
        img = open(ELF, "rb").read()
        syms = am.load_symbols(SYMBOLS)
        lo = min(v for v, _, _ in syms)
        hi = max(v + s for v, s, _ in syms)
        _T["t"] = am.disassemble(img, lo, hi)
        _T["names"] = {v: n for v, s, n in syms}
        _T["bysym"] = {v: (s, n) for v, s, n in syms}
    return _T["t"], _T["names"], _T["bysym"]


def fixed_src(name):
    for d in FIXED:
        for e in (".c", ".cpp"):
            p = os.path.join(d, name + e)
            if os.path.exists(p):
                return p
    return None


def do_one(job):
    name, va, budget = job
    t, names, bysym = table()
    if va not in bysym:
        return {"name": name, "status": "nosym"}
    fs = fixed_src(name)
    if not fs:
        return {"name": name, "status": "nofixed"}
    outdir = os.path.join(ROOT, "build", "permuter", name)
    _, err = P.build(va, outdir, t, names, bysym)
    if err:
        return {"name": name, "status": "buildfail", "msg": err[:80]}
    open(os.path.join(outdir, "base.c"), "w").write(open(fs).read())
    score, src = P.run(outdir, budget, jobs=1)
    if not src:
        return {"name": name, "status": "nomatch"}
    tmp = os.path.join(ROOT, "build", "try", name + ".c")
    os.makedirs(os.path.dirname(tmp), exist_ok=True)
    open(tmp, "w").write(src)
    ok, rep = vfy.verify_one(va, tmp, symbols=SYMBOLS, elf=ELF)
    if ok:
        dest = os.path.join(ROOT, "src", "unmatched", name + ".c")
        if not os.path.exists(dest):
            open(dest, "w").write(
                "/* 0x%08x — %s. compile-fixed m2c draft + decomp-permuter search,\n"
                " * verified byte-identical by tools/verify.py. */\n" % (va, name) + src)
        return {"name": name, "status": "BANKED", "score": score}
    return {"name": name, "status": "nomatch", "score": score}


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("worklist")
    ap.add_argument("--budget", type=int, default=40)
    ap.add_argument("--jobs", type=int, default=16)
    a = ap.parse_args()
    jobs = []
    for ln in open(a.worklist).read().splitlines():
        if not ln.strip() or ln.startswith("name"):
            continue
        f = ln.split("\t")
        jobs.append((f[0], int(f[1], 0), a.budget))
    print("permuting %d fixed drafts" % len(jobs), flush=True)
    res = []
    with Pool(a.jobs) as pool:
        for i, r in enumerate(pool.imap_unordered(do_one, jobs, chunksize=1)):
            res.append(r)
            if r["status"] == "BANKED":
                print("  BANKED %s" % r["name"], flush=True)
            if (i + 1) % 20 == 0:
                print("  %d/%d" % (i + 1, len(jobs)), flush=True)
    import collections
    print(collections.Counter(r["status"] for r in res))
