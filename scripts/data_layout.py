#!/usr/bin/env python3
"""data_layout.py — what the retail image says about its data, for tools/datamap.py.

Writes data/data-layout.tsv: facts read from the retail executable that datamap needs and cannot read
itself (it runs from committed files only). One row per fact, `va size kind`:

  ref     a datum starts here: retail code forms the address (a `lui` with the `addiu`, `ori`, load or
          store that completes it, or a `gp`-relative access). Size 0: a reference gives a start, not an
          extent
  ptr     a datum starts here by a pointer word in the data alone (word-aligned, or the start of a
          known string); no code forms the address, and the word is not inside a known string. Size 0
  table   outside the vtable section: a run of two or more words, each the start of a function, of a
          string of data/strings.json or of a referenced datum, that no other known start interrupts;
          zero words inside it are null members; it ends at its last pointer. Or an array of records of
          two to four words, each led by a function, a string, a code-formed address or an RTTI record and
          holding no other pointer (RTTI base lists, name and value pairs). Pointer-bearing records, a
          vtable-like table's null slots included (callback lists, constructor and field tables, string
          tables, CRI device interfaces)
  vtable  in the vtable section, from after the static-initializer table to the exception metadata (MWCC
          compiles only vtables into it): from a recorded vtable (data/vtables.json,
          data/vtables-getvtable.json), an 8-aligned header `[0 or a data pointer, 0]` code forms or a
          pointer names, or a 16-aligned such header followed by two function starts, to its last non-zero
          word before the next, or up to the next when 16 or more zero bytes remain: a pure virtual
          function's slot is zero
  str     a string data/strings.json leaves out: ASCII or Shift-JIS text to a zero byte at an address a
          table holds, in `.data` or `.rodata`
  zeros   a run of zero bytes: in the data every run that reaches a multiple of 4, in the code the run
          (at most 255 bytes) right before each function and regions.tsv row. datamap calls the part after
          a datum of known size padding when the next datum starts aligned and fewer than 16 bytes on: the
          retail linker raises every datum's start to `max(its alignment, 8)` (4 in `.sdata` and `.sbss`,
          and inside a GCC unit's block), MWCC aligns 16 at most (docs/engine/emitted-functions.md, "A
          unit's own data"), and before a function the assembler's `.align` pads to its alignment

The zero-initialised tail past the file image is all zeros, so datamap needs no facts there. Regenerate
after the symbol map, the string dump, the vtable dumps, config/SLUS-20836/exceptions.txt or
config/SLUS-20836/regions.tsv change (scripts/sync_data.sh does):

  python3 scripts/data_layout.py
"""
import json
import os
import re
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
    # pointer words in the data: a target in the data, word-aligned or the start of a known string; a word
    # inside a known string is text, not a pointer
    text = bytearray(FILE_HI - DATA_LO)
    for a, length in strings.items():
        if a < FILE_HI:
            text[a - DATA_LO:min(a + length, FILE_HI) - DATA_LO] = b"\1" * (min(a + length, FILE_HI) - a)
    pointed = set()
    for va in range(DATA_LO, FILE_HI, 4):
        target = word(va)
        if (DATA_LO <= target < datamap.IMG_HI and (target % 4 == 0 or target in strings)
                and not any(text[va - DATA_LO:va + 4 - DATA_LO])):
            pointed.add(target)
    refs = code_refs | pointed
    known_starts = refs | set(strings)

    # The vtable section: MWCC compiles vtables, and only vtables, into it (docs/engine/build-profiles.md),
    # from after the static-initializer table to the exception metadata that follows them
    # (config/SLUS-20836/exceptions.txt). A vtable starts at a recorded one (data/vtables.json,
    # data/vtables-getvtable.json), at an 8-aligned header `[0 or a data pointer, 0]` code forms or a pointer
    # names, or at a 16-aligned header followed by two function starts: every recorded vtable is 16-aligned
    # (a datum of 16 bytes or more is, under MWCC). It runs to its last non-zero word before the next start,
    # or over the zeros up to that start when they are 16 bytes or more: a pure virtual function's slot is
    # zero, and padding before an aligned start is shorter.
    vtables_lo = datamap.STATIC_INITIALIZERS[1]
    vtables_hi = min(lo for lo, _hi, kind in datamap.fixed_intervals() if kind == "exc" and lo >= vtables_lo)

    def header(va):
        return word(va + 4) == 0 and (word(va) == 0 or DATA_LO <= word(va) < datamap.IMG_HI)
    vtable_starts = {int(a, 16) for a in json.load(open(datamap.VTABLES))["vtables"]}
    vtable_starts |= {int(a, 16) for a in json.load(open(datamap.GETVTABLES))}
    vtable_starts |= {a for a in refs if a % 8 == 0 and vtables_lo <= a < vtables_hi and header(a)}
    vtable_starts |= {a for a in range(vtables_lo, vtables_hi, 16)
                      if header(a) and word(a + 8) in function_starts and word(a + 12) in function_starts}
    vtable_starts = sorted(a for a in vtable_starts if vtables_lo <= a < vtables_hi) + [vtables_hi]
    rows = []
    for start, following in zip(vtable_starts, vtable_starts[1:]):
        end = following
        while end > start + 8 and word(end - 4) == 0:
            end -= 4
        if following - end >= 16:
            end = following
        rows.append((start, end - start, "vtable"))

    # pointer tables elsewhere: a run of pointer words that no known start interrupts (an address code
    # forms or a pointer names begins another datum); zero words inside it are null members when a pointer
    # word follows them. An array of records of two to four words is a table too when each record is led by
    # a word naming a function, a string, an address code forms or an RTTI record (what a vtable header
    # holds, or a pointed `{name string, 0 or base list}` pair in `.rodata`), and holds no other pointer
    # (RTTI base lists, name and value pairs); it is read as records when they reach further than the plain
    # run. A single record led by an RTTI record is a table when a pointer or code names it and an all-zero
    # record follows: a base list with one base. A zero word after the last pointer is left to the padding
    # rule: where a fully matched unit defines a table that one follows, its datum ends before the zero 863
    # times and takes it in 225. The regions.tsv rows say what they hold, and are not searched
    def pointer(va):
        return word(va) in function_starts or word(va) in known_starts
    type_infos = {word(s) for s in vtable_starts[:-1] if word(s)}
    rodata = next(s for s, name in datamap.REGIONS if name == ".rodata")
    type_infos |= {a for a in pointed if rodata <= a < vtables_lo and word(a) in strings
                   and (word(a + 4) == 0 or word(a + 4) in pointed)}
    record_leads = function_starts | set(strings) | code_refs | type_infos

    def records(va, limit, stride):
        """(end of the last pointer-led record, pointer records) of a run of `stride`-word records from `va`"""
        if stride == 1:
            end, count, probe = va + 4, 1, va + 4
            while probe < limit and probe not in known_starts:
                if pointer(probe):
                    count, end = count + 1, probe + 4
                elif word(probe) != 0:
                    break
                probe += 4
            return end, count
        end, count = va, 0
        while (end + 4 * stride <= limit and word(end) in record_leads and (end == va or end not in known_starts)
               and not any(a in known_starts or pointer(a) for a in range(end + 4, end + 4 * stride, 4))):
            count, end = count + 1, end + 4 * stride
        return end, count
    regions = [(lo, hi) for lo, hi, kind in datamap.fixed_intervals() if kind == "region"]
    skipped = [(vtables_lo, vtables_hi)] + regions
    section_ends = sorted({s for s, _n in datamap.REGIONS} | {lo for lo, _hi in skipped} | {FILE_HI})
    va = DATA_LO
    while va < FILE_HI:
        inside = [hi for lo, hi in skipped if lo <= va < hi]
        if inside:
            va = inside[0]
            continue
        if not pointer(va):
            va += 4
            continue
        limit = next(s for s in section_ends if s > va)
        end, count = records(va, limit, 1)
        table = count >= 2
        for stride in (2, 3, 4):
            wider_end, wider_count = records(va, limit, stride)
            closed = (wider_count == 1 and stride == 2 and word(va) in type_infos and va in refs
                      and wider_end + 8 <= limit
                      and all(word(a) == 0 and a not in known_starts for a in range(wider_end, wider_end + 8, 4)))
            if (wider_count >= 2 or closed) and wider_end > end:
                end, table = wider_end, True
        if table:
            rows.append((va, end - va, "table"))
        va = max(end, va + 4)

    # strings data/strings.json leaves out (it skips short ones): text, ASCII or Shift-JIS, ending at a zero
    # byte, in `.data` or `.rodata` at an address a pointer table holds (string tables, name fields of
    # records), unless its first word is itself a word-aligned image address (a pointer whose bytes print)
    def byte(va):
        return image[va - 0x100000 + 0x80]

    def text_length(va):
        """Bytes of ASCII or Shift-JIS text from `va` to a zero byte, or 0 when anything else comes first."""
        end = va
        while end < FILE_HI and byte(end):
            c, trail = byte(end), byte(end + 1)
            if 0x20 <= c < 0x7F or c in (9, 10, 13):
                end += 1
            elif (0x81 <= c < 0xA0 or 0xE0 <= c < 0xFD) and 0x40 <= trail < 0xFD and trail != 0x7F:
                end += 2
            else:
                return 0
        return end - va if end < FILE_HI else 0
    tabled = {word(a) for va, size, kind in rows if kind == "table" for a in range(va, va + size, 4)}
    for target in sorted(tabled - set(strings)):
        if not DATA_LO <= target < vtables_lo or text[target - DATA_LO]:
            continue
        if target % 4 == 0 and datamap.IMG_LO <= word(target) < datamap.IMG_HI and word(target) % 4 == 0:
            continue
        length = text_length(target)
        if length:
            rows.append((target, length + 1, "str"))

    # zero runs: in the data, every run of zero bytes that reaches a multiple of 4 (where a datum can start);
    # in the code, the zeros right before a function or a regions.tsv row, at most 255 of them. datamap calls
    # the part of a run after a datum of known size padding when the next datum starts aligned and soon enough
    first = DATA_LO - 0x100000 + 0x80
    for run in re.finditer(rb"\x00+", image[first:FILE_HI - 0x100000 + 0x80]):
        lo, hi = DATA_LO + run.start(), DATA_LO + run.end()
        if hi & ~3 > lo:
            rows.append((lo, hi - lo, "zeros"))
    before = {lo for lo, _hi, kind in datamap.fixed_intervals() if kind == "region" and lo < DATA_LO}
    for start in before | {s for s in function_starts if s > 0x100000}:
        length = 0
        while length < 255 and image[start - 1 - length - 0x100000 + 0x80] == 0:
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
