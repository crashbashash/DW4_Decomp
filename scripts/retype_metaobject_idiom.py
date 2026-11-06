#!/usr/bin/env python3
"""Replace automatch's synthetic `struct G` with the recovered `igMetaObject` type.

`tools/automatch.py` emits a layout with no meaning:

    struct G { char pad[36]; int f; };
    extern struct G *DAT_0055ebc0[4];
    struct G *g = DAT_0055ebc0[0];
    if (!g || !(t = g->f & 4)) FUN_001301c0();
    return DAT_0055ebc0[0];

Every fact needed to say that meaningfully is already recovered:

  * the global is a **reflection class handle**, and what a class handle holds is an
    `igMetaObject *` — that is the reflection system's invariant, established by the
    object-model work (`_vtablePointer`, `_getMetaObjectFunction` and the lazy
    get-or-register accessor all hang off this object);
  * reflection gives the field at +36 a name: `_validity`, an `igIntMetaField`;
  * and this exact accessor is the lazy get-or-register path the repo already described
    (`if (!*handle || flags & 4 == 0) register(); return *handle;`), so
    `_validity & 4` is not a guess.

So the rewritten file says what it does, and that is the first half of typed coverage
(T10). Only files whose shape is *exactly* this are touched: a synthetic struct with one
field, at the offset of a reflected `igMetaObject` field of the same size, reached only
through that pointer, with the handle being a real class handle. Everything else is left
alone and counted.

Usage:
    scripts/retype_metaobject_idiom.py            # report what it would do
    scripts/retype_metaobject_idiom.py --apply    # rewrite; then run `make check`
"""

import argparse
import glob
import json
import os
import re
import sys

SYNTH = re.compile(r"^struct (\w+) \{ char pad\[(\d+)\]; (\w+) (\w+); \};\n", re.M)
INCLUDE_ANCHOR = re.compile(r"(\*/\n)", re.M)
GUESS = re.compile(r"The SHAPE matched; the C types are a.*?integer parameter list may be pointers\)\.", re.S)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--reflection", default="data/reflection.json")
    ap.add_argument("--src", default="src")
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()

    data = json.load(open(args.reflection))
    handles = {int(o["handle"], 16) for o in data["classes"].values()}
    meta = next(o for o in data["classes"].values() if o["class"] == "igMetaObject")
    by_offset = {f["offset"]: f for f in meta["fields"]}

    files = sorted(glob.glob(os.path.join(args.src, "**", "*.c"), recursive=True) +
                   glob.glob(os.path.join(args.src, "**", "*.cpp"), recursive=True))
    changed, converted, skipped = [], 0, {}

    def skip(reason):
        skipped[reason] = skipped.get(reason, 0) + 1

    for path in files:
        text = open(path, errors="replace").read()
        m = SYNTH.search(text)
        if not m:
            continue
        struct, pad, ftype, fname = m.group(1), int(m.group(2)), m.group(3), m.group(4)
        field = by_offset.get(pad)
        if field is None:
            skip("no reflected igMetaObject field at +%d" % pad); continue
        handle = re.search(r"extern struct %s \*DAT_([0-9a-fA-F]{6,8})\[" % struct, text)
        if not handle:
            skip("no `extern struct X *DAT_...[]` declaration"); continue
        if int(handle.group(1), 16) not in handles:
            skip("the global is not a reflection class handle"); continue
        # the field must be used only through that pointer, and only as a scalar of the
        # same width, or the rewrite would be inventing a layout
        bases = set(re.findall(r"\b(\w+)\s*->\s*%s\b" % fname, text))
        decls = set(re.findall(r"struct %s \*(\w+)" % struct, text))
        if not bases or not bases <= decls:
            skip("`->%s` used on a pointer that is not this struct" % fname); continue
        if ftype not in ("int", "unsigned int", "float", "char", "short", "long long"):
            skip("field type %s is not a 4-byte scalar" % ftype); continue
        new = text.replace(m.group(0), "")                      # drop the synthetic layout
        new = new.replace("struct " + struct, "igMetaObject")    # retype every mention
        for b in bases:
            new = re.sub(r"\b%s\s*->\s*%s\b" % (b, fname), "%s->_%s" % (b, field["name"].lstrip("_")), new)
        new = INCLUDE_ANCHOR.sub(lambda m: "*/\n#include \"dw4/reflected.h\"\n", new, count=1)
        new = GUESS.sub("The SHAPE matched; the types come from the recovered\n * reflection metadata (igMetaObject, whose +%d field `%s` this tests)." % (pad, field["name"]), new, count=1)
        converted += len(bases)
        changed.append((path, struct, pad, field["name"], sorted(bases)))
        if args.apply:
            open(path, "w").write(new)

    print("files rewritten: %d (%s)" % (len(changed), "applied" if args.apply else "dry run"))
    print("field accesses converted to recovered members: %d" % converted)
    for path, struct, pad, name, bases in changed[:4]:
        print("    %-58s struct %s(+%d) -> igMetaObject.%s on %s" %
              (path, struct, pad, name, ",".join(bases)))
    if skipped:
        print("files left alone:")
        for reason, n in sorted(skipped.items(), key=lambda kv: -kv[1]):
            print("    %-58s %d" % (reason, n))


if __name__ == "__main__":
    main()
