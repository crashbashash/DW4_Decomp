#!/usr/bin/env python3
"""seed_names_metafield_slots.py — emit `<Class>_<Method>` for the MetaField
subclasses' own vtable overrides.

`igMetaField` is an abstract reflection type: every field type (`igVec3fMetaField`,
`igLongArrayMetaField`, …) is a subclass that overrides the slots whose behaviour
depends on its element type — `+0x64` `GetSize`, `+0xd0` `SwapBytes`, and so on.
Those overrides have no symbol of their own, but their *location* identifies them:
a subclass's vtable entry at the same slot as a named `igMetaField` method is that
method's override, so it is named `<Class>_<Method>`.  Nothing here is guessed from
the body: the slot comes from the vtable and the method name from the root's own
vtable entry.

Three things have to be right for the attribution to hold, and each was a measured
trap (finding #368):

1. **Finding a class's vtable.**  `igMetaObject::_vTablePointer` (`metaobj+0x5c`)
   is filled from the class's `<Class>_GetVTable` function, which builds a
   temporary and stores the class's vtable as its first word:

       addiu a0,sp,K            ; the temporary
       jal   <helper>
       lui   v0,0x52            ; ... the class's own vtable ...
       lw    v1,<glob>(at)
       addiu v0,v0,lo
       ...
       sw    v0,K(sp)           ; ... stored into it

   so the vtable is the **first rodata-range value stored to a stack slot**, with
   registers tracked.  The tempting shortcut — the first `lui`/`addiu` pair whose
   result is in the vtable range — is wrong for two reasons: the pair is often
   split by other instructions (`igTimeAttr_GetVTable`), and every body also
   materialises the *base* class's vtable for an identity test, so a positional
   scan attributes 26 classes to `igMetaField`'s own vtable.  A first-store scan
   gets 980 of 983; the 3 misses materialise the pointer from a global.

2. **Which classes descend from `igMetaField`.**  Counting matching slots against
   the root fails: the embedded `igObject` interface block (`+0x08`..`+0x58`) sits
   at the same offsets in *every* `igObject` subclass, so all 980 vtables "match"
   and `beDemoManager` gets a `_DestructValue`.  The test used here is the share of
   the **named MetaField slots** only (the 18 the four root vtables name); the
   histogram is cleanly bimodal — 25 classes at 16–18 shared, everything else at
   ≤4.

3. **Ownership.**  A body used by more than one class's vtable cannot be attributed
   to one of them (the T7 shared-default problem); those are skipped.  Ten classes
   (`igIntMetaField`, `igBoolMetaField`, …) inherit `igMetaField`'s vtable whole —
   they appear in this table with no overrides at all.  Aliased class groups
   (`beCameraMode`/`igPickMode`/`igViewMode`, …) share one vtable and are excluded
   by rule 2 rather than by this one.

The four root vtables come from the class `GetVTable` functions: `igMetaField`
`0x52f230`, `igRefMetaField` `0x52ec50`, `igMemoryRefMetaField` `0x532a50`,
`igMemoryRefArrayMetaField` `0x52f330`.

Regeneration is idempotent — an existing symbol already carrying the generated
name is skipped, so this can be re-run after `apply_names.py`.

  scripts/seed_names_metafield_slots.py > config/SLUS-20836/names/MetaFieldSlots.tsv

As a check on the rule, the generated sizes are the element sizes the class names
imply: `igVec2fMetaField_GetSize` 8, `igVec3fMetaField_GetSize` 12,
`igVec4fMetaField_GetSize` 16, `igLongMetaField_GetSize` 8,
`igMatrix44fMetaField_GetSize` 64, and the array types return `_num * elemSize`.
"""
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
VADDR_BASE, FILE_BASE = 0x100000, 0x80
MODULE = "engine"
ROOTS = [(0x52F230, "igMetaField"), (0x52EC50, "igRefMetaField"),
         (0x532A50, "igMemoryRefMetaField"), (0x52F330, "igMemoryRefArrayMetaField")]
VLO, VHI = 0x500000, 0x580000          # .rodata / .data, where a vtable lives


def load_symbols(path):
    rows = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        rows.append((int(p[0], 16), int(p[1], 16), p[2]))
    return rows


def main():
    image = open(ELF, "rb").read()

    def word(va):
        off = va - VADDR_BASE + FILE_BASE
        if not 0 <= off <= len(image) - 4:
            return None
        return struct.unpack_from("<I", image, off)[0]

    rows = load_symbols(SYMBOLS)
    syms = {a: n for a, _, n in rows}
    named = lambda n: bool(n) and not n.startswith(("FUN_", "thunk_"))
    taken = {n for _, _, n in rows}

    def class_vtable(va, size):
        """The first rodata-range value stored to a stack slot (see docstring)."""
        reg = {}
        for k in range(size // 4):
            ins = word(va + 4 * k)
            if ins is None:
                break
            op, rs, rt, imm = ins >> 26, (ins >> 21) & 0x1F, (ins >> 16) & 0x1F, ins & 0xFFFF
            if op == 0x0F:                                        # lui
                reg[rt] = imm << 16
            elif op in (0x09, 0x0D) and rs in reg:                # addiu / ori
                reg[rt] = reg[rs] + (imm - 0x10000 if imm & 0x8000 else imm)
            elif op == 0x2B and rs == 29:                         # sw rt,imm(sp)
                v = reg.pop(rt, None)
                if v is not None and VLO <= v < VHI:
                    return v
            else:
                reg.pop(rt, None)
        return None

    # slot -> method suffix, read off the root classes' own vtable entries
    method = {}
    for vt, cls in ROOTS:
        for s in range(2, 62):
            n = syms.get(word(vt + s * 4), "")
            if named(n) and n.startswith(cls + "_"):
                method.setdefault(s, n[len(cls) + 1:])

    vtable = {}
    for a, size, n in rows:
        if not n.endswith("_GetVTable"):
            continue
        v = class_vtable(a, size)
        if v:
            vtable[n[:-len("_GetVTable")]] = v

    root = ROOTS[0][0]
    descendants = {c: v for c, v in vtable.items()
                   if sum(1 for s in method if word(v + s * 4) == word(root + s * 4))
                   >= len(method) - 2}

    # a body shared by two classes' vtables cannot be attributed to either
    users = {}
    for c, v in vtable.items():
        for s in range(2, 62):
            a = word(v + s * 4)
            if a:
                users.setdefault(a, []).append((c, s))

    out = []
    for cls in sorted(descendants):
        v = descendants[cls]
        for s in sorted(method):
            addr = word(v + s * 4)
            if not addr or addr == word(root + s * 4):
                continue                                   # inherited
            if named(syms.get(addr, "")):
                continue                                   # already has a name
            if len(users.get(addr, [])) != 1:
                continue                                   # shared body (T7)
            name = "%s_%s" % (cls, method[s])
            if name in taken:
                continue
            out.append((addr, name))

    assert len(set(n for _, n in out)) == len(out), "duplicate generated name"
    print("# generated by scripts/seed_names_metafield_slots.py — the MetaField subclasses'")
    print("# own vtable overrides, named from the slot the root class names (finding #368).")
    for addr, name in sorted(out):
        print("0x%08x\t%s\t%s" % (addr, name, MODULE))
    print("%d names for %d classes" % (len(out), len(set(n.rsplit("_", 1)[0] for _, n in out))),
          file=sys.stderr)


main()
