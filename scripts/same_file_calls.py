#!/usr/bin/env python3
"""same_file_calls.py — retail calls that show the callee was compiled earlier in the caller's file.

Under the ABI a callee may write a0-a3, t0-t9, at, v1 and f2-f19, so a caller compiled without
knowing the callee keeps nothing it needs there across the call. MWCC knows which registers a `static`
function compiled earlier in the same file writes, and keeps a value in one it leaves alone. A read of
such a register after the `jal`, on the fall-through path and with no write in between, is that
knowledge in the retail code: the callee was `static` and compiled first, so every caller of it is in
the same translation unit. No
per-function compile reproduces it, so the caller can match only in a whole-file unit
(docs/engine/emitted-functions.md, "Whole-file units").

The scan reads the generated `asm/` split (`make asm`) of every function in an MWCC unit of
config/SLUS-20836/units.tsv. One row per call, tab-separated:

  caller_va caller callee_va callee registers distance caller_unit callee_unit caller_category

`distance` is caller minus callee; a callee later in the image (a negative distance) is not this
effect and is worth a look. `caller_category` is the caller's row in data/check-categories.tsv
(`none` when it has no source).

Usage:
  python3 scripts/same_file_calls.py [--unmatched]
"""
import argparse
import bisect
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CALLER_SAVED = ({"a0", "a1", "a2", "a3", "at", "v1"} | {"t%d" % i for i in range(10)}
                | {"$f%d" % i for i in range(2, 20)})
READ_ALL = {"sb", "sh", "sw", "sd", "sq", "swc1", "sdc1", "swl", "swr", "sdl", "sdr", "sqc2",
            "mult", "multu", "div", "divu", "mult1", "multu1", "div1", "divu1", "mtlo", "mthi",
            "mtlo1", "mthi1", "teq", "tne", "mtsab", "mtsa", "madd.s", "msub.s", "madda.s",
            "msuba.s", "mula.s", "adda.s", "suba.s"}
TO_COPROCESSOR = {"mtc1", "ctc1", "qmtc2", "ctc2"}
FROM_SPECIAL = {"mfc1", "cfc1", "mflo", "mfhi", "mflo1", "mfhi1", "qmfc2", "cfc2", "mfsa"}
THREE_OPERAND = {"mult", "multu", "mult1", "multu1", "madd", "maddu", "madd1", "maddu1"}
UNCONDITIONAL = {"b", "j", "jr", "jal", "jalr"}
BRANCH = re.compile(r"^(b|j$|jr$|jalr$|bc1)")
INSN = re.compile(r"/\* ([0-9a-f]{8}): (\S+)\s*(.*?) \*/")
REG = re.compile(r"\$f\d+|\b(?:zero|at|v[01]|a[0-3]|t\d|s[0-8]|k[01]|gp|sp|fp|ra)\b")
MWCC = ("default", "combat", "3.0.3", "b52", "2.4")


def instructions(path):
    with open(path) as fh:
        return [(int(m.group(1), 16), m.group(2), m.group(3)) for m in map(INSN.search, fh) if m]


def reads_writes(op, args):
    """(read, written) registers of one instruction, as the disassembly spells them."""
    regs = REG.findall(args)
    if op in THREE_OPERAND and len(regs) == 3:
        return set(regs[1:]), set(regs[:1])
    if op in TO_COPROCESSOR:
        return set(regs[:1]), set(regs[1:])
    if op in FROM_SPECIAL:
        return set(regs[1:]), set(regs[:1])
    if op in READ_ALL or BRANCH.match(op) or op.startswith("c.") or op == "nop":
        return set(regs), set()
    return set(regs[1:]), set(regs[:1])


def kept_across(code, at):
    """Caller-saved registers the code after the call at index `at` reads before writing them."""
    written, kept = set(), set()
    for _va, op, args in code[at + 2:]:
        read, wrote = reads_writes(op, args)
        kept |= (read - written) & CALLER_SAVED
        written |= wrote
        if op in UNCONDITIONAL:
            break
    return kept


def table(path, parse):
    with open(path) as fh:
        return [parse(line) for line in fh if line.strip() and line[0] not in "#@"]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--unmatched", action="store_true", help="only callers without matched source")
    a = ap.parse_args()
    config = os.path.join(ROOT, "config", "SLUS-20836")
    symbols = table(os.path.join(config, "symbols.txt"), lambda l: (int(l.split()[0], 16), l.split()[2]))
    starts = dict(symbols)
    units = table(os.path.join(config, "units.tsv"),
                  lambda l: (int(l.split("\t")[0], 16), int(l.split("\t")[1], 16), l.split("\t")[2], l.split("\t")[3]))
    lows = [u[0] for u in units]

    def unit(va):
        i = bisect.bisect_right(lows, va) - 1
        return units[i] if i >= 0 and units[i][0] <= va < units[i][1] else (0, 0, "-", "-")

    categories = dict(table(os.path.join(ROOT, "data", "check-categories.tsv"),
                            lambda l: (int(l.split("\t")[0], 16), l.split("\t")[2])))
    for va, name in symbols:
        path = os.path.join(ROOT, "asm", name + ".s")
        category = categories.get(va, "none")
        if unit(va)[3] not in MWCC or not os.path.exists(path) or (a.unmatched and category == "match"):
            continue
        code = instructions(path)
        for at, (_va, op, args) in enumerate(code):
            if op != "jal":
                continue
            target = int(args.split()[0], 16)
            if target == va or target not in starts:
                continue
            kept = kept_across(code, at)
            if kept:
                print("\t".join(("%08x" % va, name, "%08x" % target, starts[target], ",".join(sorted(kept)),
                                 str(va - target), unit(va)[2], unit(target)[2], category)))


if __name__ == "__main__":
    main()
