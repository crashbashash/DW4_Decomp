#!/usr/bin/env python3
"""verify_texpack_layout.py -- regression check for the texture-pack pool order rule.

Derives a texture pack's pool layout from the id-order rule and diffs it against the committed
reference table (default `docs/engine/texture-pack-625-layout.tsv`).  Every row must match: an id,
a block kind, a size and an offset.

The rule
--------
A pack's `igClut`/`igImage` sub-records each carry an **object id**:

    clut : [ .., 28, 7, N, 4, id, N*4 ]                id = the word after _stride
    image: [ .., 104|108, W, H, 1, 1, 100, 0,0,0,0, 65536, W*H, id, -1 ]
                                                        id = the word after _imageSize

The pool is those blocks in **ascending id order**; a clut contributes `N*4` bytes and an image
`W*H` (an image block carries a one-byte prefix, so its grid data starts at `block + 1`).  So

    offset(id) = pool_base + sum(sizes of blocks with a smaller id)

`pool_base` is the end of the pack's object data, and 4-byte pads interrupt the run.

The pool base and the pad count come out of the pack header (see igb_texpack.py's
`header_layout`): hdr[6] == sum + 4*(nclut+2), hdr[7] == nclut+nimg+3, and the pads always
total 8 bytes.

Usage
-----
  verify_texpack_layout.py --afs NDMW.AFS --entry 625
      [--layout docs/engine/texture-pack-625-layout.tsv]
"""
import argparse
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import igb_texpack as TP
import os

HERE = os.path.dirname(os.path.abspath(__file__))



def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--afs", required=True)
    ap.add_argument("--entry", type=int, required=True)
    ap.add_argument("--base", type=lambda s: int(s, 0))
    ap.add_argument("--pads", default="")
    ap.add_argument("--layout", default=os.path.join(HERE, "..", "docs", "engine",
                                                     "texture-pack-625-layout.tsv"))
    ap.add_argument("--textures", default=os.path.join(HERE, "..", "docs", "engine",
                                                       "texture-pack-625-textures.tsv"),
                    help="texture -> image/palette fixture; '' to skip")
    args = ap.parse_args()
    pads = {int(x, 0) for x in args.pads.split(",") if x.strip()} if args.pads else None

    data = open(args.afs, "rb").read()
    off, size = struct.unpack_from("<II", data, 8 + 8 * args.entry)
    b = data[off:off + size]
    recs = TP.find_records(b)

    base = args.base
    if base is None:
        info = TP.header_layout(b, recs)
        if info is None:
            print("the header does not describe this pack's pool")
            return 1
        base, npad, total, nclut = info
        if pads is None:
            pads = set(TP.choose_pads(b, recs, base, npad))
    if pads is None:
        pads = set()
    layout, _, end = TP.build_layout(b, recs, base, pads)
    derived = [(i, kind, sz, c) for i, kind, sz, c, w, h in layout]
    print("derived %d rows, pool 0x%06x .. 0x%06x (pack 0x%06x)" % (len(derived), base, end, size))

    want = []
    for line in open(args.layout):
        if line.startswith("#") or not line.strip():
            continue
        f = line.rstrip("\n").split("\t")
        want.append((int(f[0]), f[1], int(f[2]), int(f[3], 16)))
    print("reference %d rows" % len(want))

    if len(want) != len(derived):
        print("ROW COUNT MISMATCH: %d derived vs %d reference" % (len(derived), len(want)))
        return 1
    bad = 0
    for (wi, wk, ws, wo), (di, dk, ds, do) in zip(want, derived):
        if (wi, wk, ws, wo) != (di, dk, ds, do):
            print("  MISMATCH  reference id=%s %s size=%s 0x%06x | derived id=%s %s size=%s 0x%06x"
                  % (wi, wk, ws, wo, di, dk, ds, do))
            bad += 1
    if bad:
        print("FAILED: %d rows differ" % bad)
        return 1
    print("OK: the id-order rule reproduces all %d rows" % len(derived))

    if args.textures and os.path.exists(args.textures):
        pal = TP.resolve_palettes(b, recs)
        if pal is None:
            print("FAILED: no validated id->class table, so no palette pairing")
            return 1
        off = {i: (kind, sz, c, w, h) for i, kind, sz, c, w, h in layout if kind != "pad"}
        got = {}
        for d in TP.image_records(b):
            p = pal.get(d["image"])
            got[d["name"]] = (d["w"], d["h"], d["image"], p,
                               off[d["image"]][2], off[p][2] if p in off else -1)
        nw = nbad = 0
        for line in open(args.textures):
            if line.startswith("#") or not line.strip():
                continue
            f = line.rstrip("\n").split("\t")
            want = (int(f[1]), int(f[2]), int(f[3]), int(f[4]), int(f[5], 16), int(f[6], 16))
            nw += 1
            if got.get(f[0]) != want:
                print("  TEXTURE MISMATCH %s: want %s got %s" % (f[0], want, got.get(f[0])))
                nbad += 1
        if nbad or nw != len(got):
            print("FAILED: %d of %d texture rows differ (%d derived)" % (nbad, nw, len(got)))
            return 1
        print("OK: the id->class rule pairs all %d textures with their palette" % nw)
    return 0


if __name__ == "__main__":
    sys.exit(main())
