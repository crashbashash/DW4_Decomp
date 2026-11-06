#!/usr/bin/env python3
"""modelctrl_dump.py — resolve the front-end title's model-controller chain in a pack.

Decomposes the DATA side of the animated front-end layer.  For an
AREA.AFS entry (default 620 = the title pack, model 'j_startback') it prints:

  * the id chain from `beAction2Info '<model>'` (`_switch` / `_animationDatabase` /
    `_dataList`), through `beAction2DataList` -> `beAction2Data` (NDSP/OPEN/WAIT01/CLOSE)
    -> `igNamedObjectList` -> the `beAction2*` command records (JOINTSET, WAITCHECK, ...),
  * the parallel `beModelCtrlInfo '<model>'` chain (beBaseInfoDataList -> DataSeq/DataHit
    -> igNamedObjectList -> beModelCtrlData SQ_OPEN/SQ_WAIT/SQ_CLOSE -> beModelCtrl* commands),
  * the scene graph of `igSceneInfo '<model>'`: how many `igTransform` nodes are animated
    (each with `_transformInput` -> `igTransformSequence1_5`), the keyframe lists that
    actually hold the per-joint transforms (times / translation / rotation / scale), and
    the total triangle count of the meshes the scene draws.

Every claim carries a pack offset, a class and a global id, so it can be re-checked.

The parsing primitives (type directory walk, instance chain walk, id remap table) are the
verified ones from the decompilation repo: `scripts/igb_inst.py` and
`igb_ids.py`.  Point `--scripts` at that directory (default: this file's sibling
`../scripts`, else the repo path).

Usage:
  python3 modelctrl_dump.py --afs ../local/extracted/AREA.AFS --entry 620
  python3 modelctrl_dump.py --afs AREA.AFS --entry 620 --name j_startback
  python3 modelctrl_dump.py --file area620.bin --name j_startback
"""
import argparse
import os
import struct
import sys

DEFAULT_SCRIPTS = [
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "scripts"),
]


def load_igb(scripts):
    for d in ([scripts] if scripts else []) + DEFAULT_SCRIPTS:
        if d and os.path.exists(os.path.join(d, "igb_inst.py")):
            sys.path.insert(0, d)
            import igb_inst
            import igb_ids
            return igb_inst, igb_ids
    raise SystemExit("cannot find igb_inst.py/igb_ids.py; pass --scripts DIR")


def afs_entry(path, index):
    """Return the bytes of one AFS entry (0-based, as the tools index it)."""
    data = open(path, "rb").read()
    if data[:4] != b"AFS\x00":
        raise SystemExit("%s is not an AFS archive" % path)
    n = struct.unpack_from("<I", data, 4)[0]
    if not 0 <= index < n:
        raise SystemExit("entry %d out of range 0..%d" % (index, n - 1))
    off, size = struct.unpack_from("<II", data, 8 + 8 * index)
    return data[off:off + size]


# --- field names for the classes this chain uses, by descriptor ordinal -----------------
# The directory states a type + ordinal + size per descriptor; the ordinal is the class's
# flattened 1-based slot.  `K` is the inherited-slot count, so a declared field f[i] sits at
# ordinal i + K + 1.  Where reflection.json already carries the names the
# scripts use them; this table names the handful of classes whose base fields the record
# stores but reflection does not list for the subclass.
ORD_NAMES = {
    # igTransformSequence1_5 (base igTransformSequence slots 2..10, then the 1_5 slots)
    "igTransformSequence1_5": {2: "_xlateList", 3: "_quatList", 4: "_scaleList",
                               5: "_timeList", 6: "_startTime", 7: "_uniformTimeEnabled",
                               8: "_playMode", 10: "_centerOfRotation", 11: "_timeListLong",
                               12: "_interpolationDataTranslation",
                               13: "_interpolationDataRotation",
                               14: "_interpolationDataScale", 15: "_drivenChannels",
                               16: "_interpolationMethod", 17: "_keyframeTimeOffset",
                               18: "_animationDuration", 19: "_compressedDataObject"},
    "beAction2Info": {2: "_name", 4: "_resolveState", 5: "(base._dataList)", 6: "(base._ramList)",
                      7: "_switch", 8: "_animationDatabase", 9: "_dataList"},
    "beModelCtrlInfo": {2: "_name", 4: "_resolveState", 5: "(base._dataList)",
                        6: "(base._ramList)", 7: "_kindString"},
}


class Pack:
    def __init__(self, igb_inst, igb_ids, blob, reflection):
        self.ii, self.ids = igb_inst, igb_ids
        self.blob = blob
        self.refl = igb_inst.load_reflection(reflection)
        dirs, s1, s2, chains = igb_ids.sections(blob, self.refl)
        self.dirs, self.s1, self.s2 = dirs, s1, s2
        self.p, self.cnt, self.obj_of_id = igb_ids.find_table(blob, s1, s2)
        # pool blocks, in id order alignment)
        self.memsz = {}
        for i in range(self.cnt):
            if self.obj_of_id[i] is None:
                v = struct.unpack_from("<H", blob, self.p + 8 + 2 * i)[0]
                self.memsz[i] = int(igb_ids.field_map(s1[v])["_memSize"])
        self.poff = {}
        cur = s2[-1]["end"]
        for i in sorted(self.memsz):
            self.poff[i] = cur
            cur += (self.memsz[i] + 3) & ~3

    # -- id space -----------------------------------------------------------------------
    def rec(self, i):
        k = self.obj_of_id[i] if 0 <= i < self.cnt else None
        return None if k is None else self.s2[k]

    def cls(self, i):
        r = self.rec(i)
        return None if r is None else r["class"]

    def rname(self, i):
        r = self.rec(i)
        return None if r is None else (r["name"] or "").rstrip("\x00")

    def id_of_off(self, off):
        for i in range(self.cnt):
            r = self.rec(i)
            if r and r["off"] == off:
                return i
        return None

    def fields(self, i):
        r = self.rec(i)
        return {} if r is None else {k: v for k, v, _t in r["fields"]}

    def sid(self, i):
        """A reference value -> a printable id (NULL for -1)."""
        return "NULL" if i in (None, 0xFFFFFFFF) else str(i)

    def ref_str(self, i):
        if i in (None, 0xFFFFFFFF):
            return "NULL"
        r = self.rec(i)
        if r is None:
            return "id %d -> block +0x%x (%d bytes)" % (i, self.poff.get(i, 0), self.memsz.get(i, 0))
        return "id %d -> +0x%x %s %r" % (i, r["off"], r["class"], self.rname(i))

    # -- list objects -------------------------------------------------------------------
    def block_of(self, i):
        off = self.poff.get(i)
        sz = self.memsz.get(i)
        return None if off is None else self.blob[off:off + sz]

    def list_ids(self, i):
        """The object ids a list/DataList object holds (its igMemoryRef block)."""
        r = self.rec(i)
        if r is None:
            return []
        d = self.fields(i).get("slot4")
        raw = None if d in (None, 0xFFFFFFFF) else self.block_of(d)
        return [] if raw is None else list(struct.unpack("<%dI" % (len(raw) // 4), raw))

    def list_items(self, i, kind):
        d = self.fields(i).get("slot4")
        raw = None if d in (None, 0xFFFFFFFF) else self.block_of(d)
        if raw is None:
            return None
        if kind == "long":
            return [struct.unpack_from("<q", raw, 8 * k)[0] for k in range(len(raw) // 8)]
        if kind == "quad":
            return [struct.unpack_from("<4f", raw, 16 * k) for k in range(len(raw) // 16)]
        return [struct.unpack_from("<3f", raw, 12 * k) for k in range(len(raw) // 12)]

    # -- sequence decoding --------------------------------------------------------------
    def seq_fields(self, i):
        r = self.rec(i)
        c = self.dirs[r["classIndex"]]
        names = ORD_NAMES.get(r["class"], {})
        q = 8
        out = {}
        for t, o, sz in c["trips"]:
            nm = names.get(o, "ord%d" % o)
            if t == 4:
                n = struct.unpack_from("<I", self.blob, r["off"] + q)[0]
                out[nm] = self.blob[r["off"] + q + 4:r["off"] + q + 4 + n - 1].decode("latin1")
                q += 4 + n
            elif t == 31:
                out[nm] = struct.unpack_from("<d", self.blob, r["off"] + q)[0]; q += 8
            elif t == 12:
                out[nm] = struct.unpack_from("<q", self.blob, r["off"] + q)[0]; q += 8
            elif t == 36:
                out[nm] = struct.unpack_from("<3f", self.blob, r["off"] + q); q += 12
            elif t == 16:
                out[nm] = struct.unpack_from("<f", self.blob, r["off"] + q)[0]; q += 4
            elif t == 2:
                out[nm] = self.blob[r["off"] + q]; q += 4
            elif t == 22:
                out[nm] = tuple(self.blob[r["off"] + q:r["off"] + q + 3]); q += 4
            else:
                out[nm] = struct.unpack_from("<I", self.blob, r["off"] + q)[0]; q += 4
        return out

    # -- scene graph (the port's rule, scene.c build_graph) -----------------------------
    def scene_root(self, sceneinfo_id):
        r = self.rec(sceneinfo_id)
        if r is None:
            return None
        for _k, v, ty in r["fields"]:
            if ty == 0 and isinstance(v, int) and v != 0xFFFFFFFF:
                if self.cls(v) in ("igGraphPathList", "igAttrSet", "igGroup", "igNode"):
                    return v
        return None

    def walk(self, root):
        """Breadth collection: roots + igNodeList children.  Returns [(id,parent)]."""
        order, seen = [], set()

        def add(i, parent):
            if i in seen or i >= self.cnt or len(order) > 200000:
                return
            seen.add(i)
            order.append((i, parent))
            r = self.rec(i)
            if r is None:
                return
            for _k, v, ty in r["fields"]:
                if ty == 0 and isinstance(v, int) and v != 0xFFFFFFFF and self.cls(v) == "igNodeList":
                    for e in self.list_ids(v):
                        add(e, i)
        add(root, None)
        return order

    def tris_of_geometry(self, gid):
        """Triangle count for an igGeometry node: its igAttrList array -> igGeometryAttr1_5.

        list (primType 3): `_numPrims` triangles; strip (primType 4): sum(len_i - 2) over
        the `_stripLengths` -> igPrimLengthArray1_1 length block (the port's dw4_mesh_tris)."""
        r = self.rec(gid)
        if r is None:
            return None
        al = self.fields(gid).get("slot8")          # SHAPE_ATTRS_ORD = 8
        ar = self.rec(al) if al not in (None, 0xFFFFFFFF) else None
        if ar is None:
            return None
        arr = None
        for _k, v, ty in ar["fields"]:
            if ty == 7:
                arr = v
        if arr in (None, 0xFFFFFFFF):
            return None
        raw = self.block_of(arr)
        if raw is None:
            return None
        tris = 0
        for aid in struct.unpack("<%dI" % (len(raw) // 4), raw):
            a = self.rec(aid)
            if a is None:
                continue
            pt = struct.unpack_from("<I", self.blob, a["off"] + 0x14)[0]
            np_ = struct.unpack_from("<I", self.blob, a["off"] + 0x18)[0]
            if pt == 3:
                tris += np_
            elif pt == 4:
                pl = struct.unpack_from("<I", self.blob, a["off"] + 0x30)[0]  # _stripLengths
                pr = self.rec(pl) if pl not in (0xFFFFFFFF,) else None
                if pr is None:
                    continue
                ld = struct.unpack_from("<I", self.blob, pr["off"] + 0x8)[0]  # _lengthData
                lr = self.block_of(ld)
                if lr is None:
                    continue
                for k in range(len(lr) // 4):
                    ln = struct.unpack_from("<I", lr, 4 * k)[0]
                    if ln >= 3:
                        tris += ln - 2
        return tris


def dump_command(pk, cid, indent="      "):
    f = pk.fields(cid)
    extra = ""
    if pk.cls(cid) == "beAction2JOINTSET":
        extra = "  _startTime=%s _endTime=%s _loopMode=%r" % (
            f.get("_startTime"), f.get("_endTime"),
            str(f.get("_loopMode", "")).rstrip("\x00"))
    elif pk.cls(cid) == "beAction2WAITCHECK":
        extra = "  _waitTime=%s" % f.get("_waitTime")
    elif pk.cls(cid) == "beAction2FADESET":
        extra = "  _fadeTime=%s _fadeValue=%s" % (f.get("_fadeTime"), f.get("_fadeValue"))
    print("%s%s %r  id=%s @0x%x%s" % (indent, pk.cls(cid), pk.rname(cid),
                                      cid, pk.rec(cid)["off"], extra))


def dump_action2(pk, info_id):
    r = pk.rec(info_id)
    f = pk.fields(info_id)
    print("beAction2Info %r  id=%s @0x%x" % (pk.rname(info_id), info_id, r["off"]))
    print("  _switch             %s" % pk.ref_str(f.get("_switch")))
    print("  _animationDatabase  %s" % pk.ref_str(f.get("_animationDatabase")))
    print("  _dataList           %s" % pk.ref_str(f.get("_dataList")))
    dl = f.get("_dataList")
    if dl in (None, 0xFFFFFFFF):
        return
    print("  beAction2DataList id=%s @0x%x  count=%s" % (dl, pk.rec(dl)["off"], pk.fields(dl).get("slot2")))
    for e in pk.list_ids(dl):
        print("    beAction2Data %r id=%s @0x%x  _comList=%s" % (
            pk.rname(e), e, pk.rec(e)["off"], pk.sid(pk.fields(e).get("_comList"))))
        cl = pk.fields(e).get("_comList")
        if cl in (None, 0xFFFFFFFF):
            continue
        print("      igNamedObjectList id=%s @0x%x  count=%s" % (cl, pk.rec(cl)["off"], pk.fields(cl).get("slot2")))
        for c in pk.list_ids(cl):
            dump_command(pk, c)
            # a beAction2Data's command list can hold a beAction2Data? no: commands only


def dump_modelctrl(pk, info_id):
    f = pk.fields(info_id)
    print("beModelCtrlInfo %r  id=%s @0x%x  %s" % (pk.rname(info_id), info_id, pk.rec(info_id)["off"],
                                                   pk.fields(info_id).get("_kindString")))
    dl = f.get("slot5")   # beBaseInfo._dataList
    print("  (base._dataList)    %s" % pk.ref_str(dl))
    rl = f.get("slot6")   # beBaseInfo._ramList
    print("  (base._ramList)     %s" % pk.ref_str(rl))
    if dl in (None, 0xFFFFFFFF):
        return
    for e in pk.list_ids(dl):
        if pk.cls(e) == "beModelCtrlInfoDataSeq":
            print("    beModelCtrlInfoDataSeq %r id=%s _dataList=%s" % (
                pk.rname(e), e, pk.sid(pk.fields(e).get("_dataList"))))
            sl = pk.fields(e).get("_dataList")
            if sl in (None, 0xFFFFFFFF):
                continue
            print("      igNamedObjectList id=%s @0x%x" % (sl, pk.rec(sl)["off"]))
            for s in pk.list_ids(sl):
                print("        beModelCtrlData %r id=%s @0x%x _comList=%s" % (
                    pk.rname(s), s, pk.rec(s)["off"], pk.sid(pk.fields(s).get("_comList"))))
                cl = pk.fields(s).get("_comList")
                if cl in (None, 0xFFFFFFFF):
                    continue
                for c in pk.list_ids(cl):
                    dump_command(pk, c, indent="          ")
        else:
            print("    %s %r id=%s @0x%x" % (pk.cls(e), pk.rname(e), e, pk.rec(e)["off"]))


def dump_scene(pk, scene_id):
    r = pk.rec(scene_id)
    root = pk.scene_root(scene_id)
    print("igSceneInfo %r id=%s @0x%x" % (pk.rname(scene_id), scene_id, r["off"]))
    print("  _sceneGraph %s" % pk.ref_str(root))
    order = pk.walk(root) if root is not None else []
    from collections import Counter
    cc = Counter(pk.cls(x) for x, _p in order)
    print("  scene graph: %d node(s)  %s" % (len(order), dict(cc)))
    seqs, tris, ngeo = [], 0, 0
    per_mesh = []
    for x, _p in order:
        f2 = pk.fields(x)
        if pk.cls(x) in ("igTransform", "beModelCtrlNode2"):
            ti = f2.get("_transformInput")
            if ti not in (None, 0xFFFFFFFF):
                seqs.append((x, ti))
        if pk.cls(x) == "igGeometry":
            t = pk.tris_of_geometry(x)
            ngeo += 1
            if isinstance(t, int):
                tris += t
                per_mesh.append((pk.rname(x), t))
    uniq = sorted({s for _x, s in seqs})
    motion = scaleonly = 0
    for _x, s in seqs:
        v = pk.seq_fields(s)
        if v.get("_xlateList", 0xFFFFFFFF) != 0xFFFFFFFF or v.get("_quatList", 0xFFFFFFFF) != 0xFFFFFFFF:
            motion += 1
        else:
            scaleonly += 1
    print("  animated nodes (joints): %d   distinct igTransformSequence1_5: %d" % (len(seqs), len(uniq)))
    print("    of which translation/rotation: %d   scale-only: %d" % (motion, scaleonly))
    print("  geometry meshes: %d, triangles total: %d" % (ngeo, tris))
    print("    per mesh: %s" % ", ".join("%s=%d" % (n, t) for n, t in per_mesh))
    for s in uniq:
        v = pk.seq_fields(s)
        def rd(key, kind):
            x = v.get(key)
            return None if x in (None, 0xFFFFFFFF) else pk.list_items(x, kind)
        def fmt(x, p=2):
            return None if x is None else [tuple(round(a, p) for a in e) if isinstance(e, tuple) else e for e in x]
        print("    seq id=%s @0x%x  times=%s" % (s, pk.rec(s)["off"], rd("_timeListLong", "long")))
        print("       xlate=%s" % fmt(rd("_xlateList", "vec3")))
        print("       quat =%s" % fmt(rd("_quatList", "quad")))
        print("       scale=%s" % fmt(rd("_scaleList", "vec3")))
        print("       startTime=%s duration=%s" % (v.get("_startTime"), v.get("_animationDuration")))
    return seqs


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--afs", help="AFS archive path")
    g.add_argument("--file", help="a single extracted pack file")
    ap.add_argument("--entry", type=int, default=620, help="AFS entry index (default 620)")
    ap.add_argument("--name", default="j_startback", help="model/scene name (default j_startback)")
    ap.add_argument("--reflection", default=None)
    ap.add_argument("--scripts", default=os.environ.get("DW4_SCRIPTS"))
    a = ap.parse_args()

    ii, ids = load_igb(a.scripts)
    if a.afs:
        blob = afs_entry(a.afs, a.entry)
        where = "%s entry %d" % (a.afs, a.entry)
    else:
        blob = open(a.file, "rb").read()
        where = a.file
    refl = a.reflection or os.path.join(os.path.dirname(ids.__file__), "..", "data", "reflection.json")
    pk = Pack(ii, ids, blob, refl)
    print("pack %s: %d ids (%d objects + %d memory blocks)  chain @0x%x"
          % (where, pk.cnt, sum(1 for x in pk.obj_of_id if x is not None),
             sum(1 for x in pk.obj_of_id if x is None), pk.s2[0]["off"]))
    print()

    # find the two registry records by name
    a2 = mc = scene = None
    for i in range(pk.cnt):
        r = pk.rec(i)
        if r is None or pk.rname(i) != a.name:
            continue
        if r["class"] == "beAction2Info":
            a2 = i
        elif r["class"] == "beModelCtrlInfo":
            mc = i
        elif r["class"] == "igSceneInfo":
            scene = i
    print("== ACTION-2 CONTROLLER ==")
    if a2 is not None:
        dump_action2(pk, a2)
    print("\n== MODEL-CONTROLLER ==")
    if mc is not None:
        dump_modelctrl(pk, mc)
    print("\n== SCENE / JOINTS / KEYFRAMES ==")
    if scene is not None:
        dump_scene(pk, scene)
    return 0


if __name__ == "__main__":
    sys.exit(main())
