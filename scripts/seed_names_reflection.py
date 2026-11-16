#!/usr/bin/env python3
"""seed_names_reflection.py — emit the class registrar / field-init names.

`data/reflection.json` records, for all 1,075 MetaObjects, the class name and the
two functions the static-init registrar is built from:

  register_site  the address of the `jal igMetaObject_RegisterClass` inside the
                 class's registrar — so the enclosing function *is* that class's
                 registrar, and its name is not a guess;
  post_init      the function passed to the registrar that adds the class's fields
                 (it calls igMetaObject_CreateFields / _NameFields).

This emits

  <Class>_Register     at the registrar function
  <Class>_InitFields   at the post_init function, where one exists

Two MetaObjects share the name `igModelViewMatrixBoneSelectList` (`class_prefixes`): the copy a game
library registers takes that library as a suffix (`igModelViewMatrixBoneSelectListBec`, the class its
RTTI vtable names `Gap::Bec::igModelViewMatrixBoneSelectList`), any other copy its handle address.

  scripts/seed_names_reflection.py > config/SLUS-20836/names/Reflection.tsv
"""
import bisect
import json
import os
import re
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import regions  # noqa: E402

CLASSES = os.path.join(ROOT, "data", "reflection.json")
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
# A game library that registers a class under a name Alchemy also registers: the suffix its copy takes.
LIBRARY_SUFFIX = {"bec": "Bec", "ndmw": "Ndmw"}


def class_prefixes(classes):
    """{handle: the symbol prefix of the class registered there}: the class name, unique across
    `data/reflection.json`.  A name registered twice is told apart by who registers it: the copy whose
    registrar lies in a game library takes the library's suffix (its RTTI namespace is that library's,
    `Gap::Bec::`); a copy with no such library keeps its handle address, which marks it as unresolved."""
    counts = Counter(c["class"] for c in classes.values())
    out = {}
    for handle, c in classes.items():
        name = c["class"]
        if counts[name] > 1:
            row = regions.of(toint(c["register_site"]))
            suffix = LIBRARY_SUFFIX.get(row.id) if row else None
            name = name + suffix if suffix else "%s_%s" % (name, handle[2:].lower())
        out[handle] = name
    assert len(set(out.values())) == len(out), "two classes share a symbol prefix"
    return out


def toint(x):
    return int(x, 16) if isinstance(x, str) else int(x)


def load_symbols(path):
    rows = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        rows.append((int(p[0], 16), int(p[1], 16), p[2]))
    rows.sort()
    return rows


def auto(name):
    return name.startswith(("FUN_", "thunk_FUN_"))


def nameable(current, want):
    """A symbol we may (re)name: still auto, or already carrying our own name.

    This keeps regeneration idempotent: after tools/apply_names.py has run, the
    registrars are no longer `FUN_*`, and a filter on "auto" alone would emit
    nothing and erase the overlay.
    """
    return auto(current) or current == want


def folder_of(head):
    if head == "Bec":
        return "game"
    if head == "Core":
        return "engine"
    if head.startswith("igAdx"):
        return "audio"
    if head.startswith(("igMovie", "igCriMovie")):
        return "movie"
    if head == "Gui":
        return "menu"
    return "engine"


def namespace_map(rows):
    """{leaf class: folder} from the already-named `Gap::<head>::<Class>::vfunc_N`.

    The reflection name has no namespace (`igWindow`, not `Gap::Core::igWindow`),
    so the prefix alone cannot place a class.  A class that already has named
    vfuncs can: their namespace says which folder it belongs in.
    """
    out = {}
    for _a, _s, n in rows:
        parts = n.split("__")
        if parts and parts[0] == "Gap" and "vfunc" in " ".join(parts):
            try:
                i = next(k for k, p in enumerate(parts) if p.startswith("vfunc"))
            except StopIteration:
                continue
            if i >= 2:
                out[parts[i - 1]] = folder_of(parts[1])
    return out


def module(name, nsmap):
    if name in nsmap:
        return nsmap[name]
    if name.startswith("ig"):
        return "engine"
    if name.startswith(("be", "Particle", "libBec", "libNdmw")):
        return "game"
    return "engine"


def main():
    classes = json.load(open(CLASSES))["classes"]
    rows = load_symbols(SYMBOLS)
    starts = [r[0] for r in rows]

    def containing(va):
        i = bisect.bisect_right(starts, va) - 1
        if i < 0:
            return None
        a, s, n = rows[i]
        return (a, s, n) if a <= va < a + s else None

    def at(va):
        i = bisect.bisect_left(starts, va)
        if i < len(rows) and rows[i][0] == va:
            return rows[i]
        return None

    nsmap = namespace_map(rows)
    prefixes = class_prefixes(classes)

    out = []
    for handle in sorted(classes, key=lambda h: toint(h)):
        c = classes[handle]
        name = prefixes[handle]
        reg = containing(toint(c["register_site"]))
        if reg and nameable(reg[2], "%s_Register" % name):
            out.append((reg[0], "%s_Register" % name, module(c["class"], nsmap)))
        pi = c.get("post_init")
        if pi:
            p = at(toint(pi))
            if p and nameable(p[2], "%s_InitFields" % name):
                out.append((p[0], "%s_InitFields" % name, module(c["class"], nsmap)))
    out.sort()
    assert len({n for _, n, _ in out}) == len(out), "duplicate name generated"
    print("# Class registrars and field initialisers, from data/reflection.json.")
    print("# Every class's static-init registrar ends with `jal igMetaObject_RegisterClass`")
    print("# and passes its name string; the reflection dump records that call site")
    print("# (register_site) and the field-adding post_init function. GENERATED by")
    print("# scripts/seed_names_reflection.py; do not hand-edit.")
    print("# <va>\t<name>\t<module>")
    for va, name, mod in out:
        print("0x%08x\t%s\t%s" % (va, name, mod))
    return 0


if __name__ == "__main__":
    sys.exit(main())
