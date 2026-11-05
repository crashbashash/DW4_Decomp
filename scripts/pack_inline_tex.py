#!/usr/bin/env python3
"""pack_inline_tex.py — decode an *inline* texture from a stage pack by its material name.

The destructible objects (the wooden crate/barrel) are textured neither through the live object
graph nor through a texture pack: their material is an `igAttrSet` record **inside the stage pack**
whose chain

    igAttrSet._attributes -> igAttrList -> igTextureBindAttr._texture
        -> igTextureAttr._image -> igImage._pImage / _pClut

ends at an **inline pool block** — a small indexed image plus a 256-entry palette, stored in the
pack's own content pool.  That is why `texture_map.py` (the live dump) and `dw4asset texpack` (the
texture-pack entries 618/619) both come back empty for `M_BK19a0_boxShape` / `M_BK17v1_barrelsShape`.

Palette entries are **R G B A** here (unlike the texture packs, whose clut is `A R G B`), so the
decoder reads bytes 0..2 as colour.

    python3 pack_inline_tex.py --pack <roms>/NDMW.AFS:614 --material g_woodencasez01 --png /tmp/a.png
    python3 pack_inline_tex.py --pack ... --material g_bbarrelsz01 --rgba /tmp/a.rgba   # for --texdir
    python3 pack_inline_tex.py --pack ... --list        # every material set that carries a texture

The `.rgba` is the pack's own image order (top-down, as stored and as the GS samples it), which is
what `--png` shows too.  The port owns the orientation: `dw4asset`'s texdir loader flips rows on
load, exactly as its texture-pack decoder does, because the sampler indexes with `(1 - tv)` (finding
#579).  So write the .rgba **unflipped** here.
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DECOMP = os.environ.get("DW4_DECOMP", os.path.join(os.path.dirname(HERE)))
sys.path.insert(0, os.path.join(DECOMP, "scripts"))
import igb_ids  # noqa: E402
import igb_inst  # noqa: E402
import igb_pool  # noqa: E402

ig = igb_ids.igb_inst


def load(pack, decomp):
    """(P, dirs, reflection, obj_of_id) for the pack at `AFS:ENTRY`."""
    afs, entry = pack.rsplit(":", 1)
    refl = ig.load_reflection(os.path.join(decomp, "data", "reflection.json"))
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * int(entry):12 + 8 * int(entry)], "little")
    P = igb_pool.load(afs, hex(off), refl)
    dirs, _ = ig.parse_directory(P["b"])
    _p, _cnt, obj_of_id = igb_ids.find_table(P["b"], P["s1"], P["s2"])
    return P, dirs, refl, obj_of_id


def rec_at(P, dirs, refl, off):
    return ig.decode_record(P["b"], off, dirs, refl)


def obj_off(P, obj_of_id, oid):
    if not (0 <= oid < len(obj_of_id)) or obj_of_id[oid] is None:
        return None
    return P["s2"][obj_of_id[oid]]["off"]


def blk(P, bid):
    o = P["off_of"].get(bid)
    if o is None:
        return None
    return P["b"][o:o + P["size_of"][bid]]


def field(r, name):
    return next((v for n, v, _t in r["fields"] if n == name), None)


def ftype(r, name):
    return next((t for n, _v, t in r["fields"] if n == name), None)


def all_attrsets(P, dirs, refl):
    out = []
    for r in P["s2"]:
        if r["class"] == "igAttrSet":
            rr = rec_at(P, dirs, refl, r["off"])
            if rr:
                out.append(rr)
    return out


def attrset_elements(P, dirs, refl, obj_of_id, aset):
    """The `_attributes` list's element objects (the material attrs)."""
    al_off = obj_off(P, obj_of_id, field(aset, "_attributes"))
    if al_off is None:
        return []
    al = rec_at(P, dirs, refl, al_off)
    if not al:
        return []
    arr = field(al, "slot4")
    data = blk(P, arr) if arr is not None else None
    if not data:
        return []
    elems = []
    for i in range(0, len(data) - 3, 4):
        oid = struct.unpack_from("<I", data, i)[0]
        o = obj_off(P, obj_of_id, oid)
        rr = rec_at(P, dirs, refl, o) if o is not None else None
        if rr:
            elems.append(rr)
    return elems


def texture_of(P, dirs, refl, obj_of_id, aset):
    """(image_rgba, w, h) or None — the first igTextureBindAttr in the set."""
    for a in attrset_elements(P, dirs, refl, obj_of_id, aset):
        if a["class"] == "igTextureBindAttr":
            ta_off = obj_off(P, obj_of_id, field(a, "_texture"))
            ta = rec_at(P, dirs, refl, ta_off) if ta_off is not None else None
            if not ta:
                continue
            im_off = obj_off(P, obj_of_id, field(ta, "_image"))
            im = rec_at(P, dirs, refl, im_off) if im_off is not None else None
            if not im:
                continue
            w, h = field(im, "_px"), field(im, "_py")
            idx = blk(P, field(im, "_pImage"))
            clut_off = obj_off(P, obj_of_id, field(im, "_pClut"))
            clut = rec_at(P, dirs, refl, clut_off) if clut_off is not None else None
            pal = blk(P, field(clut, "_pData")) if clut else None
            if not idx or not pal or not w or not h:
                continue
            n = int(field(im, "_imageSize") or w * h)
            bpr = int(field(im, "_bytesPerRow") or w)
            rgba = bytearray(w * h * 4)
            for y in range(h):
                for x in range(w):
                    k = y * bpr + x
                    if k >= len(idx):
                        break
                    pi = idx[k] * 4
                    if pi + 3 >= len(pal):
                        continue
                    r, g, b, al = pal[pi], pal[pi + 1], pal[pi + 2], pal[pi + 3]
                    o = (y * w + x) * 4
                    rgba[o:o + 4] = bytes((r, g, b, al))
            return bytes(rgba), int(w), int(h), n
    return None


def write_png(path, rgba, w, h):
    import zlib
    raw = b"".join(b"\x00" + bytes(rgba[y * w * 4:(y + 1) * w * 4]) for y in range(h))

    def chunk(t, d):
        c = t + d
        return struct.pack(">I", len(d)) + c + struct.pack(">I", zlib.crc32(c) & 0xFFFFFFFF)
    png = b"\x89PNG\r\n\x1a\n"
    png += chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
    png += chunk(b"IDAT", zlib.compress(raw, 9))
    png += chunk(b"IEND", b"")
    open(path, "wb").write(png)


def write_rgba(path, rgba, w, h):
    """Write `<u32 w><u32 h><RGBA>` in the pack's own (top-down) image order.

    The port flips this on load (`dw4asset.c`: `rgba_flip_rows`), matching its texture-pack decoder,
    so the .rgba must stay unflipped here.  See the module docstring (finding #579)."""
    open(path, "wb").write(struct.pack("<II", w, h) + rgba)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--pack", required=True, metavar="AFS:ENTRY")
    ap.add_argument("--material", help="the igAttrSet name, e.g. g_woodencasez01")
    ap.add_argument("--png")
    ap.add_argument("--rgba", help="write <u32 w><u32 h><RGBA> for `dw4asset render --texdir`")
    ap.add_argument("--list", action="store_true", help="every material set with a texture")
    ap.add_argument("--decomp", default=DECOMP)
    a = ap.parse_args()

    P, dirs, refl, obj_of_id = load(a.pack, a.decomp)
    sets = all_attrsets(P, dirs, refl)
    if a.list:
        for s in sets:
            t = texture_of(P, dirs, refl, obj_of_id, s)
            if t:
                print("  %-24s %dx%d" % ((s["name"] or "").strip("\x00 "), t[1], t[2]))
        return 0
    if not a.material:
        ap.error("--material or --list")
    match = [s for s in sets if (s["name"] or "").strip("\x00 ") == a.material]
    if not match:
        print("pack_inline_tex: no igAttrSet %r (have %s)"
              % (a.material, ", ".join(sorted(s["name"] for s in sets if s["name"]))))
        return 1
    t = texture_of(P, dirs, refl, obj_of_id, match[0])
    if not t:
        print("pack_inline_tex: %s carries no igTextureBindAttr image" % a.material)
        return 1
    rgba, w, h, n = t
    print("%s -> %dx%d inline texture (%d byte(s) of index data)" % (a.material, w, h, n))
    if a.png:
        write_png(a.png, rgba, w, h)
        print("  wrote", a.png)
    if a.rgba:
        write_rgba(a.rgba, rgba, w, h)
        print("  wrote", a.rgba)
    return 0


if __name__ == "__main__":
    sys.exit(main())
