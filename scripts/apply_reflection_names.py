# apply_reflection_names.py — turn the recovered MetaObject field tables
# (data/reflection.json) into Ghidra StructureDataTypes.
#
# For every class the dump records, a struct named after the class is built
# with one component per field, placed at the exact recovered byte offset and
# carrying the field name plus its recovered `ig*MetaField` type as a comment.
#
# Sizes: scalars use the MetaField type's nominal width; array types and any
# type whose nominal width would overrun the next field are sized from the gap
# to the next field (which is exact). Gaps are filled with undefined bytes, so
# a field list that skips inherited base fields still yields a correct struct.
#
#   pyghidra-run <binary> --project-path ghidra-projects/dw4 \
#       --project-name dw4 -postScript apply_reflection_names.py \
#       --reflection ghidra-projects/dw4/reflection.json --report /tmp/r.json
#   # dry run is the default; add --apply to write into the project
#
# Args:
#   --reflection PATH  reflection.json (default: ghidra-projects/dw4/reflection.json)
#   --out PATH         write the resolved type definitions as JSON
#   --report PATH      write the per-class report JSON
#   --category PATH    data type category (default /DW4/reflection)
#   --min-fields N     only build classes with at least N fields (default 1)
#   --apply            commit the structures (default: report only)
#
# @category PS2
# @runtime PyGhidra

import json
import re
import typing

if typing.TYPE_CHECKING:
    from typing import Any

    currentProgram: Any = None
    getScriptArgs: Any = None

# Nominal width of each MetaField type, in bytes. Array types are deliberately
# absent: their width depends on the declared element count and is taken from
# the gap to the next field. Values below were derived empirically from the
# recovered offsets (the modal inter-field delta), not assumed: note that
# igLong*/igUnsignedLong* are 8 bytes on this ABI, and igStruct can be inline
# (variable), so it is absent too.
NOMINAL = {
    "igBoolMetaField": 1,
    "igCharMetaField": 1,
    "igUnsignedCharMetaField": 1,
    "igShortMetaField": 2,
    "igUnsignedShortMetaField": 2,
    "igIntMetaField": 4,
    "igUnsignedIntMetaField": 4,
    "igLongMetaField": 8,
    "igUnsignedLongMetaField": 8,
    "igFloatMetaField": 4,
    "igEnumMetaField": 4,
    "igRawRefMetaField": 4,
    "igRefMetaField": 4,
    "igObjectRefMetaField": 4,
    "igDependencyMetaField": 4,
    "igVirtualCFuncMetaField": 4,
    "igTrackedElementMetaField": 4,
    "igMemoryDescriptorMetaField": 4,
    "igCompoundMetaField": 4,
    "igStringMetaField": 4,
    "igMemoryRefMetaField": 4,
    "igDoubleMetaField": 8,
    "igVec2fMetaField": 8,
    "igVec3fMetaField": 12,
    "igVec4fMetaField": 16,
    "igVec3ucMetaField": 3,
    "igVec4ucMetaField": 4,
    "igMatrix44fMetaField": 64,
}

# Types that get a real Ghidra data type; everything else is raw bytes.
FLOAT_TYPES = {"igFloatMetaField"}
DOUBLE_TYPES = {"igDoubleMetaField"}

_BAD = re.compile(r"[^A-Za-z0-9_]")


def _args(argv):
    opts = {
        "reflection": "ghidra-projects/dw4/reflection.json",
        "out": None, "report": None, "category": "/DW4/reflection",
        "min_fields": 1, "apply": False, "label_tables": False,
    }
    i = 0
    while i < len(argv):
        a = argv[i]
        if a == "--reflection" and i + 1 < len(argv):
            opts["reflection"] = argv[i + 1]; i += 2
        elif a == "--out" and i + 1 < len(argv):
            opts["out"] = argv[i + 1]; i += 2
        elif a == "--report" and i + 1 < len(argv):
            opts["report"] = argv[i + 1]; i += 2
        elif a == "--category" and i + 1 < len(argv):
            opts["category"] = argv[i + 1]; i += 2
        elif a == "--min-fields" and i + 1 < len(argv):
            opts["min_fields"] = int(argv[i + 1], 0); i += 2
        elif a == "--label-tables":
            opts["label_tables"] = True; i += 1
        elif a == "--apply":
            opts["apply"] = True; i += 1
        else:
            i += 1
    return opts


def _sanitize(name):
    s = _BAD.sub("_", name).strip("_")
    while "__" in s:
        s = s.replace("__", "_")
    if not s or s[0].isdigit():
        s = "cls_" + s
    return s


def _resolve(cls, min_fields):
    """Turn one class's field list into a list of components + diagnostics."""
    fields = [f for f in cls["fields"] if f.get("offset") is not None]
    fields.sort(key=lambda f: f["offset"])
    if len(fields) < min_fields:
        return None, None
    comps = []
    problems = []
    cursor = 0
    for i, f in enumerate(fields):
        off = f["offset"]
        if off < cursor:
            problems.append(f"field {f['name']} at +0x{off:x} overlaps previous (+0x{cursor:x})")
            continue
        nominal = NOMINAL.get(f.get("type"))
        if i + 1 < len(fields):
            delta = fields[i + 1]["offset"] - off
        else:
            delta = None
        if delta is not None:
            size = delta if (nominal is None or nominal > delta) else nominal
        else:
            size = nominal or 4
        if size <= 0:
            problems.append(f"field {f['name']} at +0x{off:x} has non-positive size")
            continue
        if delta is not None and nominal is not None and nominal < delta:
            problems.append(f"field {f['name']} at +0x{off:x}: {nominal} bytes + {delta - nominal} pad")
        if off > cursor:
            comps.append({"offset": cursor, "size": off - cursor, "name": "", "type": None,
                          "comment": "padding"})
        comps.append({"offset": off, "size": size, "name": f["name"],
                      "type": f.get("type"), "comment": f.get("type") or ""})
        cursor = off + size
    return {"components": comps, "size": cursor}, problems


def _main():
    opts = _args(list(getScriptArgs()))
    with open(opts["reflection"], encoding="utf-8") as fh:
        data = json.load(fh)

    definitions = {}
    report = {"built": [], "skipped": [], "problems": []}
    for handle, cls in sorted(data["classes"].items(), key=lambda kv: kv[1]["class"]):
        name = _sanitize(cls["class"])
        if name in definitions:
            report["skipped"].append({"class": cls["class"], "reason": "duplicate sanitized name"})
            continue
        resolved, problems = _resolve(cls, opts["min_fields"])
        if resolved is None:
            continue
        definitions[name] = {"class": cls["class"], "handle": handle,
                             "field_table": cls.get("field_table"),
                             "ctor_table": cls.get("ctor_table"), **resolved}
        report["built"].append({"class": cls["class"], "name": name,
                                "fields": len(cls["fields"]), "size": resolved["size"]})
        if problems:
            report["problems"].append({"class": cls["class"], "problems": problems})

    if opts["out"]:
        with open(opts["out"], "w", encoding="utf-8") as fh:
            fh.write(json.dumps(definitions, indent=1))
    if opts["report"]:
        with open(opts["report"], "w", encoding="utf-8") as fh:
            fh.write(json.dumps(report, indent=1))

    print(f"apply_reflection_names: {len(definitions)} structs "
          f"({len(report['skipped'])} skipped, {len(report['problems'])} with layout notes) "
          f"from {opts['reflection']}")

    if not opts["apply"]:
        print("dry run (no changes); pass --apply to commit")
        return

    from ghidra.program.model.data import (
        ArrayDataType, BooleanDataType, CategoryPath, CharDataType,
        DataTypeConflictHandler, DoubleDataType, FloatDataType,
        IntegerDataType, LongLongDataType, PointerDataType, ShortDataType,
        StructureDataType, Undefined, UnsignedCharDataType,
        UnsignedIntegerDataType, UnsignedLongLongDataType, UnsignedShortDataType,
    )

    dtm = currentProgram.getDataTypeManager()
    cat = CategoryPath(opts["category"])
    undefined1 = Undefined.getUndefinedDataType(1)

    def bytes_type(size):
        """A datatype that is exactly `size` bytes (undefined1 ignores length)."""
        if size in (1, 2, 4, 8):
            return Undefined.getUndefinedDataType(size)
        return ArrayDataType(undefined1, size, 1)

    scalar = {
        "igBoolMetaField": BooleanDataType.dataType,
        "igCharMetaField": CharDataType.dataType,
        "igUnsignedCharMetaField": UnsignedCharDataType.dataType,
        "igShortMetaField": ShortDataType.dataType,
        "igUnsignedShortMetaField": UnsignedShortDataType.dataType,
        "igIntMetaField": IntegerDataType.dataType,
        "igUnsignedIntMetaField": UnsignedIntegerDataType.dataType,
        "igLongMetaField": LongLongDataType.dataType,
        "igUnsignedLongMetaField": UnsignedLongLongDataType.dataType,
        "igFloatMetaField": FloatDataType.dataType,
        "igDoubleMetaField": DoubleDataType.dataType,
        "igStringMetaField": PointerDataType(),
        "igRawRefMetaField": PointerDataType(),
        "igRefMetaField": PointerDataType(),
        "igObjectRefMetaField": PointerDataType(),
        "igVec2fMetaField": ArrayDataType(FloatDataType.dataType, 2, 4),
        "igVec3fMetaField": ArrayDataType(FloatDataType.dataType, 3, 4),
        "igVec4fMetaField": ArrayDataType(FloatDataType.dataType, 4, 4),
        "igMatrix44fMetaField": ArrayDataType(FloatDataType.dataType, 16, 4),
    }

    def field_type(name, size):
        dt = scalar.get(name)
        if dt is not None and dt.getLength() == size:
            return dt
        return bytes_type(size)
    tx = currentProgram.startTransaction("apply_reflection_names")
    created = 0
    try:
        for name, d in sorted(definitions.items()):
            try:
                st = StructureDataType(cat, name, d["size"], dtm)
                for c in d["components"]:
                    dt = field_type(c["type"], c["size"])
                    st.replaceAtOffset(c["offset"], dt, c["size"],
                                       c["name"] or None, c["comment"] or None)
                st.setDescription(
                    f"Recovered MetaObject reflection layout for {d['class']} "
                    f"({len(d['components'])} components)."
                )
                dtm.addDataType(st, DataTypeConflictHandler.REPLACE_HANDLER)
                created += 1
            except Exception as exc:                       # noqa: BLE001
                print(f"  failed {name}: {exc}")
    finally:
        currentProgram.endTransaction(tx, True)
    print(f"apply_reflection_names: created/replaced {created} structures "
          f"under {opts['category']}")

    if opts["label_tables"]:
        from ghidra.program.model.symbol import SourceType

        symtab = currentProgram.getSymbolTable()
        tx = currentProgram.startTransaction("label reflection tables")
        labelled = 0
        try:
            for name, d in sorted(definitions.items()):
                for kind, key in (("fields", "field_table"), ("ctors", "ctor_table")):
                    va = d.get(key)
                    if not va:
                        continue
                    addr = toAddr(int(va, 16))
                    try:
                        symtab.createLabel(addr, f"reflect_{name}_{kind}", SourceType.USER_DEFINED)
                        labelled += 1
                    except Exception:  # noqa: BLE001
                        pass
        finally:
            currentProgram.endTransaction(tx, True)
        print(f"apply_reflection_names: added {labelled} reflection table labels")


def main():
    import traceback

    try:
        _main()
    except BaseException:
        traceback.print_exc()
        raise


main()
