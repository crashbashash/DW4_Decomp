#!/usr/bin/env python3
"""format_registrars.py — lay out the class registrars (`<Class>_Register`) for a reader.

Every reflected class has a static-init function that calls `igMetaObject_RegisterClass`
with eleven arguments (docs/engine/reflection-metadata.md, section 1).  The machine draft
puts them on one line with no hint which is which.  This rewrites each standard-shape
registrar with one argument per line, a comment naming its role, and a header saying
which class it registers and which class it derives from (the base registrar's name).
The list in the last argument, a `DAT_<addr>` in the draft, is named
`g_<Class>_callbackList_<addr>` through `config/SLUS-20836/data-names.tsv` (rule `callback-list`).

Only whitespace, comments and that rename change: `make check` verifies the bytes.

  python3 scripts/format_registrars.py            # dry run: how many files would change
  python3 scripts/format_registrars.py --apply
"""
import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCOPE = ("engine", "game", "audio", "menu", "movie", "lua")
CALL = re.compile(r"igMetaObject_RegisterClass\((?P<args>[^;()]+)\);")
ROLES = {0: "abstract", 6: "instance size", 9: "extra callback item", 10: "callback list"}


def rewrite(text, cls, lists):
    m = CALL.search(text)
    if not m:
        return text
    line = text.rfind("\n", 0, m.start()) + 1
    indent = re.match(r"[ \t]*", text[line:]).group(0)
    args = [a.strip() for a in m.group("args").split(",")]
    if len(args) != 11:
        return text
    cb = re.fullmatch(r"DAT_([0-9a-f]{8})", args[10])
    old_list = cb.group(0) if cb else None
    if cb:
        args[10] = "g_%s_callbackList_%s" % (cls, cb.group(1))
        lists[int(cb.group(1), 16)] = args[10]
    rows = []
    for i, a in enumerate(args):
        role = " /* %s */" % ROLES[i] if i in ROLES and a[0].isdigit() else ""
        rows.append("%s    %s%s%s" % (indent, a, "," if i < 10 else "", role))
    call = "igMetaObject_RegisterClass(\n%s\n%s);" % ("\n".join(rows), indent)
    text = text[:m.start()] + call + text[m.end():]
    if old_list:
        text = re.sub(r"\b%s\b" % old_list, args[10], text)
    return text


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    changed, lists = 0, {}
    for mod in SCOPE:
        d = os.path.join(ROOT, "src", mod)
        for f in sorted(os.listdir(d)):
            m = re.fullmatch(r"(\w+)_Register\.(?:c|cpp)", f)
            if not m or "RegisterClass(\n" in open(os.path.join(d, f)).read():
                continue
            path = os.path.join(d, f)
            old = open(path).read()
            new = rewrite(old, m.group(1), lists)
            if new != old:
                changed += 1
                if a.apply:
                    open(path, "w").write(new)
    if a.apply and lists:
        table = os.path.join(ROOT, "config/SLUS-20836/data-names.tsv")
        have = {ln.split("\t")[0] for ln in open(table) if not ln.startswith("#")}
        with open(table, "a") as fh:
            for va, name in sorted(lists.items()):
                if "0x%08x" % va not in have:
                    fh.write("0x%08x\t%s\tcallback-list\n" % (va, name))
    print("%s %d registrars" % ("rewrote" if a.apply else "would rewrite", changed))


if __name__ == "__main__":
    sys.exit(main())
