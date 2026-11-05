#!/usr/bin/env python3
"""merge_units.py — fold per-function unit files into one translation unit.

The repository's source is translation units (`src/lua/api.c`, `src/game/beCameraMode.c`),
but the m2c pipeline banks one function per file.  This is the one-way step that
turns a module's per-function files into the unit file the module will live in
from then on.

The functions are written in **retail address order**, which is the order the
original compiler saw (MWCC emits a unit's functions in source order), and each
gets a `/* 0xADDR */` comment.

Declarations follow one rule, chosen so the unit still compiles one function at a
time:

* an `#include`, an `extern "C" { … }` block, or a declaration every user agrees on
  is hoisted once;
* a symbol two functions declare differently — m2c guesses `int[4]` here and
  `char[]` there — is kept **inside** each function that uses it, as a block-scope
  `extern`.  Declarations have no effect on codegen, so this changes nothing the
  matcher sees, and the conflict disappears.

  merge_units.py --out src/lua/api.c --title "the Lua native-API implementations" \
      src/Lua/*.c
  merge_units.py --out src/lua/api.c --title ... --remove src/Lua/*.c   # and delete
"""
import argparse
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import units  # noqa: E402


def load_symbols(path):
    return {ln.split()[2]: int(ln.split()[0], 16)
            for ln in open(path) if ln.strip() and not ln.startswith("#")}


def decl_name(text):
    """The symbol a declaration introduces: `extern int DAT_x[4];` -> DAT_x."""
    t = text.strip().rstrip(";")
    m = re.search(r"([A-Za-z_]\w*)\s*[\[(]", t)
    if m:
        return m.group(1)
    m = re.search(r"([A-Za-z_]\w*)\s*$", t)
    return m.group(1) if m else None


def prelude_chunks(text):
    """[(name-or-None, text)] for the text before the file's first definition.

    A chunk is one declaration, one `#include`, or one balanced brace block —
    `extern "C" { … }` and its contents travel together, so hoisting cannot leave
    a stray brace.  `name` is None for a chunk that cannot be split (a block): it
    is hoisted whole or not at all.
    """
    defs = units.definitions(text)
    head = text[:defs[0][1]] if defs else ""
    if "*/" in head:
        head = head.split("*/", 1)[1]
    chunks, cur, depth = [], [], 0
    for ln in head.splitlines():
        s = ln.strip()
        if not s and not cur:
            continue
        cur.append(ln.rstrip())
        depth += s.count("{") - s.count("}")
        if depth > 0:
            continue
        block = any("{" in c for c in cur)
        if block or s.startswith("#") or s.endswith(";"):
            t = "\n".join(cur)
            chunks.append((None if block else decl_name(t), t))
            cur = []
    if cur:
        t = "\n".join(cur)
        chunks.append((decl_name(t), t))
    return chunks


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", required=True)
    ap.add_argument("--title", required=True, help="one line, goes in the header comment")
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--remove", action="store_true", help="delete the input files after writing")
    ap.add_argument("files", nargs="+")
    a = ap.parse_args(argv)

    va_of = load_symbols(a.symbols)
    items = []
    for f in a.files:
        text = open(f).read()
        defs = units.definitions(text)
        if len(defs) != 1:
            print("merge_units: %s defines %d functions, expected 1"
                  % (f, len(defs)), file=sys.stderr)
            return 2
        name = defs[0][0]
        if name not in va_of:
            print("merge_units: %s is not in %s" % (name, a.symbols), file=sys.stderr)
            return 2
        items.append([va_of[name], name, f, text, prelude_chunks(text)])
    items.sort(key=lambda it: it[0])

    by_name = collections.defaultdict(set)
    for it in items:
        for nm, t in it[4]:
            if nm is not None:
                by_name[nm].add(t)

    hoisted, seen = [], set()
    for _va, _n, _f, _t, chunks in items:
        for nm, t in chunks:
            # A block is always hoisted whole; a declaration is hoisted unless a
            # sibling declares the same symbol differently.
            if nm is None or len(by_name[nm]) == 1:
                if t not in seen:
                    seen.add(t)
                    hoisted.append(t)

    parts = ["/* %s — %s" % (os.path.relpath(a.out), a.title),
             " *",
             " * One translation unit: %d functions, in retail address order.  Folded" % len(items),
             " * from the per-function units by tools/merge_units.py; the matching build",
             " * splits a function back out with tools/units.py, so `make check` still",
             " * verifies one function at a time. */"]
    parts += hoisted + [""]
    localized = 0
    for va, name, f, text, chunks in items:
        d = units.definitions(text)[0]
        body = text[d[1]:d[2]].rstrip()
        local = [t for nm, t in chunks if nm is not None and len(by_name[nm]) > 1]
        if local:
            brace = body.index("{")
            body = body[:brace + 1] + "\n    " + "\n    ".join(local) + body[brace + 1:]
            localized += len(local)
        parts += ["/* 0x%08x */" % va, body, ""]
    os.makedirs(os.path.dirname(a.out) or ".", exist_ok=True)
    open(a.out, "w").write("\n".join(parts).rstrip() + "\n")
    print("merge_units: wrote %s (%d functions, %d hoisted chunks, %d localized)"
          % (a.out, len(items), len(hoisted), localized))
    if a.remove:
        for _va, _n, f, _t, _c in items:
            os.remove(f)
    return 0


if __name__ == "__main__":
    sys.exit(main())
