#!/usr/bin/env python3
"""Map the platform boundary of the image: which functions touch EE hardware.

The EE talks to the outside world through memory-mapped registers -- the SIF (to the
IOP), the DMA controller, the VIF/GIF (to the VU and the GS), the timers, the
interrupt controller, the CDVD interface -- and through IOP RPC calls that those
registers carry.  A function that forms an address in one of those ranges is
*platform* code by construction: it cannot work on another machine without being
replaced.  That set, and its extent, is the port's replacement surface (tracker
T9); it also separates the statically linked Sony SDK from game logic, which the
empty `.symtab` cannot do.

Method: scan every instruction word for a `lui rt, hi` and look a few instructions
ahead for how `rt` is used:

  * `addiu`/`ori rt, rt, lo` or a load/store `rs == rt` resolves the address exactly;
  * `addu`/`or` with another register means the low half is dynamic, so only the
    `hi << 16` range is known -- still enough to name the block when the whole
    64 KB page falls inside one;
  * anything else (another `lui`, an unrelated write to `rt`) ends the search.

Addresses are normalised across the KSEG0/KSEG1 aliases first, because the SDK
reaches some registers cached (`0x1000F000`) and some uncached (`0xB000F000`).

Usage:  platform_map.py [--elf PATH] [--symbols PATH] [--json OUT] [--top N]
"""

import argparse
import bisect
import collections
import json
import struct
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
from mips_literals import LOADSTORE, make_word, scan_from_lui  # noqa: E402

VADDR_BASE, FILE_BASE = 0x100000, 0x80

# The EE's register blocks (physical addresses).  Names follow the published EE
# memory map; the long tail of MMIO outside these ranges is reported as mmio_other
# rather than guessed at.
BLOCKS = [
    (0x10000000, 0x10002000, "timer"),      # TIM0..TIM3
    (0x10002000, 0x10003000, "ipu"),
    (0x10003000, 0x10003800, "dma_spr"),    # DMA source/dest pointer regs
    (0x10003800, 0x10003C00, "vif0"),
    (0x10003C00, 0x10004000, "vif1"),
    (0x10004000, 0x10005000, "gif"),
    (0x10005000, 0x10008000, "vu1_regs"),
    (0x10008000, 0x1000E000, "dmac"),       # D0..D9 channel registers
    (0x1000E000, 0x1000F000, "dmac_ctrl"),  # D_STAT / D_ENABLE / ...
    (0x1000F000, 0x1000F100, "intc"),       # INTC_STAT / INTC_MASK
    (0x1000F100, 0x1000F200, "sbus"),
    (0x1000F200, 0x1000F300, "sif"),        # SIF registers
    (0x1000F400, 0x1000F500, "cdvd"),
    (0x1000F500, 0x10010000, "gs_priv"),
    (0x11000000, 0x11004000, "vu0_micro"),
    (0x11004000, 0x11008000, "vu0_mem"),
    (0x11008000, 0x1100C000, "vu1_micro"),
    (0x1100C000, 0x11010000, "vu1_mem"),
    (0x12000000, 0x12010000, "gs"),
]

MMIO_RANGES = [(0x10000000, 0x10010000), (0x11000000, 0x11010000), (0x12000000, 0x12010000)]


def phys(addr):
    """Normalise a KSEG0/KSEG1/uncached alias to its physical address."""
    if 0xA0000000 <= addr < 0xC0000000:
        return addr - 0xA0000000
    if 0x80000000 <= addr < 0xA0000000:
        return addr - 0x80000000
    return addr


def classify(addr):
    """Register block name for an address, or None if it is not MMIO."""
    p = phys(addr)
    for lo, hi, name in BLOCKS:
        if lo <= p < hi:
            return name
    for lo, hi in MMIO_RANGES:
        if lo <= p < hi:
            return "mmio_other"
    return None


def load_image(path):
    with open(path, "rb") as fh:
        return fh.read()


def load_symbols(path):
    syms = []
    with open(path) as fh:
        for ln in fh:
            if ln.startswith("#"):
                continue
            p = ln.split()
            if len(p) >= 3:
                syms.append((int(p[0], 16), int(p[1], 16), p[2]))
    syms.sort()
    return syms, [s[0] for s in syms]


def owner(syms, starts, va):
    i = bisect.bisect_right(starts, va) - 1
    if i >= 0 and syms[i][0] <= va < syms[i][0] + syms[i][1]:
        return syms[i]
    return None


def scan(img, syms, starts, code_lo, code_hi):
    """{function_va: {"exact": set(...), "range": set(...)}} of MMIO touches."""
    hits = collections.defaultdict(lambda: {"exact": set(), "range": set()})
    word = make_word(img)

    for va in range(code_lo, code_hi - 4, 4):
        ins = word(va)
        if ins is None or (ins >> 26) != 0x0F:  # lui
            continue
        hi, rt = ins & 0xFFFF, (ins >> 16) & 0x1F
        fn = owner(syms, starts, va)
        if not fn:
            continue
        for kind, addr in scan_from_lui(word, va, hi, rt):
            if classify(addr):
                key = "exact" if kind == "exact" else "range"
                hits[fn[0]][key].add(addr)
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--elf", default="orig/SLUS-20836/SLUS_208.36")
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--code-lo", default="0x100000")
    ap.add_argument("--code-hi", default="0x554b00")
    ap.add_argument("--json")
    ap.add_argument("--top", type=int, default=12)
    args = ap.parse_args()

    img = load_image(args.elf)
    syms, starts = load_symbols(args.symbols)
    hits = scan(img, syms, starts, int(args.code_lo, 16), int(args.code_hi, 16))

    def fn_of(va):
        return owner(syms, starts, va)

    by_block = collections.Counter()
    rows = []
    for fn_va, h in hits.items():
        blocks = sorted({classify(a) for a in h["exact"]} | {classify(a) for a in h["range"]})
        for b in blocks:
            by_block[b] += 1
        fn = fn_of(fn_va)
        rows.append((fn_va, fn[2], fn[1], len(h["exact"]), len(h["range"]), blocks))
    rows.sort(key=lambda t: (-(t[3] + t[4]), t[0]))

    print("platform boundary (EE memory-mapped registers)")
    print("  functions touching MMIO: %d of %d (%.1f%%)" % (len(hits), len(syms), 100.0 * len(hits) / len(syms)))
    if rows:
        print("  address range of those functions: 0x%06x .. 0x%06x" % (min(r[0] for r in rows), max(r[0] for r in rows)))
    print("  number of them that are anonymous FUN_: %d"
          % sum(1 for r in rows if r[1].startswith("FUN_")))
    print("  by block (functions touching each):")
    for b, n in by_block.most_common():
        print("    %-12s %4d" % (b, n))
    print("  busiest functions:")
    for fn_va, name, size, nex, nrg, blocks in rows[:args.top]:
        print("    0x%06x  %-22s size=%-5d exact=%-4d range=%-3d %s"
              % (fn_va, name, size, nex, nrg, ",".join(blocks)))
    if args.json:
        out = {
            "functions": {
                "0x%08x" % va: {
                    "name": fn_of(va)[2],
                    "size": fn_of(va)[1],
                    "blocks": sorted({classify(a) for a in h["exact"]} | {classify(a) for a in h["range"]}),
                    "exact": sorted({"0x%08x" % a for a in h["exact"]}),
                    "range": sorted({"0x%08x" % a for a in h["range"]}),
                }
                for va, h in sorted(hits.items())
            },
            "by_block": dict(by_block),
        }
        with open(args.json, "w") as fh:
            json.dump(out, fh, indent=1, sort_keys=True)
        print("wrote %s" % args.json)


if __name__ == "__main__":
    main()
