#!/usr/bin/env python3
"""check_regions.py — test config/SLUS-20836/regions.tsv against the retail image.

Fails when the rows stop tiling the image, an anchor is not at its row's start, a library latch
or its registrars leave their row, or a function's saved registers disagree with its row's build:
GCC saves s registers with `sd`, MWCC with `sq`, and MWCC starts every function on 16 bytes.

  python3 tools/check_regions.py
"""
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import regions  # noqa: E402

VADDR_BASE, FILE_BASE = 0x100000, 0x80
IMAGE_END = 0x554B00
SAVED = set(range(16, 24)) | {30}
PROLOGUE_BYTES = 128
SD, SQ, JAL = 0x3F, 0x1F, 0x03
SP = 29
HAND_WRITTEN = {
    0x100008: "startup assembly",
    0x100228: "startup assembly",
    0x12A1E8: "tuned string routine",
    0x1EBA74: "debug-register setup",
}
ELF = os.environ.get("DW4_ELF", os.path.join(regions.ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
SYMBOLS = os.path.join(regions.ROOT, "config", "SLUS-20836", "symbols.txt")


def load_symbols(path=SYMBOLS):
    out = []
    for line in open(path):
        m = re.match(r"([0-9a-f]{8}) ([0-9a-f]+) (\S+)", line)
        if m:
            out.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
    return sorted(out)


def check_tiling(rows):
    errors = []
    if rows[0].lo != VADDR_BASE or rows[-1].hi != IMAGE_END:
        errors.append("rows cover 0x%x-0x%x, not the image" % (rows[0].lo, rows[-1].hi))
    for a, b in zip(rows, rows[1:]):
        if a.hi != b.lo:
            errors.append("%s ends at 0x%x but %s starts at 0x%x" % (a.id, a.hi, b.id, b.lo))
    return errors


def check_anchors(rows, symbols):
    where = {name: va for va, _size, name in symbols}
    return ["%s: anchor %s is at 0x%x, not 0x%x" % (r.id, r.anchor, where.get(r.anchor, 0), r.lo)
            for r in rows if r.anchor != "-" and where.get(r.anchor) != r.lo]


def saves(word, va, size):
    """(sd, sq) counts of s-register saves in a function's prologue."""
    sd = sq = 0
    for a in range(va, min(va + size, va + PROLOGUE_BYTES), 4):
        ins = word(a)
        op, base, reg = ins >> 26, (ins >> 21) & 31, (ins >> 16) & 31
        if base == SP and reg in SAVED:
            sd += op == SD
            sq += op == SQ
    return sd, sq


def check_build(rows, symbols, word, path=regions.DEFAULT_PATH):
    errors = []
    for va, size, name in symbols:
        if va in HAND_WRITTEN:
            continue
        r = regions.of(va, path)
        sd, sq = saves(word, va, size)
        if r.build == "data":
            errors.append("%s: function %s at 0x%x" % (r.id, name, va))
        elif r.build == "gcc" and sq:
            errors.append("%s: %s at 0x%x saves with sq" % (r.id, name, va))
        elif r.build == "mwcc" and (va % 16 or (sd and not sq)):
            errors.append("%s: %s at 0x%x has a GCC start or prologue" % (r.id, name, va))
    return errors


def check_latches(symbols, word, path=regions.DEFAULT_PATH):
    """A library's latch and everything that calls it share one row."""
    latches = {va: name for va, _size, name in symbols if name.endswith("Library_MarkRegistered")}
    errors = []
    seen = collections.Counter()
    for va, name in latches.items():
        seen[regions.of(va, path).id] += 1
    errors += ["%s holds %d latches" % (rid, n) for rid, n in seen.items() if n > 1]
    for va, size, name in symbols:
        for a in range(va, va + size, 4):
            ins = word(a)
            if ins >> 26 != JAL:
                continue
            target = (ins & 0x3FFFFFF) << 2
            if target in latches and regions.of(target, path) is not regions.of(va, path):
                errors.append("%s at 0x%x calls %s in another row" % (name, va, latches[target]))
    return errors


def main():
    image = open(ELF, "rb").read()

    def word(va):
        return struct.unpack_from("<I", image, va - VADDR_BASE + FILE_BASE)[0]

    rows = regions.load()
    symbols = load_symbols()
    errors = (check_tiling(rows) + check_anchors(rows, symbols)
              + check_build(rows, symbols, word) + check_latches(symbols, word))
    for e in errors:
        print("check_regions: " + e)
    if errors:
        return 1
    print("check_regions: %d rows agree with the image (%d functions)" % (len(rows), len(symbols)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
