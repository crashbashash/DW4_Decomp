#!/usr/bin/env python3
"""live_materials.py — the *material state* of every live material attr set, from an EE RAM dump.

`texture_map.py` stops at the texture bind; this dumps **every** attribute of the sets the engine
builds at load time (`beTextureCtrlInfo._name` -> `beTextureCtrlAttr._attrSet` -> `igAttrSet`), so a
mesh's material colour, lighting-enabled flag, shade model, blend/alpha state and texture state come
out of the game's own memory instead of the port's guesses (finding #563).

    python3 live_materials.py --from <ee-dump>.bin [--name BGGround00n]
"""
import argparse
import importlib.util
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DECOMP = os.environ.get("DW4_DECOMP", os.path.join(os.path.dirname(HERE)))
sys.path.insert(0, HERE)
import texture_map as tm  # noqa: E402


def load_vtables(decomp):
    """{vtable address: class name} from both recovered tables (RTTI-named + GetVTable)."""
    out = {}
    p = os.path.join(decomp, "data", "vtables.json")
    if os.path.exists(p):
        d = json.load(open(p))
        rtti_names = {int(k, 16): v.get("name") for k, v in (d.get("rtti") or {}).items()}
        for k, v in (d.get("vtables") or {}).items():
            cls = v.get("class") or rtti_names.get(int(v.get("rtti") or "0", 16))
            if cls:
                out.setdefault(int(k, 16), cls.split("::")[-1])
    p = os.path.join(decomp, "data", "vtables-getvtable.json")
    if os.path.exists(p):
        for k, v in json.load(open(p)).items():
            if isinstance(v, dict) and v.get("class"):
                out.setdefault(int(k, 16), v["class"].split("::")[-1])
    return out


def fields_of(refl, cls):
    for c in refl.values():
        if c.get("class") == cls:
            return [(f["name"], f["offset"], f["type"]) for f in c.get("fields", [])]
    return []


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="src", required=True)
    ap.add_argument("--name", help="only this material set")
    ap.add_argument("--dump", action="store_true", help="every attribute of every set (long)")
    a = ap.parse_args()

    refl = json.load(open(os.path.join(DECOMP, "data", "reflection.json")))["classes"]
    vt = load_vtables(DECOMP)
    blob = open(a.src, "rb").read()
    m = tm.TextureMap(blob)
    r = m.r

    def vec4(addr):
        return tuple(round(struct.unpack_from("<f", blob, addr - r.lo + 4 * i)[0], 4)
                     for i in range(4))

    def attr_line(e):
        cls = vt.get(r.u32(e), "?")
        vals = []
        for nm, off, typ in fields_of(refl, cls):
            if nm.startswith("_pad"):
                continue
            v = r.u32(e + off)
            if typ == "igVec4fMetaField":
                v = vec4(e + off)
            elif typ == "igFloatMetaField":
                v = round(struct.unpack_from("<f", blob, e - r.lo + off)[0], 4)
            elif typ == "igObjectRefMetaField":
                v = "ref %#x" % v if v else 0
            vals.append("%s=%s" % (nm, v))
        return "%-26s %s" % (cls, " ".join(vals))

    shown = 0
    for info in m._objects("beTextureCtrlInfo"):
        name = r.string(r.ptr(info + 8))
        if not name or (a.name and name != a.name):
            continue
        dl = r.ptr(info + 0x20)
        print("=== %s   (beTextureCtrlInfo %#x)" % (name, info))
        for attr in (m._elems(dl) if dl else []):
            if r.cls(attr) != "beTextureCtrlAttr":
                continue
            aset = r.ptr(attr + 0x0c)
            cl = r.ptr(aset + 0x1c) if aset else 0
            print("  beTextureCtrlAttr %#x -> igAttrSet %#x  (%d shapes)" % (
                attr, aset,
                sum(1 for _ in (m._elems(cl) if cl else []))))
            if not aset:
                continue
            al = r.ptr(aset + 0x20)
            for e in (m._elems(al) if al else []):
                print("     " + attr_line(e))
            shown += 1
    print("material attr sets shown: %d" % shown)


if __name__ == "__main__":
    sys.exit(main())
