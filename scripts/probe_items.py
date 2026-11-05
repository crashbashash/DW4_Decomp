#!/usr/bin/env python3
"""
probe_items.py — generate batched test saves to map device-folder item IDs to
in-game names (Digimon World 4, USA).

Fills the 9 device-folder slots (save +0x6c..0x8c) with candidate IDs, equips
the first 3 (weapon slots +0x2e4/8/c -> indices 0,1,2), and writes one .ps2
per batch. The user loads each, opens the equipment screen, and reads off the
9 names. This empirically pins the id->name table (see docs/systems/items.md).

Usage:
  probe_items.py <src.ps2> <outdir> --ids 0x0000..0x0048 --step 5
  probe_items.py <src.ps2> <outdir> --ids 0,25,50,75,1293,1298,1299,8213
  probe_items.py <src.ps2> <outdir> --range 0x0000 0x0100   # every id

  --ids A..B      inclusive range of ids (ints; hex ok), optional --step
  --ids a,b,c     explicit comma list
  --range LO HI   same as --ids LO..HI step 1

Each generated save: Mcd001_probe_<firstid>_<lastid>.ps2
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))


def parse_ids(args):
    ids = []
    i = 0
    while i < len(args):
        a = args[i]
        if a == "--ids":
            spec = args[i + 1]
            if ".." in spec:
                lo_s, hi_s = spec.split("..", 1)
                ids = list(range(int(lo_s, 0), int(hi_s, 0) + 1))
            else:
                ids = [int(x, 0) for x in spec.split(",")]
            i += 2
        elif a == "--range":
            lo, hi = int(args[i + 1], 0), int(args[i + 2], 0)
            ids = list(range(lo, hi + 1))
            i += 3
        elif a == "--step":
            step = int(args[i + 1], 0)
            ids = ids[::step]
            i += 2
        else:
            i += 1
    return ids


def main():
    src = sys.argv[1]
    outdir = sys.argv[2]
    ids = parse_ids(sys.argv[3:])
    if not ids:
        print(__doc__)
        return 1
    os.makedirs(outdir, exist_ok=True)

    # 9 device-folder slots start at +0x6c, stride 4; weapon slots +0x2e4/8/c
    DEV = 0x6C
    WEP = 0x2E4
    EMPTY = 0xFFFFFFFF

    batches = [ids[j:j + 9] for j in range(0, len(ids), 9)]
    for b in batches:
        edits = []
        for k, vid in enumerate(b):
            edits.append(f"{DEV + 4 * k}={vid}")
        # pad remaining slots empty
        for k in range(len(b), 9):
            edits.append(f"{DEV + 4 * k}={EMPTY}")
        # equip first three present ids (weapon slots hold folder indices)
        edits.append(f"{WEP}=0")
        edits.append(f"{WEP + 4}=1")
        edits.append(f"{WEP + 8}=2")
        dst = os.path.join(outdir, f"Mcd001_probe_{b[0]:#06x}_{b[-1]:#06x}.ps2")
        print(f"batch {b[0]:#06x}..{b[-1]:#06x}: {[hex(x) for x in b]}")
        # apply the edits to the copied card
        from save_probe import block_sum, fix_checksums  # noqa: F401
        import struct, shutil
        from ps2mc.ps2mc import Ps2mc

        shutil.copy(src, dst)
        with open(dst, "r+b") as f:
            mc = Ps2mc(f)
            fe = None
            for e in mc.find_sub_entries(mc.get_root_entry()):
                if e.name == "BASLUS-20836savedata" and e.is_dir():
                    for s in mc.find_sub_entries(e):
                        if s.is_file() and s.name == "BASLUS-20836savedata":
                            fe = s
            if fe is None:
                print("  save file not found")
                return 1
            data = bytearray(mc.read_data_cluster(fe))
            for off_val in edits:
                off_s, val_s = off_val.split("=")
                off, val = int(off_s, 0), int(val_s, 0)
                for blk in (0, 0xA000):
                    struct.pack_into("<I", data, blk + off, val)
            fix_checksums(data)
            mc.write_data_cluster(fe, bytes(data))
        print(f"  wrote {dst}")
    print(f"\n{len(batches)} save(s) -> {outdir}")
    print("Load each, open equipment/status, read the 9 names in slot order.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
