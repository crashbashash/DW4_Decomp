#!/usr/bin/env python3
"""verify_models_layout.py -- regression check for the offline model chain (findings #477/#478).

Re-derives a model pack's geometry-attribute table by the offline rule and diffs it against the
committed reference table (default `docs/engine/model-pack-621-attributes.tsv`).  Every row must
match: the vertex array id, the primitive mode and count, the vertex count, the stream-list block,
the number of primitive lengths and the stream ids.

The rule
--------
A model pack addresses its own geometry — no replay, no RAM dump:

    igGeometryAttr1_5  _vertexArray   (+0x0c)  -> an igObjectRef id
                       _indexArray    (+0x10)  -> 0 (NULL; there is no index buffer)
                       _primType      (+0x14)  -> 3 list / 4 strip
                       _numPrims      (+0x18)
                       _stripLengths  (+0x30)  -> igPrimLengthArray1_1
      igVertexArray1_1 _vdata         (+0x08)  -> a block listing this array's stream ids
                       _numVerts      (+0x0c)
    igPrimLengthArray1_1
                       _lengthData    (+0x08)  -> the u32 primitive lengths
                       _numStrips     (+0x0c)

An `igObjectRef` id indexes the pack's remap table (`igb_ids.py`, finding #460) and a block's
offset is the pool prefix sum with **every block 4-byte aligned** (`igb_pool.py`, finding #478).
A stream block's `_memSize` IS its content size — `12*_numVerts` for the positions, `8*_numVerts`
for the UVs (finding #477) — so a stream starts at its block's offset and needs no search.  Both
links are validated by the format's own arithmetic: the `_vdata` block must list a `12*_numVerts`
stream, and the lengths must sum to `_numVerts`.

The last column is the model's name, recovered offline through the shape -> attribute link: an
`igGeometry` (a `M_*Shape`) record's ordinal-2 value is the DCC part name (`pCylinderShape3`, …) and its
ordinal-8 value is an `igAttrList` whose array block holds that shape's attribute ids (finding #458,
reached from the pack, which is what the live namer does from RAM).  Found by ordinal and not by offset
-- a record's byte offsets shift with a variable-length value (a long name moves everything after it),
while the container's slot numbers do not.  444 of the 549 attributes are named this way; the other 105
have a shape with an empty name, or no named shape at all, and stay unnamed rather than borrowing a
neighbour's name.

Usage
-----
  verify_models_layout.py --afs NDMW.AFS --entry 621
      [--table docs/engine/model-pack-621-attributes.tsv] [--rewrite]
"""
import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import igb_ids      # noqa: E402
import igb_models   # noqa: E402
import igb_pool     # noqa: E402

DEFAULT_TABLE = os.path.join(HERE, "..", "docs", "engine",
                            "model-pack-621-attributes.tsv")


def derive(afs, entry, reflection):
    """The attribute rows the rule produces, exactly as the fixture spells them."""
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * entry:12 + 8 * entry], "little")
    refl = igb_ids.igb_inst.load_reflection(reflection)
    P = igb_pool.load(afs, hex(off), refl)
    rows = []
    for g in igb_models.read_geometry(P, refl):
        ids = [s[0] for s in igb_models.streams(P, g["vdata"])]
        rows.append("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s"
                    % (g["vertex_array"], g["prim_type"], g["num_prims"],
                       g["num_verts"] or 0, g["vdata"] or 0, len(g["lengths"]),
                       ",".join(str(i) for i in ids), g.get("name") or ""))
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--afs", required=True)
    ap.add_argument("--entry", type=int, default=621)
    ap.add_argument("--reflection", default=os.path.join(HERE, "..", "data",
                                                         "reflection.json"))
    ap.add_argument("--table", default=DEFAULT_TABLE)
    ap.add_argument("--rewrite", action="store_true",
                    help="write the derived rows over the table (after a deliberate change)")
    args = ap.parse_args()

    rows = derive(args.afs, args.entry, args.reflection)
    if args.rewrite:
        head = [l for l in open(args.table) if l.startswith("#")]
        open(args.table, "w").write("".join(head) + "\n".join(rows) + "\n")
        print("rewrote %s (%d rows)" % (args.table, len(rows)))
        return 0

    want = [l.rstrip("\n") for l in open(args.table) if l.strip() and not l.startswith("#")]
    if want == rows:
        print("OK: the offline chain reproduces all %d attributes of entry %d"
              % (len(rows), args.entry))
        return 0
    if len(want) != len(rows):
        print("MISMATCH: table has %d rows, the rule derives %d" % (len(want), len(rows)))
    for i in range(max(len(want), len(rows))):
        a = want[i] if i < len(want) else "<missing>"
        b = rows[i] if i < len(rows) else "<missing>"
        if a != b:
            print("  row %d:\n    table: %s\n    rule : %s" % (i, a, b))
            break
    return 1


if __name__ == "__main__":
    sys.exit(main())
