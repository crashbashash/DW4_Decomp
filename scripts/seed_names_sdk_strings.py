#!/usr/bin/env python3
"""Seed SDK function names from the strings those functions reference.

The PS2 SDK reports errors as `sceXxx: ...` from inside `sceXxx`, so a function whose
only string is *its own name* in an error path is that function.  This recovers names
that no symbol table can supply -- the image ships an empty `.symtab` -- and it is the
only naming source for the statically linked SDK that is evidence rather than shape.

Method: read `data/strings.json`, keep the strings that open with an `sceXxx` identifier
or that name one in an error message, then find the functions that materialise those
strings' addresses.  A string address is formed as `lui rt, hi` + `addiu`/`ori rt, rt,
lo`, tracked for a few instructions and stopped by anything that writes `rt`.

Writes `config/SLUS-20836/names/Sdk.tsv` (`<va>\t<name>\tmodule`), which `tools/split.py --names`
merges over the Ghidra dump.  Also prints the strings that name a *library* (`libpad:`,
`*.irx`) without naming a function -- those attribute a function to an SDK library but
are not a name, so they are reported rather than written.

Usage:  seed_names_sdk_strings.py [--out config/SLUS-20836/names/Sdk.tsv] [--report]
"""

import argparse
import bisect
import collections
import json
import re
import struct
import sys

sys.path.insert(0, "tools")

sys.path.insert(0, "tools")
from mips_literals import make_word, scan_from_lui

VADDR_BASE, FILE_BASE = 0x100000, 0x80
# "<name>:" / "<name> is" / "<name> RPC" -- the SDK's own error-reporting shapes.
SELF_NAME = re.compile(r"^\s*(sce[A-Z]\w+)(?::|\s+(?:is|was|RPC|error|faild|failed))")
LIBRARY = re.compile(r"^\s*lib(\w+)\s*:|(\w+)\.irx\b")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--elf", default="orig/SLUS-20836/SLUS_208.36")
    ap.add_argument("--strings", default="data/strings.json")
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--out", default="config/SLUS-20836/names/Sdk.tsv")
    ap.add_argument("--report", action="store_true")
    args = ap.parse_args()

    img = open(args.elf, "rb").read()
    word = make_word(img)

    syms = []
    for ln in open(args.symbols):
        if ln.startswith("#"):
            continue
        p = ln.split()
        if len(p) >= 3:
            syms.append((int(p[0], 16), int(p[1], 16), p[2]))
    syms.sort()
    starts = [s[0] for s in syms]

    def owner(va):
        i = bisect.bisect_right(starts, va) - 1
        return syms[i] if i >= 0 and syms[i][0] <= va < syms[i][0] + syms[i][1] else None

    strings, selfnames, libs = {}, {}, {}
    for s in json.load(open(args.strings))["strings"]:
        v = s.get("value")
        if not isinstance(v, str) or not v:
            continue
        a = int(s["address"], 16)
        strings[a] = v
        m = SELF_NAME.match(v)
        if m:
            selfnames[a] = m.group(1)
        else:
            m2 = LIBRARY.search(v)
            if m2:
                libs[a] = "lib" + m2.group(1) if m2.group(1) else m2.group(2)

    # Which function materialises which string address?
    refs = collections.defaultdict(set)
    for va in range(0x100000, 0x554B00 - 4, 4):
        ins = word(va)
        if ins is None or (ins >> 26) != 0x0F:
            continue
        hi, rt = ins & 0xFFFF, (ins >> 16) & 0x1F
        for kind, a in scan_from_lui(word, va, hi, rt):
            if kind == "exact" and a in strings:
                o = owner(va)
                if o:
                    refs[o[0]].add(a)

    found, lib_only = {}, {}
    for fn, addrs in refs.items():
        named = [(a, selfnames[a]) for a in addrs if a in selfnames]
        if named:
            # A function that names several SDK functions keeps the first -- that is
            # the one whose error path it is reporting from.
            found[fn] = sorted(named)[0][1]
        else:
            libbed = sorted({libs[a] for a in addrs if a in libs})
            if libbed:
                lib_only[fn] = libbed

    with open(args.out, "w") as fh:
        fh.write("# SDK functions whose own name appears in a string they reference -- the PS2 SDK\n"
                 "# convention is to report errors as \"sceXxx: ...\", so a function whose only string\n"
                 "# is its own name in an error path *is* that function. Recovered by\n"
                 "# scripts/seed_names_sdk_strings.py; see docs/engine/platform-boundary.md.\n")
        for fn, name in sorted(found.items()):
            fh.write("0x%08x\t%s\tsdk\n" % (fn, name))
    print("wrote %s: %d named functions" % (args.out, len(found)))

    if args.report:
        print("\nfunctions attributed to an SDK *library* (not a name -- findings only):")
        for fn, bl in sorted(lib_only.items()):
            print("    0x%08x  %-24s %s" % (fn, owner(fn)[2], ",".join(bl)))


if __name__ == "__main__":
    main()
