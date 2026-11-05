#!/usr/bin/env python3
"""Summarize DW4 story state and diff saves in the supplied progression order.

Accept extracted saves or memory-card images (optional ps2mc). With no filenames,
use the historical checkpoint inventory under the workspace's private memcards.
"""
import argparse
from pathlib import Path
from diff_story import REGIONS, story_state

MCDIR = Path(__file__).resolve().parents[2] / "local/testing/memcards"

# Historical progression order.
ORDER = [
    'Mcd001_op_base.ps2',
    'prog_humid_cave.ps2',
    'prog_cliff_dungeon.ps2',
    'prog_leomon_save.ps2',   # missing from the inventory
    'prog_world1.ps2',
    'prog_ophanimon_key.ps2',
    'prog_ophanimon_key_used.ps2',
    'prog_disable_power_plant.ps2',
    'prog_sand_labrynth.ps2',
    'prog_ancient_ruins.ps2',
    'prog_world2.ps2',
    'prog_world3_unlocked.ps2',
    'prog_gecko_path.ps2',
    'prog_vine_tunnel.ps2',
    'prog_vein.ps2',
    'prog_world3.ps2',
    'prog_world4_unlocked.ps2',
]


def flag_summary(name, st):
    flags = st['flags']
    ones = [i for i, b in enumerate(flags) if b == 0x01]
    other = {i: b for i, b in enumerate(flags) if b not in (0x00, 0x01)}
    folder = [i for i, b in enumerate(st['folder']) if b == 0x01]
    folder_other = {i: b for i, b in enumerate(st['folder']) if b not in (0x00, 0x01)}
    # counters as u32 LE
    c = st['counter']
    counters = []
    for i in range(0, len(c) - 3, 4):
        counters.append(int.from_bytes(c[i:i+4], 'little'))
    return ones, other, folder, folder_other, counters


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("saves", nargs="*", help="filenames in progression order")
    parser.add_argument("--directory", type=Path, default=MCDIR)
    args = parser.parse_args()
    order = args.saves or ORDER
    states = {}
    for fn in order:
        p = args.directory / fn
        if p.exists():
            try:
                states[fn] = story_state(p)
            except (OSError, ValueError) as exc:
                parser.error(f"{p}: {exc}")
        else:
            print(f"# MISSING: {fn}")

    # per-save summary
    for fn in order:
        if fn not in states:
            continue
        ones, other, folder, fo, counters = flag_summary(fn, states[fn])
        print(f"\n=== {fn} ===")
        print(f"  folder SET: {folder}" + (f"  other: {fo}" if fo else ""))
        print(f"  counters u32[0..{len(counters)-1}]: {[hex(x) for x in counters]}")
        if other:
            print(f"  flags non-00/01: {other}")
        # compact set-flag list
        print(f"  set flags ({len(ones)}): {ones}")

    # consecutive diffs
    print("\n\n########## CONSECUTIVE DIFFS ##########")
    prev = None
    for fn in order:
        if fn not in states:
            print(f"\n### (skipping missing {fn})")
            continue
        if prev is not None:
            pa, pb = states[prev], states[fn]
            print(f"\n--- {prev} -> {fn} ---")
            for region in ('flags', 'folder'):
                ba, bb = pa[region], pb[region]
                base = REGIONS[region][0]
                changes = []
                for i, (x, y) in enumerate(zip(ba, bb)):
                    if x != y:
                        changes.append(f"  {region}[{i}] (0x{i:03x} / off 0x{base+i:04x}): 0x{x:02x} -> 0x{y:02x}")
                if changes:
                    print("\n".join(changes))
                else:
                    print(f"  ({region}: no change)")
            # counter changes
            ca, cb = pa['counter'], pb['counter']
            for i in range(0, len(ca) - 3, 4):
                va = int.from_bytes(ca[i:i+4], 'little')
                vb = int.from_bytes(cb[i:i+4], 'little')
                if va != vb:
                    print(f"  counter[{i//4}] (off 0x{0x72c+i:04x}): 0x{va:08x} -> 0x{vb:08x}")
        prev = fn


if __name__ == '__main__':
    main()
