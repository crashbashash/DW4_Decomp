#!/usr/bin/env python3
"""seed_names_metaobject.py — emit the MetaObject accessors, vtable getters and
the decoded `igMetaObject` system methods.

`igMetaObject_RegisterClass`'s arguments map onto the igMetaObject reflection
struct (`data/reflection.json`, class `igMetaObject`), which names them exactly:

  t0 -> `metaobj+0x54` `_getMetaObjectFunction`  the class's lazy get-or-register
       accessor: `if (!*handle || flags&4==0) register(); return *handle;`
       (verified in the decompiler for two unrelated classes).  For 485 classes the
       registrar passes the accessor itself; for 572 it passes a thin
       `j <accessor>; nop` thunk (the real accessor is a separate function), which
       is resolved here from the thunk's own bytes, so all 1,057 distinct accessors
       are named `<Class>_GetMetaObject`.  The thunks are themselves promoted and
       named `thunk_<accessor>` by `tools/split.py`.
  t3 -> `metaobj+0x5c` `_vTablePointer`          called only when `base_index==0`;
       `FUN_001300b0` builds a temporary with the class's vtable and returns that
       pointer.  All 983 targets are symbols, unique per class -> `<Class>_GetVTable`.
  t2 -> `+0x48` `_sizeofSize`, t1 -> `+0x1c` `_name` (not functions, no names).
  fn1/fn2 are the base class's registrar and accessor (inherited), so no names.

The `igMetaObject` methods the registrar and instance factory call are named from
their decompiled bodies.

Regeneration is idempotent: a target whose symbol already carries the generated
name is re-emitted, so this can be re-run after `apply_names.py` without losing
the overlay.

  scripts/seed_names_metaobject.py > config/SLUS-20836/names/MetaObject.tsv
"""
import bisect
import json
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CLASSES = os.path.join(ROOT, "data", "reflection.json")
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
ELF = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
VADDR_BASE, FILE_BASE = 0x100000, 0x80

# igMetaObject methods, named from the decompiled registrar/instance factory.
SYSTEM = [
    (0x002FDC50, "igMetaObject_InheritFromBase"),
    (0x002FDDB0, "igMetaObject_SetName"),
    (0x002FDF00, "igMetaObject_GetFieldAt"),
    (0x002FE470, "igMetaObject_GetFieldCount"),
    (0x002FE7A0, "igMetaObject_AssignTypeId"),
    (0x002FDA40, "igMetaObject_CreateInstance"),
    (0x002D3480, "igArray_Append"),
]


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


def tracker():
    """dump_reflection's constant tracker, without running its `main()`."""
    src = open(os.path.join(ROOT, "scripts", "dump_reflection.py")).read()
    ns = {}
    exec(src.replace("\nmain()\n", "\n"), ns)          # noqa: S102 (our own script)
    return ns


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
    out = {}
    for _a, _s, n in rows:
        parts = n.split("__")
        if parts and parts[0] == "Gap":
            try:
                i = next(k for k, p in enumerate(parts) if p.startswith("vfunc"))
            except StopIteration:
                continue
            if i >= 2:
                out[parts[i - 1]] = folder_of(parts[1])
    return out


def nameable(current, want):
    """A symbol we may (re)name: still auto, or already carrying our own name."""
    return current.startswith(("FUN_", "thunk_FUN_")) or current == want


def thunk_target(img, va):
    """`j <target>; nop` -> target, else None.

    The registrar's `t0` is either the class's accessor or a two-instruction thunk
    to it; the thunk has no symbol of its own, so the pointer is the only way to
    find the accessor.
    """
    off = va - VADDR_BASE + FILE_BASE
    if off < 0 or off + 8 > len(img):
        return None
    w, d = struct.unpack_from("<II", img, off)
    if (w >> 26) == 2 and d == 0:
        return (va & 0xF0000000) | ((w & 0x03FFFFFF) << 2)
    return None


def main():
    classes = json.load(open(CLASSES))["classes"]
    rows = load_symbols(SYMBOLS)
    starts = [r[0] for r in rows]
    nsmap = namespace_map(rows)

    ns = tracker()
    elf = open(ELF, "rb").read()
    buf = bytearray(elf[FILE_BASE:])
    img = ns["Image"](VADDR_BASE, buf, VADDR_BASE + len(buf),
                      ns["_detect_codemax"](VADDR_BASE, buf, VADDR_BASE + len(buf)))

    def at(va):
        i = bisect.bisect_left(starts, va)
        return rows[i] if i < len(rows) and rows[i][0] == va else None

    counts = {}
    for c in classes.values():
        counts[c["class"]] = counts.get(c["class"], 0) + 1

    out, gap = [], 0
    for handle in sorted(classes, key=lambda h: toint(h)):
        c = classes[handle]
        name = c["class"]
        if counts[name] > 1:
            name = "%s_%s" % (name, handle[2:].lower())
        mod = nsmap.get(c["class"], "engine")
        regs, _stack = ns["resolve_call"](img, toint(c["register_site"]))
        # t0 -> +0x54 _getMetaObjectFunction; t3 -> +0x5c _vTablePointer
        for reg, suffix in ((8, "GetMetaObject"), (11, "GetVTable")):
            v = regs.get(reg)
            if not isinstance(v, int) or v == 0:
                continue
            # t0 may be the accessor itself or a `j <accessor>; nop` thunk to it.
            # Resolve the thunk from the bytes, not from `at(v) is None`: split.py
            # promotes and names the thunks (`thunk_<accessor>`), so a symbol at `v`
            # no longer means `v` is the accessor.  Both are emitted, so the overlay
            # stays authoritative and `apply_names.py` can move a name that used to
            # sit on a thunk onto the accessor it belongs to.
            thunk_va = None
            if suffix == "GetMetaObject":
                t = thunk_target(elf, v)
                if t is not None:
                    thunk_va, v = v, t
            want = "%s_%s" % (name, suffix)
            f = at(v)
            if f is None or not nameable(f[2], want):
                if suffix == "GetMetaObject":
                    gap += 1
                continue
            out.append((v, want, mod))
            if thunk_va is not None:
                out.append((thunk_va, "thunk_%s" % want, mod))
    out += [(va, nm, "engine") for va, nm in SYSTEM]
    out.sort()
    seen = set()
    for _va, nm, _m in out:
        assert nm not in seen, "duplicate generated name %s" % nm
        seen.add(nm)
    print("# igMetaObject: the per-class accessor (t0 -> _getMetaObjectFunction) and")
    print("# vtable getter (t3 -> _vTablePointer), plus the decoded system methods.")
    print("# GENERATED by scripts/seed_names_metaobject.py from data/reflection.json +")
    print("# the register_site tracker; do not hand-edit.  %d accessor targets are still"
          % gap)
    print("# unresolved (neither an accessor nor a `j` thunk to one) and are not listed;")
    print("# registrar and accessor, so they add no names.")
    print("# <va>\t<name>\t<module>")
    for va, nm, mod in out:
        print("0x%08x\t%s\t%s" % (va, nm, mod))
    return 0


if __name__ == "__main__":
    sys.exit(main())
