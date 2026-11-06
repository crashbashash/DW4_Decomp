#!/usr/bin/env python3
"""live_skin.py — export a skinned character mesh (bind + posed) from a paused EE-RAM dump.

The engine's skinning data is **runtime only**: the model pack carries a 4-byte stub for
`igVertexArray1_1._blendWeights`, and the real weight/index arrays are allocated at load
.  This reads them from a paused game's dump, where they exist:

    igVertexArray1_1   vtable 0x00525190
      +0x08  _vdata          -> {positions, normals}; [0] is the positions block
      +0x0c  _numVerts
      +0x20  _blendWeights   f32 per vertex (runtime)
      +0x24  _blendIndices   u8 per vertex  (runtime)  -> a bone number
    igBlendMatrixSelect  vtable 0x0052a400   _blendMatrixIndices (+0x28) -> igIntList
        bone number -> matrix slot
    igBlendMatricesAttr  vtable 0x00524190   _matrixCache (+0x0c) count (+0x10)
        the matrix palette (64-byte igMatrix44f, row-major, translation in elements 12..14)

Skinning is single- or multi-bone: `v' = sum_i w_i * M[slots[bone_i]] * v`, with each `M`
already a skinning matrix (the inverse bind is baked in).  Measured: the Goblin Pass
capture's only skinned mesh is `ogre_skinShape` (pack `NDMW.AFS:614` id 5150, 1473 verts),
one bone per vertex with weight 1.0 and bone numbers 0..32; the bone map is
`[0,0,0,1,2,3,4,5,0,6,7,8,9,0,0,10,11,12,13,14,15,0,16,17,18,0,19,0,20,0,21,22,23]`.

**Measured open item:** no pointer links the mesh/select to *its*
`igBlendMatricesAttr` in the object graph, so the palette is chosen here by `--palette`
(an index into the non-empty pool in address order) rather than resolved.  The live pool
holds several 24-matrix palettes that differ only slightly; the default is the first.

Usage:
    python3 live_skin.py --from RAM.bin --list
    python3 live_skin.py --from RAM.bin --out posed.obj [--bind bind.obj] [--palette 0]
"""
import argparse
import os
import struct
import sys

VT_VERTEXARRAY = 0x00525190
VT_GEOMATTR = 0x005238C0
VT_BLENDSELECT = 0x0052A400
VT_BLENDMATS = 0x00524190
RAM_LO = 0x00100000


class Ram:
    def __init__(self, path=None):
        self.buf = open(path, "rb").read() if path else None

    def read(self, addr, size):
        if self.buf is None:
            return b""
        off = addr - RAM_LO
        if off < 0 or off + size > len(self.buf):
            return b""
        return self.buf[off:off + size]

    def u32(self, addr):
        b = self.read(addr, 4)
        return struct.unpack_from("<I", b, 0)[0] if b else 0

    def find(self, value):
        p = struct.pack("<I", value)
        out, i = [], 0
        while True:
            i = self.buf.find(p, i)
            if i < 0:
                return out
            out.append(RAM_LO + i)
            i += 1

    def objects(self, vtable):
        return [a for a in self.find(vtable) if a % 4 == 0]


def read_skinned(ram):
    """Every live igVertexArray1_1 that has both runtime blend arrays, with its data."""
    out = []
    for a in ram.objects(VT_VERTEXARRAY):
        nv = ram.u32(a + 0x0c)
        bw, bi, vd = ram.u32(a + 0x20), ram.u32(a + 0x24), ram.u32(a + 0x08)
        if not (nv and 0x100000 < bw < 0x2000000 and 0x100000 < bi < 0x2000000
                and 0x100000 < vd < 0x2000000):
            continue
        pos = ram.u32(vd)
        verts = [struct.unpack_from("<3f", ram.read(pos, nv * 12), 12 * i)
                 for i in range(nv)]
        weights = [struct.unpack_from("<f", ram.read(bw + 4 * i, 4), 0)[0] for i in range(nv)]
        indices = list(ram.read(bi, nv))
        out.append(dict(va=a, pos=pos, num_verts=nv, verts=verts,
                        weights=weights, indices=indices))
    return out


def geometry_for(ram, va):
    """The igGeometryAttr1_5 whose `_vertexArray` (+0xc) is `va`."""
    for a in ram.objects(VT_GEOMATTR):
        if ram.u32(a + 0x0c) == va:
            return dict(addr=a, prim_type=ram.u32(a + 0x14), num_prims=ram.u32(a + 0x18),
                        prim_lengths=ram.u32(a + 0x30))
    return None


def bone_maps(ram):
    """{select_addr: [slot per bone]} for every live igBlendMatrixSelect."""
    out = {}
    for a in ram.objects(VT_BLENDSELECT):
        lst = ram.u32(a + 0x28)
        if not (0x100000 < lst < 0x2000000):
            continue
        cnt, arr = ram.u32(lst + 0x08), ram.u32(lst + 0x10)
        if 0 < cnt < 256 and 0x100000 < arr < 0x2000000:
            out[a] = [ram.u32(arr + 4 * i) for i in range(cnt)]
    return out


def palettes(ram):
    """[(addr, count, [16-float matrices])] for the non-empty igBlendMatricesAttr pool."""
    out = []
    for a in ram.objects(VT_BLENDMATS):
        cache, cnt = ram.u32(a + 0x0c), ram.u32(a + 0x10)
        if 0 < cnt <= 256 and 0x100000 < cache < 0x2000000:
            mats = [struct.unpack_from("<16f", ram.read(cache + 64 * i, 64), 0)
                    for i in range(cnt)]
            out.append((a, cnt, mats))
    out.sort()
    return out


def load_lengths(ram, g, nv):
    if g["prim_type"] != 4 or not (0x100000 < g["prim_lengths"] < 0x2000000):
        return []
    cnt = ram.u32(g["prim_lengths"] + 0x0c)
    data = ram.u32(g["prim_lengths"] + 0x08)
    return [ram.u32(data + 4 * i) for i in range(cnt)] if cnt and data else []


def triangles(g, nv, lengths):
    if g["prim_type"] == 3:
        return [(3 * i, 3 * i + 1, 3 * i + 2) for i in range(g["num_prims"])]
    tris, off = [], 0
    for L in lengths:
        for k in range(L - 2):
            tris.append((off + k, off + k + 1, off + k + 2))
        off += L
    return tris


def skin(verts, weights, indices, slots, mat):
    out = []
    for i, v in enumerate(verts):
        bone = indices[i]
        m = mat[slots[bone] % len(mat)] if bone < len(slots) else mat[0]
        x, y, z = v
        out.append((x * m[0] + y * m[4] + z * m[8] + m[12],
                    x * m[1] + y * m[5] + z * m[9] + m[13],
                    x * m[2] + y * m[6] + z * m[10] + m[14]))
    return out


def write_obj(path, verts, tris, comment):
    with open(path, "w") as f:
        f.write("# %s\n" % comment)
        for v in verts:
            f.write("v %.6f %.6f %.6f\n" % v)
        for a, b, c in tris:
            f.write("f %d %d %d\n" % (a + 1, b + 1, c + 1))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="ram", required=True)
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--out")
    ap.add_argument("--bind")
    ap.add_argument("--palette", type=int, default=0, help="index into the palette pool")
    args = ap.parse_args()

    ram = Ram(args.ram)
    skins = read_skinned(ram)
    maps = bone_maps(ram)
    pals = palettes(ram)
    if args.list:
        print("skinned vertex arrays:")
        for s in skins:
            g = geometry_for(ram, s["va"])
            print("  VA %08x  %d verts  weights %s  bones %d..%d  geometry %s"
                  % (s["va"], s["num_verts"],
                     sorted({round(w, 2) for w in s["weights"]})[:4],
                     min(s["indices"]), max(s["indices"]),
                     hex(g["addr"]) if g else "-"))
        print("igBlendMatrixSelect bone maps:")
        for a, slots in maps.items():
            print("  %08x  %d bones -> slots %d..%d" % (a, len(slots), min(slots), max(slots)))
        print("igBlendMatricesAttr palettes (%d):" % len(pals))
        for k, (a, cnt, _m) in enumerate(pals):
            print("  [%d] %08x  %d matrices" % (k, a, cnt))
        return 0

    if not skins:
        sys.exit("no skinned vertex array in the dump")
    s = max(skins, key=lambda x: x["num_verts"])
    g = geometry_for(ram, s["va"])
    if g is None:
        sys.exit("no igGeometryAttr1_5 references VA %08x" % s["va"])
    slots = None
    for a, m in maps.items():
        if len(m) == max(s["indices"]) + 1:
            slots = m          # the select's bone count must be exactly the mesh's
            break
    if slots is None:
        for a, m in maps.items():
            if len(m) > max(s["indices"]):
                slots = m
                break
    if slots is None:
        sys.exit("no bone map covers bone %d" % max(s["indices"]))
    if not pals:
        sys.exit("no non-empty palette")
    k = max(0, min(args.palette, len(pals) - 1))
    pa, cnt, mat = pals[k]
    lengths = load_lengths(ram, g, s["num_verts"])
    tris = triangles(g, s["num_verts"], lengths)
    print("skin: VA %08x geometry %08x  %d verts  %d tris  bone map %d bones  palette [%d] %08x (%d)"
          % (s["va"], g["addr"], s["num_verts"], len(tris), len(slots), k, pa, cnt))
    if args.bind:
        write_obj(args.bind, s["verts"], tris, "bind pose, igVertexArray1_1 %08x" % s["va"])
        print("  wrote", args.bind)
    if args.out:
        posed = skin(s["verts"], s["weights"], s["indices"], slots, mat)
        write_obj(args.out, posed, tris,
                  "posed: palette %08x via bone map; live_skin.py" % pa)
        print("  wrote", args.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
