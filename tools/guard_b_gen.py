#!/usr/bin/env python3
"""guard_b_gen.py [--out DIR] [--dry-run] NAME... — emit the guard-family MetaObject accessors as C++.

The `<Class>_GetMetaObject` / `<Class>_ResolveMetaObject` accessors (docs/engine/guard-family.md) share one
retail body of 18 or 19 words: the published `igMetaObject *` slot is loaded, null-tested, its `_validity`
(+36) flag bit 2 is materialised with `sltu rd,zero,rs`, in the 19-word form ('variant B') a dead `nop` sits
where the null-test branch lands, the class's registrar is called, and the slot is reloaded and returned.

The source shape that reproduces those words depends on the unit's compiler (phase 3b,
docs/engine/build-profiles.md), so the generator resolves the unit profile of the function and picks:

  default (3.0-011126)  the materialised flag survives as `bool ready = g->_validity & 4` only when the
                        value is tested; in the 19-word form the dead `nop` has to be written: `asm { nop }`
                        after the flag branch inside `if (g) { ... }` with the call outside it (a goto to
                        the return).  The 18-word form is the same test without the asm statement.
  combat / 3.0.3        `-O3` and `-O3,p` keep the `sltu` for an `unsigned char` flag compared with 0 and
                        pad the branch target themselves, so no `asm` statement is needed and the body is
                        plain C++ (the `-O3,p` branch-target alignment gives the extra nop).

Both shapes read the slot through `igMetaObject` from include/dw4/reflected.h (its +36 field is `_validity`).  Reads the retail words from asm/NAME.s; writes NAME.cpp into the folder that holds the
function today (default src/unmatched), renaming a `.c` twin with `git mv` so one file owns the function.
Verify afterwards with tools/verify.py (the generator does not claim a match).
"""
import argparse
import glob
import os
import re
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import verify  # noqa: E402
import unitprofiles  # noqa: E402

DEFAULT_COMPILER = "local/mwcps2/3.0-011126/mwccps2.exe"


def s16(v):
    return v - 0x10000 if v & 0x8000 else v


def load_syms():
    syms, addr_of = {}, {}
    for line in open(os.path.join(ROOT, "config/SLUS-20836/symbols.txt")):
        p = line.split()
        if len(p) >= 3 and not line.startswith("#"):
            try:
                syms[int(p[0], 16)] = p[2]
                addr_of[p[2]] = int(p[0], 16)
            except ValueError:
                pass
    return syms, addr_of


def names_in_unit(name):
    """{address: identifier} for the address-bearing identifiers the current translation unit uses."""
    names, table = {}, verify.data_symbols()
    for path in glob.glob(os.path.join(ROOT, "src", "*", name + ".c*")):
        text = open(path).read()
        for m in re.finditer(r"\b([A-Za-z_]\w*?_([0-9a-f]{8}))\b", text):
            names.setdefault(int(m.group(2), 16), m.group(1))
        for m in re.finditer(r"\b[A-Za-z_]\w*\b", text):
            if m.group(0) in table:
                names.setdefault(table[m.group(0)], m.group(0))
    return names


def parse(name):
    """(slot address, flag mask, registrar address) from the 19-word body, or None when the shape differs."""
    words = [int(m, 16) for m in re.findall(r"\.word 0x([0-9a-f]{8})", open(os.path.join(ROOT, "asm", name + ".s")).read())]
    if len(words) not in (18, 19):
        return None
    dead_nop = len(words) == 19
    w = list(words)
    if not dead_nop:
        w.insert(10, 0)                   # align the 18-word body with the 19-word layout below
    if w[0] != 0x27bdfff0 or (w[1] >> 16) != 0x3c01 or w[2] != 0xffbf0000:
        return None
    hi = w[1] & 0xFFFF
    if (w[3] >> 16) != 0x8c22:
        return None
    lo = s16(w[3] & 0xFFFF)
    if (w[5] != 0) or (w[6] >> 16) != 0x8c42 or (w[7] >> 16) != 0x3042 or w[8] != 0x0002102b:
        return None
    off = w[6] & 0xFFFF
    mask = w[7] & 0xFFFF
    if off != 36:
        return None                       # not igMetaObject._validity
    if w[10] != 0 or w[11] != 0 or (w[12] >> 26) != 3 or w[13] != 0:
        return None
    target = (w[12] & 0x3FFFFFF) << 2
    if w[14] != w[1] or (w[16] >> 16) != 0x8c22 or (w[16] & 0xFFFF) != (w[3] & 0xFFFF):
        return None
    return (hi << 16) + lo, mask, target, dead_nop


def gen(name, va, syms):
    parsed = parse(name)
    if parsed is None:
        return None
    slot, mask, target, dead_nop = parsed
    cls = re.sub(r"_(Get|Resolve)MetaObject$", "", name)
    old = names_in_unit(name)
    callee = syms.get(target) or old.get(target) or "FUN_%08x" % target
    slot_name = old.get(slot) if old.get(slot) and not old[slot].startswith("DAT_") else "g_%s_metaObject_%08x" % (cls, slot)
    res = unitprofiles.resolve(va, "-O3 -Iinclude", DEFAULT_COMPILER)
    compiler = os.path.basename(os.path.dirname(res.profile.compiler))
    default = compiler == "3.0-011126"
    variant_b = default and dead_nop
    head = ("/* 0x%08x %s: returns the published MetaObject of %s, registering the class first when the\n"
            " * slot is empty or its igMetaObject._validity (+36) lacks the ready bit (mask %d).  Generated by\n"
            " * tools/guard_b_gen.py from asm/%s.s; see docs/engine/guard-family.md.\n" % (va, name, cls, mask, name))
    if variant_b:
        head += (" * Guard variant B for the %s compiler: the dead nop the null-test branch lands on is written as\n"
                 " * `asm { nop }`; the flag test is kept as a value so the `sltu` is materialised. */\n" % compiler)
    elif default:
        head += (" * Guard variant A (no dead word) for the %s compiler: the flag test is kept as a value so the\n"
                 " * `sltu` is materialised. */\n" % compiler)
    else:
        head += (" * The %s compiler materialises the flag for an unsigned char compared with zero and pads the\n"
                 " * branch target itself, so the body is plain C++. */\n" % compiler)
    out = head
    out += '#include "dw4/reflected.h"\n'
    out += 'extern "C" {\n'
    out += "void %s(void);\n" % callee
    out += "extern igMetaObject *%s[4];\n" % slot_name
    out += "igMetaObject *%s(void);\n" % name
    out += "}\n\n"
    out += "igMetaObject *%s(void)\n{\n" % name
    if variant_b:
        out += ("    igMetaObject *meta = %s[0];\n"
                "    bool ready;\n"
                "    if (meta) {\n"
                "        if (ready = meta->_validity & %d) goto done;\n"
                "        asm { nop }  /* matching construct: guard variant B — the dead word the null-test branch skips */\n"
                "    }\n"
                "    %s();\n"
                "done:\n"
                "    return %s[0];\n}\n" % (slot_name, mask, callee, slot_name))
    elif default:
        out += ("    igMetaObject *meta = %s[0];\n"
                "    bool ready;\n"
                "    if (!meta || !(ready = meta->_validity & %d))\n"
                "        %s();\n"
                "    return %s[0];\n}\n" % (slot_name, mask, callee, slot_name))
    else:
        out += ("    unsigned char ready;\n"
                "    if (%s[0] != 0) {\n"
                "        ready = (%s[0]->_validity & %d) != 0;\n"
                "        if (ready != 0) goto done;\n"
                "    }\n"
                "    %s();\n"
                "done:\n"
                "    return %s[0];\n}\n" % (slot_name, slot_name, mask, callee, slot_name))
    return out


def rename_tracked(old, new):
    """`git mv` when the old file is tracked (keeps the rename in history), plain rename otherwise.
    Concurrent generators contend for the index lock, so a failed `git mv` is retried briefly."""
    if subprocess.run(["git", "-C", ROOT, "ls-files", "--error-unmatch", old], capture_output=True).returncode != 0:
        os.replace(old, new)
        return
    for attempt in range(100):
        r = subprocess.run(["git", "-C", ROOT, "mv", "-f", old, new], capture_output=True, text=True)
        if r.returncode == 0:
            return
        if "index.lock" not in r.stderr:
            raise RuntimeError("git mv %s -> %s failed: %s" % (old, new, r.stderr.strip()))
        time.sleep(0.2)
    raise RuntimeError("git mv %s -> %s: index lock held for too long" % (old, new))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=None, help="output folder (default: the folder that holds the function today)")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("names", nargs="+")
    a = ap.parse_args()
    syms, addr_of = load_syms()
    for n in a.names:
        va = addr_of.get(n)
        if va is None:
            print("skip", n, "not in config/SLUS-20836/symbols.txt", file=sys.stderr)
            continue
        s = gen(n, va, syms)
        if s is None:
            print("skip", n, "not the 18/19-word guard body", file=sys.stderr)
            continue
        hits = glob.glob(os.path.join(ROOT, "src", "*", n + ".c*"))
        folder = a.out or (os.path.dirname(hits[0]) if hits else os.path.join(ROOT, "src", "unmatched"))
        path = os.path.join(folder, n + ".cpp")
        if a.dry_run:
            print("would write", os.path.relpath(path, ROOT))
            continue
        for h in hits:
            if a.out is None and os.path.abspath(h) != os.path.abspath(path):
                rename_tracked(h, path)
        open(path, "w").write(s)
        print("wrote", os.path.relpath(path, ROOT))


if __name__ == "__main__":
    main()
