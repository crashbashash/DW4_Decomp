#!/usr/bin/env python3
"""data_layout.py — what the retail image says about its data, for tools/datamap.py.

Writes data/data-layout.tsv: facts read from the retail executable that datamap needs and cannot read
itself (it runs from committed files only). One row per fact, `va size kind`:

  ref     a datum starts here: retail code forms the address (a `lui` with the `addiu`, `ori`, load or
          store that completes it, or a `gp`-relative access). Size 0: a reference gives a start, not an
          extent
  ptr     a datum starts here by a pointer word in the data alone (word-aligned, or the start of a
          known string); no code forms the address. Size 0
  table   a run of two or more words, each the start of a function, of a string of data/strings.json or
          of a referenced datum, with at most one zero word ending it: a pointer table (callback lists,
          constructor and field tables, string tables)
  vtable  a header `[0 or a data pointer, 0]` followed by two or more function starts: the layout of
          an MWCC vtable, RTTI or not
  zeros   the zero bytes (at most 15) right before an 8-aligned datum start: a start a reference names,
          or an address whose first byte is not zero. datamap calls the gap padding when a datum of known
          size ends inside it: the retail linker raises every datum's start to `max(its alignment, 8)`
          (4 in `.sbss`), and MWCC aligns 16 at most (docs/engine/emitted-functions.md, "A unit's own data")

The zero-initialised tail past the file image is all zeros, so datamap needs no facts there. Regenerate
after the symbol map or the string dump changes (scripts/sync_data.sh does):

  python3 scripts/data_layout.py
"""
import json
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import datamap  # noqa: E402  (the region table and the sized kinds)
import verify  # noqa: E402

ELF = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
OUT = os.path.join(ROOT, "data", "data-layout.tsv")
DATA_LO = datamap.REGIONS[0][0]                 # first data byte the regions table types
FILE_HI = 0x554B00                              # end of the file image
LOADS_STORES = {0x1A, 0x1B, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
                0x2B, 0x2C, 0x2D, 0x2E, 0x31, 0x37, 0x39, 0x3F}
STORES = {0x1F, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x39, 0x3F}
WINDOW = 64                                     # instructions a `lui` value is followed for


def sext(value):
    return value - 0x10000 if value & 0x8000 else value


def destination(word):
    """The general register an instruction writes, or None."""
    op = word >> 26
    if op == 0x00:
        return (word >> 11) & 31
    if op == 0x03:
        return 31
    if op in (0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17) or op in STORES:
        return None
    return (word >> 16) & 31


def code_references(image, functions, gp):
    """Data addresses retail code forms: `lui` + completing instruction, and `gp`-relative accesses."""
    out = set()
    for start, size in functions:
        words = [struct.unpack_from("<I", image, start - 0x100000 + 0x80 + i)[0] for i in range(0, size, 4)]
        for i, word in enumerate(words):
            op, rs, rt, imm = word >> 26, (word >> 21) & 31, (word >> 16) & 31, word & 0xFFFF
            if rs == 28 and (op in LOADS_STORES or op == 0x09):
                out.add((gp + sext(imm)) & 0xFFFFFFFF)
            if op != 0x0F:
                continue
            for later in words[i + 1:i + 1 + WINDOW]:
                lop, lrs, limm = later >> 26, (later >> 21) & 31, later & 0xFFFF
                if lrs == rt and (lop in (0x09, 0x0D) or lop in LOADS_STORES):
                    out.add(((imm << 16) + (limm if lop == 0x0D else sext(limm))) & 0xFFFFFFFF)
                if destination(later) == rt:
                    break
    return {a for a in out if DATA_LO <= a < datamap.IMG_HI}


def main():
    image = open(ELF, "rb").read()
    gp = verify.reginfo_gp(ELF)
    functions = []
    for line in open(os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")):
        if not line.startswith("#") and line.strip():
            p = line.split()
            functions.append((int(p[0], 16), int(p[1], 16)))
    function_starts = {va for va, _ in functions}
    strings = {}
    for s in json.load(open(datamap.STRINGS))["strings"]:
        a = int(s["address"], 16)
        if DATA_LO <= a < datamap.IMG_HI:
            strings[a] = s["length"] + 1

    def word(va):
        return struct.unpack_from("<I", image, va - 0x100000 + 0x80)[0]

    code_refs = code_references(image, functions, gp)
    # pointer words in the data: a target in the data, word-aligned or the start of a known string
    pointed = set()
    for va in range(DATA_LO, FILE_HI, 4):
        target = word(va)
        if DATA_LO <= target < datamap.IMG_HI and (target % 4 == 0 or target in strings):
            pointed.add(target)
    refs = code_refs | pointed
    known_starts = refs | set(strings)

    # pointer tables and vtables
    rows = []
    va = DATA_LO
    while va < FILE_HI:
        target = word(va)
        if target in function_starts or target in known_starts:
            end = va
            while end < FILE_HI and (word(end) in function_starts or word(end) in known_starts):
                end += 4
            count = (end - va) // 4
            if end < FILE_HI and word(end) == 0:
                end += 4
            if count >= 2:
                functions_only = all(word(a) in function_starts for a in range(va, va + count * 4, 4))
                head = va - 8
                if (functions_only and head >= DATA_LO and word(head + 4) == 0
                        and (word(head) == 0 or DATA_LO <= word(head) < datamap.IMG_HI)):
                    rows.append((head, va + count * 4 - head, "vtable"))
                else:
                    rows.append((va, end - va, "table"))
            va = max(end, va + 4)
        else:
            va += 4

    # zero gaps before datum starts: an 8-aligned address that a reference names or whose first byte is
    # not zero, and the zero bytes (at most 15) right before it; datamap calls such a gap padding when a
    # datum of known size ends inside it. Functions are aligned the same way, so a function start counts
    # too: the gap after the previous function is its padding
    candidates = [s for s in range(DATA_LO + 8, FILE_HI, 8)
                  if image[s - 0x100000 + 0x80] != 0 or s in known_starts]
    candidates += sorted(s for s in function_starts if s % 8 == 0 and s > 0x100000)
    for start in candidates:
        length = 0
        while length < 15 and image[start - 1 - length - 0x100000 + 0x80] == 0:
            length += 1
        if length:
            rows.append((start - length, length, "zeros"))

    rows += [(a, 0, "ref") for a in code_refs]
    rows += [(a, 0, "ptr") for a in pointed - code_refs]
    text = ("# va\tsize\tkind — GENERATED by scripts/data_layout.py from the retail executable; do not edit. "
            "Read by tools/datamap.py.\n" + "".join("%08x\t%d\t%s\n" % row for row in sorted(set(rows))))
    if "--check" in sys.argv[1:]:
        current = open(OUT).read() if os.path.exists(OUT) else ""
        if current != text:
            print("data_layout: %s is stale; run python3 scripts/data_layout.py" % os.path.relpath(OUT, ROOT))
            return 1
        print("data_layout: %s is current" % os.path.relpath(OUT, ROOT))
        return 0
    with open(OUT, "w") as fh:
        fh.write(text)
    counts = {}
    for _a, n, kind in set(rows):
        counts[kind] = counts.get(kind, 0) + (n or 1)
    print("data_layout: %s -> %s" % (", ".join("%s %d" % kv for kv in sorted(counts.items())),
                                     os.path.relpath(OUT, ROOT)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
