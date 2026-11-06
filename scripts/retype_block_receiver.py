#!/usr/bin/env python3
"""Retype an *unnamed* matched function's receiver from the class its symbol block proves.

`retype_receiver_class.py` reads the receiver class from the function's **name**
(`igMetaEnum_GetNameCount` -> `igMetaEnum`), so it cannot touch a `FUN_*`.  But many
`FUN_*` bodies sit **between two `...<Class>__vfunc_N` symbols of the same class**, and
MWCC emits a translation unit's functions contiguously, so the block proves the class the
same way it proves `FUN_00388e60` is a `beHitLandModelOrder` method.

That alone is weak for a one-cast function, so this pass also **validates** the class
against the body: every `arg0`/`this` offset cast must land on a reflected field of that
class and the cast width must equal the field width.  A function is rewritten only when it
has at least one cast and *all* of them match.  The rewrite is

    void FUN_0038f0e0(void *arg0) {         void FUN_0038f0e0(beMessenger *arg0) {
        *(int *)((char *)arg0 + 12) = 1;  ->    arg0->_flag = 1;
    }                                       }

so the receiver is typed while the function keeps its `FUN_` name (the role is still
unrecovered; naming it is the module loop's job).  Width-checked, so `make check` and
`make link` must both stay green.

The middleware set is deliberately excluded (`--game-only`, the module map's game region
0x334000..0x460000).

Usage:
    scripts/retype_block_receiver.py                 # report (all)
    scripts/retype_block_receiver.py --game-only     # report the in-scope set
    scripts/retype_block_receiver.py --game-only --apply
"""

import argparse
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, "..", "tools"))
from retype_receiver_class import CAST_RE, TYPE_WIDTH, load_header  # noqa: E402
from typed_coverage import split_functions  # noqa: E402

GAME_LO, GAME_HI = 0x334000, 0x460000
INCLUDE_ANCHOR = re.compile(r"(\*/\n)", re.M)
VFUNC_RE = re.compile(r"^(?:Gap__\w+__)?(.+?)__vfunc_\d+$")


def read_symbols(path):
    """[(addr, name)] in address order."""
    out = []
    for line in open(path, errors="replace"):
        p = line.split()
        if len(p) < 3:
            continue
        try:
            out.append((int(p[0], 16), p[2]))
        except ValueError:
            continue
    out.sort()
    return out


def block_class_map(symfile, header):
    """{FUN_ name: (addr, class)} for every `FUN_*` bracketed by two vfuncs of one class.

    A run of `FUN_*` is treated as one body, so the nearest vfunc on each side decides;
    only a class the generated header knows is kept."""
    lines = read_symbols(symfile)
    out = {}
    for i, (addr, name) in enumerate(lines):
        if not name.startswith("FUN_"):
            continue
        j = i - 1
        while j >= 0 and lines[j][1].startswith("FUN_"):
            j -= 1
        k = i + 1
        while k < len(lines) and lines[k][1].startswith("FUN_"):
            k += 1
        if j < 0 or k >= len(lines):
            continue
        a = VFUNC_RE.match(lines[j][1])
        b = VFUNC_RE.match(lines[k][1])
        if a and b and a.group(1) == b.group(1) and a.group(1) in header:
            out[name] = (addr, a.group(1))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--header", default="include/dw4/reflected.h")
    ap.add_argument("--src", default="src")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--game-only", action="store_true",
                    help="only the module map's game region (0x334000..0x460000)")
    args = ap.parse_args()

    header = load_header(args.header)
    blocks = block_class_map(args.symbols, header)
    files = {}
    for f in (glob.glob(os.path.join(args.src, "**", "*.c"), recursive=True)
              + glob.glob(os.path.join(args.src, "**", "*.cpp"), recursive=True)):
        files[os.path.basename(f).rsplit(".", 1)[0]] = f

    changed, total, skipped = [], 0, 0
    for name, (addr, cls) in sorted(blocks.items(), key=lambda kv: kv[1][0]):
        if args.game_only and not (GAME_LO <= addr < GAME_HI):
            continue
        path = files.get(name)
        if not path:
            continue
        text = open(path, errors="replace").read()
        fields = header[cls]
        done = False
        for fn_name, _sig, start, end in split_functions(text):
            if fn_name != name:
                continue
            body = text[start:end]
            fn_hits, ok = [], True
            for cm in CAST_RE.finditer(body):
                ctype, base, off = cm.group(1).strip(), cm.group(2), int(cm.group(3))
                f = fields.get(off)
                if not f or f[2] or TYPE_WIDTH.get(ctype, 4) != TYPE_WIDTH.get(f[1], 4):
                    ok = False
                    break
                a, b = cm.span()
                fn_hits.append(((start + a, start + b), "%s->%s" % (base, f[0])))
            if ok and fn_hits:
                # confine the receiver retype to this function, not the whole folded unit
                hits = list(fn_hits)
                for sm in re.finditer(r"void\s*\*\s*arg0\b", body):
                    hits.append(((start + sm.start(), start + sm.end()), "%s *arg0" % cls))
                new = text
                for (a, b), repl in sorted(hits, key=lambda h: -h[0][0]):
                    new = new[:a] + repl + new[b:]
                if '#include "dw4/reflected.h"' not in new:
                    if INCLUDE_ANCHOR.search(new):
                        new = INCLUDE_ANCHOR.sub(
                            lambda mm: "*/\n#include \"dw4/reflected.h\"\n", new, count=1)
                    else:
                        new = '#include "dw4/reflected.h"\n' + new
                changed.append((path, name, cls, len(fn_hits)))
                total += len(fn_hits)
                done = True
                if args.apply:
                    open(path, "w").write(new)
            break
        if not done:
            skipped += 1

    print("functions retyped: %d (%s), field accesses converted: %d"
          % (len(changed), "applied" if args.apply else "dry run", total))
    for path, name, cls, n in changed:
        print("    %-34s %-30s %d access(es)" % (name, cls, n))
    if skipped:
        print("    (%d candidate(s) left alone: a cast did not match)" % skipped)


if __name__ == "__main__":
    main()
