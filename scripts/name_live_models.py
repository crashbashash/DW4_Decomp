#!/usr/bin/env python3
"""Map live DW4 geometry attributes to their model (part) names.

Needs a **paused** game (the heap mutates every frame, so unpaused reads are not
reproducible).

Recovered chain:

    M_<model>Shape object        vtable 0x00528e70   (826 live on stag0102)
      +0x08  name string pointer    e.g. "M_BK17v1_barrelmShape", "pCubeShape5", "barrelbody"
      +0x1c  -> wrapper object (vtable 0x0052ab20) with an attr embedded at +0x18 (this is the
                shape's FIRST attr, of any attr subclass -- not necessarily the geometry one)
      +0x20  -> exactly ONE igAttrList (vtable 0x00524420), {_count +0x08, _array +0x10}; its
                array holds the shape's attr object pointers, and the entries whose vtable is
                0x005238c0 are that shape's geometry attribute.

**One list per shape, at +0x20.**  An earlier version of this tool walked a "chain" of lists by
stride 0x18 -- that over-claims badly: the igAttrList objects live in a packed shared arena, so the
object 0x18 bytes past one shape's list is simply the *next shape's* list.  With the stride walk 637
of 752 attributes were claimed by more than one shape and a glyph quad landed under `font000`.
The shape/list relation is 1:1 (826 shapes, 826 distinct +0x20 pointers) and each list holds one
geometry attr for 786 of them, so the +0x20 list alone names them with zero collisions.  The +0x1c
wrapper attr is used only as a fallback when +0x20 yields nothing, because it usually duplicates the
list entry (and is a different attr subclass on ~1100 other objects).

So a geometry attr's name is the name of the M_*Shape whose attr list contains it.  The names come
from the DCC source (Maya/3ds Max); the binary keeps no model names of its own.  145 of the 826
shapes carry a **null** name pointer (runtime/UI sub-meshes, mostly font glyphs), so their attrs
cannot be named this way -- the tool reports them rather than guessing a neighbour's name.

This tool reads EE RAM **once** into a local buffer and then resolves every pointer offline.  The
first version issued one PINE round trip per pointer chase (tens of thousands) and never finished --
keep it bulk.  `--dump` writes that buffer so a later run can work `--from` it with no emulator.

Usage:
    # with the game paused:
    python3 name_live_models.py --tsv <out-dir>/model-names.tsv --rename-dir <out-dir> --dump /tmp/ee.bin
    # later, emulator off:
    python3 name_live_models.py --from /tmp/ee.bin --tsv <out-dir>/model-names.tsv
"""
import argparse
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
VT_SHAPE = 0x00528E70     # M_*Shape
VT_WRAPPER = 0x0052AB20
VT_ATTRLIST = 0x00524420  # igAttrList
VT_GEOM = 0x005238C0      # igGeometryAttr1_5

LO, HI, CHUNK = 0x00100000, 0x02000000, 0x00080000   # EE RAM


class EeRam:
    """EE RAM held locally; every accessor resolves against it, never PINE."""

    def __init__(self, blob, lo=LO):
        self.b, self.lo = blob, lo

    def inrange(self, a, n=1):
        return self.lo <= a and a + n <= self.lo + len(self.b)

    def u32(self, a):
        if not self.inrange(a, 4):
            return 0
        return struct.unpack_from("<I", self.b, a - self.lo)[0]

    def ptr(self, a):
        """A plausible heap pointer."""
        v = self.u32(a)
        return v if self.lo < v < self.lo + len(self.b) else 0

    def bytes(self, a, n):
        if not self.inrange(a, n):
            return b""
        return self.b[a - self.lo:a - self.lo + n]

    def string(self, p, n=96):
        if not self.inrange(p, 2):
            return None
        s = self.bytes(p, n).split(b"\x00")[0]
        if len(s) >= 2 and all(32 <= c < 127 for c in s):
            return s.decode("latin1")
        return None


def read_ram(lo, hi):
    out = bytearray()
    a = lo
    while a < hi:
        n = min(CHUNK, hi - a)
        r = subprocess.run([*live(), "read", hex(a), "--size", str(n), "--raw"],
                           capture_output=True, check=True)
        if len(r.stdout) != n:
            print("  read 0x%08x: got %d of %d bytes" % (a, len(r.stdout), n), file=sys.stderr)
            out.extend(bytes(n))
        else:
            out.extend(r.stdout)
        a += n
        print("  read to 0x%08x (%.1f MB)" % (a, len(out) / 1e6), file=sys.stderr)
    return bytes(out)


def find_all(ram, vtable):
    """All addresses holding `vtable` (4-aligned), resolved from the local buffer."""
    pat = struct.pack("<I", vtable)
    out, start = [], 0
    while True:
        i = ram.b.find(pat, start)
        if i < 0:
            break
        if (ram.lo + i) % 4 == 0:
            out.append(ram.lo + i)
        start = i + 1
    return out


def list_attrs(ram, lst):
    """Geometry attrs held by ONE igAttrList object."""
    out = []
    if not lst or ram.u32(lst) != VT_ATTRLIST:
        return out
    cnt, arr = ram.u32(lst + 0x08), ram.ptr(lst + 0x10)
    if arr and 0 < cnt < 4096:
        for i in range(cnt):
            v = ram.u32(arr + 4 * i)
            if v and ram.u32(v) == VT_GEOM:
                out.append(v)
    return out


def attrs_of_shape(ram, shape):
    """Every geometry-attr address this M_*Shape owns, plus its name.

    The shape owns the one igAttrList at +0x20.  Only if that yields nothing do we fall back to
    the attr embedded in the +0x1c wrapper (which normally duplicates the list entry).
    """
    name = ram.string(ram.ptr(shape + 0x08))
    out = list_attrs(ram, ram.ptr(shape + 0x20))
    if not out:
        w = ram.ptr(shape + 0x1C)
        if w and ram.u32(w) == VT_WRAPPER and ram.u32(w + 0x18) == VT_GEOM:
            out = [w + 0x18]
    return out, name


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dump", help="write EE RAM to this file (requires a paused game)")
    ap.add_argument("--from", dest="src", help="use a saved EE RAM dump instead of PINE")
    ap.add_argument("--lo", type=lambda s: int(s, 0), default=LO)
    ap.add_argument("--hi", type=lambda s: int(s, 0), default=HI)
    ap.add_argument("--tsv", help="write 'geomAttr<TAB>name' rows here")
    ap.add_argument("--rename-dir", help="rename model_<addr>.obj to <name>.obj in this dir")
    ap.add_argument("--list", action="store_true", help="print the mapping")
    args = ap.parse_args()

    if args.src:
        blob = open(args.src, "rb").read()
        print("loaded %s (%.1f MB)" % (args.src, len(blob) / 1e6), file=sys.stderr)
    else:
        print("reading EE RAM 0x%08x..0x%08x ..." % (args.lo, args.hi), file=sys.stderr)
        blob = read_ram(args.lo, args.hi)
        if args.dump:
            open(args.dump, "wb").write(blob)
            print("wrote", args.dump, file=sys.stderr)
    ram = EeRam(blob, args.lo)

    shapes = find_all(ram, VT_SHAPE)
    print("live M_*Shape objects: %d" % len(shapes), file=sys.stderr)
    amap = {}
    claimed_by = {}
    unnamed = 0
    unnamed_attrs = set()
    nolist = 0
    for s in shapes:
        attrs, name = attrs_of_shape(ram, s)
        if not ram.ptr(s + 0x20):
            nolist += 1
        if not name:
            unnamed += 1
            unnamed_attrs.update(attrs)
            continue
        for a in attrs:
            amap.setdefault(a, set()).add(name)
            claimed_by.setdefault(a, set()).add(s)
    multi = sum(1 for v in amap.values() if len(v) > 1)
    multi_shape = sum(1 for v in claimed_by.values() if len(v) > 1)
    print("named shapes: %d   unnamed shapes: %d (owning %d attrs)   shapes with no +0x20: %d"
          % (len(shapes) - unnamed, unnamed, len(unnamed_attrs), nolist), file=sys.stderr)
    print("geometry attrs mapped to a name: %d   (attr claimed by >1 name: %d, by >1 shape: %d)"
          % (len(amap), multi, multi_shape), file=sys.stderr)
    print("distinct model names: %d" % len({n for v in amap.values() for n in v}), file=sys.stderr)
    if unnamed_attrs:
        print("UNNAMED (null +0x08, left un-renamed): %d attrs, e.g. %s"
              % (len(unnamed_attrs), ", ".join("0x%08x" % a for a in sorted(unnamed_attrs)[:6])),
              file=sys.stderr)

    rows = sorted((a, sorted(n)[0]) for a, n in amap.items())
    if args.tsv:
        with open(args.tsv, "w") as f:
            f.write("#geomAttr\tmodelShapeName\n")
            for a, n in rows:
                f.write("0x%08x\t%s\n" % (a, n))
        print("wrote", args.tsv, file=sys.stderr)

    renamed = 0
    if args.rename_dir:
        for a, n in rows:
            src = os.path.join(args.rename_dir, "model_%08x.obj" % a)
            if not os.path.exists(src):
                continue
            dst = os.path.join(args.rename_dir, n + ".obj")
            if os.path.exists(dst):
                dst = os.path.join(args.rename_dir, "%s__%08x.obj" % (n, a))
            os.rename(src, dst)
            renamed += 1
        print("renamed %d OBJ(s)" % renamed, file=sys.stderr)

    if args.list or not (args.tsv or args.rename_dir):
        for a, n in rows[:60]:
            print("0x%08x  %s" % (a, n))


if __name__ == "__main__":
    main()
