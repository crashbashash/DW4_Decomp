#!/usr/bin/env python3
"""capture_scene.py — where a stage's models actually sit, from a live EE RAM dump.

This closes the two gaps the pack cannot answer: which geometry a node draws
and, with the model's own attr list in hand, what it is called.  Both are **load-time assignments**,
so they only exist in RAM — and a saved dump is as live as a paused emulator, so no emulator is
needed to read it:

    igGeometry ("M_*Shape", vtable 0x00528e70)   826 of them in a loaded stage
      +0x08  name pointer        the DCC part name
      +0x10  parent list         the node chain -- igTransform objects, whose `_m` is at +32
      +0x20  igAttrList          {_count +0x08, _array +0x10}; the entries whose vtable is
                                 the geometry attr (0x005238c0) are the mesh this node draws

Emitted as one row per node: the composed world matrix, the model name, and the geometry attribute
addresses it draws, so the port's renderer can place real geometry:

    name<TAB>m0 m1 ... m15<TAB>attr-addresses (comma)

The *name* is only a DCC label and is neither unique nor complete: a pack holds 35 meshes
named `polySurfaceShape1`, and the largest environment meshes carry no name at all, so a name
join over-draws and drops the stage shell.  `--pack` closes that by matching each live
geometry attribute to the pack mesh with the *same vertex buffer* (the loader copies the pack
geometry byte-for-byte), and writing the pack attribute's id as a fifth column.  That id is
exactly `dw4_scene_mesh.attr_id` in the port, so the renderer can join on identity, not a label.

Usage
-----
  capture_scene.py --from <ee-dump>.bin --tsv /tmp/scene.tsv [--limit N]
  # with the stage's model pack, so the fifth column carries pack identity
  capture_scene.py --from dump.bin --pack /path/NDMW.AFS:614 --tsv /tmp/scene.tsv
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

VT_SHAPE = 0x00528E70      # igGeometry
VT_GEOM = 0x005238C0       # igGeometryAttr1_5
VT_ATTRLIST = 0x00524420   # igAttrList
LO, HI = 0x00100000, 0x02000000


class Ram:
    def __init__(self, blob, lo=LO):
        self.b, self.lo = blob, lo

    def ok(self, a, n=1):
        return self.lo <= a and a + n <= self.lo + len(self.b)

    def u32(self, a):
        return struct.unpack_from("<I", self.b, a - self.lo)[0] if self.ok(a, 4) else 0

    def ptr(self, a):
        v = self.u32(a)
        return v if LO < v < HI else 0

    def string(self, p, n=64):
        if not self.ok(p, n):
            return ""
        raw = self.b[p - self.lo:p - self.lo + n]
        return raw.split(b"\x00")[0].decode("latin-1")

    def mat(self, a):
        if not self.ok(a, 64):
            return None
        return struct.unpack_from("<16f", self.b, a - self.lo)


def scan(ram, vtable):
    """Every address in RAM whose first word is `vtable` (objects are 8-byte aligned)."""
    out = []
    for a in range(LO, HI - 4, 4):
        if ram.ok(a, 4) and ram.u32(a) == vtable:
            out.append(a)
    return out


def compose(child, parent):
    """child * parent, both row-major 4x4 (the layout `_m` is stored in)."""
    out = [0.0] * 16
    for i in range(4):
        for j in range(4):
            out[4 * i + j] = sum(child[4 * i + k] * parent[4 * k + j] for k in range(4))
    return out


def plausible(m):
    """An affine transform: last row (0,0,0,1) and orthonormal rotation rows (unit, orthogonal)."""
    if not m or any(v != v or abs(v) > 1e12 for v in m):        # NaN / absurd
        return False
    if abs(m[3]) > 1e-3 or abs(m[7]) > 1e-3 or abs(m[11]) > 1e-3 or abs(m[15] - 1.0) > 1e-3:
        return False
    rows = [m[0:3], m[4:7], m[8:11]]
    for r in rows:
        n = sum(v * v for v in r) ** 0.5
        if not 0.5 < n < 2.0:                                   # a scale is allowed, not a collapse
            return False
    for i in range(3):
        for j in range(i + 1, 3):
            d = sum(rows[i][k] * rows[j][k] for k in range(3))
            if abs(d) > 0.05:
                return False
    return True


def parent_of(ram, node):
    """The first entry of a node's `_parentList` (+16): the list's array of node pointers."""
    lst = ram.ptr(node + 16)
    if not lst:
        return 0
    arr = ram.ptr(lst + 16)
    if not arr:
        arr = ram.ptr(lst + 8)
    return ram.ptr(arr) if arr else 0


def placement(ram, node):
    """The world matrix: walk up the parent chain, composing each igTransform's `_m` (+32).

    Only plausible affine matrices are used, which is also the check that the offsets are right --
    a wrong field reads as zeros, NaNs or garbage and is dropped rather than multiplied in."""
    total, seen, node = None, 0, node
    while node and seen < 64:
        m = ram.mat(node + 32)
        if plausible(m):
            total = m if total is None else compose(total, m)
        node = parent_of(ram, node)
        seen += 1
    return total


def attrs_of(ram, shape):
    """The geometry-attribute addresses a shape's +0x20 igAttrList holds."""
    lst = ram.ptr(shape + 0x20)
    out = []
    if not lst or ram.u32(lst) != VT_ATTRLIST:
        return out
    count = ram.u32(lst + 8)
    arr = ram.ptr(lst + 16)
    if not arr or count > 4096:
        return out
    for i in range(count):
        a = ram.ptr(arr + 4 * i)
        if a and ram.u32(a) == VT_GEOM:
            out.append(a)
    return out


def load_pack_map(afs, entry, decomp):
    """Vextex-buffer tuple -> pack geometry-attribute id, for one model pack.

    The port's `dw4_scene_mesh.attr_id` is the pack's `igGeometryAttr1_5` object id, so this is
    the identity the renderer joins on.  Identical vertex buffers (a reused primitive) collapse
    to the same key, which is harmless: the geometry is the same.
    """
    sys.path.insert(0, os.path.join(decomp, "scripts"))
    import igb_ids
    import igb_models
    import igb_pool
    refl = igb_ids.igb_inst.load_reflection(os.path.join(decomp, "data", "reflection.json"))
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * entry:12 + 8 * entry], "little")
    P = igb_pool.load(afs, hex(off), refl)
    m = {}
    for g in igb_models.read_geometry(P, refl):
        got, _why = igb_models.extract(P, g)
        if got is None or g.get("id") is None:
            continue
        key = tuple(got[0])
        if key not in m:
            m[key] = g["id"]
    return m


def pack_ids_of(el, attrs, packmap):
    """The pack attribute id for each live geometry attr, or -1 when it does not resolve."""
    ids = []
    for a in attrs:
        g = el.read_geom(a)
        if not g:
            ids.append(-1)
            continue
        try:
            verts, _tris, _lengths, _normals, _uvs = el.extract(g)
        except Exception:
            ids.append(-1)
            continue
        ids.append(packmap.get(tuple(verts), -1))
    return ids


def attr_pack_map(blob, pack, decomp):
    """live geometry-attribute address -> pack attribute id, for one dump + model pack.

    This is the same content match `--pack` does (the loader copies a pack mesh's vertex buffer
    byte-for-byte), exposed so a caller that already knows a live attr address -- e.g. the
    texture map -- can name its pack identity without re-walking the scene.
    """
    ram = Ram(blob)
    afs, entry = pack.rsplit(":", 1)
    import extract_live_models as el_mod
    el_mod._RAM = blob
    packmap = load_pack_map(afs, int(entry, 0), decomp)
    out = {}
    for s in scan(ram, VT_SHAPE):
        attrs = attrs_of(ram, s)
        for a, pid in zip(attrs, pack_ids_of(el_mod, attrs, packmap)):
            out[a] = pid
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="src", required=True, help="an EE RAM dump")
    ap.add_argument("--tsv", required=True)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--pack", metavar="AFS:ENTRY",
                    help="a stage model pack, to write each attr's pack id in a fifth column")
    ap.add_argument("--decomp", default=os.path.join(os.path.dirname(HERE)),
                    help="the decompilation checkout (its scripts/refl are used for --pack)")
    ap.add_argument("--keep-unplaced", action="store_true",
                    help="emit identity for a node with no plausible transform instead of dropping it"
                         " (the stage's world-space environment meshes live on such nodes)")
    ap.add_argument("--textures", action="store_true",
                    help="add a sixth column: the mesh's live texture name(s) (texture_map.py),"
                         " from the beTextureCtrlAttr material attr set")
    args = ap.parse_args()

    blob = open(args.src, "rb").read()
    ram = Ram(blob)
    shapes = scan(ram, VT_SHAPE)

    packmap = None
    el = None
    tm = None
    if args.pack:
        afs, entry = args.pack.rsplit(":", 1)
        import extract_live_models as el_mod
        el_mod._RAM = blob                      # the same dump, so the chain resolves offline
        packmap = load_pack_map(afs, int(entry, 0), args.decomp)
        el = el_mod
        print("pack %s: %d distinct vertex buffer(s)" % (args.pack, len(packmap)))
    if args.textures:
        import texture_map
        tm = texture_map.TextureMap(blob)
        print("texture map: %d geometry attr(s) carry a texture" % len(tm.attr_textures))
    print("igGeometry objects: %d" % len(shapes))
    rows = []
    no_attr = no_name = unplaced = 0

    IDENT = [1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 1.0]
    for s in shapes:
        name = ram.string(ram.ptr(s + 8))
        attrs = attrs_of(ram, s)
        if not attrs:
            no_attr += 1
        if not name:
            no_name += 1
        m = placement(ram, s)
        if m is None:
            unplaced += 1
            if not args.keep_unplaced:
                continue
            # No plausible transform in the node chain: the stage's static environment is authored
            # in world space and its node carries no usable matrix, so identity is the placement.
            m = IDENT
        ids = pack_ids_of(el, attrs, packmap) if packmap else []
        texs = sorted({t for a in attrs for t in (tm.attr_textures.get(a, ()) if tm else ())})
        rows.append((name, m, attrs, s, ids, texs))
    with open(args.tsv, "w") as f:
        for name, m, attrs, s, ids, texs in rows:
            line = "%s\t%s\t%s\t0x%08x\t%s" % (
                name or "-", " ".join("%.6f" % v for v in m),
                ",".join("0x%08x" % a for a in attrs), s,
                ",".join(str(i) for i in ids))
            if args.textures:
                line += "\t" + ",".join(texs)
            f.write(line + "\n")
    ntex = sum(1 for r in rows if r[5])
    print("wrote %s: %d node(s); %d without a geometry attr, %d without a name, %d unplaced%s%s"
          % (args.tsv, len(rows), no_attr, no_name, unplaced,
             " (kept as identity)" if args.keep_unplaced else " (dropped)",
             ", %d with a texture" % ntex if args.textures else ""))
    if args.list:
        for name, m, attrs, s, _ids, _texs in rows[:args.limit or 12]:
            print("  %-26s at (%8.2f, %8.2f, %8.2f)  %d attr(s)"
                  % (name or "-", m[12], m[13], m[14], len(attrs)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
