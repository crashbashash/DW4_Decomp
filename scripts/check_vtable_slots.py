#!/usr/bin/env python3
"""Check that every `vfunc_NN` declared in a local dummy-vtable view sits at slot NN.

The project names a class's virtual functions by their slot after the vtable header:
`__vt__Class` is `{rtti, 0}` followed by the slots, so vfunc 0 is the word at +0x08 and
vfunc NN the word at +0x08 + 4*NN (docs/engine/rtti-and-vtables.md, config/SLUS-20836/symbols.txt).
A C++ unit that reaches a slot through a locally declared class with dummy virtuals
dispatches the k-th declared virtual (0-based, dummies included) at that same +0x08 + 4*k,
so a declared virtual named `vfunc_NN` is only honest when NN == k.  Two units had NN two
slots off (`vfunc_31` at k = 29 reaches the project's `vfunc_29`), which is what this check
catches: the bytes are the same either way, the name is not.

Scope: every class/struct body that declares virtuals, in src/**/*.cpp and include/dw4/**.
A class with a base is skipped (its slots start after the base's and are not knowable
here) and is reported as such with --verbose.

Usage: scripts/check_vtable_slots.py [--src src] [--include include/dw4] [--verbose] [FILE ...]
Exit status 1 when a declared `vfunc_NN` is not at slot NN.
"""
import argparse
import glob
import os
import re
import sys

BODY_RE = re.compile(r"\b(class|struct)\s+([A-Za-z_]\w*)\s*(:[^{;]*)?\{")
VIRTUAL_RE = re.compile(r"\bvirtual\b[^;{]*?\b([A-Za-z_~]\w*)\s*\(")
VFUNC_RE = re.compile(r"^vfunc_?(\d+)$")


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), text, flags=re.S)
    return re.sub(r"//[^\n]*", "", text)


def bodies(text):
    """Yield (kind, name, has_base, body, line) for every class/struct body in `text`."""
    for m in BODY_RE.finditer(text):
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += (text[i] == "{") - (text[i] == "}")
            i += 1
        yield (m.group(1), m.group(2), bool(m.group(3)), text[m.end():i - 1],
               text[:m.start()].count("\n") + 1)


def check_text(text, path="<text>"):
    """-> (hits, skipped): hits are (path, line, class, declared name, declared NN, actual k)."""
    hits, skipped = [], []
    for kind, name, has_base, body, line in bodies(strip_comments(text)):
        # a nested class body would be counted twice; drop nested bodies from this one
        flat = re.sub(r"\{[^{}]*\}", "", body)
        virtuals = VIRTUAL_RE.findall(flat)
        if not virtuals:
            continue
        if has_base:
            skipped.append((path, line, name))
            continue
        for k, vname in enumerate(virtuals):
            vm = VFUNC_RE.match(vname)
            if vm and int(vm.group(1)) != k:
                hits.append((path, line, name, vname, int(vm.group(1)), k))
    return hits, skipped


def default_files(src, include):
    files = glob.glob(os.path.join(src, "**", "*.cpp"), recursive=True)
    files += glob.glob(os.path.join(include, "**", "*"), recursive=True)
    return sorted(f for f in files if os.path.isfile(f) and "/asmbody/" not in f)


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", default="src")
    ap.add_argument("--include", default="include/dw4")
    ap.add_argument("--verbose", action="store_true", help="also list the classes with a base (skipped)")
    ap.add_argument("files", nargs="*")
    a = ap.parse_args(argv)
    files = a.files or default_files(a.src, a.include)
    hits, skipped, classes = [], [], 0
    for path in files:
        text = open(path, errors="replace").read()
        if "virtual" not in text:
            continue
        h, s = check_text(text, path)
        hits += h
        skipped += s
        classes += sum(1 for _ in bodies(strip_comments(text)))
    for path, line, cls, vname, nn, k in hits:
        print("%s:%d: %s::%s is declared virtual #%d: the slot it dispatches is vfunc_%02d (declared %d)"
              % (path, line, cls, vname, k, k, nn))
    if a.verbose:
        for path, line, cls in skipped:
            print("%s:%d: %s has a base class; its slots are not checked" % (path, line, cls))
    print("vtable slots: %d files, %d hit(s), %d derived class(es) skipped"
          % (len(files), len(hits), len(skipped)))
    return 1 if hits else 0


if __name__ == "__main__":
    sys.exit(main())
