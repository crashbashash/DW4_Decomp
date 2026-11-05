#!/usr/bin/env python3
"""
probe_items2.py — generate item-ID probe saves for cores (cat 0x10) and mods
(cat 0x30), filling the 9 device-folder slots with candidate u32 IDs.

Unlike probe_items.py (weapons), these probes clear the weapon/armor/mod/sub
equip slots so the game won't try to equip an armor/core as a weapon.

Usage:
  probe_items2.py <src.ps2> <outdir> <name> --ids 0x1000,0x1003,... [--armor]
"""
import os
import shutil
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from save_probe import fix_checksums, find_entry  # noqa: E402

BLOCK = 0xA000
DEV = 0x6C
WEP = 0x2E4
EMPTY = 0xFFFFFFFF


def main():
    src = sys.argv[1]
    outdir = sys.argv[2]
    name = sys.argv[3]
    args = sys.argv[4:]
    ids = []
    armor = False
    i = 0
    while i < len(args):
        a = args[i]
        if a == "--ids":
            spec = args[i + 1]
            ids = [int(x, 0) for x in spec.split(",")]
            i += 2
        elif a == "--armor":
            armor = True
            i += 1
        else:
            i += 1
    if not ids or len(ids) > 9:
        print(__doc__)
        return 1

    os.makedirs(outdir, exist_ok=True)
    dst = os.path.join(outdir, f"{name}.ps2")
    shutil.copy(src, dst)

    from ps2mc.ps2mc import Ps2mc
    with open(dst, "r+b") as f:
        mc = Ps2mc(f)
        fe = find_entry(mc, "BASLUS-20836savedata", "BASLUS-20836savedata")
        data = bytearray(mc.read_data_cluster(fe))

        for k, vid in enumerate(ids):
            for b in (0, BLOCK):
                struct.pack_into("<I", data, b + DEV + 4 * k, vid)
        for k in range(len(ids), 9):
            for b in (0, BLOCK):
                struct.pack_into("<I", data, b + DEV + 4 * k, EMPTY)
        # clear equip slots
        for off in (0x2E4, 0x2E8, 0x2EC, 0x2F0, 0x2F4, 0x2F8, 0x2FC, 0x300,
                    0x308, 0x30C, 0x310, 0x314, 0x318, 0x31C):
            for b in (0, BLOCK):
                struct.pack_into("<I", data, b + off, EMPTY)
        if armor:
            for b in (0, BLOCK):
                struct.pack_into("<I", data, b + 0x304, 0)  # equip slot 0 as armor
        fix_checksums(data)
        mc.write_data_cluster(fe, bytes(data))

    print(f"wrote {dst} with {len(ids)} ids: {[hex(x) for x in ids]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
