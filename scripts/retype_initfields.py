#!/usr/bin/env python3
"""Type the `<Class>_InitFields` family from the reflection field list.

Every `<Class>_InitFields` is the same shape (the 142-function
family):

    temp_s1 = (void *)(DAT_0055f170[0]);                              /* class handle */
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004865a0[0], 9);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));    /* field k = 0 */
    *(int *)((char *)(temp_s2) + 56) = FUN_0014b980();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_00149aa0);

`temp_s0` is the class's own field count, and the loop runs over the class's **own
declared fields in reflection order** — so `GetFieldAt(_, count + k)` returns the
MetaField object for `reflection[Class].fields[k]`, and *its class* is that field's
declared type (`igObjectRefMetaField`, `igEnumMetaField`, …).  That type fixes what
+52 and +56 mean: `igGeometryAttr`'s object-ref fields at k = 0,1,5,7,8 get
`_metaObject` at +56 and its one enum field at k = 2 gets `_getMetaEnumFunction` at
+52 — which is exactly the 5 + 1 accesses the file contains.

The rewrite adds an explicit cast around the temporary rather than retyping its
declaration, so it touches one expression and cannot change codegen:

    *(int *)((char *)(temp_s2) + 56) = X;   ->   ((igObjectRefMetaField *)temp_s2)->_metaObject = X;

Signatures live in `config/SLUS-20836/signatures.tsv`, seeded from the recovered object model
(`igMetaObject_GetFieldAt -> igMetaField *`, …); the pass reads it so the call
types are data, not hard-coded.

Usage:
    scripts/retype_initfields.py            # report
    scripts/retype_initfields.py --apply    # rewrite; then `make check` + `make link`
"""

import argparse
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tools"))
from typed_coverage import split_functions  # noqa: E402

TYPE_WIDTH = {"char": 1, "signed char": 1, "unsigned char": 1, "short": 2,
              "unsigned short": 2, "int": 4, "unsigned int": 4, "float": 4,
              "long": 4, "unsigned long": 4, "long long": 8,
              "unsigned long long": 8, "double": 8}

STRUCT_RE = re.compile(r"typedef struct (\w+) \{(.*?)\} \1;", re.S)
FIELD_RE = re.compile(r"^\s*([A-Za-z_][\w ]*?)\s*(\*?)(\w+)(\[\d+\])?\s*;\s*/\*\s*\+(\d+)", re.M)
INCLUDE_ANCHOR = re.compile(r"(\*/\n)", re.M)
INITFIELDS_RE = re.compile(r"^(\w+)_InitFields$")
GETFIELD_RE = re.compile(r"(\w+)\s*=\s*\(\s*void\s*\*\s*\)\s*\(\s*igMetaObject_GetFieldAt"
                         r"\s*\([^,]+,\s*(\w+)\s*(?:\+\s*(0[xX][0-9A-Fa-f]+|\d+)\s*)?\)\s*\)")


def load_header(path):
    text = open(path, errors="replace").read()
    out = {}
    for m in STRUCT_RE.finditer(text):
        fields = {}
        for fm in FIELD_RE.finditer(m.group(2)):
            if re.match(r"_pad\d+$", fm.group(3)):
                continue
            fields[int(fm.group(5))] = (fm.group(3), fm.group(1).strip(), bool(fm.group(4)))
        out[m.group(1)] = fields
    return out


def load_hierarchy(path):
    """{class: base} from `data/class-hierarchy.tsv` (generated, do not hand-edit)."""
    parent = {}
    if not os.path.exists(path):
        return parent
    for line in open(path):
        if line.startswith("#") or not line.strip():
            continue
        parts = line.rstrip("\n").split("\t")
        if len(parts) >= 2 and parts[0] and parts[1]:
            parent[parts[0]] = parts[1]
    return parent


def merge_base_fields(own, parent, cls, cache):
    """A class's fields plus every ancestor's, keyed by absolute offset.

    A generated struct only carries the class's *own* fields: `igObjectRefMetaField`
    is `char _pad0[56]` then `_metaObject`, so the `_construct` its objects inherit
    from `igRefMetaField` is not in it.  Layouts are inherited at offset 0, so a
    base's offsets are already absolute and a merge is just a dict union with the
    subclass winning on a collision.
    """
    if cls in cache:
        return cache[cls]
    fields = {}
    base = parent.get(cls)
    if base and base != cls and base in own:
        fields.update(merge_base_fields(own, parent, base, cache))
    for off, entry in own.get(cls, {}).items():
        fields[off] = entry + (cls,)      # (name, ctype, is_array, declaring class)
    cache[cls] = fields
    return fields


def load_signatures(path):
    """{name: (return_type, [param_types])} from `config/SLUS-20836/signatures.tsv`."""
    out = {}
    if not os.path.exists(path):
        return out
    for line in open(path):
        line = line.rstrip("\n")
        if not line or line.startswith("#") or line.startswith("\t"):
            continue
        parts = line.split("\t")
        if len(parts) < 2:
            continue
        name, ret = parts[0], parts[1]
        params = [p.strip() for p in parts[2].split(",") if p.strip()] if len(parts) > 2 else []
        out[name] = (ret, params)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--header", default="include/dw4/reflected.h")
    ap.add_argument("--hierarchy", default="data/class-hierarchy.tsv")
    ap.add_argument("--reflection", default="data/reflection.json")
    ap.add_argument("--signatures", default="config/SLUS-20836/signatures.tsv")
    ap.add_argument("--src", default="src")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--check", action="store_true",
                    help="validate every emitted _InitFields member against the mapping")
    args = ap.parse_args()

    own = load_header(args.header)
    parent = load_hierarchy(args.hierarchy)
    cache = {}
    header = {c: merge_base_fields(own, parent, c, cache) for c in own}
    sigs = load_signatures(args.signatures)
    refl = json.load(open(args.reflection))
    # The field index a `_InitFields` body uses is **registration order**, not offset order:
    # `CreateFields` registers the class's own fields in the order reflection lists them, and
    # that is the order `GetFieldAt(metaObject, count + k)` indexes.  The two disagree for 55
    # of 470 classes (e.g. igCollisionGrid lists _cells, _activeCells, _processedCells, ...
    # and only then _sizeX/_sizeY/_sizeZ), so sorting by offset silently skips the fields that
    # moved.  Use the given order.
    classes = {o["class"]: o["fields"] for o in refl["classes"].values()}

    getfield_ret = sigs.get("igMetaObject_GetFieldAt", ("igMetaField *", []))[0]
    if getfield_ret not in ("igMetaField *", "igMetaField*"):
        print("warning: igMetaObject_GetFieldAt does not return igMetaField * "
              "in %s (%r)" % (args.signatures, getfield_ret))

    files = sorted(glob.glob(os.path.join(args.src, "**", "*.c"), recursive=True) +
                   glob.glob(os.path.join(args.src, "**", "*.cpp"), recursive=True))

    if args.check:
        member_re = re.compile(r"\(\s*\(\s*(\w+)\s*\*\s*\)\s*(\w+)\s*\)\s*->\s*(_\w+)")
        bad, n = [], 0
        for path in files:
            text = open(path, errors="replace").read()
            if "igMetaObject_GetFieldAt" not in text:
                continue
            for name, _sig, start, end in split_functions(text):
                m = INITFIELDS_RE.match(name)
                if not m or m.group(1) not in classes:
                    continue
                fields = classes[m.group(1)]
                body = text[start:end]
                for gm in GETFIELD_RE.finditer(body):
                    var, k = gm.group(1), int(gm.group(3), 0) if gm.group(3) else 0
                    if k >= len(fields):
                        continue
                    etype = fields[k]["type"]
                    # Initializers reuse temporaries for different descriptors.
                    # Only the uses after this lookup and before reassignment
                    # describe the field at index k.
                    uses = body[gm.end():]
                    reassignment = re.search(r"\b%s\s*=(?!=)" % re.escape(var), uses)
                    if reassignment:
                        uses = uses[:reassignment.start()]
                    for mm in member_re.finditer(uses):
                        if mm.group(2) != var:
                            continue
                        cast, member = mm.group(1), mm.group(3)
                        offs = [o for o, e in header.get(cast, {}).items() if e[0] == member]
                        if not offs:
                            continue
                        exp = header.get(etype, {}).get(offs[0])
                        n += 1
                        if not exp or exp[0] != member:
                            bad.append((path, m.group(1), k, fields[k]["name"], cast, member))
        print("checked %d emitted member accesses on GetFieldAt results" % n)
        if bad:
            print("  %d do NOT match the reflection field for their index:" % len(bad))
            for b in bad[:15]:
                print("    %-52s %-24s k=%-3d field=%-22s as %s%s"
                      % (b[0].replace(args.src + "/", ""), b[1], b[2], b[3], b[4], b[5]))
            raise SystemExit(1)
        print("  all consistent with the registration-order field list")
        return
    changed, total = [], 0
    skipped = {}

    def skip(r):
        skipped[r] = skipped.get(r, 0) + 1

    for path in files:
        text = open(path, errors="replace").read()
        if "igMetaObject_GetFieldAt" not in text:
            continue
        fns = split_functions(text)
        edits, classes_here, n_field = [], [], 0
        for name, _sig, start, end in fns:
            m = INITFIELDS_RE.match(name)
            if not m:
                continue
            cls = m.group(1)
            fields = classes.get(cls)
            if not fields:
                skip("no reflection fields for %s" % cls)
                continue
            body = text[start:end]
            for gm in GETFIELD_RE.finditer(body):
                var, k = gm.group(1), int(gm.group(3), 0) if gm.group(3) else 0
                if k >= len(fields):
                    skip("%s field index %d out of range" % (cls, k))
                    continue
                ftype = fields[k]["type"]
                fstruct = header.get(ftype)
                if not fstruct:
                    skip("no reflected struct %s (field %s.%s)"
                         % (ftype, cls, fields[k]["name"]))
                    continue
                cast_re = re.compile(
                    r"\*\(\s*([A-Za-z_][\w \t\*]*?)\s*\*\s*\)\s*\(\s*"
                    r"\(\s*char\s*\*\s*\)\s*\(?\s*%s\s*\)?\s*\+\s*(\d+)\s*\)"
                    % re.escape(var))
                for cm in cast_re.finditer(body):
                    ctype, off = cm.group(1).strip(), int(cm.group(2))
                    f = fstruct.get(off)
                    if not f:
                        skip("no %s field at +%d (field %s.%s)"
                             % (ftype, off, cls, fields[k]["name"]))
                        continue
                    fname, fct, is_arr, owner = f
                    if is_arr:
                        skip("array field %s._%s" % (ftype, fname))
                        continue
                    if TYPE_WIDTH.get(ctype, 4) != TYPE_WIDTH.get(fct, 4):
                        skip("width %s cast vs %s field %s._%s"
                             % (ctype, fct, ftype, fname))
                        continue
                    a, b = cm.span()
                    # cast to the struct that *declares* the field: a subclass's generated
                    # struct does not restate its base's fields (`igObjectRefMetaField`
                    # is `_pad0[56]` then `_metaObject`), so `_construct` must be reached
                    # through `igRefMetaField *`
                    repl = "((%s *)%s)->%s" % (owner, var, fname)
                    edits.append(((start + a, start + b), repl))
                    n_field += 1
            if n_field:
                classes_here.append(cls)
        if not edits:
            continue
        new = text
        for (a, b), repl in sorted(edits, key=lambda e: -e[0][0]):
            new = new[:a] + repl + new[b:]
        if "#include \"dw4/reflected.h\"" not in new:
            if INCLUDE_ANCHOR.search(new):
                new = INCLUDE_ANCHOR.sub(lambda mm: "*/\n#include \"dw4/reflected.h\"\n",
                                         new, count=1)
            else:
                new = "#include \"dw4/reflected.h\"\n" + new
        changed.append((path, sorted(set(classes_here))[0], n_field))
        total += n_field
        if args.apply:
            open(path, "w").write(new)

    print("files rewritten: %d (%s)" % (len(changed), "applied" if args.apply else "dry run"))
    print("field accesses converted: %d" % total)
    for path, cls, n in changed[:15]:
        print("    %-56s %-28s %d" % (path.replace(args.src + "/", ""), cls, n))
    if len(changed) > 15:
        print("    ... and %d more files" % (len(changed) - 15))
    if skipped:
        print("accesses left raw:")
        for r, n in sorted(skipped.items(), key=lambda kv: -kv[1])[:10]:
            print("    %-62s %d" % (r, n))


if __name__ == "__main__":
    main()
