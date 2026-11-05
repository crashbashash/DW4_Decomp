#!/usr/bin/env python3
"""m2c_context.py — build an m2c `--context` file from the recovered metadata.

m2c's output is only as good as its type knowledge. Without a context it emits
`void *` for every parameter and every global, member-accesses them anyway
(`arg->unk4`), and the result does not compile — 5,620 of the 10,859 remaining
candidates fail for exactly that reason (see [`m2c-bulk.md`](../docs/engine/m2c-bulk.md)).

Two repo artifacts supply most of the missing types, and neither is used by the
compiler pass yet:

* `data/reflection.json` — the engine's per-class `MetaObject` field tables: 659
  classes, 3,680 fields, each with its **byte offset** and `ig*MetaField` type.
  Every class also carries its **handle address** (the global the engine stores
  the object pointer in) — `0x55ebc0` is `igVisualContextAttrDefaultManager`,
  which is the guard family's global.
* `data/vtables.json` — 478 vtables and 1,286 named vfuncs, each bound to its
  owning class.

Field *widths* come from the same `NOMINAL` table `scripts/apply_reflection_names.py`
derived empirically from the recovered offsets, so the generated structs have
exactly the layout the game has; where a nominal width would overrun the next
field (arrays, inline structs) the gap to the next field is used instead, which
is exact.

Usage:
  m2c_context.py                        # -> build/m2c_context.c
  m2c_context.py --out /tmp/ctx.c --globals pointer
  m2c_context.py --report               # what was and was not typed
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

# Byte width of each ig*MetaField, copied from scripts/apply_reflection_names.py
# (derived there from the modal inter-field delta, not assumed).
NOMINAL = {
    "igBoolMetaField": 1, "igCharMetaField": 1, "igUnsignedCharMetaField": 1,
    "igShortMetaField": 2, "igUnsignedShortMetaField": 2,
    "igIntMetaField": 4, "igUnsignedIntMetaField": 4, "igEnumMetaField": 4,
    "igLongMetaField": 8, "igUnsignedLongMetaField": 8, "igDoubleMetaField": 8,
    "igFloatMetaField": 4,
    "igRawRefMetaField": 4, "igRefMetaField": 4, "igObjectRefMetaField": 4,
    "igDependencyMetaField": 4, "igVirtualCFuncMetaField": 4,
    "igTrackedElementMetaField": 4, "igMemoryDescriptorMetaField": 4,
    "igCompoundMetaField": 4, "igStringMetaField": 4, "igMemoryRefMetaField": 4,
    "igVec2fMetaField": 8, "igVec3fMetaField": 12, "igVec4fMetaField": 16,
    "igVec3ucMetaField": 3, "igVec4ucMetaField": 4, "igMatrix44fMetaField": 64,
}
C_TYPE = {
    "igBoolMetaField": "char", "igCharMetaField": "char",
    "igUnsignedCharMetaField": "unsigned char",
    "igShortMetaField": "short", "igUnsignedShortMetaField": "unsigned short",
    "igIntMetaField": "int", "igUnsignedIntMetaField": "unsigned int",
    "igEnumMetaField": "int",
    "igLongMetaField": "long long", "igUnsignedLongMetaField": "long long",
    "igDoubleMetaField": "double", "igFloatMetaField": "float",
    "igRawRefMetaField": "void *", "igRefMetaField": "void *",
    "igObjectRefMetaField": "void *", "igDependencyMetaField": "void *",
    "igVirtualCFuncMetaField": "void *", "igTrackedElementMetaField": "void *",
    "igMemoryDescriptorMetaField": "void *", "igCompoundMetaField": "void *",
    "igStringMetaField": "void *", "igMemoryRefMetaField": "void *",
}

_BAD = re.compile(r"[^A-Za-z0-9_]")
# A recovered field name can collide with a C keyword (`default`, `register`, ...);
# pycparser then fails the whole context.
KEYWORDS = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
    "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Bool",
    "class", "new", "delete", "this", "template", "typename", "namespace", "operator",
    "private", "protected", "public", "virtual", "bool", "true", "false", "try",
    "catch", "throw", "using", "friend", "mutable", "explicit", "export", "wchar_t",
}


def cname(recovered):
    """`Gap::Bec::ParticleArray` -> `Gap__Bec__ParticleArray` (the repo convention)."""
    n = _BAD.sub("__", recovered)
    if not n or n[0].isdigit():
        n = "_" + n
    return n


def field_name(raw, offset, used):
    n = _BAD.sub("_", raw or "").strip("_") or ("f%x" % offset)
    if n[0].isdigit() or n in KEYWORDS:
        n = "f_" + n
    while n in used:
        n += "_"
    used.add(n)
    return n


def struct_for(cls, used_types):
    """One flat struct: offsets are absolute, gaps become char arrays."""
    name = cname(cls["class"])
    fields = [f for f in cls.get("fields", []) if isinstance(f.get("offset"), int)]
    fields.sort(key=lambda f: f["offset"])
    lines, cur, used = [], 0, set()
    for i, f in enumerate(fields):
        off, ty = f["offset"], f.get("type", "")
        if off < cur:                       # overlapping/duplicate: skip
            continue
        if off > cur:
            lines.append("    char pad%X[%d];" % (cur, off - cur))
        nxt = fields[i + 1]["offset"] if i + 1 < len(fields) else None
        w = NOMINAL.get(ty)
        if w is None:                        # array/inline/unknown: exact gap
            w = (nxt - off) if nxt else 4
        if nxt is not None:
            w = min(w, nxt - off)
        if w <= 0:
            continue
        nm = field_name(f.get("name"), off, used)
        ct = C_TYPE.get(ty) if NOMINAL.get(ty) == w else None
        if ct is None:                       # width and type disagree -> raw bytes
            ct = "char"
            lines.append("    %s %s[%d];" % (ct, nm, w))
        else:
            lines.append("    %s %s;" % (ct, nm))
        cur = off + w
    if not lines:
        return None
    used_types.add(name)
    return "struct %s {\n%s\n};\n" % (name, "\n".join(lines))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--reflection", default=os.path.join(ROOT, "data", "reflection.json"))
    ap.add_argument("--vtables", default=os.path.join(ROOT, "data", "vtables.json"))
    ap.add_argument("--out", default=os.path.join(ROOT, "build", "m2c_context.c"))
    ap.add_argument("--globals", choices=["none", "pointer", "array"], default="array",
                    help="how to declare the per-class handle globals: "
                         "`array` (4 pointers, forces absolute lui/lw addressing like "
                         "retail) or `pointer` (small data, gp-relative)")
    ap.add_argument("--vtables-protos", action="store_true",
                    help="also declare the 1,286 named vfuncs as `void FUN_x();`")
    ap.add_argument("--report", action="store_true")
    a = ap.parse_args(argv)

    refl = json.load(open(a.reflection))
    classes = refl["classes"]
    used_types, structs, globals_, skipped = set(), [], [], 0

    for handle, cls in sorted(classes.items(), key=lambda kv: int(kv[0], 16)):
        st = struct_for(cls, used_types)
        if st is None:
            skipped += 1
            continue
        structs.append(st)
        if a.globals != "none":
            v = int(handle, 16)
            tn = cname(cls["class"])
            # The handle is the address the engine stores the object pointer at,
            # so the symbol is a pointer. Declared as a 4-element array in `array`
            # mode so MWCC uses absolute `lui at`/`lw` (a lone 4-byte pointer is
            # small data and goes gp-relative; finding #311).
            if a.globals == "array":
                globals_.append("extern struct %s *DAT_%08x[4];" % (tn, v))
            else:
                globals_.append("extern struct %s *DAT_%08x;" % (tn, v))

    protos = []
    if a.vtables_protos:
        vt = json.load(open(a.vtables))
        for addr, info in sorted(vt.get("names", {}).items(), key=lambda kv: int(kv[0], 16)):
            owner = info.get("owner")
            if not owner:
                continue
            protos.append("void FUN_%08x(struct %s *);" % (int(addr, 16), cname(owner)))

    head = ["/* GENERATED by tools/m2c_context.py — do not edit.",
            " * Types recovered from data/reflection.json and data/vtables.json.",
            " * %d classes with fields, %d handle globals, %d vfunc prototypes. */"
            % (len(used_types), len(globals_), len(protos))]
    text = "\n".join(head) + "\n\n" + "\n".join(structs) + "\n" + "\n".join(globals_) \
        + "\n" + "\n".join(protos) + "\n"
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    open(a.out, "w").write(text)

    if a.report:
        typed = {}
        for handle, cls in classes.items():
            for f in cls.get("fields", []):
                typed[f.get("type", "?")] = typed.get(f.get("type", "?"), 0) + 1
        print("reflection: %d classes (%d with fields, %d skipped), %d fields"
              % (len(classes), len(classes) - skipped, skipped,
                 sum(len(c.get("fields", [])) for c in classes.values())))
        print("wrote %s: %d bytes, %d bytes of structs, %d globals"
              % (a.out, len(text), sum(len(s) for s in structs), len(globals_)))
    else:
        print("m2c_context: %d structs + %d globals + %d prototypes -> %s"
              % (len(used_types), len(globals_), len(protos), a.out))
    return 0


if __name__ == "__main__":
    sys.exit(main())
