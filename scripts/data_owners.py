#!/usr/bin/env python3
"""data_owners.py — which library owns each stretch of the data, from the code that reaches it.

The linker lays data out by section and, inside a section, in the same object order as the code,
so each address the code forms belongs to the library that forms it most, and those owners run in
link order. Runs too small to tell from a shared string or a stray reference are absorbed by their
neighbours. A new section starts where the order falls back to the start of the link, and within
a section the heaviest chain of runs in link order stands; the rest are counted as strays.

  scripts/data_owners.py                # print the table
  scripts/data_owners.py --out config/SLUS-20836/data-owners.tsv
  scripts/data_owners.py --check
"""
import argparse
import collections
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import regions  # noqa: E402

ELF = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
OUT = os.path.join(ROOT, "config", "SLUS-20836", "data-owners.tsv")
BASE, FILE_BASE = 0x100000, 0x80
CODE_END, DATA_END = 0x467120, 0x58d280
BSS_START = 0x554b00
MEMORY_OPS = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 46, 49, 55, 57, 63}
ADDIU, ORI, LUI = 9, 13, 15
WINDOW = 48        # bytes a lui is followed for its low half
MIN_RUN = 4        # references a run needs to stand as its own owner
LINK_START = 0     # the link position that opens a section: the first object, the runtime
FALL_BACK = 8      # link positions a section must reach before it can end
SECTION_START = 6  # references the opening run of a section needs


def written(w):
    """The general register an instruction writes, or None."""
    op, rt, rd = w >> 26, (w >> 16) & 31, (w >> 11) & 31
    if op == 0 or op == 28:
        return rd
    if op in (2, 3, 4, 5, 6, 7, 20, 21, 22, 23) or 40 <= op <= 47 or op in (1, 16, 17, 18, 31, 49, 57, 63):
        return None
    return rt


def references(image):
    """-> {data address: Counter(region id)} for every address the code forms with lui."""
    def word(at):
        return struct.unpack_from("<I", image, FILE_BASE + at - BASE)[0]

    found = collections.defaultdict(collections.Counter)
    high = {}
    for at in range(BASE, CODE_END, 4):
        w = word(at)
        op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xffff
        if op == LUI:
            high[rt] = (at, imm << 16)
            continue
        base = high.get(rs)
        target = None
        if base is not None and at - base[0] <= WINDOW:
            if op in MEMORY_OPS or op == ADDIU:
                target = (base[1] + imm - ((imm & 0x8000) << 1)) & 0xffffffff
            elif op == ORI:
                target = base[1] | imm
        if target is not None and CODE_END <= target < DATA_END:
            found[target][regions.of(at).id] += 1
        high.pop(written(w), None)
    return found


def runs(found):
    """Owner runs over the referenced addresses: [first, last, owner, references]."""
    out = []
    for target in sorted(found):
        owner, count = found[target].most_common(1)[0][0], sum(found[target].values())
        if out and out[-1][2] == owner:
            out[-1][1] = target
            out[-1][3] += count
        else:
            out.append([target, target, owner, count])
    return out


def in_order(rows, order):
    """The heaviest chain of rows whose owners keep to link order."""
    best = []
    for i, row in enumerate(rows):
        weight, before = row[3], None
        for j in range(i):
            if order[rows[j][2]] <= order[row[2]] and best[j][0] + row[3] > weight:
                weight, before = best[j][0] + row[3], j
        best.append((weight, before))
    i = max(range(len(rows)), key=lambda k: best[k][0])
    chain = []
    while i is not None:
        chain.append(rows[i])
        i = best[i][1]
    return chain[::-1]


def sections(rows, order):
    """Split where the owners fall back to the start of the link and stay there."""
    out, current, furthest = [], [], 0
    for row in rows:
        index = order[row[2]]
        if index <= LINK_START and furthest > LINK_START + FALL_BACK and row[3] >= SECTION_START:
            out.append(current)
            current, furthest = [], 0
        current.append(row)
        furthest = max(furthest, index)
    return out + [current]


def table(image):
    order = {row.id: index for index, row in enumerate(regions.load())}
    rows = [run for run in runs(references(image)) if run[3] >= MIN_RUN]
    lines = []
    parts = sections(rows, order)
    for number, part in enumerate(parts):
        chain = in_order(part, order)
        joined = []
        for run in chain:
            if joined and joined[-1][2] == run[2]:
                joined[-1][1] = run[1]
                joined[-1][3] += run[3]
            else:
                joined.append(list(run))
        strays = sum(run[3] for run in part) - sum(run[3] for run in joined)
        limit = parts[number + 1][0][0] if number + 1 < len(parts) else DATA_END
        for position, (first, _last, owner, count) in enumerate(joined):
            end = joined[position + 1][0] if position + 1 < len(joined) else limit
            lines.append("0x%08x\t0x%08x\t%d\t%s\t%d" % (first, end, number, owner, count))
        lines.append("# section %d: %d references out of link order" % (number, strays))
    head = ["# Library owning each stretch of data, from the code that reaches it.",
            "# GENERATED by scripts/data_owners.py; docs/engine/data-regions.md gives the method.",
            "# start\tend\tsection\towner\treferences"]
    return "\n".join(head + lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__.partition("\n")[0])
    parser.add_argument("--out")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = table(open(ELF, "rb").read())
    if args.check:
        if open(OUT).read() != text:
            print("data_owners: %s is stale" % os.path.relpath(OUT, ROOT))
            return 1
        print("data_owners: current")
        return 0
    if args.out:
        open(args.out, "w").write(text)
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
