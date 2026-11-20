#!/usr/bin/env python3
"""Generate C structs for the classes the reflection metadata recovered.

`data/reflection.json` holds 659 classes with 3,680 fields, each with a name, a byte
offset and a MetaField type. That is enough to state the layout of every reflected class
as a real C struct — the thing m2c's `*(int *)((char *)p + 12)` cannot express, and the
first half of typed coverage (the second half applies them to the C).

Three decisions make the output trustworthy rather than plausible:

  * **the layout comes from the offsets, the type and size from the metadata.** A field sits
    at the offset reflection recorded; gaps become explicit padding. Its *size* is fixed by
    the MetaField kind: a bool is one byte (`igMetaField` has `_persistent` at +38 and
    `_shallowCopyMethod` at +39, so a map that guessed `int` there would shift every later
    field), a vector is 2/3/4 floats, a matrix is 16 floats, and a reference or string is a
    4-byte handle. Only an inline *array* (`ig*ArrayMetaField`) takes its element count from
    the distance to the next field, because reflection does not record it.
  * **the registered instance size closes the struct.** Every class passes its `sizeof` to
    `igMetaObject_RegisterClass` (`li t2,N` in `asm/<Class>_Register.s`, docs/engine/
    reflection-metadata.md section 1). That is what sizes a *last* field that is an array
    (`igMersenneTwisterRandomNumber._mt`: 2508 - 12 = 624 words, the MT19937 state) and what
    pads the tail, so `sizeof(Class)` on the host equals the retail instance size
    (scripts/check_reflected_layout.py asserts it).
  * **a disagreement is reported, not hidden.** Where the metadata's size for a field
    contradicts the distance to the next field, or the fields overrun the registered
    instance size, the offset wins and the mismatch is printed, because that is a real fact
    about the recovered metadata.

Usage:
    scripts/gen_type_headers.py [--out include/dw4/support/reflected.h] [--asm asm] [--report]
"""

import argparse
import json
import os
import re
import sys

sys.path.insert(0, "tools")
from typed_coverage import META_TO_C  # noqa: E402  (one source of truth for the mapping)

# Natural size of each C type we emit, for the last field of a class (where no next
# offset bounds it) and for validating the metadata.
C_SIZE = {"char": 1, "unsigned char": 1, "short": 2, "unsigned short": 2,
          "int": 4, "unsigned int": 4, "long long": 8, "unsigned long long": 8,
          "float": 4, "double": 8}

# The flavour to fall back on when the span and the metadata disagree about size.
BY_SIZE = {
    ("int", 1): "unsigned char", ("int", 2): "short", ("int", 4): "int", ("int", 8): "long long",
    ("unsigned int", 1): "unsigned char", ("unsigned int", 2): "unsigned short",
    ("unsigned int", 4): "unsigned int", ("unsigned int", 8): "unsigned long long",
    ("float", 4): "float",
    ("char", 1): "char", ("char", 2): "short", ("char", 4): "int", ("char", 8): "long long",
    ("short", 2): "short", ("short", 1): "char", ("short", 4): "int", ("short", 8): "long long",
    ("unsigned short", 2): "unsigned short",
    ("long long", 8): "long long", ("long long", 4): "int", ("long long", 1): "unsigned char",
    ("double", 8): "double", ("double", 4): "float",
}

# MetaField types whose C type is FIXED by the metadata, with the byte size it denotes.
# For these the distance to the next field is not the field's size: a bool followed 4 bytes
# later by an int is a 1-byte bool plus 3 bytes of alignment padding, and the padding walk
# covers the rest.  This is what lets a `*(unsigned char *)((char *)p + 60)` store type as a
# member -- without it a bool span of 4 was emitted as `int` and could not take a 1-byte
# write.  Refs are 4-byte handles stored inline, not inline aggregates, so they are here too.
SCALAR = {
    "igBoolMetaField": ("unsigned char", 1),
    "igCharMetaField": ("char", 1),
    "igUnsignedCharMetaField": ("unsigned char", 1),
    "igShortMetaField": ("short", 2),
    "igUnsignedShortMetaField": ("unsigned short", 2),
    "igIntMetaField": ("int", 4),
    "igUnsignedIntMetaField": ("unsigned int", 4),
    "igEnumMetaField": ("int", 4),
    "igFloatMetaField": ("float", 4),
    "igLongMetaField": ("long long", 8),
    "igUnsignedLongMetaField": ("unsigned long long", 8),
    "igDoubleMetaField": ("double", 8),
    "igObjectRefMetaField": ("int", 4),
    # Decision: a string field is the 4-byte handle of an interned string, emitted as `int` like the
    # object references -- `const char *` would widen the field on a 64-bit host, and the matched C
    # reads it as a word.  Readers cast at the use site: `(const char *)self->_name`.
    "igStringMetaField": ("int", 4),
    "igRawRefMetaField": ("int", 4),
    "igMemoryRefMetaField": ("int", 4),
}

# Inline aggregates whose size the MetaField kind fixes: a vector or matrix is stored *in* the
# object as consecutive floats (igMatrix44f_SetIdentity writes 16 of them), whatever the distance
# to the next field says -- a trailing vector has no next field at all, and a 4-byte gap after a
# matrix (igModelViewMatrixAttr) is padding, not a 17th element.
VECTOR = {
    "igVec2fMetaField": ("float", 2),
    "igVec3fMetaField": ("float", 3),
    "igVec4fMetaField": ("float", 4),
    "igMatrix44fMetaField": ("float", 16),
}

# Vector kinds whose C++ type exists in the kit's form (an array of floats with inline operations):
# a whole, float-aligned field of that kind is declared as the type under C++, and C keeps the floats.
# {kind: (C++ type, header)}
KIT_VECTOR = {
    "igVec2fMetaField": ("igVec2f", "dw4/maths/igVec2f.h"),
    "igVec3fMetaField": ("igVec3f", "dw4/maths/igVec3f.h"),
    "igVec4fMetaField": ("igVec4f", "dw4/maths/igVec4f.h"),
}

# Inline arrays: the element type comes from the kind, the element count from the distance to the
# next field (reflection records no count), or for a last field from the registered instance size.
ARRAY = {
    "igIntArrayMetaField": "int",
    "igEnumArrayMetaField": "int",
    "igUnsignedIntArrayMetaField": "unsigned int",
    "igFloatArrayMetaField": "float",
    "igCharArrayMetaField": "char",
    "igUnsignedCharArrayMetaField": "unsigned char",
    "igBoolArrayMetaField": "unsigned char",
    "igShortArrayMetaField": "short",
    "igUnsignedShortArrayMetaField": "unsigned short",
    "igVec4fArrayMetaField": "float",
    "igObjectRefArrayMetaField": "int",
}
# igStructMetaField is an inline struct of a type reflection does not name; it keeps the
# distance-to-next-field rule and is emitted as words.

# Fields kept at their old `int` spelling because matched units read them as a word and the
# typed spelling changes their bytes: {(class, field): number of such units}.  Each entry is a
# measured exception (see docs/engine/typed-coverage.md, "Sizing fields by their MetaField kind").
WORD_TYPED = {
}

REGISTER_SIZE_RE = re.compile(r"\bli\s+t2,(\d+)\b")

KEYWORDS = {"int", "char", "float", "double", "short", "long", "unsigned", "signed",
            "void", "const", "static", "struct", "union", "enum", "default", "case",
            "switch", "while", "for", "if", "else", "return", "bool", "class"}


def ident(name):
    """A safe C identifier for a reflected field name."""
    out = re.sub(r"\W", "_", name)
    if out[0].isdigit():
        out = "_" + out
    if out in KEYWORDS:
        out += "_"
    return out


def load_hierarchy(path):
    """{class: base} from `data/class-hierarchy.tsv` (generated, do not hand-edit)."""
    parent = {}
    try:
        fh = open(path)
    except FileNotFoundError:
        return parent
    for line in fh:
        if line.startswith("#") or not line.strip():
            continue
        parts = line.rstrip("\n").split("\t")
        if len(parts) >= 2 and parts[0] and parts[1]:
            parent[parts[0]] = parts[1]
    return parent


def load_instance_sizes(asm_dir, classes):
    """{class: registered instance size} read from `asm/<Class>_Register.s`.

    The registrar passes `sizeof(Class)` as the seventh argument of igMetaObject_RegisterClass
    (`li t2,N`; docs/engine/reflection-metadata.md section 1, `_sizeofSize` at metaobj+0x48).
    The assembly split is generated text, so a tree without it simply gets no sizes.
    """
    sizes = {}
    if not asm_dir or not os.path.isdir(asm_dir):
        return sizes
    for cls in classes:
        path = os.path.join(asm_dir, cls + "_Register.s")
        if not os.path.exists(path):
            continue
        found = REGISTER_SIZE_RE.findall(open(path, errors="replace").read())
        if found:
            sizes[cls] = int(found[-1])
    return sizes


def declare(cls, f, field_name, span, trailing, inst_size):
    """The C declaration of one reflected field.

    Returns (decl, size, align, is_aggregate, mismatch): the member text, its byte size and host
    alignment, whether it is an inline aggregate, and None or a (natural size, span, reason)
    triple for the report.  `span` is the distance to the next field, or the natural size when
    the field is the last one (`trailing`).
    """
    kind = f["type"]
    off = f["offset"]
    natural = META_TO_C.get(kind, "int")
    nsize = C_SIZE.get(natural, 4)

    def member(ctype, count=None, mismatch=None, comment=""):
        esize = C_SIZE[ctype]
        text = "%s %s%s;%s" % (ctype, field_name, "" if count is None else "[%d]" % count, comment)
        return text, esize * (count or 1), min(8, esize), count is not None, mismatch

    if (cls, f["name"]) in WORD_TYPED:
        # a measured exception: the typed spelling changes matched bytes, so the field stays a
        # word and says so
        return member("int", comment=" /* typed int: %d matched units read it as a word (see classlink) */"
                      % WORD_TYPED[(cls, f["name"])])
    scalar = SCALAR.get(kind)
    if scalar is not None:
        # the metadata's scalar type fixes the field's size; whatever is left of the
        # distance to the next field is alignment padding, added by the caller
        return member(scalar[0])
    vector = VECTOR.get(kind)
    if vector is not None:
        elem, count = vector
        if off % 4 != 0:
            # not float-aligned: keep the bytes rather than let the host compiler shift the field
            return member("unsigned char", 4 * count)
        if not trailing and span < 4 * count:
            # the next field sits inside the vector: the offset wins, the overlap is reported
            return member(elem, span // 4, (4 * count, span, "vector-overlap"))
        return member(elem, count)
    elem = ARRAY.get(kind)
    if elem is not None:
        esize = C_SIZE[elem]
        if trailing:
            if inst_size is not None and inst_size > off and (inst_size - off) % esize == 0:
                count = (inst_size - off) // esize
            else:
                # no registered size to bound the array: one element, and the report says so
                return member(elem, 1, (esize, 0, "count-unknown"))
        else:
            count = max(1, span // esize)
        if off % esize != 0:
            return member("unsigned char", count * esize)
        return member(elem, count)
    # igStructMetaField (and any kind the tables do not name): an inline aggregate whose shape
    # reflection does not record, so the distance to the next field is its size
    if span == nsize:
        if nsize > 1 and off % nsize != 0:
            return member("unsigned char", nsize)
        return member(natural)
    if span > nsize and span % 4 == 0:
        return member(natural, span // 4)
    if span > nsize:
        return member("unsigned char", span)
    return member(natural, mismatch=(nsize, span, "sub-field"))


def load_members(path):
    """{class: [declaration]} from `config/class-members.tsv`: the member functions and static members a
    class declares under C++, written into its class body in table order (empty when the table is absent).
    A declaration may open with the kit's access label (`protected: igObject();`); one without is public."""
    members = {}
    for cls, decl in table_rows(path, 2):
        members.setdefault(cls, []).append(decl.strip())
    return members


_ACCESS = re.compile(r"^(public|protected|private)\s*:\s*")


def split_access(decl):
    """(access, declaration) of a class-members.tsv declaration: its label's, else public."""
    m = _ACCESS.match(decl)
    return (m.group(1), decl[m.end():]) if m else ("public", decl)


def member_lines(decls, access):
    """The class-body lines of a class's rows in table order, a label opening each run of one access (the kit
    header's sections); `access` is the one in effect before them -> (lines, access after them). An object
    macro row leaves the class public, as the macros end."""
    out = []
    for decl in decls:
        want, text = split_access(decl)
        if want != access:
            out.append("%s:" % want)
            access = want
        out.append("    " + text)
    return out, access


def load_typed_fields(path):
    """{(class, field): C++ type} from `config/typed-fields.tsv`: an object-reference field a class declares
    with its referenced type under C++ (C keeps the word)."""
    return {(cls, field): ctype.strip() for cls, field, ctype in table_rows(path, 3)}


def load_converted(path):
    """{class: library namespace} from `config/converted-classes.tsv`: the classes declared, under C++, as
    `Gap::<library>::<class>` polymorphic classes beside their flat struct."""
    return {cls: lib.strip() for cls, lib in table_rows(path, 2)}


def table_rows(path, columns):
    rows = []
    if path and os.path.exists(path):
        with open(path) as fh:
            lines = fh.readlines()
        for number, line in enumerate(lines, 1):
            if line.startswith("#") or not line.strip():
                continue
            row = line.rstrip("\n").split("\t", columns - 1)
            if len(row) != columns or not all(cell.strip() for cell in row):
                sys.exit("%s:%d: expected %d tab-separated columns" % (path, number, columns))
            rows.append(row)
    return rows


# The root's declarations are config/class-members.tsv's igObject rows, in table order: its constructor (retail's
# igObject_InitHeader), its class operator delete, its virtual functions in vtable order (slot n at vtable byte
# offset 8 + 4 * n, after the two-word class header; the order of include/dw4/core/igObjectDispatchView.h) with
# the inline virtual getMeta at slot 20, then its static members. It declares no destructor: Alchemy's
# destructors are not virtual, and slot 0 is an ordinary method.


def converted_classes(converted, parent, layouts, members):
    """The C++ declarations of the converted classes: each `Gap::<library>::<class>` derives from its
    converted parent (the root `Gap::Core::igObject` at the top) and declares only its own fields, at
    their reflected offsets after the parent's registered size, then its config/class-members.tsv rows.
    Every converted class is promoted into `Gap` (`using <library>::<class>;`), as the kit's headers do,
    so code in any Gap library names it unqualified; outside `Gap` the flat struct keeps the name."""
    order, seen = [], set()

    def visit(cls, chain=()):
        if cls in seen:
            return
        if cls in chain:
            sys.exit("config/converted-classes.tsv: %s is its own ancestor" % cls)
        base = parent.get(cls)
        if cls != "igObject":
            if base not in converted:
                sys.exit("config/converted-classes.tsv: %s derives from %s, which is not converted"
                         % (cls, base))
            visit(base, chain + (cls,))
        seen.add(cls)
        order.append(cls)

    for cls in sorted(converted):
        if cls not in layouts:
            sys.exit("config/converted-classes.tsv: %s has no reflected layout" % cls)
        visit(cls)

    out = ["#ifdef __cplusplus",
           "/* The converted classes: Alchemy's polymorphic classes in their Gap namespaces",
           " * (config/converted-classes.tsv). The flat structs above stay the C view. */",
           "#include \"dw4/core/igObject.h\""]
    if any("igSmartPointer<" in line for cls in order for _off, _size, line in layouts[cls][4]):
        # a smart-pointer member needs the template, which reads the flat igObject above
        out.append("#include \"dw4/core/igSmartPointer.h\"")
    if any(re.search(r"\bigStringRef \w+;", line) for cls in order for _off, _size, line in layouts[cls][4]):
        # a string member is the pool's counted reference
        out.append("#include \"dw4/core/igStringRef.h\"")
    out.append("namespace Gap {")
    for lib in sorted(set(converted.values())):
        out.append("namespace %s { %s }" % (lib, " ".join("class %s;" % c for c in sorted(converted)
                                                        if converted[c] == lib)))
    out.extend("using %s::%s;" % (converted[c], c) for c in sorted(converted))
    out.append("}")
    for cls in order:
        handle, nfields, size_note, size, placed = layouts[cls]
        lib = converted[cls]
        out.append("")
        out.append("namespace Gap {")
        out.append("namespace %s {" % lib)
        out.append("/* handle 0x%06x, %d field(s), %s */" % (handle, nfields, size_note))
        if cls == "igObject":
            if not any(split_access(decl)[1].startswith(("virtual ", "inline virtual "))
                       for decl in members.get(cls, [])):
                sys.exit("config/class-members.tsv: the root igObject declares no virtual function; its rows "
                         "give its constructor, virtual slots and getMeta")
            out.append("class igObject {")
            # the slot declarations come before the reference count, as the kit's root declares them
            access = split_access(members[cls][0])[0]
            out.append("%s:" % access)
            lines, access = member_lines(members[cls], access)
            out.extend(lines)
            if access != "public":
                out.append("public:")                    # the fields: C code reads them as data
            cursor = 4
            placed = [p for p in placed if p[0] >= 4]
        else:
            base = parent[cls]
            out.append("class %s : public Gap::%s::%s {" % (cls, converted[base], base))
            out.append("public:")
            cursor = layouts[base][3]
        for off, fsize, line in placed:
            if off < cursor:
                sys.exit("%s: field at +%d lies inside its parent (%d bytes)" % (cls, off, cursor))
            if off > cursor:
                out.append("    char _pad%d[%d];" % (cursor, off - cursor))
            out.append(line)
            cursor = off + fsize
        if size > cursor:
            out.append("    char _pad%d[%d];" % (cursor, size - cursor))
        if cls != "igObject":
            out.extend(member_lines(members.get(cls, []), "public")[0])
        out.append("};")
        out.append("}")
        out.append("}")
    out.append("#endif")
    out.append("")
    return out


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--reflection", default="data/reflection.json")
    ap.add_argument("--hierarchy", default="data/class-hierarchy.tsv")
    ap.add_argument("--asm", default="asm",
                    help="assembly split holding <Class>_Register.s (registered instance sizes)")
    ap.add_argument("--out", default="include/dw4/support/reflected.h")
    ap.add_argument("--report", action="store_true")
    ap.add_argument("--members", default="config/class-members.tsv",
                    help="member declarations each class gets under C++ (class, declaration)")
    ap.add_argument("--typed-fields", default="config/typed-fields.tsv",
                    help="object-reference fields typed under C++ (class, field, C++ type)")
    ap.add_argument("--converted", default="config/converted-classes.tsv",
                    help="classes declared as Gap::<Library>::<Class> polymorphic classes (class, library)")
    args = ap.parse_args(argv)

    data = json.load(open(args.reflection))
    parent = load_hierarchy(args.hierarchy)
    own = {}
    for handle, o in data["classes"].items():
        own[o["class"]] = sorted(o.get("fields") or [], key=lambda f: f["offset"])

    # Authoritative fields reflection does not list (igObject's vtable and reference count, unreflected
    # members such as igAdxFile's ADXF handle): config/SLUS-20836/authoritative-fields.tsv, inherited by
    # every subclass like any other field.
    overlay = os.path.join(os.path.dirname(os.path.abspath(args.reflection)), "..", "config",
                           "SLUS-20836",
                           "authoritative-fields.tsv")
    if os.path.exists(overlay):
        for line in open(overlay):
            if line.strip() and not line.startswith("#"):
                cls, off, mtype, fname = line.rstrip("\n").split("\t")[:4]
                own.setdefault(cls, []).append({"name": fname, "offset": int(off), "type": mtype,
                                                "overlay": True})
                own[cls].sort(key=lambda f: f["offset"])

    # A class's struct carries its **ancestors' fields too**.  Reflection lists only a class's
    # own fields, so `igVec3fList` (whose `_count`/`_capacity`/`_data` come from `igDataList`)
    # had *no struct at all* -- you could not declare a pointer to it, which is what typing
    # an object-graph walk needs (`((igVec3fList *)p)->_count`).  The
    # layout does not change: a base sits at offset 0, so inherited fields keep their
    # absolute offsets.
    cache = {}

    def merged(cls):
        if cls in cache:
            return cache[cls]
        out = []
        base = parent.get(cls)
        if base and base != cls and base in own:
            out.extend(merged(base))
        out.extend(own[cls])
        cache[cls] = out
        return out

    # The game layer (config/typed-scope.tsv, tools/typed_scope.py): its classes always get a
    # struct, even a field-less one (igObject's header words only), so a pointer to any of them can be declared.
    scope_classes = set()
    scope_tsv = os.path.join(os.path.dirname(os.path.abspath(args.reflection)), "..", "config", "typed-scope.tsv")
    if os.path.exists(scope_tsv):
        for line in open(scope_tsv):
            f = line.rstrip("\n").split("\t")
            if len(f) > 1 and not line.startswith("#"):
                scope_classes.add(f[1])

    # a converted class needs its layout for the namespaced declaration even when it gets no flat struct
    converted_names = set(load_converted(args.converted))

    classes = []
    unflat = set()
    seen = set()
    for handle, o in data["classes"].items():
        if o["class"] in seen:
            # reflection.json keys by handle, and one name (`igModelViewMatrixBoneSelectList`,
            # two handles, no own fields) appears twice; emitting both would redefine the tag
            continue
        fields = merged(o["class"])
        # a class whose only fields are the inherited authoritative overlay (igObject's two words)
        # gets no struct of its own, except igObject itself
        if not fields or (o["class"] != "igObject" and o["class"] not in scope_classes
                          and all(f.get("overlay") for f in fields)):
            if not fields or o["class"] not in converted_names:
                continue
            unflat.add(o["class"])
        seen.add(o["class"])
        classes.append((o["class"], int(handle, 16), fields))
    # igObject comes first: under C++ every other class derives from it.
    classes.sort(key=lambda c: (c[0] != "igObject", c[0]))
    inst_sizes = load_instance_sizes(args.asm, [c[0] for c in classes])
    flat_classes = [c for c in classes if c[0] not in unflat]

    lines = [
        "/* GENERATED by scripts/gen_type_headers.py — do not edit.",
        " *",
        " * Structs for every class the reflection metadata recovered (%d classes, %d fields,"
        % (len(flat_classes), sum(len(c[2]) for c in flat_classes)),
        " * from data/reflection.json). Each struct carries its **ancestors' fields too**",
        " * (data/class-hierarchy.tsv): reflection lists only a class's own fields, so a subclass",
        " * whose fields are all inherited (igVec3fList, whose _count/_capacity/_data come from",
        " * igDataList) would otherwise have no struct at all. The layout is unchanged — a base",
        " * sits at offset 0, so inherited fields keep their absolute offsets.",
        " *",
        " * Field offsets are the reflected ones; gaps are explicit padding, so each field sits",
        " * exactly where reflection recorded it. A field's *type and size* come from its MetaField",
        " * kind: a bool is one byte (igMetaField has a bool at +38 and a char at +39), a vector is",
        " * float[2]/[3]/[4], a matrix float[16], a string or object reference a 4-byte handle",
        " * (`int`), and an inline array takes its element type from",
        " * the kind and its count from the distance to the next field. The struct's size is the",
        " * instance size the class registers (`li t2,N` in asm/<Class>_Register.s), which sizes a",
        " * trailing array and the tail padding; `sizeof N` in each struct's comment records it and",
        " * scripts/check_reflected_layout.py asserts it on the host.",
        " *",
        " * These are the recovered types, not the ones the matched C happens to use: where the",
        " * two disagree the C wins and the disagreement is a measurement (tools/typed_coverage.py).",
        " * A field marked `typed int: N matched units read it as a word` is such a measured",
        " * exception, kept as a word so those units keep their bytes.",
        " */",
        "#ifndef DW4_REFLECTED_H",
        "#define DW4_REFLECTED_H",
        "",
    ]
    members = load_members(args.members)
    typed_fields = load_typed_fields(args.typed_fields)
    converted = load_converted(args.converted)
    if converted:
        # the polymorphic root every converted class derives from
        converted.setdefault("igObject", "Core")
    kit_headers = sorted({header for _type, header in KIT_VECTOR.values()})
    if members or converted or kit_headers:
        lines.extend(["#ifdef __cplusplus"]
                     + (["#include \"dw4/core/igObjectMacros.h\""] if members or converted else [])
                     + ["#include \"%s\"" % header for header in kit_headers] + ["#endif", ""])
    mismatches = []
    aggregates = 0
    sized = 0
    layouts = {}
    for name, handle, fields in classes:
        used, body = set(), []
        cursor = 0
        maxalign = 1
        inst_size = inst_sizes.get(name)
        flat = name not in converted
        own_ids = {id(f) for f in own.get(name, [])}
        placed = []
        for i, f in enumerate(fields):
            off, raw_name = f["offset"], f["name"]
            field_name = ident(raw_name)
            while field_name in used:
                field_name += "_"
            used.add(field_name)
            trailing = i + 1 >= len(fields)
            span = C_SIZE.get(META_TO_C.get(f["type"], "int"), 4) if trailing \
                else fields[i + 1]["offset"] - off
            if off < cursor:
                # reflection listed a field inside the previous one; the offset still wins,
                # so the field is dropped rather than allowed to overlap
                mismatches.append((name, raw_name, off, f["type"], cursor - off, 0, "overlap"))
                continue
            decl, size, align, is_aggregate, mismatch = declare(name, f, field_name, span,
                                                                trailing, inst_size)
            aggregates += is_aggregate
            maxalign = max(maxalign, align)
            if mismatch:
                mismatches.append((name, raw_name, off, f["type"]) + mismatch)
            if off > cursor:
                body.append("    char _pad%d[%d];" % (cursor, off - cursor))
            line = "    %-46s /* +%-4d %s */" % (decl, off, f["type"])
            typed = typed_fields.get((name, raw_name))
            kit = KIT_VECTOR.get(f["type"])
            if not typed and kit and decl == "float %s[%d];" % (field_name, VECTOR[f["type"]][1]):
                # the whole vector, float-aligned: the kit's type under C++
                typed = kit[0]
            if typed:
                typed_line = "    %-46s /* +%-4d %s */" % ("%s %s;" % (typed, field_name), off, f["type"])
            if typed and flat:
                body.extend(["#ifdef __cplusplus", typed_line, "#else", line, "#endif"])
            else:
                body.append(line)
            if id(f) in own_ids:
                placed.append((off, size, typed_line if typed else line))
            cursor = off + size
        # Close the struct at the registered instance size: tail padding so sizeof() on the
        # host is the retail one.  Fields past the registered size are reported (the offsets
        # still win), and a class with no registrar keeps the size its fields imply.
        if inst_size is not None and inst_size >= cursor:
            if inst_size > cursor:
                body.append("    char _pad%d[%d];" % (cursor, inst_size - cursor))
            size_note = "sizeof %d (registered instance size)" % inst_size
            struct_size = inst_size
            sized += 1
        else:
            if inst_size is not None:
                mismatches.append((name, "<instance size>", inst_size, "igMetaObject_RegisterClass",
                                   inst_size, cursor, "fields-overrun-instance-size"))
            struct_size = (cursor + maxalign - 1) // maxalign * maxalign
            size_note = "sizeof %d (from the fields; %s)" % (
                struct_size, "no registrar found" if inst_size is None
                else "registered %d is smaller" % inst_size)
        layouts[name] = (handle, len(fields), size_note, struct_size, placed)
        if name in unflat:
            continue
        # Under C++ a class holding igObject's two words derives from it, so a smart pointer can
        # convert T * to igObject * implicitly. The layout is the same, and C keeps the flat view.
        derives = name != "igObject" and [f["name"] for f in fields[:2]] == ["_vtable", "_refCount"] \
            and len(body) >= 2
        if derives:
            lines.append("#ifdef __cplusplus")
            lines.append("typedef struct %s : public igObject {" % name)
            lines.append("#else")
        lines.append("/* handle 0x%06x, %d field(s), %s */" % (handle, len(fields), size_note))
        lines.append("typedef struct %s {" % name)
        if derives:
            lines.extend(body[:2])
            lines.append("#endif")
            lines.extend(body[2:])
        else:
            lines.extend(body)
        if flat and members.get(name):
            lines.append("#ifdef __cplusplus")
            lines.extend(member_lines(members[name], "public")[0])
            lines.append("#endif")
        lines.append("} %s;" % name)
        lines.append("")

    if converted:
        lines.extend(converted_classes(converted, parent, layouts, members))
    for cls in sorted(members):
        if cls not in converted and cls not in layouts:
            sys.exit("config/class-members.tsv: %s has no reflected struct to hold members; "
                     "declare it in config/converted-classes.tsv" % cls)
    lines.append("#endif /* DW4_REFLECTED_H */")
    open(args.out, "w").write("\n".join(lines) + "\n")
    print("wrote %s: %d classes, %d fields" % (args.out, len(flat_classes),
                                               sum(len(c[2]) for c in flat_classes)))
    print("  %d field(s) are inline aggregates (vectors, matrices, arrays): emitted as "
          "arrays of the element type" % aggregates)
    print("  %d of %d classes closed at their registered instance size (%s)"
          % (sized, len(flat_classes), args.asm))
    if WORD_TYPED:
        print("  %d field(s) kept as `int` because matched units read them as a word"
              % len(WORD_TYPED))
    if mismatches:
        print("  %d field(s) where the metadata's size disagrees with the recorded layout "
              "(the offset won; the field is padded, truncated or dropped):" % len(mismatches))
        for m in mismatches[:12 if not args.report else len(mismatches)]:
            print("    %-28s %-22s +%-5d %-24s meta=%-3d span=%-4d %s" % m)


if __name__ == "__main__":
    main()
