#!/usr/bin/env python3
"""restore_dropped_args.py — recover m2c's dropped/gap call parameters (M7 near-miss tier).

m2c names a recovered parameter `argN` by its **EE register index**, and it silently
drops any argument the retail body never reads:

  * a *leading* argument — a wrapper whose first touched register is `a1` is recovered
    as `(int arg1)`, and MWCC then passes it in `a0`;
  * a *gap* — a function that uses `a0` and `a2` is recovered as `(void *arg0, int arg2)`,
    and the `arg2` value lands in `a1`.

Either way the wrapper misses by one or two instructions.  The fix is mechanical: rebuild
each parameter list as slots `0..maxIndex`, keep the recovered parameter in its own slot,
and fill every hole with an unused `int dummyN`, then re-verify.

This runs over the *drafts* the m2c loop writes to `build/m2c/` (regenerate them with
`tools/m2c_loop.py --sample N --process`, or the sweep that produced the worklist).  A
candidate is banked into `src/unmatched/` only when `tools/verify.py` proves it
byte-identical; the `.cpp` extension is chosen when the draft carries C++ syntax (the
virtual-call transforms emit `class `/`extern "C"`).

Usage:
  python3 tools/restore_dropped_args.py FUN_00300d70 FUN_00378e40 Gap__Core__x__vfunc_24
  python3 tools/restore_dropped_args.py $(cut -f1 build/m2c_worklist.tsv | tail -n +2)
"""
import os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import automatch as am            # noqa: E402
import verify as vfy              # noqa: E402

SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
ELF = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
CAND_DIR = os.path.join(ROOT, "build", "m2c")
TRY_DIR = os.path.join(ROOT, "build", "try")

_syms = {(v, n): (s, v) for v, s, n in am.load_symbols(SYMBOLS)}


def strip_header(text):
    """Drop m2c_loop's provenance block, leaving the bare translation unit."""
    keep = [ln for ln in text.splitlines(keepends=True)
            if not ln.startswith("/*") and not ln.startswith(" * ")]
    return "".join(keep).lstrip("\n")


def restore(text, name):
    """Fill the parameter holes.  Returns (new_text, param_summary) or (None, reason)."""
    m = re.search(r'\b%s\(([^)]*)\)\s*\{' % re.escape(name), text)
    if not m:
        return None, "no definition"
    params = [p.strip() for p in m.group(1).split(",") if p.strip()]
    idx = {}
    for p in params:
        gm = re.search(r'arg(\d+)$', p)
        idx[int(gm.group(1)) if gm else len(idx)] = p
    if not idx:
        return None, "no argN parameters"
    slots = [idx.get(k, "int dummy%d" % k) for k in range(max(idx) + 1)]
    new_list = ", ".join(slots)
    if new_list == ", ".join(params):
        return None, "already complete"
    text = re.sub(r'\b(%s)\(%s\)' % (re.escape(name), re.escape(m.group(1))),
                  lambda mm: "%s(%s)" % (mm.group(1), new_list), text)
    return text, new_list


def process(name):
    draft = os.path.join(CAND_DIR, name + ".c")
    if not os.path.exists(draft):
        return "skip", "no draft"
    text, info = restore(strip_header(open(draft).read()), name)
    if text is None:
        return "skip", info
    ext = ".cpp" if ("class " in text or 'extern "C"' in text) else ".c"
    tmp = os.path.join(TRY_DIR, name + ext)
    os.makedirs(TRY_DIR, exist_ok=True)
    open(tmp, "w").write("/* %s */\n" % name + text)
    if name not in {n for (_, n) in _syms}:
        return "skip", "no symbol"
    size, va = _syms[[k for k in _syms if k[1] == name][0]]
    ok, _rep = vfy.verify_one(va, tmp, symbols=SYMBOLS, elf=ELF)
    if not ok:
        return "fail", "still differs"
    dest = os.path.join(ROOT, "src", "unmatched", name + ext)
    open(dest, "w").write(
        "/* 0x%08x — %s. m2c draft with dropped/gap parameters restored; verified\n"
        " * byte-identical by tools/verify.py (loop: tools/m2c_loop.py; transform:\n"
        " * tools/restore_dropped_args.py). */\n%s" % (va, name, text))
    return "bank", info


def main(argv):
    if not argv:
        print(__doc__)
        return 1
    tally = {"bank": 0, "fail": 0, "skip": 0}
    for name in argv:
        status, info = process(name)
        tally[status] += 1
        if status == "bank":
            print("BANK %-40s %s" % (name, info))
        elif status == "fail":
            print("FAIL %-40s %s" % (name, info))
    print("\nbanked %d, failed %d, skipped %d" % (tally["bank"], tally["fail"], tally["skip"]))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
