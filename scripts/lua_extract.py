#!/usr/bin/env python3
"""
lua_extract.py — extract every Lua 4.0.1 chunk's string constants from
NDMW.AFS (Digimon World 4). Prints a compact per-chunk summary and writes a
JSONL with the full per-chunk string tables for later grep.

Usage:
  python3 scripts/lua_extract.py ../local/extracted/NDMW.AFS /tmp/dw4_lua_strings.jsonl
"""
import struct
import sys
import json
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from lua_dump import parse_chunk, Chunk  # noqa: E402


def find_magic(data, magic):
    starts = []
    i = 0
    while True:
        j = data.find(magic, i)
        if j < 0:
            break
        starts.append(j)
        i = j + 1
    return starts


def main():
    afs_path = sys.argv[1]
    out_path = sys.argv[2]
    data = open(afs_path, "rb").read()
    count = struct.unpack("<I", data[4:8])[0]
    entries = [struct.unpack("<II", data[8 + i * 8: 8 + i * 8 + 8])
               for i in range(count)]

    magic = b"\x1bLua"
    outf = open(out_path, "w")
    total = 0
    for eidx, (off, size) in enumerate(entries):
        blob = data[off:off + size]
        starts = find_magic(blob, magic)
        if not starts:
            continue
        for cidx, s in enumerate(starts):
            try:
                hdr, main, c = parse_chunk(blob, s)
            except Exception:
                continue
            # collect ALL strings recursively
            allstr = []

            def walk(fn):
                allstr.extend(fn["kstr"])
                for sub in fn["kproto"]:
                    walk(sub)

            walk(main)
            rec = {
                "entry": eidx,
                "chunk": cidx,
                "off": off + s,
                "size": c.pos - s,
                "source": main["source"],
                "line": main["lineDefined"],
                "params": main["numparams"],
                "strings": allstr,
            }
            outf.write(json.dumps(rec) + "\n")
            total += 1
    outf.close()
    print(f"parsed {total} chunks -> {out_path}")


if __name__ == "__main__":
    main()
