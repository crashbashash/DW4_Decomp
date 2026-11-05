#!/usr/bin/env python3
"""lua_find_items.py — scan NDMW.AFS Lua chunks for item-ID number constants.

Reports chunks whose number constants include any of the known device-folder
item IDs (0, 25, 50, 75, 1293, 1298, 1299, 8213, ...) plus their surrounding
numbers — used to locate the shop/item lists and recover the item order.

Usage: python3 lua_find_items.py local/extracted/NDMW.AFS
"""
import struct
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from lua_dump import parse_chunk

ITEM_IDS = {0, 25, 50, 75, 1293, 1298, 1299, 8213}
MAGIC = b"\x1bLua"


def main():
    path = sys.argv[1]
    data = open(path, "rb").read()
    count = struct.unpack("<I", data[4:8])[0]
    entries = [struct.unpack("<II", data[8 + i * 8:8 + i * 8 + 8]) for i in range(count)]

    for eidx, (off, size) in enumerate(entries):
        blob = data[off:off + size]
        i = 0
        hits = 0
        while True:
            j = blob.find(MAGIC, i)
            if j < 0:
                break
            try:
                hdr, main, c = parse_chunk(blob, j)
            except Exception:
                i = j + 1
                continue
            # collect numbers recursively
            nums = []

            def walk(fn):
                nums.extend(fn["knum"])
                for sub in fn["kproto"]:
                    walk(sub)

            walk(main)
            found = [n for n in nums if n in ITEM_IDS]
            if found:
                # print chunk summary + the numbers in order (to see item order)
                strs = []

                def ws(fn):
                    strs.extend(fn["kstr"])
                    for sub in fn["kproto"]:
                        ws(sub)
                ws(main)
                ints = [int(n) for n in nums if n == int(n) and 0 <= n < 20000]
                print(f"entry {eidx} chunk@{off+j:#x}: source={main['source']!r} "
                      f"strs={len(strs)} nums={len(nums)} found={found}")
                # show a compact window of the integer constants (item-id candidates)
                print(f"   ints: {ints[:80]}")
                print(f"   strings: {strs[:20]}")
                hits += 1
            i = j + 1
        if hits:
            print(f"   [{hits} chunks matched in entry {eidx}]")


if __name__ == "__main__":
    main()
