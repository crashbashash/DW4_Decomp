#!/usr/bin/env python3
"""texture_map.py — the live world-mesh -> texture-name link, read out of an EE RAM dump.

An earlier reading concluded the world-mesh texture binding is *not* in the live object graph, and that
only UI/effect/font meshes link to a texture directly.  That is true for the geometry attribute's own
fields, but the binding is one level up: the **material attr set**.

    beTextureCtrlInfo._name            the set's name (e.g. `BGObj00n`, `wall01z01`)
      _dataList (+0x20) -> beTextureCtrlAttr   one per material
        _attrSet (+0x0c) -> igAttrSet
          +0x20 `_attributes` -> igAttrList
              -> igTextureBindAttr._texture (+0x0c) -> igTextureAttr._image (+0x30) -> igPsx2Image
          +0x1c -> igNodeList of the igGeometry shapes the material applies to

So an `igGeometry` shape reached from a `beTextureCtrlAttr`'s child list gets that attr's texture.
The child list can also name a `beModelCtrlNode2` model node (a `wall01z01` attr set holds an `igSwitch`
that points at one), so the walk descends through those too; that lifts the map from 90 to 106 live
geometry attributes.  The geometry attribute is the shape's `+0x20` attr list (an `igGeometrySetAttr`
indirection on some packs).  This module walks that graph offline; it needs no emulator.

The class vtables below are the recovered no-RTTI ones (the engine's `ig*`/`be*` classes carry no
`__RTTI__` record, so `data/vtables.json` does not list them).  They were recovered from each class's
`<Class>_GetVTable` function (`scripts/seed_names_metafield_slots.py`'s first-store rule) and
cross-checked against the live objects' reflection offsets.

Public API:
    tm = TextureMap(blob)
    tm.attr_textures[geom_attr_addr] -> set(names)
    tm.attr_of_shape[shape_addr]     -> [geom_attr_addr, ...]
    tm.info_of_shape[shape_addr]     -> set(info names)
"""
import struct

LO, HI = 0x00100000, 0x02000000

# vtable -> short class name (the recovered IG classes; see the module docstring)
VT = {
    0x539620: "beTextureCtrlInfo",
    0x5395C0: "beTextureCtrlAttr",
    0x539560: "beTextureCtrlData",
    0x5294B0: "igAttrSet",
    0x528E70: "igGeometry",
    0x528DD0: "igGroup",
    0x528590: "igSwitch",
    0x5360B0: "beGroupKeep",
    0x5284F0: "igTransform",       # shared with beCopyModelCtrl2 / beModelCtrlNode2 (same layout)
    0x52AB20: "igNodeList",
    0x5238C0: "igGeometryAttr1_5",
    0x5237B0: "igGeometrySetAttr",
    0x522BD0: "igTextureBindAttr",
    0x522C60: "igTextureAttr",
    0x525630: "igPsx2Image",
    0x524420: "igAttrList",
    0x537F40: "beModelCtrlNode2",
    0x537BB0: "beModelCtrlInfoRamData",
}
_GEOM = ("igGeometryAttr1_5", "igGeometryAttr")
_GROUPS = ("igGroup", "igSwitch", "beGroupKeep", "igTransform", "igAttrSet",
           "beModelCtrlNode2", "beModelCtrlInfoRamData")


class _Ram:
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
        return self.b[p - self.lo:p - self.lo + n].split(b"\x00")[0].decode("latin-1")

    def cls(self, a):
        return VT.get(self.u32(a))

    def list_count(self, a):
        n = self.u32(a + 8)
        return n if 0 < n <= 4096 else 0


class TextureMap:
    def __init__(self, blob, lo=LO, hi=HI):
        self.r = _Ram(blob, lo)
        self.lo, self.hi = lo, hi
        self.attr_textures = {}      # geom attr addr -> set(texture names)
        self.attr_bind_textures = {} # geom attr addr -> set(names) of its material attr only
        self.attr_shape_key = {}     # geom attr addr -> (primType, numPrims)
        self.attr_of_shape = {}      # shape addr -> [geom attr addr]
        self.info_of_shape = {}      # shape addr -> set(info names)
        self.info_textures = {}      # info name -> set(texture names)
        self.name_textures = {}      # live shape name -> set(texture names)
        self._build()

    # -- low level ------------------------------------------------------------------------------
    def _objects(self, cls):
        out, r = [], self.r
        for a in range(self.lo, self.hi - 4, 4):
            if r.u32(a) in VT and VT[r.u32(a)] == cls:
                out.append(a)
        return out

    def _elems(self, lst):
        r = self.r
        n = r.list_count(lst)
        data = r.ptr(lst + 0x10)
        if not n or not data:
            return []
        return [r.ptr(data + 4 * i) for i in range(n)]

    def _textures_of_attr(self, attr):
        names = set()
        aset = self.r.ptr(attr + 0x0c)
        if not aset:
            return names
        al = self.r.ptr(aset + 0x20)
        for e in (self._elems(al) if al else []):
            if self.r.cls(e) == "igTextureBindAttr":
                tex = self.r.ptr(e + 0x0c)
                img = self.r.ptr(tex + 0x30) if tex else 0
                if img:
                    nm = self.r.string(self.r.ptr(img + 0x58))
                    if nm:
                        names.add(nm)
        return names

    def _textures_on_obj(self, obj):
        """The texture names an `igAttrSet`-shaped object's `_attributes` (+0x20) list names.

        A live material attr set hangs off the **node**, not the `igGeometry` shape: the
        character's is an `igBlendMatrixSelect` (an `igAttrSet` subclass) whose `_attributes`
        list holds `igTextureBindAttr` -> `igTextureAttr` -> `igPsx2Image`.  The `+0x20` word
        must actually be an `igAttrList` before it is read, because on a plain `igTransform`
        the same offset is `_m`.
        """
        r = self.r
        names = set()
        al = r.ptr(obj + 0x20)
        if not al or r.u32(al) != 0x524420:
            return names
        for e in self._elems(al):
            if r.cls(e) == "igTextureBindAttr":
                tex = r.ptr(e + 0x0c)
                img = r.ptr(tex + 0x30) if tex else 0
                if img:
                    nm = r.string(r.ptr(img + 0x58))
                    if nm:
                        names.add(nm)
        return names

    def _node_textures(self, shape):
        """Texture names on a shape's parent-chain node attr sets (the node-held material)."""
        r = self.r
        out = set()
        pl = r.ptr(shape + 0x10)
        for e in self._elems(pl) if pl else []:
            out |= self._textures_on_obj(e)
            pl2 = r.ptr(e + 0x10)
            if pl2:
                for e2 in self._elems(pl2):
                    out |= self._textures_on_obj(e2)
        return out

    def _geoms_below(self, root, depth=0, seen=None):
        r = self.r
        if seen is None:
            seen = set()
        if not root or root in seen or depth > 8:
            return []
        seen.add(root)
        c = r.cls(root)
        if c == "igGeometry":
            return [root]
        if c == "igNodeList":
            out = []
            for e in self._elems(root):
                out += self._geoms_below(e, depth + 1, seen)
            return out
        out = []
        if c in _GROUPS:
            cl = r.ptr(root + 0x1c)
            for e in (self._elems(cl) if cl else []):
                out += self._geoms_below(e, depth + 1, seen)
        return out

    def _attrs_of_shape(self, shape):
        r = self.r
        out = []
        al = r.ptr(shape + 0x20)
        for e in (self._elems(al) if al else []):
            c = r.cls(e)
            if c in _GEOM:
                out.append(e)
            elif c == "igGeometrySetAttr":
                gl = r.ptr(e + 0x14)
                for g in (self._elems(gl) if gl else []):
                    if r.cls(g) in _GEOM:
                        out.append(g)
            elif c == "igAttrList":
                for g in self._elems(e):
                    if r.cls(g) in _GEOM:
                        out.append(g)
        return out

    # -- the walk -------------------------------------------------------------------------------
    def _build(self):
        for info in self._objects("beTextureCtrlInfo"):
            name = self.r.string(self.r.ptr(info + 8))
            if not name:
                continue
            dl = self.r.ptr(info + 0x20)
            for attr in (self._elems(dl) if dl else []):
                if self.r.cls(attr) != "beTextureCtrlAttr":
                    continue
                texnames = self._textures_of_attr(attr)
                self.info_textures.setdefault(name, set()).update(texnames)
                aset = self.r.ptr(attr + 0x0c)
                if not aset:
                    continue
                cl = self.r.ptr(aset + 0x1c)
                geoms = []
                for e in (self._elems(cl) if cl else []):
                    geoms += self._geoms_below(e)
                for sh in set(geoms):
                    self.info_of_shape.setdefault(sh, set()).add(name)
                    for ga in self._attrs_of_shape(sh):
                        self.attr_of_shape.setdefault(sh, [])
                        if ga not in self.attr_of_shape[sh]:
                            self.attr_of_shape[sh].append(ga)
                        self.attr_textures.setdefault(ga, set()).update(texnames)
                        self.attr_bind_textures.setdefault(ga, set()).update(texnames)
                        self.attr_shape_key.setdefault(
                            ga, (self.r.u32(ga + 0x14), self.r.u32(ga + 0x18)))
                        # register on the shape even when the attr list is otherwise unreadable
                        self.attr_textures.setdefault(ga, set())
        # The node-held material (the character's skin, and the sibling attr set of any shape that
        # has one): the shape's own +0x20 list is geometry only, so walk its parent nodes.
        for sh in self._objects("igGeometry"):
            names = self._node_textures(sh)
            if not names:
                continue
            nm = self.r.string(self.r.ptr(sh + 8))
            if nm:
                self.name_textures.setdefault(nm, set()).update(names)
            for ga in self._attrs_of_shape(sh):
                self.attr_textures.setdefault(ga, set()).update(names)

    def pack_id_textures(self, attr2pack):
        """pack geometry-attr id -> set(texture names), from an attr-address -> pack-id map."""
        out = {}
        for ga, names in self.attr_textures.items():
            pid = attr2pack.get(ga)
            if pid is not None and pid >= 0:
                out.setdefault(pid, set()).update(names)
        return out

    def per_shape_pack_textures(self, key2ids):
        """pack geometry-attr id -> its material's texture, keyed by ``(primType, numPrims)``.

        a live material is a list of ``beTextureCtrlAttr`` records, each carrying
        **one** texture bind and **one** shape list, so the binding is per shape.  The live shape's
        vertex buffer is drained, so the content match cannot reach it; the shape's
        ``_primType``/``_numPrims`` can, and ``key2ids`` is the pack's ``(primType, numPrims) ->
        [id]`` map.  A key shared by several pack ids (the
        small props) assigns the texture to all of them; the caller prefers the distinctive keys.
        """
        out = {}
        # A live key shared by materials that disagree on the texture (the small UI/prop shapes
        # collide on (4,1), (4,2), (4,24), (4,25) ...) is genuinely ambiguous without the drained
        # vertex buffer, so leave those ids to the caller's fallback rather than guess.
        key_sets = {}
        for ga, names in self.attr_bind_textures.items():
            key = self.attr_shape_key.get(ga)
            if not key or not names:
                continue
            key_sets.setdefault(key, set()).add(frozenset(names))
        for key, sets in key_sets.items():
            if len(sets) != 1:
                continue
            names = set(next(iter(sets)))
            for pid in key2ids.get(key, ()):
                out.setdefault(pid, set()).update(names)
        return out


if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--from", dest="src", required=True)
    a = ap.parse_args()
    tm = TextureMap(open(a.src, "rb").read())
    print("geometry attrs with a texture: %d" % len(tm.attr_textures))
    for info, names in sorted(tm.info_textures.items()):
        if names:
            print("  %-16s %s" % (info, sorted(names)))
