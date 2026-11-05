#!/usr/bin/env python3
"""igb_models.py — extract model geometry from a stage's model pack, offline.

No running game, no RAM dump and no load replay: a model-pack's own ids address its pool.

The chain (findings #455, #457/#458, #477, #478):

    igGeometryAttr1_5   slot 4 (+0x0c) _vertexArray  -> an igObjectRef id
                        slot 5 (+0x10) _indexArray   -> 0 (NULL; there is no index buffer)
                        slot 6 (+0x14) _primType     -> 3 list / 4 strip
                        slot 7 (+0x18) _numPrims
                        slot 13 (+0x30) _stripLengths -> igPrimLengthArray1_1
      (slot k sits at offset 4*(k-1))

    igVertexArray1_1    slot 3 (+0x08) _vdata  -> a memory block listing this array's streams
                        slot 4 (+0x0c) _numVerts
    igPrimLengthArray1_1 slot 3 (+0x08) _vdata -> the u32 primitive lengths
                        slot 4 (+0x0c) the count

A stream block's `_memSize` is its content size exactly -- `12*_numVerts` for the positions,
`8*_numVerts` for the UVs -- and its offset is the pool's, where every block is 4-byte aligned
(finding #478), so a stream lands on its own block start and no search is needed:

    offset(id) = pool_start + sum(align4(_memSize) of every id below it)

Verified against the live extraction: 432 of the 446 located live vertex buffers sit exactly on
the block start this predicts, and a decoded model is byte-identical to the live OBJ.

Usage
-----
  igb_models.py --afs NDMW.AFS --entry 621 --list
  igb_models.py --afs NDMW.AFS --entry 621 --out-dir geom/ [--limit N]
  igb_models.py --afs NDMW.AFS --entry 621 --obj 13842 --out one.obj
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import igb_pool  # noqa: E402


def triples_from(prim_type, num_prims, num_verts, lengths):
    """Triangles for the two primitive modes; mirrors tools/extract_live_models.py."""
    if prim_type == 3:
        if num_verts < 3 * num_prims:
            return None, "list: numVerts=%d < 3*numPrims=%d" % (num_verts, 3 * num_prims)
        return [(3 * i, 3 * i + 1, 3 * i + 2) for i in range(num_prims)], None
    if not lengths:
        return None, "strip: no primitive lengths"
    if sum(lengths) != num_verts:
        return None, "sum(primLengths)=%d != numVerts=%d" % (sum(lengths), num_verts)
    tris, off = [], 0
    for L in lengths:
        if L < 3:
            return None, "degenerate primitive length %d" % L
        for k in range(L - 2):
            # A strip alternates winding -- triangle k is (k, k+1, k+2) for even k and
            # (k+1, k, k+2) for odd k -- so every triangle keeps the same facing.  The old form
            # emitted (k, k+1, k+2) for both, so half of every strip was wound the other way;
            # that was invisible while nothing culled and it is what makes back-face culling
            # possible now (finding #575).  This mirrors src/mesh.c's `dw4_mesh_tris`.
            if k % 2 == 0:
                tris.append((off + k, off + k + 1, off + k + 2))
            else:
                tris.append((off + k + 1, off + k, off + k + 2))
        off += L
    return tris, None


def u32(b, off):
    return struct.unpack_from("<I", b, off)[0]


def field_off(refl, cls, name):
    """The record-relative offset of `cls`.`name`, from data/reflection.json.

    reflection.json gives each class only the fields it *declares*, at absolute offsets
    within the object, and does not record the base link -- so a base class like
    `igGeometryAttr` must be named as the declarer, which is why the callers below pass
    the declaring class rather than the concrete one."""
    for f in (refl.get(cls) or {}).get("fields", []):
        if f["name"] == name:
            return f["offset"]
    return None


def read_lengths(P, b, rec, ld_off, ns_off, nverts):
    """The u32 primitive lengths of an `igPrimLengthArray1_1`, validated by the format's own
    arithmetic: they must consume every vertex (`sum == _numVerts`)."""
    if rec is None or rec["class"] != "igPrimLengthArray1_1":
        return []
    ld, ns = u32(b, rec["off"] + ld_off), u32(b, rec["off"] + ns_off)
    if ld not in P["off_of"] or not (0 < ns < (1 << 20)):
        return []
    o = P["off_of"][ld]
    if o + 4 * ns > len(b):
        return []
    vals = [u32(b, o + 4 * i) for i in range(ns)]
    return vals if sum(vals) == nverts else []


def read_names(P, refl, geom_ids):
    """`{geometry attr id: model name}` -- the offline replacement for the live `M_*Shape` walk.

    A shape is an `igGeometry` record: its `_name` (+0x08) is the DCC part name (`pCylinderShape3`,
    `M_BK17v1_barrelmShape`, ...), and its **attr list is ordinal 8** (the live finding #458 link).
    That `igAttrList`'s array (+0x10) is a block of attribute ids; the ones that are
    `igGeometryAttr1_5` records are the shape's geometry, so they take its name.  The list's count
    (+0x08) must equal the array block's u32 count -- the self-check.  An empty name (105 of the 549
    shapes here) or an empty list names nothing, so those attributes stay unnamed rather than
    inheriting a neighbour's name.

    **Ordinals, not offsets**: the container reports each value's slot number, and a record's byte
    offsets shift with a variable-length value (a long `_name` pushes everything after it), so the
    list is found by slot number.  A value whose target is an `igAttrList` is accepted as a fallback,
    which is what makes this self-validating.
    """
    b = P["b"]
    s2, cnt, obj_of_id = P["s2"], P["cnt"], P["obj_of_id"]
    off_to_id = {}
    for i in range(cnt):
        k = obj_of_id[i]
        if k is not None and k < len(s2):
            off_to_id.setdefault(s2[k]["off"], i)

    def target(v):
        if not isinstance(v, int) or v == 0xFFFFFFFF or not (0 <= v < cnt):
            return None
        k = obj_of_id[v]
        return s2[k] if k is not None and k < len(s2) else None

    names = {}
    for r in s2:
        if r["class"] != "igGeometry":
            continue
        vals = {n: v for n, v, _t in r["fields"]}
        name = (vals.get("_name") or vals.get("slot2") or "").rstrip("\x00")
        al = target(vals.get("slot8"))
        if al is None or al["class"] != "igAttrList":
            al = next((t for t in (target(v) for v in vals.values())
                       if t is not None and t["class"] == "igAttrList"), None)
        if al is None or not name:
            continue
        arr = u32(b, al["off"] + 0x10)
        if arr not in P["off_of"]:
            continue
        o, n = P["off_of"][arr], P["size_of"][arr]
        if n // 4 != u32(b, al["off"] + 0x08):
            continue                       # the list's own count disagrees with its array
        for k in range(n // 4):
            gid = u32(b, o + 4 * k)
            if gid in geom_ids:
                names[gid] = name
    return names


def read_geometry(P, refl):
    """Yield one dict per igGeometryAttr1_5 record: its ids, counts and mode.

    The field offsets come from data/reflection.json -- `igGeometryAttr` (`_vertexArray`
    +0x0c, `_indexArray` +0x10, `_primType` +0x14, `_numPrims` +0x18), `igVertexArray`
    (`_vdata` +0x08, `_numVerts` +0x0c), `igPrimLengthArray` (`_lengthData` +0x08,
    `_numStrips` +0x0c) and igGeometryAttr1_5's own `_stripLengths` (+0x30).

    Every value is then validated with the format's own arithmetic, so an offset that did not
    hold would show up as a skipped attribute rather than as wrong geometry:

      * the vertex array must be an `igVertexArray1_1` whose `_vdata` block lists a stream of
        exactly `12*_numVerts` bytes (finding #477: `_memSize` IS the stream's content size);
      * the primitive lengths must sum to `_numVerts`.

    Each row also carries the model's `name` where the pack names it (see `read_names`).

    (An earlier version of this function *searched* for the fields instead of reading them,
    because the ordinal the container reports does not map straight to an offset; the
    reflection settles it, and with the offsets fixed all 549 attributes of entry 621
    resolve.)
    """
    import igb_ids
    b = P["b"]
    _d, s1, s2, _ch = igb_ids.sections(b, refl)
    _p, cnt, obj_of_id = igb_ids.find_table(b, s1, s2)
    P["cnt"], P["s2"], P["obj_of_id"] = cnt, s2, obj_of_id

    va_off = field_off(refl, "igGeometryAttr", "_vertexArray")
    pt_off = field_off(refl, "igGeometryAttr", "_primType")
    np_off = field_off(refl, "igGeometryAttr", "_numPrims")
    sl_off = field_off(refl, "igGeometryAttr1_5", "_stripLengths")
    vd_off = field_off(refl, "igVertexArray", "_vdata")
    nv_off = field_off(refl, "igVertexArray", "_numVerts")
    ld_off = field_off(refl, "igPrimLengthArray", "_lengthData")
    ns_off = field_off(refl, "igPrimLengthArray", "_numStrips")

    def rec_of(v):
        """The section-2 record an object-ref id names, or None."""
        if v is None or v == 0xFFFFFFFF or not (0 <= v < cnt):
            return None
        k = obj_of_id[v]
        return s2[k] if k is not None and k < len(s2) else None

    off_to_id = {}
    for i in range(cnt):
        k = obj_of_id[i]
        if k is not None and k < len(s2):
            off_to_id.setdefault(s2[k]["off"], i)

    out = []
    for r in s2:
        if r["class"] != "igGeometryAttr1_5":
            continue
        o = r["off"]
        pt = u32(b, o + pt_off)
        if pt not in (3, 4):
            continue
        va, npr, pl = u32(b, o + va_off), u32(b, o + np_off), u32(b, o + sl_off)
        vdata = nverts = None
        vrec = rec_of(va)
        if vrec is not None and vrec["class"] == "igVertexArray1_1":
            vd = u32(b, vrec["off"] + vd_off)
            nv = u32(b, vrec["off"] + nv_off)
            if any(size == 12 * nv for _i, _o, size in stream_list(P, vd)):
                vdata, nverts = vd, nv
        lengths = read_lengths(P, b, rec_of(pl), ld_off, ns_off, nverts) if nverts else []
        out.append(dict(rec_off=o, id=off_to_id.get(o), vertex_array=va, prim_type=pt,
                        num_prims=npr, vdata=vdata, num_verts=nverts, lengths=lengths,
                        name=None))
    names = read_names(P, refl, {g["id"] for g in out if g["id"] is not None})
    for g in out:
        g["name"] = names.get(g["id"])
        yield g


def stream_list(P, vdata):
    """The ids listed in a `_vdata` block, resolved to `(id, offset, size)`."""
    b = P["b"]
    if vdata is None or vdata not in P["off_of"]:
        return []
    o, n = P["off_of"][vdata], P["size_of"][vdata]
    out = []
    for k in range(n // 4):
        i = struct.unpack_from("<I", b, o + 4 * k)[0]
        if i == 0xFFFFFFFF or i not in P["off_of"]:
            continue
        out.append((i, P["off_of"][i], P["size_of"][i]))
    return out


def streams(P, vdata):
    return stream_list(P, vdata)


def extract(P, g):
    """`(verts, uvs, tris)` for one geometry record, or `(None, reason)`."""
    if not g["num_verts"]:
        return None, "no _numVerts"
    n = g["num_verts"]
    pos = uv = None
    for _i, off, size in streams(P, g["vdata"]):
        if size == 12 * n and pos is None:
            pos = off
        elif size == 8 * n and uv is None:
            uv = off
    if pos is None:
        return None, "no stream of 12*%d bytes" % n
    b = P["b"]
    verts = [struct.unpack_from("<3f", b, pos + 12 * i) for i in range(n)]
    uvs = ([struct.unpack_from("<2f", b, uv + 8 * i) for i in range(n)] if uv else [])
    tris, why = triples_from(g["prim_type"], g["num_prims"], n, g["lengths"])
    if tris is None:
        return None, why
    return (verts, uvs, tris), None


def obj_basename(g):
    """`model_<name>.obj` when the pack names the shape, else `model_<vertexArrayId>.obj`.
    A name goes into a filename, so anything outside `[A-Za-z0-9._-]` becomes `_`."""
    if not g.get("name"):
        return "model_%d.obj" % g["vertex_array"]
    safe = "".join(c if (c.isalnum() or c in "._-") else "_" for c in g["name"])
    return "model_%s.obj" % safe


def write_obj(path, verts, uvs, tris):
    with open(path, "w") as f:
        f.write("# DW4 model, extracted offline from the model pack\n")
        for v in verts:
            f.write("v %.6f %.6f %.6f\n" % v)
        for t in uvs:
            f.write("vt %.6f %.6f\n" % t)
        for a, c, d in tris:
            if uvs:
                f.write("f %d/%d %d/%d %d/%d\n" % (a + 1, a + 1, c + 1, c + 1, d + 1, d + 1))
            else:
                f.write("f %d %d %d\n" % (a + 1, c + 1, d + 1))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file", nargs="?", default="")
    ap.add_argument("--afs")
    ap.add_argument("--entry", type=int)
    ap.add_argument("--blob", help="file offset of the pack, when not using --afs")
    ap.add_argument("--reflection", default=os.path.join(HERE, "..", "data", "reflection.json"))
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--tsv", action="store_true",
                    help="one machine-readable row per geometry attribute (the cross-check)")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--obj", type=int, help="extract the model whose _vertexArray is this id")
    ap.add_argument("--out")
    ap.add_argument("--out-dir")
    args = ap.parse_args()

    blob = args.blob
    if args.afs:
        data = open(args.afs, "rb").read()
        off, size = struct.unpack_from("<II", data, 8 + 8 * args.entry)
        blob = hex(off)
    elif not args.file:
        ap.error("give a pack file, --afs/--entry, or --blob")

    import igb_ids
    refl = igb_ids.igb_inst.load_reflection(args.reflection)
    P = igb_pool.load(args.file or args.afs, blob, refl)
    if P["aligned"] == P["poolsz"]:
        print("pool @+0x%x, %d bytes; %d blocks, exact after 4-byte alignment"
              % (P["pool"], P["poolsz"], len(P["off_of"])))
    else:
        print("pool @+0x%x, %d bytes; %d blocks, short by %d"
              % (P["pool"], P["poolsz"], len(P["off_of"]), P["poolsz"] - P["aligned"]))

    geoms = list(read_geometry(P, refl))
    print("geometry attributes: %d" % len(geoms))

    if args.tsv:
        for g in geoms:
            ids = [s[0] for s in streams(P, g["vdata"])]
            print("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s"
                  % (g["vertex_array"], g["prim_type"], g["num_prims"],
                     g["num_verts"] or 0, g["vdata"] or 0, len(g["lengths"]),
                     ",".join(str(i) for i in ids), g.get("name") or ""))
        return 0

    if args.list:
        for k, g in enumerate(geoms[:args.limit or 40]):
            print("  %3d  vertexArray id %-7s primType %s numPrims %-5s numVerts %-5s streams %s"
                  % (k, g["vertex_array"], g["prim_type"], g["num_prims"], g["num_verts"],
                     [s[0] for s in streams(P, g["vdata"])]))
        return 0

    todo = geoms
    if args.obj is not None:
        todo = [g for g in geoms if g["vertex_array"] == args.obj]
        if not todo:
            sys.exit("no geometry attribute with _vertexArray id %d" % args.obj)
    if args.limit:
        todo = todo[:args.limit]

    ok = bad = 0
    for k, g in enumerate(todo):
        got, why = extract(P, g)
        if got is None:
            bad += 1
            print("  %3d  vertexArray %-7s SKIP (%s)" % (k, g["vertex_array"], why))
            continue
        verts, uvs, tris = got
        ok += 1
        if args.out:
            write_obj(args.out, verts, uvs, tris)
            print("  wrote %s: %d verts, %d uvs, %d tris (vertexArray id %s)"
                  % (args.out, len(verts), len(uvs), len(tris), g["vertex_array"]))
            return 0
        if args.out_dir:
            os.makedirs(args.out_dir, exist_ok=True)
            p = os.path.join(args.out_dir, obj_basename(g))
            write_obj(p, verts, uvs, tris)
        else:
            print("  %3d  vertexArray %-7s %d verts, %d uvs, %d tris"
                  % (k, g["vertex_array"], len(verts), len(uvs), len(tris)))
    print("extracted %d, skipped %d%s" % (ok, bad, (" -> " + args.out_dir) if args.out_dir else ""))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
