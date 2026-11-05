#!/usr/bin/env python3
"""
layout.py — turn the symbol map into a DISJOINT, ordered tiling of the section.

`config/SLUS-20836/symbols.txt` describes functions, and Ghidra's function boundaries are not
a partition: 33 pairs overlap (a function defined inside another's range), so
linking every unit as-is would emit some bytes twice. A relink needs each byte
exactly once, in address order, so this produces that plan:

  config/SLUS-20836/layout.txt   `va size kind name` for every byte of the 4,541,184-byte
                      section — `code` units (functions) and `data` units (the
                      regions between them, mostly alignment padding plus one
                      644 KB block)

Overlaps are resolved by truncating the earlier unit at the later one's start, so
the later (inner) function keeps its own full unit and the earlier one loses only
the bytes the inner one claims. Truncated units are marked so nobody mistakes one
for a whole function.

Usage:
  layout.py                # write config/SLUS-20836/layout.txt
  layout.py --report       # print the shape, write nothing
  layout.py --limit 40     # first 40 units
"""
import argparse
import os
import sys

SECTION_LO, SECTION_HI = 0x100000, 0x100000 + 0x454B00


def load_symbols(path):
    out = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.append((int(p[0], 16), int(p[1], 16), p[2]))
    out.sort()
    return out


def build(syms, spans=(), section_lo=SECTION_LO, section_hi=SECTION_HI):
    """-> [(va, size, kind, name, truncated)] tiling [SECTION_LO, SECTION_HI).

    `spans` is `[(lo, hi, owner_fn_name)]`, one per function's jump table (see
    tools/jumptables.py). A compiler-generated table lives in `.rodata`, i.e. inside
    a data unit, so it gets its own unit here: without that the relink would emit the
    retail table bytes AND orphan the compiled one.
    """
    if not 0 <= section_lo < section_hi <= 0x100000000:
        raise ValueError("invalid section bounds")
    if any(va < section_lo or size <= 0 or va + size > section_hi
           for va, size, _name in syms):
        raise ValueError("function extent outside selected section")
    units = []
    cur = section_lo
    for i, (va, sz, name) in enumerate(syms):
        if va + sz <= cur:
            continue                      # wholly inside what we already emitted
        if va > cur:
            units.append((cur, va - cur, "data", "data_%08x" % cur, False))
            cur = va
        start = cur                        # >= va; may be inside due to an overlap
        end = va + sz
        nxt = syms[i + 1][0] if i + 1 < len(syms) else section_hi
        truncated = end > nxt
        if end > nxt:
            end = nxt                      # let the next function own its bytes
        # a truncated unit's bytes up to `start` belong to an earlier unit
        if end > start:
            units.append((start, end - start, "code", name, truncated))
            cur = end
    if cur < section_hi:
        units.append((cur, section_hi - cur, "data", "data_%08x" % cur, False))
    return split_spans(units, spans)


def split_spans(units, spans):
    """Carve each jump-table span out of the data unit that covers it."""
    if not spans:
        return units
    spans = sorted(spans)
    out = []
    for u in units:
        va, sz, kind, name = u[0], u[1], u[2], u[3]
        if kind != "data":
            out.append(u)
            continue
        end, cur = va + sz, va
        for lo, hi, owner in spans:
            if hi <= cur or lo >= end:
                continue
            if lo > cur:
                out.append((cur, lo - cur, "data", "data_%08x" % cur, False))
            out.append((lo, hi - lo, "jtbl", "jtbl_%08x" % lo, owner))
            cur = hi
        if cur < end:
            out.append((cur, end - cur, "data", "data_%08x" % cur, False))
    return out


def load_spans(path, syms):
    """config/SLUS-20836/jumptables.txt -> [(lo, hi, owner)] — one span per function's tables.

    A function's tables may be several (18 of the 123 are) and MWCC aligns each to
    16 bytes; the compiler emits that padding too, so the span runs from the first
    table to the end of the last one and the gap bytes stay inside the unit. The
    checks in tools/jumptables.py already proved the starts are 16-aligned and the
    inter-table padding is zero, and verify.py compares every byte of the span.
    """
    if not os.path.exists(path):
        return []
    names = {v: n for v, s, n in syms}
    per = {}
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        per.setdefault(int(p[0], 16), []).append((int(p[1], 16), int(p[2], 16)))
    out = []
    for fn, tabs in sorted(per.items()):
        lo = min(t[0] for t in tabs)
        hi = max(t[0] + 4 * t[1] for t in tabs)
        out.append((lo, hi, names.get(fn, "FUN_%08x" % fn)))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--jumptables", default="config/SLUS-20836/jumptables.txt")
    ap.add_argument("--out", default="config/SLUS-20836/layout.txt")
    ap.add_argument("--section-start", type=lambda s: int(s, 0), default=SECTION_LO)
    ap.add_argument("--section-size", type=lambda s: int(s, 0), default=SECTION_HI - SECTION_LO)
    ap.add_argument("--report", action="store_true")
    ap.add_argument("--limit", type=int, default=0)
    a = ap.parse_args(argv)

    syms = load_symbols(a.symbols)
    spans = load_spans(a.jumptables, syms)
    section_hi = a.section_start + a.section_size
    units = build(syms, spans, a.section_start, section_hi)
    code = [u for u in units if u[2] == "code"]
    data = [u for u in units if u[2] == "data"]
    jtbl = [u for u in units if u[2] == "jtbl"]
    trunc = [u for u in code if u[4]]
    total = sum(u[1] for u in units)
    covered = sum(u[1] for u in code)

    print(f"units      : {len(units)}  ({len(code)} code, {len(jtbl)} jtbl, {len(data)} data)")
    print(f"bytes      : {total} of {a.section_size} covered "
          f"({'OK' if total == a.section_size else 'BAD'})")
    print(f"code       : {covered} bytes in {len(code)} units")
    print(f"jtbl       : {sum(u[1] for u in jtbl)} bytes in {len(jtbl)} units")
    print(f"data       : {total - covered - sum(u[1] for u in jtbl)} bytes in "
          f"{len(data)} units (largest {max((u[1] for u in data), default=0)})")
    print(f"truncated  : {len(trunc)} code units shortened by an overlapping function")
    # sanity: no gaps, no overlaps
    pos = a.section_start
    for u in units:
        va, sz = u[0], u[1]
        if va != pos:
            print(f"  !! layout hole/overlap at 0x{va:x} (expected 0x{pos:x})", file=sys.stderr)
            return 1
        pos = va + sz
    if pos != section_hi:
        print(f"  !! layout ends at 0x{pos:x}, expected 0x{section_hi:x}", file=sys.stderr)
        return 1
    if a.report:
        return 0
    with open(a.out, "w") as fh:
        fh.write("# va size kind name [owner|truncated] — GENERATED by tools/layout.py; do not edit.\n")
        fh.write("# Disjoint, ordered tiling of 0x%06x..0x%06x. 'code' units are functions\n"
                 "# (name matches config/SLUS-20836/symbols.txt); 'data' units are everything between them;\n"
                 "# 'jtbl' units are a compiled switch's .rodata (owner = the function's name).\n"
                 % (a.section_start, section_hi))
        for u in (units[:a.limit] if a.limit else units):
            va, sz, kind, name, t = u[:5]
            fh.write("%08x %06x %s %s" % (va, sz, kind, name))
            if kind == "jtbl":
                fh.write(" %s" % t)
            elif t:
                fh.write(" truncated")
            fh.write("\n")
    print(f"wrote {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
