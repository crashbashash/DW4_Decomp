#!/usr/bin/env python3
"""Extract model geometry from a *paused* running DW4 (PINE).

Recovered live-object chain:

    igGeometryAttr1_5   vtable 0x005238c0   (concrete igGeometryAttr)
      +0x0c  _vertexArray   -> igVertexArray object (vtable 0x00525190)
      +0x10  _indexArray    -> igIndexArray object or 0 (NULL)
      +0x14  _primType      (4 = triangle strip, 3 = triangle list)
      +0x18  _numPrims      == count of the prim-length array
      +0x30  _primLengths   -> igPrimLengthArray1_1 (vtable 0x00526590)

    igVertexArray object
      +0x08  _vdata      -> a {positions, normals} PAIR of heap pointers, not a {start,end}
                            descriptor.  [0] positions, 12*n bytes; [1] normals, 12*n bytes, or 0
                            for the ~80 % of meshes that ship none (UI/2D).
      +0x0c  _numVerts

    igPrimLengthArray1_1 object
      +0x08  _vdata      -> a *direct* pointer to the u32 lengths (no descriptor)
      +0x0c  _count

**There is no index array on the shipped models.**  The strip lengths consume
the vertex buffer *sequentially*: primitive i uses vertices
[off, off+L_i), off += L_i, so a primitive of length L is a strip of L-2
triangles.  (sum(primLengths) == _numVerts, which is the self-check this tool
asserts.)

The **UV** stream has no field pointing at it: it is the 8-byte {u,v} pair per vertex that follows
the last 12-byte stream in the loader's packed pool, at
`align8((normals or positions) + 12*numVerts)` (a 4-byte tag, then 8-byte alignment).  Confirmed
geometrically, not by field name (a cylinder's u tracks atan2(z,x) at corr 0.998).  Both normals and
UVs are written into the OBJ as `vn`/`vt`.

Usage:
    python3 extract_live_models.py --list
    python3 extract_live_models.py --out-dir <out-dir> --limit 20
    python3 extract_live_models.py --addr 0x1260d88 --out <out-dir>/barrel.obj
    # offline, from a paused-game EE-RAM dump (no emulator):
    python3 extract_live_models.py --from <ee-dump>.bin --out-dir /tmp/geom
"""
import argparse
import json
import os
import struct
import subprocess
import sys


def host_command(service):
    """The host probe's command line for a live read, or None. The probe lives outside the
    repository: point DW4_HOST_TOOLS at its folder. A saved RAM dump (`--from`) needs none of it."""
    tools = os.environ.get("DW4_HOST_TOOLS")
    probe = os.path.join(tools, "host_probe.py") if tools else None
    return [sys.executable, probe, service] if probe and os.path.isfile(probe) else None


def live():
    if PINE is None:
        sys.exit("a live read needs the host probe, which is kept outside the repository: set "
                 "DW4_HOST_TOOLS to its folder, or read a saved RAM dump with --from")
    return PINE


PINE = host_command("memory")
VT_GEOM = 0x005238C0      # igGeometryAttr1_5
VT_VERTEXARRAY = 0x00525190
VT_PRIMLEN = 0x00526590

# Offline mode: with --from the whole RAM is read once and every accessor resolves against it,
# so extraction is reproducible from a single captured dump (the game must have been *paused*).
_RAM = None
_RAM_LO = 0x00100000


def pine_read(addr, size):
    if _RAM is not None:
        off = addr - _RAM_LO
        if off < 0 or off + size > len(_RAM):
            return b""
        return _RAM[off:off + size]
    r = subprocess.run([*live(), "read", hex(addr), "--size", str(size), "--raw"],
                       capture_output=True, check=True)
    return r.stdout


def u32(buf, off):
    return struct.unpack_from("<I", buf, off)[0]


def align8(x):
    """Start of the buffer after one ending at x: a 4-byte tag, then 8-byte alignment."""
    return (x + 4 + 7) & ~7


def read_descriptor(addr):
    """Read the {positions, normals} pair `igVertexArray._vdata` points at.

    It is NOT a {start, end} descriptor: [0] is the positions block and [1] the normals block
    (0 when the mesh ships none).  Sizing always comes from `_numVerts`, never from [1]."""
    d = pine_read(addr, 8)
    if len(d) < 8:
        return None, None
    start, end = u32(d, 0), u32(d, 4)
    if not (0x00100000 < start < 0x02000000):
        return None, None
    return start, end


def find_objects(vtable, limit=2000):
    if _RAM is not None:
        pat = struct.pack("<I", vtable)
        out, start = [], 0
        while len(out) < limit:
            i = _RAM.find(pat, start)
            if i < 0:
                break
            if (_RAM_LO + i) % 4 == 0:
                out.append(_RAM_LO + i)
            start = i + 1
        return out
    r = subprocess.run([*live(), "find", hex(vtable), "--type", "u32",
                        "--region", "ee-ram", "--align", "4",
                        "--limit", str(limit), "--json"], capture_output=True, text=True, check=True)
    try:
        return [int(h, 16) for h in json.loads(r.stdout).get("hits", [])]
    except Exception:
        return []


def read_geom(addr):
    """Return a dict describing one igGeometryAttr1_5, or None if unloaded."""
    b = pine_read(addr, 0x38)
    if len(b) < 0x38 or u32(b, 0) != VT_GEOM:
        return None
    g = {"addr": addr, "vertexArray": u32(b, 12), "indexArray": u32(b, 16),
         "primType": u32(b, 20), "numPrims": u32(b, 24), "primLengths": u32(b, 48)}
    if not (0x00100000 < g["vertexArray"] < 0x02000000):
        return None                      # unloaded or freed slot (_primType 0)
    vb = pine_read(g["vertexArray"], 0x10)
    if len(vb) < 0x10:
        return None
    g["vdata"] = u32(vb, 8)
    g["numVerts"] = u32(vb, 12)
    if g["primType"] == 4:
        if not (0x00100000 < g["primLengths"] < 0x02000000):
            return None
        pb = pine_read(g["primLengths"], 0x10)
        if len(pb) < 0x10:
            return None
        g["plData"] = u32(pb, 8)
        g["plCount"] = u32(pb, 12)
    elif g["primType"] != 3:
        return None                      # 0 = empty, anything else undecoded
    return g


def extract(g):
    """Read vertices (+ strip lengths) and build (verts, tris, lengths).

    Two representations are shipped (self-checked, not guessed):
      _primType 4 == triangle strip  -- an igPrimLengthArray1_1 at +0x30 gives
          the strip lengths; vertices are consumed *sequentially* and a strip of
          length L is L-2 triangles.  sum(lengths) == numVerts.
      _primType 3 == triangle list   -- no prim array; _numPrims(+0x18) triangles
          read straight through the vertices in triples.  3*numPrims == numVerts.
    """
    start, _end = read_descriptor(g["vdata"])
    if start is None:
        raise ValueError("no vertex descriptor at 0x%08x" % g["vdata"])
    vbytes = pine_read(start, g["numVerts"] * 12)
    if len(vbytes) != g["numVerts"] * 12:
        raise ValueError("vertex read %d != numVerts*12 (%d)"
                         % (len(vbytes), g["numVerts"] * 12))
    verts = list(struct.iter_unpack("<3f", vbytes))
    normals, uvs = read_streams(g, start)

    if g["primType"] == 3:
        if len(verts) < 3 * g["numPrims"]:
            raise ValueError("list: numVerts=%d < 3*numPrims=%d"
                             % (len(verts), 3 * g["numPrims"]))
        if len(verts) != 3 * g["numPrims"]:
            # A handful of stale slots in the scratch region disagree by a few
            # vertices; they have no index array and no prim lengths, so the
            # extra vertices are unused.  Draw the declared triangles and say so.
            print("  WARN 0x%08x list: numVerts=%d != 3*numPrims=%d (using %d tris)"
                  % (g["addr"], len(verts), 3 * g["numPrims"], g["numPrims"]),
                  file=sys.stderr)
        return (verts, [(3 * i, 3 * i + 1, 3 * i + 2) for i in range(g["numPrims"])],
                [], normals, uvs)

    # The prim-length array's _vdata is a *direct* pointer to the lengths.
    pbytes = pine_read(g["plData"], g["plCount"] * 4)
    if len(pbytes) != g["plCount"] * 4:
        raise ValueError("prim-length read mismatch")
    lengths = [u32(pbytes, 4 * i) for i in range(g["plCount"])]

    if sum(lengths) != len(verts):
        raise ValueError("sum(primLengths)=%d != numVerts=%d" % (sum(lengths), len(verts)))

    tris, off = [], 0
    for L in lengths:
        if L < 3:
            raise ValueError("degenerate primitive length %d" % L)
        for k in range(L - 2):
            tris.append((off + k, off + k + 1, off + k + 2))
        off += L

    # Self-check on structured data, not a guess: the prim lengths must consume
    # the whole buffer, and every index must be in range.
    assert off == len(verts)
    assert all(0 <= i < len(verts) for t in tris for i in t)
    return verts, tris, lengths, normals, uvs


def read_streams(g, pos):
    """Read the optional normal block and the UV block that follows the positions.

    Layout in the shared buffer pool is [positions (12*nv)][tag+pad][normals (12*nv)][tag+pad]
    [uv (8*nv)].  `_vdata[1]` is the normals pointer and is **0 for the ~80 % of shipped meshes
    that carry no normals** (UI/text/2D: fonts, icons, planes, cylinders); for those the buffer
    right after the positions is the UV, not the normals.  The UV stream is therefore at
    align8(last 12-byte stream + 12*nv); each entry is an 8-byte {u,v} float pair.  Nothing in the
    object points at it -- it was pinned geometrically (a cylinder's u tracks atan2(z,x), 0.998).
    """
    pair = pine_read(g["vdata"], 8)
    nrm_ptr = u32(pair, 4) if len(pair) >= 8 else 0
    normals = None
    if nrm_ptr and 0x00100000 < nrm_ptr < 0x02000000:
        nb = pine_read(nrm_ptr, g["numVerts"] * 12)
        if len(nb) == g["numVerts"] * 12:
            normals = list(struct.iter_unpack("<3f", nb))
    uvs = None
    uv_ptr = align8((nrm_ptr or pos) + 12 * g["numVerts"])
    ub = pine_read(uv_ptr, g["numVerts"] * 8)
    if len(ub) == g["numVerts"] * 8:
        uvs = list(struct.iter_unpack("<2f", ub))
    return normals, uvs


def write_obj(path, verts, tris, name="model", comment="", normals=None, uvs=None):
    with open(path, "w") as f:
        f.write("# DW4 live model %s  (%d verts, %d tris%s)\n"
                % (name, len(verts), len(tris),
                   ", normals" if normals else ", no normals"))
        if comment:
            f.write("# %s\n" % comment)
        for x, y, z in verts:
            f.write("v %.6f %.6f %.6f\n" % (x, y, z))
        if uvs:
            for u, v in uvs:
                f.write("vt %.6f %.6f\n" % (u, v))
        if normals:
            for x, y, z in normals:
                f.write("vn %.6f %.6f %.6f\n" % (x, y, z))
        for a, b, c in tris:
            if uvs and normals:
                f.write("f %d/%d/%d %d/%d/%d %d/%d/%d\n"
                        % (a + 1, a + 1, a + 1, b + 1, b + 1, b + 1, c + 1, c + 1, c + 1))
            elif normals:
                f.write("f %d//%d %d//%d %d//%d\n"
                        % (a + 1, a + 1, b + 1, b + 1, c + 1, c + 1))
            elif uvs:
                f.write("f %d/%d %d/%d %d/%d\n"
                        % (a + 1, a + 1, b + 1, b + 1, c + 1, c + 1))
            else:
                f.write("f %d %d %d\n" % (a + 1, b + 1, c + 1))


def load_pack(spec):
    """spec = '<path-to-AFS>[:entryIndex]' -> (entry index, bytes)."""
    path, _, idx = spec.partition(":")
    idx = int(idx) if idx else 621
    with open(path, "rb") as f:
        f.seek(4)
        n = u32(f.read(4), 0)
        ent = [struct.unpack("<II", f.read(8)) for _ in range(n)]
        off, size = ent[idx]
        f.seek(off)
        return idx, f.read(size)


def pack_offset(blob, g, raw):
    """Offset of this model's vertex block inside the pack, or None.

    The geometry ships *uncompressed* in the stage's model pack (no stored
    offset points at it -- the loader reconstructs the pool), so a block is
    identified by its bytes.  This is a bridge to the offline reader, not a
    substitute for the load replay.
    """
    if blob is None:
        return None
    o = blob.find(raw[:48])
    return o if o >= 0 else None


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--list", action="store_true", help="list geometry attrs and sizes")
    ap.add_argument("--addr", help="extract one geometry attr address")
    ap.add_argument("--out", help="output .obj for --addr")
    ap.add_argument("--out-dir", help="extract every loaded model here")
    ap.add_argument("--limit", type=int, default=0, help="cap models extracted")
    ap.add_argument("--min-tris", type=int, default=1)
    ap.add_argument("--pack", metavar="AFS[:ENTRY]",
                    help="annotate each model with its offset in a stage model pack")
    ap.add_argument("--pack-tsv", help="write the (model, pack entry, pack offset, sizes) map")
    ap.add_argument("--from", dest="src", help="read a saved EE RAM dump instead of PINE")
    ap.add_argument("--lo", type=lambda s: int(s, 0), default=0x00100000,
                    help="EE RAM base of the dump (default 0x00100000)")
    args = ap.parse_args()

    global _RAM, _RAM_LO
    if args.src:
        _RAM = open(args.src, "rb").read()
        _RAM_LO = args.lo
        print("loaded %s (%.1f MB)" % (args.src, len(_RAM) / 1e6), file=sys.stderr)

    blob = None
    if args.pack:
        eidx, blob = load_pack(args.pack)
        print("pack %s entry %d: %d bytes" % (args.pack, eidx, len(blob)), file=sys.stderr)

    if args.addr:
        g = read_geom(int(args.addr, 16))
        if not g:
            sys.exit("no loaded igGeometryAttr1_5 at %s" % args.addr)
        verts, tris, lengths, normals, uvs = extract(g)
        print("0x%08x: primType=%d %d verts, %d prims, %d tris, normals=%s, uvs=%s"
              % (g["addr"], g["primType"], len(verts),
                 len(lengths) or g["numPrims"], len(tris),
                 "yes" if normals else "no", "yes" if uvs else "no"))
        if args.out:
            note = ""
            if blob is not None:
                raw = pine_read(read_descriptor(g["vdata"])[0], len(verts) * 12)
                po = pack_offset(blob, g, raw)
                note = "pack offset %s" % (hex(po) if po is not None else "not found")
                print(note)
            write_obj(args.out, verts, tris, hex(g["addr"]), note, normals, uvs)
            print("wrote", args.out)
        return

    attrs = find_objects(VT_GEOM)
    print("igGeometryAttr1_5 objects found:", len(attrs), file=sys.stderr)
    ok = fail = skip = miss = 0
    tsv = []
    if args.out_dir:
        os.makedirs(args.out_dir, exist_ok=True)
    for a in attrs:
        g = read_geom(a)
        if not g:
            skip += 1
            continue
        try:
            verts, tris, lengths, normals, uvs = extract(g)
        except Exception as e:
            print("  FAIL 0x%08x: %s" % (a, e), file=sys.stderr)
            fail += 1
            continue
        if len(tris) < args.min_tris:
            continue
        ok += 1
        po = None
        if blob is not None:
            raw = pine_read(read_descriptor(g["vdata"])[0], len(verts) * 12)
            po = pack_offset(blob, g, raw)
            if po is None:
                miss += 1
            tsv.append((hex(a), g["primType"], len(verts), len(lengths) or g["numPrims"],
                        len(tris), hex(po) if po is not None else "-", hex(g.get("primLengths") or 0)))
        line = "0x%08x  type=%d verts=%-6d prims=%-5d tris=%-6d plen=0x%08x" % (
            a, g["primType"], len(verts), len(lengths) or g["numPrims"], len(tris),
            g.get("primLengths") or 0)
        if po is not None:
            line += "  pack=0x%08x" % po
        if args.list or not args.out_dir:
            print(line)
        if args.out_dir:
            write_obj(os.path.join(args.out_dir, "model_%08x.obj" % a), verts, tris, hex(a),
                      "pack offset 0x%08x" % po if po is not None else "", normals, uvs)
        if args.limit and ok >= args.limit:
            break
    if args.pack_tsv and tsv:
        with open(args.pack_tsv, "w") as f:
            f.write("#liveAddr\tprimType\tnumVerts\tnumPrims\tnumTris\tpackOffset\tprimLengthsObject\n")
            for r in tsv:
                f.write("\t".join(str(x) for x in r) + "\n")
        print("wrote", args.pack_tsv)
    msg = "extracted=%d failed=%d unloaded=%d" % (ok, fail, skip)
    if blob is not None:
        msg += " pack-miss=%d" % miss
    print(msg, file=sys.stderr)


if __name__ == "__main__":
    main()
