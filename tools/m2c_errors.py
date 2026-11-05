#!/usr/bin/env python3
"""m2c_errors.py — bucket the worklist's compile failures by MWCC's own error message.

`m2c_batch.py` records `status = compile` for a candidate whose best address form does
not compile, but it keeps no reason: `diffs = -1` is a verdict, not a diagnosis. This is
the triage half of the M7 loop — it regenerates each candidate with the current pipeline,
reads the first diagnostic MWCC emitted, and counts the buckets, so a mechanical pass can
be aimed at whatever is actually on top instead of at a guess.

Per candidate:

  1. `m2c_loop.prepare` — m2c, the cleaner in all three address forms, keep the closest;
  2. `m2c_loop.mwcc_error` — the compiler's full output for that candidate;
  3. `first_error` — the first `Error:` block, with the caret/echo lines dropped and the
     varying identifiers normalised (`DAT_x`, `0xN`, `@N`) so the *type* names, which are
     the signal, survive untouched.

Usage:
  m2c_errors.py --sample 200                       # 200 candidates spread across the size range
  m2c_errors.py --all                              # the whole tier (~10 min at 5,000 rows)
  m2c_errors.py --status mismatch --sample 100     # any tier, not only compile
  m2c_errors.py --all --max-size 64                # only the small end
"""

import argparse
import collections
import os
import re
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import m2c_loop as loop  # noqa: E402

WORKLIST = os.path.join(loop.ROOT, "build", "m2c_worklist.tsv")


def normalise(msg):
    """Collapse the parts that vary between functions, keep the type names."""
    msg = re.sub(r"DAT_[0-9a-fA-F]+", "DAT_x", msg)
    msg = re.sub(r"FUN_[0-9a-fA-F]+", "FUN_x", msg)
    msg = re.sub(r"0x[0-9a-fA-F]+", "0xN", msg)
    msg = re.sub(r"@[0-9]+", "@N", msg)
    msg = re.sub(r"build\\m2c\\\S+", "PKG.c", msg)
    msg = re.sub(r"\bbuild/m2c/\S+", "PKG.c", msg)
    return re.sub(r"\s+", " ", msg).strip()


def first_error(text):
    """The first `Error:` block of an MWCC run, as one normalised line.

    MWCC prints the offending source line, a caret, then `Error:` and the message, which
    itself wraps; the continuation lines carry the same `#` prefix, so they are collected
    until the next diagnostic's `###` header, a blank line, or the trailer.
    """
    started = False
    msgs = []
    for ln in text.splitlines():
        s = ln.strip()
        body = s[2:].strip() if s.startswith("# ") else (s[1:].strip() if s.startswith("#") else s)
        if not started:
            if body.startswith("Error:") or body.startswith("error:"):
                started = True
                rest = body.split(":", 1)[1].strip()
                if rest and rest != "^":
                    msgs.append(rest)
            continue
        if not body or body.startswith("Errors caused") or body.startswith("----") \
                or body.startswith("#"):
            break
        if body == "^" or body.startswith("File:") or body.startswith("Error:") \
                or body.startswith("error:"):
            break
        msgs.append(body)
    if not started:
        head = [l for l in text.splitlines() if l.strip()]
        return normalise(head[0]) if head else "(no compiler output)"
    return normalise(" ".join(msgs)) or "(empty Error: block)"


def median(vals):
    if not vals:
        return 0
    vals = sorted(vals)
    return vals[len(vals) // 2]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=loop.ELF_DEFAULT)
    ap.add_argument("--symbols", default=loop.SYMBOLS_DEFAULT)
    ap.add_argument("--worklist", default=WORKLIST)
    ap.add_argument("--status", default="compile")
    ap.add_argument("--sample", type=int, default=0,
                    help="pick N candidates spread across the size range")
    ap.add_argument("--all", action="store_true", help="every row of the tier")
    ap.add_argument("--min-size", type=int, default=0)
    ap.add_argument("--max-size", type=int, default=10 ** 9)
    ap.add_argument("--top", type=int, default=25, help="how many buckets to print")
    ap.add_argument("--examples", type=int, default=3, help="example functions per bucket")
    a = ap.parse_args(argv)

    rows = loop.read_worklist(a.worklist)
    if a.status == "compile":
        pool = [r for r in rows if r["status"] == "compile"]
    else:
        pool = [r for r in rows if r["status"] == a.status and r["diffs"] >= 0]
    pool = [r for r in pool if a.min_size <= r["size"] <= a.max_size]
    pool.sort(key=lambda r: (r["size"], r["va"]))
    if not a.all and a.sample:
        picks, seen = [], set()
        n = min(a.sample, len(pool))
        for i in range(n):
            idx = round(i * (len(pool) - 1) / max(n - 1, 1))
            if idx not in seen:
                seen.add(idx)
                picks.append(pool[idx])
    else:
        picks = pool
    if not picks:
        print("no %s rows in %d..%d bytes" % (a.status, a.min_size, a.max_size))
        return 1

    print("%s tier: %d rows in %d..%d bytes; measuring %d"
          % (a.status, len(pool), a.min_size, a.max_size, len(picks)))
    t0 = time.time()
    buckets = collections.OrderedDict()   # message -> [count, [sizes], [names]]
    out = collections.Counter()
    for i, r in enumerate(picks, 1):
        name, va, size = r["name"], r["va"], r["size"]
        try:
            res, err, _dt = loop.prepare(va, name, size, a.symbols, a.elf)
        except Exception as exc:                                   # noqa: BLE001
            err = "tool exception: %s" % exc
        if err:
            msg = normalise(err.splitlines()[0] if err.splitlines() else "(empty)")
            out["m2c-fail"] += 1
        else:
            _va, _n, _sz, _mode, nb, ok, _src, _rep = res
            if ok:
                msg = None
                out["match"] += 1
            elif nb >= 10 ** 9:
                msg = first_error(loop.mwcc_error(os.path.join(loop.CAND_DIR, name + ".c")))
                out["compile"] += 1
            else:
                msg = None
                out["mismatch"] += 1
        if msg:
            b = buckets.setdefault(msg, [0, [], []])
            b[0] += 1
            b[1].append(size)
            if len(b[2]) < a.examples:
                b[2].append(name)
        if i % 100 == 0:
            print("  %d/%d  [%.0fs]" % (i, len(picks), time.time() - t0))

    print("\n%s   [%.0fs]" % ("  ".join("%s=%d" % kv for kv in sorted(out.items())),
                              time.time() - t0))
    print("\n%-6s %-7s %s" % ("count", "medB", "MWCC's first error"))
    for msg, (cnt, sizes, names) in sorted(buckets.items(), key=lambda kv: -kv[1][0])[:a.top]:
        print("%-6d %-7d %s" % (cnt, median(sizes), msg))
        print("       e.g. %s" % ", ".join(names))
    print("\n%d distinct messages over %d compile failures"
          % (len(buckets), out["compile"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
