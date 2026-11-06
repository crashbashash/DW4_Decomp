#!/usr/bin/env python3
"""Retype a matched function's receiver from the recovered reflection metadata.

The first batch of typed coverage rewrote automatch's synthetic `struct G`
into `igMetaObject` in 550 files.  This is the second, and it is the general form of it:
a matched function is named `<Class>_<Method>` (or a sanitised `Gap__Bec__<Class>__vfunc_N`
or `thunk_...`), its first argument is the receiver, and `data/reflection.json` already
names every field of `<Class>` with an offset.  So

    int igMetaField_Write(void *arg0) {
        return -(*(unsigned char *)((char *)(arg0) + 38) == 0);
    }

becomes

    #include "dw4/reflected.h"
    int igMetaField_Write(igMetaField *arg0) {
        return -(arg0->_persistent == 0);
    }

Rules that keep it honest (all enforced, everything else left alone and counted):

  * the receiver class comes from the **function's name**, never inferred from the body;
  * the field comes from `reflection.json` and its **width must equal the cast's width** —
    a `char` field accessed with a 4-byte cast is left raw, because rewriting it would
    change codegen and `make check` would (correctly) fail;
  * only **scalar** fields are rewritten (an array field's access width is not the
    element width in general);
  * the base must be the receiver (`arg0` / `this`), never a temporary — a temporary
    often holds a *different* object (an `_InitFields` body's `temp_s2` is the field
    object returned by `igMetaObject_GetFieldAt`, not the class the function is named for).

Usage:
    scripts/retype_receiver_class.py            # report
    scripts/retype_receiver_class.py --apply    # rewrite; then `make check` + `make link`
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
CAST_RE = re.compile(r"\*\(\s*([A-Za-z_][\w \t\*]*?)\s*\*\s*\)\s*\(\s*"
                     r"\(\s*char\s*\*\s*\)\s*\(?\s*(arg0|this)\s*\)?\s*\+\s*(\d+)\s*\)")


def load_header(path):
    """{class: {offset: (field_name, ctype, is_array)}} from the generated header.

    The offset is the one the generator printed in the field's trailing comment
    (`/* +38 igBoolMetaField */`) -- reflection's offset, the authority -- not a running
    total, which drifts as soon as a field needs alignment padding.
    """
    text = open(path, errors="replace").read()
    out = {}
    for m in STRUCT_RE.finditer(text):
        cls, body = m.group(1), m.group(2)
        fields = {}
        for fm in FIELD_RE.finditer(body):
            name, arr, off = fm.group(3), fm.group(4), int(fm.group(5))
            if re.match(r"_pad\d+$", name):
                continue
            fields[off] = (name, fm.group(1).strip(), bool(arr))
        out[cls] = fields
    return out


def receiver_class(name):
    """The class a function name implies for its receiver, or None."""
    name = re.sub(r"^thunk_", "", name)
    m = re.match(r"^(.+?)__(?:vfunc|ctor|dtor|InitFields)?_?\d*$", name)
    if m and any(p and p[0].isupper() for p in m.group(1).split("__")):
        return m.group(1).split("__")[-1]
    m = re.match(r"^(.+?)::(?:vfunc|ctor|dtor)", name)
    if m:
        return m.group(1).split("::")[-1]
    if "_" not in name:
        return None
    return name.rsplit("_", 1)[0]


def load_overlay(path):
    """{function name: class} from config/SLUS-20836/receiver-classes.tsv (an unnamed function's receiver
    class, recovered by scripts/seed_receiver_classes.py; a type only, never a method name)."""
    out = {}
    if os.path.exists(path):
        for ln in open(path):
            if ln.startswith("#") or not ln.strip():
                continue
            va, cls = ln.split("\t")[:2]
            out["FUN_%08x" % int(va, 16)] = cls
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--header", default="include/dw4/reflected.h")
    ap.add_argument("--src", default="src")
    ap.add_argument("--overlay", default="config/SLUS-20836/receiver-classes.tsv")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--class-regex", default=None,
                    help="only retype receivers whose class matches this regex (e.g. 'be' for the "
                         "game classes; the engine `ig*` set is the port plan's out-of-scope "
                         "middleware)")
    args = ap.parse_args()

    header = load_header(args.header)
    overlay = load_overlay(args.overlay)
    files = sorted(glob.glob(os.path.join(args.src, "**", "*.c"), recursive=True) +
                   glob.glob(os.path.join(args.src, "**", "*.cpp"), recursive=True))
    changed, total = [], 0
    skipped = {}

    def skip(r):
        skipped[r] = skipped.get(r, 0) + 1

    for path in files:
        text = open(path, errors="replace").read()
        # per function, never per file: a folded translation unit holds several functions
        # whose `arg0` may be different classes
        fns = split_functions(text)
        hits = []          # (span, replacement) in the ORIGINAL text
        classes_here = []
        n_field = 0
        for name, _sig, start, end in fns:
            cls = overlay.get(re.sub(r"^thunk_", "", name)) or receiver_class(name)
            if cls not in header:
                continue
            if args.class_regex and not re.match(args.class_regex, cls):
                continue
            fields = header[cls]
            body = text[start:end]
            fn_hits = []
            for cm in CAST_RE.finditer(body):
                ctype, base, off = cm.group(1).strip(), cm.group(2), int(cm.group(3))
                f = fields.get(off)
                if not f:
                    skip("no reflected %s field at +%d" % (cls, off))
                    continue
                fname, ftype, is_arr = f
                if is_arr:
                    skip("array field %s._%s" % (cls, fname))
                    continue
                if TYPE_WIDTH.get(ctype, 4) != TYPE_WIDTH.get(ftype, 4):
                    skip("width %s cast vs %s field %s._%s" % (ctype, ftype, cls, fname))
                    continue
                a, b = cm.span()
                fn_hits.append(((start + a, start + b), "%s->%s" % (base, fname)))
                n_field += 1
            if not fn_hits:
                continue
            uses_arg0 = any(r.startswith("arg0->") for _, r in fn_hits)
            declares_cls = re.search(r"\b%s\s*\*\s*arg0\b" % re.escape(cls), text[start:end])
            sm = re.search(r"void\s*\*\s*arg0\b", text[start:end])
            if uses_arg0 and not sm and not declares_cls:
                # the receiver is `arg0` but it is declared as some *other* pointer type,
                # so a member access on it would be wrong.  A receiver already declared
                # `<Class> *arg0` needs no rewrite and is fine to convert.
                skip("receiver of %s is not a `void *arg0`" % name)
                continue
            hits.extend(fn_hits)
            classes_here.append(cls)
        if not hits:
            continue
        if len(set(classes_here)) != 1:
            skip("mixed receiver classes in one file (%s)" % ",".join(sorted(set(classes_here))))
            continue
        cls = classes_here[0]
        # a .cpp unit may carry an `extern "C" { ... }` forward declaration as well as the
        # definition; retype every `void *arg0` in the file so the two agree
        for sm in re.finditer(r"void\s*\*\s*arg0\b", text):
            hits.append((sm.span(), "%s *arg0" % cls))
        new = text
        for (a, b), repl in sorted(hits, key=lambda h: -h[0][0]):
            new = new[:a] + repl + new[b:]
        if "#include \"dw4/reflected.h\"" not in new:
            if INCLUDE_ANCHOR.search(new):
                new = INCLUDE_ANCHOR.sub(lambda mm: "*/\n#include \"dw4/reflected.h\"\n",
                                         new, count=1)
            else:
                new = "#include \"dw4/reflected.h\"\n" + new
        changed.append((path, classes_here[0], n_field, sorted({r for _, r in hits if "->" in r})))
        total += n_field
        if args.apply:
            open(path, "w").write(new)

    print("files rewritten: %d (%s)" % (len(changed), "applied" if args.apply else "dry run"))
    print("field accesses converted to recovered members: %d" % total)
    for path, cls, n, repls in changed:
        print("    %-58s %-32s %d access(es): %s"
              % (path.replace(args.src + "/", ""), cls, n,
                 ", ".join(sorted(set(repls)))))
    if skipped:
        print("accesses left raw:")
        for r, n in sorted(skipped.items(), key=lambda kv: -kv[1])[:12]:
            print("    %-58s %d" % (r, n))


if __name__ == "__main__":
    main()
