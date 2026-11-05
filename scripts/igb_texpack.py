#!/usr/bin/env python3
"""igb_texpack.py -- read a DW4 texture pack (the second kind of pack in NDMW.AFS).

A texture pack is a small object graph (a class directory, a string table, and one
descriptor record per texture) followed by a flat **pool** that holds every texture's
palette and index grid.  Neither the descriptor records nor the pool carry an offset,
so the pool has to be *derived*.

The layout rule (finding #472, verified 52/52 on NDMW.AFS entry 625):

  * The pack stores one `igClut` sub-record and one `igImage` sub-record per texture.
    Each carries an **object id**: the clut's is the word after `_stride` in
    `[.., 28, 7, N, 4, id, N*4]`; the image's is the word after `_imageSize` in
    `[.., 104|108, W, H, 1, 1, 100, 0,0,0,0, 65536, W*H, id, -1]`.
  * A clut contributes a 1024-byte block, an image a `W*H`-byte block.
  * The pool is those blocks laid out in **ascending id order**.
  * The pool begins immediately after the pack's object data; a small number of
    4-byte slots pad the run (two in entry 625).

So `offset(id) = pool_base + sum(block sizes with a smaller id)`.

The pool base is the end of the pack's object data (it sits immediately after a trailing
4-byte-strided list of small ids); a few 4-byte pads interrupt the run.  Both are detected
where possible and can be given explicitly with --base / --pads.  For NDMW.AFS entry 625 the
exact call is `--base 0x2c08 --pads 129,140`; the verified result is
`../docs/engine/texture-pack-625-layout.tsv` and `verify_texpack_layout.py` re-runs the check.

Each record is a **serialised igObject** whose fields sit at the reflected offsets, so an
igImage carries its own name, size, grid id (`_pImage`) and palette id (`_pClut`) -- these
are ordinary igBinary records with a `{u32 class}{u32 bytes}` header, not the flat
descriptors earlier work read them as (finding #476).  `_pClut` is an id in the pack's id
space rather than a block id; `resolve_palettes` turns it into the palette block through
the pack's id->class table, and `decode_rgba` reproduces the texture.

Usage
-----
  igb_texpack.py FILE                    show the derived layout
  igb_texpack.py --afs A --entry N       read entry N of an AFS archive
  igb_texpack.py ... --base 0x2c08       set the pool base (default: auto-detect)
  igb_texpack.py ... --pads 129,140      ids each followed by a 4-byte pad
  igb_texpack.py ... --textures          list name, size, image id and palette id
  igb_texpack.py ... --decode NAME --out F   write one texture as raw RGBA
  igb_texpack.py ... --dump ID [--out F] write one block
  igb_texpack.py ... --tsv F             write the layout as id/kind/size/offset rows
"""
import argparse
import itertools
import struct
import sys


def read_pack(args):
    if args.afs is not None:
        data = open(args.afs, "rb").read()
        if data[:4] != b"AFS\x00":
            sys.exit("%s: not an AFS archive" % args.afs)
        off, size = struct.unpack_from("<II", data, 8 + 8 * args.entry)
        if size == 0:
            sys.exit("AFS entry %d is empty" % args.entry)
        return data[off:off + size]
    return open(args.file, "rb").read()


def find_records(b):
    """Return the pack's clut and image sub-records as (offset, kind, id, size, w, h)."""
    recs = []
    n = len(b)
    for p in range(0, n - 64):
        v = struct.unpack_from("<16I", b, p)
        # igClut:  _numEntries, _stride, _pData(id), _clutSize
        if (v[1] == 28 and v[2] == 7 and 1 <= v[3] <= 256
                and v[4] in (2, 4) and v[6] == v[3] * v[4] and v[0] < 64):
            recs.append((p, "clut", v[5], v[3] * v[4], v[3], 1))
        # igImage: _pfmt 65536, _imageSize == W*H
        elif (v[1] in (104, 108) and 4 <= v[2] <= 1024 and 4 <= v[3] <= 1024
              and v[4] == 1 and v[5] == 1 and v[6] == 100 and v[11] == 65536
              and v[12] == v[2] * v[3] and v[0] < 64):
            recs.append((p, "img", v[13], v[12], v[2], v[3]))
    recs.sort(key=lambda r: r[2])
    return recs


def csml_ok(block):
    """A palette's RGB bytes are CSM1-expanded: v&7 == v>>5."""
    n = ok = 0
    for k in range(0, len(block), 4):
        for t in (1, 2, 3):
            if k + t < len(block):
                v = block[k + t]
                n += 1
                ok += (v & 7) == (v >> 5)
    return ok / n if n else 0.0


def header_layout(b, recs):
    """Read the pool base and the pad count out of the pack header.

    Two header words are exact functions of the sub-records (verified on all 44 texture
data packs of NDMW.AFS):

        hdr[6] == sum(block sizes) + 4 * (nclut + 2)
        hdr[7] == nclut + nimg + 3

    The tool lays the pool down as `[table, pool)`, where the table is one 4-byte id per
    texture and the pool is the blocks plus a fixed 8 bytes of pads, and the region ends
    one byte before EOF:

        table_start = EOF - 1 - hdr[6]
        pool_base   = table_start + 4 * nclut

    Returns `(base, npads, total, nclut)` or None when the header disagrees with the
    records (a multi-asset pack, or an incomplete parse).
    """
    if len(b) < 0x30:
        return None
    h6, h7 = struct.unpack_from("<2I", b, 0x18)
    nclut = sum(1 for r in recs if r[1] == "clut")
    nimg = len(recs) - nclut
    total = sum(r[3] for r in recs)
    if nclut == 0 or h7 != nclut + nimg + 3 or total != h6 - 4 * (nclut + 2):
        return None
    base = len(b) - h6 + 4 * nclut - 1
    pads = h6 - 4 * nclut - total
    if base < 0 or pads < 0 or pads % 4 or base + total + pads > len(b):
        return None
    return base, pads // 4, total, nclut


def choose_pads(b, recs, base, npads):
    """Place the 4-byte pads.

    A pad is a small block, so it can only sit in a gap in the id sequence.  Among the
    gap positions, the one that lines up the most palettes wins -- a palette block starts
    at a 4-byte entry whose RGB is the index-0 colour, which is black in every texture.
    Ties go to the latest position (the ids adjacent to the following block), which is
    what the pack's own numbering uses.
    """
    if npads == 0:
        return []
    cand = [recs[p][2] for p in range(len(recs) - 1)
            if recs[p + 1][2] - recs[p][2] > 1]
    if len(cand) < npads:
        return []

    def score(pads):
        c = base
        good = 0
        for p, kind, i, size, w, h in recs:
            if kind == "clut" and b[c + 1] == 0 and b[c + 2] == 0 and b[c + 3] == 0:
                good += 1
            c += size
            if i in pads:
                c += 4
        return good

    best = (-1, ())
    for combo in itertools.combinations(cand, npads):
        s = score(set(combo))
        if s > best[0] or (s == best[0] and tuple(combo) > best[1]):
            best = (s, tuple(combo))
    return list(best[1])


def image_records(b):
    """Every igImage record as a dict: name, rec, image (grid id), clut, w, h.

    A texture's igImage is a **serialised igImage object**: the reflected field offsets
    hold in the file (#476), so `_px/_py` are at +8/+12, `_pImage` (an igMemoryRef, i.e.
    the grid block's id) at +52, `_pClut` (an igObjectRef) at +68 and the `_pNameString`
    length at +88 with the bytes after it.  The `[1, 0, C, bitsIdx, DIM, 0, 0, namelen,
    name]` run earlier work read as a separate "descriptor entry" is just this record's
    tail -- `_localImage`, `_bitsInt`, `_pClut`, `_bitsIdx`, `_bytesPerRow`, ... -- which
    is why the record looked 60 bytes long.
    """
    out = []
    for p, kind, i, size, w, h in find_records(b):
        if kind != "img":
            continue
        n, = struct.unpack_from("<I", b, p + 88)
        name = ""
        if 0 < n <= 64:
            name = b[p + 92:p + 92 + n].rstrip(b"\x00").decode("latin-1")
        clut, = struct.unpack_from("<I", b, p + 68)
        out.append(dict(name=name, rec=p, image=i, clut=clut, w=w, h=h))
    out.sort(key=lambda d: d["rec"])
    return out


def find_textures(b):
    """Return the pack's textures as `(name, image_record_offset, image_id)`."""
    return [(d["name"], d["rec"], d["image"]) for d in image_records(b)]


def class_table(b, recs):
    """Locate and validate the pack's **id -> class** table.

    Same shape as the object packs' id remap table (#460) -- `{u32 tableBytes}`
    `{u32 idCount}` then idCount u16 -- but the entries are the *class* of each id rather
    than a record index.  The class numbering is pack-local: on NDMW.AFS 625 the clut
    blocks are class 0 and the igClut objects class 8, on 626 it is 4 and 1.

    Validated by requiring two classes to match exactly: one whose id set is precisely
    the clut blocks' ids, and one whose id set is precisely the igImages' `_pClut`
    values.  Returns `(offset, idCount, classes, block_class, object_class)` or None.
    """
    blocks = {r[2] for r in recs if r[1] == "clut"}
    objs = {d["clut"] for d in image_records(b)}
    nclut = sum(1 for r in recs if r[1] == "clut")
    if not blocks or not objs:
        return None
    for p in range(0x30, len(b) - 8):
        tb, cnt = struct.unpack_from("<II", b, p)
        if tb != 8 + 2 * cnt or cnt < len(blocks) or p + tb > len(b):
            continue
        cl = [struct.unpack_from("<H", b, p + 8 + 2 * i)[0] for i in range(cnt)]
        grp = {}
        for i, v in enumerate(cl):
            grp.setdefault(v, set()).add(i)
        kb = [k for k, v in grp.items() if v == blocks]
        ko = [k for k, v in grp.items() if v == objs]
        if kb and ko and len(grp[ko[0]]) == nclut:
            return p, cnt, cl, kb[0], ko[0]
    return None


def resolve_palettes(b, recs):
    """`{image block id: palette block id}` -- the texture -> palette link (#476).

    An igImage's `_pClut` is an **id in the pack's id space, not a block id**: the space
    interleaves the pack's objects and their memory blocks, and the class table says
    which each id is.  So the rank of `_pClut` among the ids of its class is that
    object's position in the loader's creation order -- which is **file order** -- hence
    the r-th such id names the r-th igClut record, and that record's `_pData` is the
    palette block.  Verified pixel-for-pixel on all 26 textures of NDMW.AFS 625.

    Returns None when the pack has no validated class table.
    """
    t = class_table(b, recs)
    if t is None:
        return None
    _p, _cnt, cl, _kb, ko = t
    cluts = sorted([r for r in recs if r[1] == "clut"], key=lambda r: r[0])
    rank = {i: k for k, i in enumerate(sorted(i for i, v in enumerate(cl) if v == ko))}
    out = {}
    for d in image_records(b):
        k = rank.get(d["clut"])
        if k is None or k >= len(cluts):
            return None
        out[d["image"]] = cluts[k][2]
    return out


def decode_rgba(b, layout, image_id, clut_id):
    """Decode one texture to `(w, h, RGBA bytes)`; the grid starts one byte into its block."""
    # A pad row reuses the id of the block it follows, so take the first (block) row.
    off = {}
    for i, kind, size, o, w, h in layout:
        if kind != "pad":
            off.setdefault(i, (kind, size, o, w, h))
    if image_id not in off or clut_id not in off:
        return None
    _k, gsz, goff, w, h = off[image_id]
    _k2, _csz, coff, _w, _h = off[clut_id]
    grid = b[goff + 1:goff + 1 + gsz]
    pal = b[coff:coff + 1024]
    if len(grid) < w * h:
        return None
    out = bytearray(w * h * 4)
    for y in range(h):
        for x in range(w):
            e = 4 * grid[(h - 1 - y) * w + x]
            o = (y * w + x) * 4
            out[o:o + 3] = pal[e + 1:e + 4]
            out[o + 3] = pal[e]
    return w, h, bytes(out)


def build_layout(b, recs, base=None, pads=None):
    info = header_layout(b, recs)
    if base is None:
        if info is None:
            raise SystemExit("the header does not describe this pack's pool "
                             "(multi-asset pack or incomplete parse); pass --base/--pads")
        base = info[0]
        if pads is None:
            pads = set(choose_pads(b, recs, base, info[1]))
    if pads is None:
        pads = set()
    c = base
    out = []
    for p, kind, i, size, w, h in recs:
        out.append((i, kind, size, c, w, h))
        c += size
        if i in pads:
            out.append((i, "pad", 4, c, 0, 0))
            c += 4
    return out, base, c


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file", nargs="?")
    ap.add_argument("--afs")
    ap.add_argument("--entry", type=int)
    ap.add_argument("--base", type=lambda s: int(s, 0))
    ap.add_argument("--pads", default="", help="ids each followed by a 4-byte pad")
    ap.add_argument("--dump", type=int, metavar="ID")
    ap.add_argument("--textures", action="store_true",
                    help="list each texture's name, size, image id and palette id")
    ap.add_argument("--decode", metavar="NAME",
                    help="write one texture's decoded RGBA to --out")
    ap.add_argument("--out", metavar="FILE")
    ap.add_argument("--tsv", metavar="FILE")
    args = ap.parse_args()
    pads = {int(x, 0) for x in args.pads.split(",") if x.strip()} if args.pads else None
    if args.file is None and args.afs is None:
        ap.error("give a pack file or --afs/--entry")

    b = read_pack(args)
    recs = find_records(b)
    if not recs:
        sys.exit("no clut/image sub-records found (not a texture pack?)")
    layout, base, end = build_layout(b, recs, args.base, pads)
    nclut = sum(1 for r in layout if r[1] == "clut")
    nimg = sum(1 for r in layout if r[1] == "img")
    print("%d blocks: %d clut + %d image%s" % (
        nclut + nimg, nclut, nimg,
        " + %d pads" % sum(1 for r in layout if r[1] == "pad")))
    print("pool 0x%06x .. 0x%06x   pack size 0x%06x" % (base, end, len(b)))
    if args.textures:
        pal = resolve_palettes(b, recs)
        if pal is None:
            print("  (no validated id->class table: pairing only the grid)")
        for d in image_records(b):
            print("  %-18s %4dx%-4d image id %-4d palette id %s" % (
                d["name"], d["w"], d["h"], d["image"],
                pal.get(d["image"]) if pal else "?"))
        return
    if args.decode:
        pal = resolve_palettes(b, recs)
        d = [x for x in image_records(b) if x["name"] == args.decode]
        if not d:
            sys.exit("no texture named %r" % args.decode)
        d = d[0]
        cid = pal.get(d["image"]) if pal else None
        if cid is None:
            sys.exit("cannot resolve the palette for %r" % args.decode)
        w, h, px = decode_rgba(b, layout, d["image"], cid)
        open(args.out, "wb").write(px)
        print("wrote %s: %s %dx%d RGBA (%d bytes)" % (args.out, d["name"], w, h, len(px)))
        return
    if args.dump is not None:
        for i, kind, size, off, w, h in layout:
            if i == args.dump:
                data = b[off:off + size]
                if kind == "img":
                    # the grid data follows a one-byte block prefix
                    data = b[off + 1:off + 1 + size]
                if args.out:
                    open(args.out, "wb").write(data)
                    print("wrote %d bytes of %s id %d to %s" % (len(data), kind, i, args.out))
                else:
                    print("%s id %d at 0x%06x (%d bytes) %s" % (kind, i, off, size, data[:16].hex()))
                return
        sys.exit("no block with id %d" % args.dump)
    for i, kind, size, off, w, h in layout:
        extra = "%dx%d" % (w, h) if kind == "img" else ("%d entries" % w if kind == "clut" else "")
        print("  id %-4d %-5s 0x%06x  %-6d  %s" % (i, kind, off, size, extra))
    if args.tsv:
        with open(args.tsv, "w") as f:
            f.write("id\tkind\tsize\toffset\tw\th\n")
            for i, kind, size, off, w, h in layout:
                f.write("%d\t%s\t%d\t0x%06x\t%d\t%d\n" % (i, kind, size, off, w, h))
        print("wrote %s" % args.tsv)


if __name__ == "__main__":
    main()
