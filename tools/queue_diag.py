#!/usr/bin/env python3
"""queue_diag.py — cluster the unmatched queue by *why* each function misses.

`m2c_batch.py --worklist` gives every unmatched function a verdict (`mismatch` with an
instruction-diff count, `compile`, `m2cfail`, `sdk`) but not a *diagnosis*: "3 diffs"
does not say which three instructions, and two functions both at 3 diffs may need the
same one-line transform or two unrelated ones. This turns the verdict into a shape.

Per candidate it reruns the pipeline (`m2c_loop.prepare`), verifies verbosely, and
records two signatures:

  * **shape** — the retail instruction mnemonics in order, constants and register
    numbers folded to `N`/`RN`. Two functions with the same shape are the same code
    modulo its constants, so one transform (or one template) fixes both.
  * **diffsig** — for each differing instruction it stores its index and the
    `retail_mnemonic -> ours_mnemonic` pair, so "the same fold is missing at the same
    place" is visible as a repeated row rather than as a count.

A large `(shape, diffsig)` cluster is the next mechanical block; a large `shape` with
scattered diffsigs is a register-allocation problem, which no one-line transform fixes.

Usage:
  queue_diag.py --max-diffs 3 --limit 200          # quick look at the 3-diff tier
  queue_diag.py --max-diffs 3 --jobs 8 --out build/near.tsv
  queue_diag.py --status compile --limit 200       # pair with tools/m2c_errors.py
"""
import argparse
import collections
import os
import re
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import m2c_batch  # noqa: E402
import m2c_loop as loop  # noqa: E402

_HEX = re.compile(r"0x[0-9a-fA-F]+|\b\d+\b")
_LOCAL = re.compile(r"^(__)?(gp|sp|ra|at)$")  # not registers we want to fold


def norm_sym(mnem, ops):
    """A mnemonic+operands with the varying parts folded, for shape comparison."""
    ops = _HEX.sub("N", ops)
    ops = re.sub(r"\bv[01]\b|\ba[0-3]\b|\bt[0-9]\b|\bs[0-7]\b|\bk[01]\b|\bfp\b", "R", ops)
    return mnem + " " + ops


def shape_of(retail, va, n):
    """The retail mnemonic skeleton, constants and register numbers folded."""
    dis = loop.disasm_words([retail.get(i, 0) for i in range(n)], va)
    return " ; ".join(norm_sym(*dis.get(va + 4 * i, ("?", ""))) for i in range(n))


def diffsig_of(ours, retail, va, n):
    dis = loop.disasm_words([retail.get(i, 0) for i in range(n)], va)
    diso = loop.disasm_words([ours.get(i, 0) for i in range(n)], va)
    parts = []
    for i in range(n):
        if ours.get(i) == retail.get(i):
            continue
        rm = " ".join(dis.get(va + 4 * i, ("?", "")))[:28]
        om = " ".join(diso.get(va + 4 * i, ("?", "")))[:28]
        parts.append("%d:%s=>%s" % (i, _HEX.sub("N", rm), _HEX.sub("N", om)))
    return " | ".join(parts), len(parts)


_LOCK = threading.Lock()


_SIZE_RE = re.compile(r"size: retail (\d+), ours (\d+)")


def diag(cand):
    name, va, size, status, diffs, mode = cand
    try:
        with _LOCK:  # m2c.main is not thread-safe (m2c_batch serialises it the same way)
            src, rep, _ = loop.prepare(va, name, size, show=False)
    except Exception as exc:  # noqa: BLE001
        return (name, va, size, size, diffs, "prepare-failed:%s" % type(exc).__name__, "")
    if src is None:
        return (name, va, size, size, diffs, "m2c-fail", "")
    ok, vrep = loop.vfy.verify_one(va, "build/m2c/%s.c" % name,
                                   symbols=loop.SYMBOLS_DEFAULT, elf=loop.ELF_DEFAULT,
                                   verbose=True)
    if ok:
        return (name, va, size, size, 0, "MATCH", "")
    head = vrep.splitlines()[0] if vrep else ""
    if "compile failed" in head:
        return (name, va, size, size, diffs, "compile", "")
    m = _SIZE_RE.search(vrep)
    osz = int(m.group(2)) if m else size
    ours, retail = loop.parse_verbose(vrep)
    # verify.py compares over min(len(ours), len(retail)), so a shorter ours reports a
    # deceptively small diff. Keep the sizes so a *structural* miss stays visible.
    n = max(len(ours), len(retail))
    sig, dn = diffsig_of(ours, retail, va, n)
    kind = "size!" if osz != size else ""
    if kind:
        sig = "SIZE retail %d ours %d | %s" % (size, osz, sig)
    return (name, va, size, osz, dn + (1 if kind else 0), (kind + " " + shape_of(retail, va, n)).strip(), sig)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--worklist", default="/tmp/wl.tsv")
    ap.add_argument("--max-diffs", type=int, default=3)
    ap.add_argument("--min-diffs", type=int, default=0)
    ap.add_argument("--status", default="mismatch")
    ap.add_argument("--only", default=None, help="substring filter on the symbol name")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=1)
    ap.add_argument("--out", default=None, help="TSV of every row (name, va, size, diffs, shape, diffsig)")
    ap.add_argument("--top", type=int, default=15)
    a = ap.parse_args(argv)

    cands = []
    for i, line in enumerate(open(a.worklist)):
        if i == 0:
            continue
        p = line.rstrip("\n").split("\t")
        if len(p) < 6 or p[3] != a.status:
            continue
        d = int(p[4])
        if not (a.min_diffs <= d <= a.max_diffs):
            continue
        if a.only and a.only not in p[0]:
            continue
        cands.append((p[0], int(p[1], 16), int(p[2]), p[3], d, p[5]))
    if a.limit:
        cands = cands[:a.limit]
    print("queue_diag: %d candidates (%s, %d..%d diffs), jobs=%d"
          % (len(cands), a.status, a.min_diffs, a.max_diffs, a.jobs))

    t0 = time.time()
    rows = []
    if a.jobs > 1:
        with ThreadPoolExecutor(max_workers=a.jobs) as ex:
            for i, r in enumerate(ex.map(diag, cands), 1):
                rows.append(r)
                if i % 50 == 0:
                    print("  %d/%d (%.0fs)" % (i, len(cands), time.time() - t0), flush=True)
    else:
        for i, c in enumerate(cands, 1):
            rows.append(diag(c))
            if i % 50 == 0:
                print("  %d/%d (%.0fs)" % (i, len(cands), time.time() - t0), flush=True)

    if a.out:
        with open(a.out, "w") as fh:
            fh.write("name\tva\tsize\toursize\tdiffs\tshape\tdiffsig\n")
            for r in rows:
                fh.write("%s\t0x%08x\t%d\t%d\t%d\t%s\t%s\n" % r)
        print("wrote %s" % a.out)

    print("\nstatus:", dict(collections.Counter(r[5] if r[5] in
          ("MATCH", "compile", "m2c-fail") else "clean-run" for r in rows)))
    clean = [r for r in rows if r[5] not in ("MATCH", "compile", "m2c-fail")]
    trunc = [r for r in clean if r[3] != r[2]]
    print("size mismatch (diff count under-reports - verification is over min(len)): "
          "%d of %d clean runs" % (len(trunc), len(clean)))
    same = [r for r in clean if r[3] == r[2]]
    print("true same-size near misses: %d" % len(same))
    if clean:
        print("\ntop (shape, diffsig) clusters that are the SAME code + SAME miss:")
        for (sh, sg), c in collections.Counter((r[5], r[6]) for r in clean).most_common(a.top):
            print("  x%-4d %s" % (c, sg[:150]))
        print("\ntop shapes (same code; diffs may differ = allocation class):")
        for sh, c in collections.Counter(r[5] for r in clean).most_common(a.top):
            nsig = len(set(r[6] for r in clean if r[5] == sh))
            print("  x%-4d shapesigs=%-4d %s" % (c, nsig, sh[:130]))
    if any(r[5] == "MATCH" for r in rows):
        got = [r for r in rows if r[5] == "MATCH"]
        print("\n%d ALREADY MATCH (bankable now): %s" % (len(got), ", ".join(r[0] for r in got[:10])))
    return 0


if __name__ == "__main__":
    sys.exit(main())
