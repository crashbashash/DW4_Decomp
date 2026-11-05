#!/usr/bin/env python3
"""gen_reflection.py — emit the port's reflection schema from the decompilation dump.

The recovered class metadata lives in `DW4_Decomp/data/reflection.json` (T1: every MetaObject's
declared fields with their absolute byte offsets and MetaField types).  The port's runtime object
model (`src/object.c`) needs that as C tables, so this generator writes `src/reflection_data.c`
and `make check` re-runs it with `--check` to keep it in step.

The field **type** is stored as the igBinary descriptor type id (the 48-name string-table index of
`docs/engine/igbinary-format.md`), so construction can match a record's descriptor to the declared
field it belongs to -- the same match `DW4_Decomp/scripts/igb_inst.py:find_K` does.  Array/struct
types that `igb_inst` deliberately does not name are stored as `0xff` (no match), so the port's
naming agrees with the Python reference class for class.

  python3 tools/gen_reflection.py [--decomp ..] [--out src/reflection_data.c] [--check]
"""
import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)

# igBinary string-table index -> ig*MetaField name (docs/engine/igbinary-format.md).
TID_NAME = {
    0: "igObjectRef", 1: "igInt", 2: "igBool", 3: "igChar", 4: "igString",
    5: "igRawRef", 6: "igEnum", 7: "igMemoryRef", 8: "igUnsignedChar",
    9: "igUnsignedInt", 10: "igUnsignedShort", 11: "igStruct", 12: "igLong",
    13: "igUnsignedLong", 14: "igIntArray", 15: "igCharArray", 16: "igFloat",
    17: "igShort", 18: "igVirtualCFunc", 19: "igUnsignedShortArray",
    20: "igUnsignedLongArray", 21: "igUnsignedIntArray", 22: "igUnsignedCharArray",
    23: "igStringArray", 24: "igShortArray", 25: "igRawRefArray", 26: "igObjectRefArray",
    27: "igMemoryRefArray", 28: "igLongArray", 29: "igFloatArray", 30: "igEnumArray",
    31: "igDouble", 32: "igDoubleArray", 33: "igDependency", 34: "igBoolArray",
    35: "igMemoryDescriptor", 36: "igVec3f", 37: "igVec2f", 38: "igVec4f",
    39: "igVec4uc", 40: "igMatrix44f", 41: "igTrackedElement",
    42: "igVertexBlendShaderCapsInfo", 43: "igVec4fArray", 44: "igItemDataBase",
    45: "igVec3uc", 46: "igInterfaceDeclaration", 47: "igCharMetrics",
}
# The subset igb_inst.TID2REF carries; anything else is an unmatchable field type (0xff),
# so our K search and field naming fail the same way the Python reference does.
NAMED = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 17, 31, 36, 37, 38, 39, 40, 45, 47}
NAME_TID = {n: i for i, n in TID_NAME.items()}


def align(x, n=4):
    return (x + n - 1) // n * n


def esc(s):
    return s.replace("\\", "\\\\").replace('"', '\\"')


def build(decomp):
    refl = json.load(open(os.path.join(decomp, "data", "reflection.json")))
    classes = list(refl["classes"].values())
    # the class's vtable address (finding #359: the instance's +0 word IS its class vtable), so the
    # ported igObject_InitHeader can stamp a real object header.  Two sources: the 478 vtables that
    # carry an `__RTTI__` record (`vtables.json`) and, for the classes that emit none, the class's
    # own `<Class>_GetVTable` (`vtables-getvtable.json`, finding #529) — together 976 of the 1,074
    # reflection classes.  RTTI wins where both name a vtable; the extension fills the rest.
    vtables = {}
    for fname in ("vtables.json", "vtables-getvtable.json"):
        vp = os.path.join(decomp, "data", fname)
        if not os.path.exists(vp):
            continue
        data = json.load(open(vp))
        table = data.get("vtables", data)
        for k, v in table.items():
            vtables.setdefault(v["class"].split("::")[-1], int(k, 16))
    parents = {}
    hp = os.path.join(decomp, "data", "class-hierarchy.tsv")
    if os.path.exists(hp):
        for line in open(hp):
            p = line.split()
            if len(p) >= 2:
                parents[p[0]] = p[1]

    by_name = {}
    for c in classes:
        name = c["class"].split("::")[-1]
        by_name.setdefault(name, c)

    out = []
    for name in sorted(by_name):
        c = by_name[name]
        # the instance size: walk the ancestry (offsets are absolute) and take the largest end.
        size = 0
        seen = set()
        n = name
        while n and n in by_name and n not in seen:
            seen.add(n)
            for f in by_name[n]["fields"]:
                tid = NAME_TID.get(f["type"].replace("MetaField", ""))
                # a rough element size for the offset sum; the descriptor is authoritative
                sz = 4
                if f["type"] == "igBoolMetaField" or f["type"] == "igCharMetaField" \
                        or f["type"] == "igUnsignedCharMetaField":
                    sz = 1
                elif f["type"] in ("igShortMetaField", "igUnsignedShortMetaField"):
                    sz = 2
                elif f["type"] in ("igLongMetaField", "igDoubleMetaField"):
                    sz = 8
                elif f["type"] == "igVec2fMetaField":
                    sz = 8
                elif f["type"] == "igVec3fMetaField":
                    sz = 12
                elif f["type"] == "igVec4fMetaField":
                    sz = 16
                elif f["type"] == "igMatrix44fMetaField":
                    sz = 64
                if f["offset"] + sz > size:
                    size = f["offset"] + sz
            n = parents.get(n)
        size = align(size, 16) or 16
        fields = []
        for f in c["fields"]:
            short = f["type"].replace("MetaField", "")
            tid = NAME_TID.get(short)
            fields.append((f["name"], 0xff if tid is None or tid not in NAMED else tid, f["offset"]))
        out.append((name, parents.get(name, ""), size, vtables.get(name, 0), fields))
    return out


def emit(classes, path):
    w = []
    w.append("/* Generated by tools/gen_reflection.py -- do not hand-edit.\n"
             " *\n"
             " * The port's reflection schema, from DW4_Decomp/data/reflection.json (T1).  Field\n"
             " * `tid` is the igBinary descriptor type id (0xff = a type igb_inst does not name);\n"
             " * `offset` is the absolute byte offset the engine's field initialiser registers. */\n")
    w.append('#include "dw4/object.h"\n\n')
    for i, (name, parent, size, vtable, fields) in enumerate(classes):
        if not fields:
            continue
        w.append("static const dw4_metafield mo_f%d[] = {\n" % i)
        for fn, tid, off in fields:
            w.append('    { "%s", %d, 0x%x },\n' % (esc(fn), tid, off))
        w.append("};\n")
    w.append("\nconst dw4_metaobject dw4_metaobjects[] = {\n")
    for i, (name, parent, size, vtable, fields) in enumerate(classes):
        w.append('    { "%s", "%s", 0x%x, 0x%x, %s, %d },\n'
                 % (esc(name), esc(parent), size, vtable,
                    ("mo_f%d" % i) if fields else "0", len(fields)))
    w.append("};\n")
    w.append("const int dw4_nmetaobjects = %d;\n" % len(classes))
    text = "".join(w)
    if path == "-":
        sys.stdout.write(text)
        return text
    old = open(path).read() if os.path.exists(path) else None
    if old != text:
        open(path, "w").write(text)
    return text


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--decomp", default=os.environ.get("DW4_DECOMP", os.path.join(PORT, "..")))
    ap.add_argument("--out", default=os.path.join(PORT, "src", "reflection_data.c"))
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    classes = build(a.decomp)
    text = emit(classes, a.out)
    nfields = sum(len(c[4]) for c in classes)
    if a.check:
        cur = open(a.out).read() if os.path.exists(a.out) else ""
        if cur != text:
            print("gen_reflection: %s is stale" % a.out)
            return 1
        print("gen_reflection: current (%d classes, %d fields)" % (len(classes), nfields))
        return 0
    print("gen_reflection: wrote %s (%d classes, %d fields)" % (a.out, len(classes), nfields))
    return 0


if __name__ == "__main__":
    sys.exit(main())
