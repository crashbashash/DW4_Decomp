#!/usr/bin/env python3
"""igb_sections.py — report an igBinary blob's object sections and their counts.

An igBinary blob (one AFS entry, or a standalone `.igb`) carries **two** object
sections, and the blob header states both counts:

    hdr[1]  the first object section's record count
    hdr[5]  the second object section's record count

They are not "the object count" and "a small side section": both are real object
chains, and the loader's object reader (`FUN_002e7390`, which loops `ctx+0x70` set
from header word 1 by `FUN_002e6090`) reads the **`hdr[1]`** one.  On NDMW.AFS:

    entry 622 (stag0102 generators)   50 + 1206
    entry 183                          33 + 266
    entry 621 (stag0102 models)     1122 + 38135
    entry 140 (beFileListInfo)         6 + 5

so a pack's id window spans both sections, in file order.

Usage:
    igb_sections.py NDMW.AFS --blob 0x21307000
    igb_sections.py NDMW.IGB --blob 0
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import igb_inst  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file")
    ap.add_argument("--blob", required=True, help="file offset of the blob")
    ap.add_argument("--reflection",
                    default=os.path.join(HERE, "..", "data", "reflection.json"))
    a = ap.parse_args()

    lo = int(a.blob, 0)
    data = open(a.file, "rb").read()
    size, where = igb_inst.blob_extent(data, lo)
    if size is None:
        size, where = len(data) - lo, "to end of file"
    b = data[lo:lo + size]
    hdr = struct.unpack_from("<12I", b, 0)

    reflection = igb_inst.load_reflection(a.reflection)
    dirs, _ = igb_inst.parse_directory(b)
    chains = [c for c in igb_inst.find_chains(b, dirs, reflection) if len(c) > 1]
    chains.sort(key=lambda c: c[0]["off"])

    print("blob 0x%08x  %d bytes (%s)" % (lo, len(b), where))
    print("hdr[1]=%d  hdr[5]=%d  (class count hdr[3]=%d)"
          % (hdr[1], hdr[5], hdr[3]))
    got = [len(c) for c in chains]
    print("object chains in file order: %s" % [(hex(c[0]["off"]), len(c)) for c in chains])
    if sorted(got) == sorted([hdr[1], hdr[5]]) and hdr[1] and hdr[5]:
        print("OK: hdr[1]/hdr[5] equal the two chain lengths")
    else:
        print("WARN: header counts %s != chain lengths %s" % ([hdr[1], hdr[5]], got))
    for c in chains:
        counts = {}
        for r in c:
            counts[r["class"]] = counts.get(r["class"], 0) + 1
        top = sorted(counts.items(), key=lambda kv: -kv[1])[:5]
        print("  chain +0x%06x  %5d records  %s"
              % (c[0]["off"], len(c), ", ".join("%s %d" % kv for kv in top)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
