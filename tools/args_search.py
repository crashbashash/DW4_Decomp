#!/usr/bin/env python3
"""args_search.py — restore the call arguments m2c drops, over the near-miss tier.

The measured family this closes: m2c emits a call with fewer arguments than retail passes, and the
missing ones are the **leading** arguments — the enclosing function's own incoming parameters, which
m2c does not carry as live to the call. `FUN_001033f8` retail is `jal FUN_00102d08` with a2 = arg3
and a0/a1 untouched, i.e. `FUN_00102d08(arg0, arg1, arg3)`; m2c wrote `FUN_00102d08(arg3)`.

For every call statement in the body it tries two corrections, hill-climbs on the instruction-diff
count and stops when `verify.py` agrees. Fail-closed: a match is written only to
`build/m2c/<name>.c` (bank it with `m2c_loop.py --bank`), and only after the bytes match retail.
It banked 59 functions across the two ≤3-instruction tiers, 41 of the first tier's 50; the economics
are in [`../docs/engine/m2c-bulk.md`](../docs/engine/m2c-bulk.md) §The per-function loop.

* **dropped leading parameters** — m2c does not carry the enclosing function's own parameters as
  live to a call, so they go missing from the argument list (`FUN_001033f8` retail passes
  `(arg0, arg1, arg3)`, m2c wrote `(arg3)`).
* **dropped constant arguments** — the retail form loads a small immediate into an argument register
  at the call site (`li a0,1`) where m2c emits no argument at all, so the body is a bare
  `FUN_x();`. `FUN_0016cde0` (`j FUN_00207420` with `li a0,1` in the delay slot) is the measured
  example; the constants are tried in likelihood order at every argument position, leading
  positions first.

Usage:
  args_search.py --max-diffs 3 [--limit N]           # the whole near-miss tier
  args_search.py --names FUN_001033f8 FUN_0013c180   # named functions
  args_search.py --sample 30 --band 48-63            # a stratified sample
"""
import os
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
sys.path.insert(0, os.environ.get("DW4_M2C_DIR", os.path.join(ROOT, "local", "m2c")))

import m2c_loop as ml          # noqa: E402
import m2c_batch as mb         # noqa: E402
import verify as vfy           # noqa: E402

BUDGET = 80
CALL_RE = re.compile(r"(?<![\w.])(FUN_[0-9a-f]{8})\s*\(")

# Small immediates, most likely first. A dropped constant argument is an `li`/`addiu` of a small
# value (0/1/2 dominate); the longer tail is cheap because the diff count prunes it.
CONSTS = [str(c) for c in (0, 1, 2, 3, 4, 5, 6, 7, 8, -1, 10, 16, 32, 64, 100, 128, 255, 256,
                           1000)]


def split_args(s):
    """Top-level comma split of an argument list (paren-aware)."""
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def find_calls(src):
    """[(start, end, name, args_text)] for every call in the body (after the `{`)."""
    brace = src.find("{")
    if brace < 0:
        return []
    res = []
    for m in CALL_RE.finditer(src, brace):
        i = m.end()          # just after '('
        depth, j = 1, i
        while j < len(src) and depth:
            if src[j] == "(":
                depth += 1
            elif src[j] == ")":
                depth -= 1
            j += 1
        if depth:
            continue
        res.append((m.end(), j - 1, m.group(1), src[i:j - 1]))
    return res


def params_of(src):
    m = re.search(r"^\s*[A-Za-z_][\w \t*]*\b(\w+)\s*\(([^)]*)\)\s*\{", src, re.M)
    if not m:
        return []
    ps = split_args(m.group(2))
    return [re.search(r"(\w+)\s*$", p).group(1) for p in ps if p and p != "void"]


def diffcount(va, src, path="/tmp/args_search_%d.c" % os.getpid()):
    open(path, "w").write(src)
    ok, rep = vfy.verify_one(va, path, verbose=False)
    first = rep.splitlines()[0]
    if "compile failed" in first:
        return ok, 10 ** 9
    return ok, mb._diffcount(rep) + (1 if "size:" in rep else 0)


def arg_candidates(cur, params):
    """Ordered candidate argument lists for one call site.

    The proven family comes first (a prefix of the enclosing parameters), then a dropped leading
    constant, then a constant inserted at each later position, then a trailing constant. Duplicates
    are dropped so a parameter named like a constant cannot be tried twice.
    """
    out, seen = [], set()

    def add(cand):
        key = ",".join(cand)
        if key not in seen:
            seen.add(key)
            out.append(cand)

    for k in range(1, len(params) + 1):
        add(params[:k] + cur)
    for c in CONSTS:
        add([c] + cur)
    for i in range(1, len(cur) + 1):
        for c in CONSTS:
            add(cur[:i] + [c] + cur[i:])
    for c in CONSTS:
        add(cur + [c])
    return out


def search(va, name, src, verbose=True):
    """Hill-climb the dropped-arg correction. -> (matched, src, ncompiles, trace)"""
    n = [0]

    def dcount(s):
        n[0] += 1
        return diffcount(va, s)[1]

    best = dcount(src)
    if best == 0:
        return True, src, 1, ["already matches"]
    trace = []
    for _round in range(6):
        improved = False
        for (ins, close, cname, args) in find_calls(src):
            if n[0] > BUDGET:
                break
            cur = split_args(args)
            for cand in arg_candidates(cur, params_of(src)):
                if n[0] > BUDGET:
                    break
                newsrc = src[:ins] + ", ".join(cand) + src[close:]
                d = dcount(newsrc)
                if d < best:
                    src, best = newsrc, d
                    trace.append("+%s at %s -> %d diffs" % (",".join(cand), cname, d))
                    improved = True
                    break
            if improved:
                break
        if best == 0:
            ok, _ = diffcount(va, src)
            return True, src, n[0], trace + ["MATCH"]
        if not improved or n[0] > BUDGET:
            break
    return False, src, n[0], trace


def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--worklist", default=os.path.join(ROOT, "build", "m2c_worklist.tsv"))
    ap.add_argument("--max-diffs", type=int, default=3)
    ap.add_argument("--band", default=None)
    ap.add_argument("--sample", type=int, default=0)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--names", nargs="*", default=[])
    a = ap.parse_args()

    picks = []
    if a.names:
        syms = ml.am.load_symbols(ml.SYMBOLS_DEFAULT)
        for nm in a.names:
            for v, s, n in syms:
                if n == nm:
                    picks.append((n, v, s, "?", "?"))
    else:
        rows = ml.read_worklist(a.worklist)
        if a.sample:
            band = None
            if a.band:
                lo, _, hi = a.band.partition("-")
                band = (int(lo), int(hi or 10 ** 9))
            picks = [(r["name"], r["va"], r["size"], r["status"], r["diffs"])
                     for r in ml.sample(rows, a.sample, a.max_diffs, band=band)]
        else:
            pool = [r for r in rows if r["status"] == "mismatch"
                    and 0 <= r["diffs"] <= a.max_diffs]
            if a.band:
                lo, _, hi = a.band.partition("-")
                pool = [r for r in pool if int(lo) <= r["size"] <= int(hi or 10 ** 9)]
            picks = [(r["name"], r["va"], r["size"], r["status"], r["diffs"]) for r in pool]
            if a.limit:
                picks = picks[:a.limit]

    t0 = time.time()
    matched = 0
    for i, (name, va, size, status, diffs) in enumerate(picks):
        res, err, dt = ml.prepare(va, name, size)
        if err:
            print("%-32s 0x%08x %4dB  prepare-fail: %s" % (name, va, size, err.splitlines()[0]))
            continue
        _va, _n, _s, mode, nb, ok, src, _rep = res
        if ok:
            matched += 1
            print("%-32s 0x%08x %4dB  already matched by the cleaner fix (diffs=%s)"
                  % (name, va, size, diffs))
            continue
        ok2, src2, ncomp, trace = search(va, name, src)
        if ok2:
            matched += 1
            open(os.path.join(ml.CAND_DIR, name + ".c"), "w").write(src2)
        print("%-32s 0x%08x %4dB  %s  (%d compiles)%s"
              % (name, va, size, "MATCH" if ok2 else "differ",
                 ncomp, "  " + "; ".join(trace) if trace else ""))
        if a.limit and i + 1 >= a.limit:
            break
    print("\n%d/%d matched in %.0fs" % (matched, len(picks), time.time() - t0))


if __name__ == "__main__":
    main()
