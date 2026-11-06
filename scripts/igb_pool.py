#!/usr/bin/env python3
"""igb_pool.py — read a pack's content pool by memory-ref id, offline.

A pack's `igMemoryRef` values (a list's `_data`, `igImage._pImage`, `igClut._pData`,
geometry buffers, ...) are the **global ids of their pool blocks**.  The pool is the
concatenation of those blocks in id order, so a block's offset is

    pool_start + sum(_memSize of every igMemoryDirEntry id below it)

with `pool_start` the end of the object section and the id table read by
`scripts/igb_ids.py`.  Each block is placed at a **4-byte boundary**, so a
`_memSize` that is not a multiple of 4 is followed by 1-3 padding bytes:

    offset(id) = pool_start + sum(align4(_memSize) of every id below it)

and `sum(align4(_memSize))` is the pool size **exactly** on every pack checked — the "~141-byte
residual" of *was* this alignment.  On the generator packs (entry 622: 228 blocks,
7,112 bytes) the rule is unchanged because every size is already a multiple of 4; on the model packs
it removes the drift and makes a geometry buffer land on its own block start (verified against 432
live-located vertex buffers, and the geometry decodes byte-identically to the live extraction).

  igb_pool.py NDMW.AFS --blob 0x21307000 --check
  igb_pool.py NDMW.AFS --blob 0x21307000 --id 0 --dump /tmp/blk.bin
  igb_pool.py NDMW.AFS --blob 0x21307000 --list
  igb_pool.py NDMW.AFS --blob 0x20e33000 --image E_ogre01 --png /tmp/ogre.png
"""
import argparse
import os
import struct
import sys
import zlib

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import igb_ids  # noqa: E402

ig = igb_ids.igb_inst


def load(file, blob, reflection):
    data = open(file, "rb").read()
    lo = int(blob, 0)
    size, where = ig.blob_extent(data, lo)
    b = data[lo:lo + (size or len(data) - lo)]
    dirs, s1, s2, _ch = igb_ids.sections(b, reflection)
    p, cnt, obj_of_id = igb_ids.find_table(b, s1, s2)
    pool = max(r["end"] for r in s2)
    off_of, size_of, run = {}, {}, 0
    for i in range(cnt):
        v = struct.unpack_from("<H", b, p + 8 + 2 * i)[0]
        r = s1[v]
        if r["class"] == "igMemoryDirEntry":
            ms = igb_ids.field_map(r)["_memSize"]
            off_of[i], size_of[i] = pool + run, ms
            # A block is placed at a 4-byte boundary, so a `_memSize` that is not a
            # multiple of 4 is followed by 1-3 padding bytes.  Without
            # this the offsets drift, which is what the old ~141-byte "residual" was:
            # sum(align4(_memSize)) == the pool size exactly.
            run += (ms + 3) // 4 * 4
    return dict(b=b, s1=s1, s2=s2, pool=pool, poolsz=len(b) - pool, cnt=cnt,
                off_of=off_of, size_of=size_of, sum=sum(size_of.values()),
                aligned=sum((n + 3) // 4 * 4 for n in size_of.values()), where=where)


def write_png(path, rows, w, h):
    raw = b"".join(b"\x00" + bytes(v for px in row for v in px) for row in rows)

    def chunk(t, d):
        c = t + d
        return struct.pack(">I", len(d)) + c + struct.pack(">I", zlib.crc32(c) & 0xFFFFFFFF)

    open(path, "wb").write(b"\x89PNG\r\n\x1a\n"
                           + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
                           + chunk(b"IDAT", zlib.compress(raw, 6)) + chunk(b"IEND", b""))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file")
    ap.add_argument("--blob", required=True)
    ap.add_argument("--reflection", default=os.path.join(HERE, "..", "data", "reflection.json"))
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--id", type=lambda s: int(s, 0))
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--dump")
    ap.add_argument("--image", help="extract an igImage by its _pNameString (8-bit, RGBA32 palette)")
    ap.add_argument("--png")
    a = ap.parse_args()
    P = load(a.file, a.blob, ig.load_reflection(a.reflection))
    b, s2 = P["b"], P["s2"]
    print("pack %s: pool @+0x%x, %d bytes; %d pool blocks, id sizes sum to %d once each block is"
          " aligned to 4 (%s)"
          % (P["where"], P["pool"], P["poolsz"], len(P["off_of"]), P["aligned"],
             "exact" if P["aligned"] == P["poolsz"] else
             "short by %d" % (P["poolsz"] - P["aligned"])))

    if a.check:
        return 0
    if a.list:
        for i in sorted(P["off_of"])[:40]:
            print("  id %-7d off +0x%-8x size %-8d %s"
                  % (i, P["off_of"][i], P["size_of"][i], b[P["off_of"][i]:P["off_of"][i] + 12].hex()))
        return 0
    if a.id is not None:
        o, n = P["off_of"][a.id], P["size_of"][a.id]
        print("id %d -> +0x%x, %d bytes" % (a.id, o, n))
        print("  first 32:", b[o:o + 32].hex())
        if a.dump:
            open(a.dump, "wb").write(b[o:o + n])
            print("  wrote", a.dump)
        return 0
    if a.image:
        img = None
        for r in s2:
            f = igb_ids.field_map(r)
            if r["class"] == "igImage" and a.image in str(f.get("_pNameString")):
                img = f
                break
        if img is None:
            raise SystemExit("no igImage named %r" % a.image)
        iid, cid = img["_pImage"], img["_pClut"]
        # clut: _pClut is an object ref -> igClut -> _pData is a block id
        dirs, s1, s2b, _ch = igb_ids.sections(b, ig.load_reflection(a.reflection))
        p, cnt, obj_of_id = igb_ids.find_table(b, s1, s2b)
        ck = obj_of_id[cid]
        cf = igb_ids.field_map(s2b[ck])
        W, H, bpr = img["_px"], img["_py"], img["_bytesPerRow"]
        idx = b[P["off_of"][iid]:P["off_of"][iid] + img["_imageSize"]]
        pal = b[P["off_of"][cf["_pData"]]:P["off_of"][cf["_pData"]] + cf["_clutSize"]]
        rows = []
        for y in range(H - 1, -1, -1):
            row = []
            for x in range(W):
                v = idx[y * bpr + x]
                row.append((pal[4 * v], pal[4 * v + 1], pal[4 * v + 2], 255))
            rows.append(row)
        print("igImage %r: %dx%d, image block +0x%x, clut block +0x%x (%d entries, fmt %s)"
              % (a.image, W, H, P["off_of"][iid], P["off_of"][cf["_pData"]],
                 cf["_numEntries"], cf["_fmt"]))
        if a.png:
            write_png(a.png, rows, W, H)
            print("  wrote", a.png)
        return 0
    return 0


if __name__ == "__main__":
    sys.exit(main())
