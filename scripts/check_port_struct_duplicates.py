#!/usr/bin/env python3
"""Fail if the port declares a struct under the name of a class in include/dw4/reflected.h.

include/dw4/reflected.h is the one authoritative layout of the game's objects (generated from
data/reflection.json, plus config/SLUS-20836/authoritative-fields.tsv). The technical specification retargets
recovered code to the host, so the port includes that header; a second definition under the same
name in port/include or port/src would be a duplicate that can drift. Port-native types use the
`dw4_` prefix and are not affected.

Usage: scripts/check_port_struct_duplicates.py   (exit 1 on a duplicate)
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    hdr = open(os.path.join(ROOT, "include", "dw4", "reflected.h"), errors="replace").read()
    classes = set(re.findall(r"typedef struct (\w+) \{", hdr))
    bad = []
    files = (glob.glob(os.path.join(ROOT, "port", "include", "**", "*.h"), recursive=True) +
             glob.glob(os.path.join(ROOT, "port", "src", "**", "*.[ch]"), recursive=True) +
             glob.glob(os.path.join(ROOT, "port", "tools", "*.[ch]")))
    for path in files:
        text = open(path, errors="replace").read()
        names = set(re.findall(r"\bstruct\s+(\w+)\s*\{", text))
        names |= set(re.findall(r"\}\s*(\w+)\s*;", text))
        names |= set(re.findall(r"\btypedef\s+struct\s+\w+\s+(\w+)\s*;", text))
        for n in sorted(names & classes):
            bad.append((os.path.relpath(path, ROOT), n))
    for path, n in bad:
        print("duplicate of a reflected class: %s defines %s" % (path, n))
    if bad:
        return 1
    print("port structs: %d files scanned, none redefines one of the %d reflected classes" % (len(files), len(classes)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
