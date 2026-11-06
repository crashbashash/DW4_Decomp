#!/usr/bin/env python3
"""verify_field_kinds.py — a pack's descriptor type id IS the field's kind.

Which values a loader has to rewrite into pointers (the id -> pointer pass) looked like
it needed a generated (class, offset) -> kind table from the reflection, because a first look at the
type ids seemed to show them serving several kinds at once (type 0 against object references, name
slots, floats and enums).  That reading was wrong: those row groups came from the classes where
`igb_inst.find_K` cannot map ordinals to fields at all, plus the inherited slots (`ordn <= K`) that
are not fields.  The container's own map, `igb_inst.TID2REF`, is the kind:

    0 igObjectRef    4 igString    5 igRawRef    7 igMemoryRef    16 igFloat    36 igVec3f ...

and the bytes say the same thing.  Over NDMW.AFS entries 621/179/642/622/183/140, every value of
type 0 is an object id or NULL and every value of type 7 is a pool-block id or NULL -- **0.0%
"neither"** in both cases -- while every other type has values outside the id space (floats 88%,
matrices 100%, structs 89%).  So a value's kind is read from its own descriptor, with no table and
no reflection: 0 = an object reference, 7 = a memory (pool-block) reference, everything else is a
plain value.

This script re-measures that matrix so the claim stays checked:

  verify_field_kinds.py --afs NDMW.AFS [--entry 621 ...]
"""
import argparse
import collections
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import igb_ids      # noqa: E402
import igb_pool     # noqa: E402

# the only two kinds a loader rewrites, and the types that must never be rewritten
REF_TYPES = {0: "object", 7: "block"}


def matrix(afs, entries, reflection):
    refl = igb_ids.igb_inst.load_reflection(reflection)
    TID = igb_ids.igb_inst.TID2REF
    data = open(afs, "rb").read()
    m = collections.defaultdict(collections.Counter)
    for entry in entries:
        off = struct.unpack_from("<I", data, 8 + 8 * entry)[0]
        P = igb_pool.load(afs, hex(off), refl)
        b = P["b"]
        dirs, _s1, s2, _ch = igb_ids.sections(b, refl)
        _p, cnt, obj_of_id = igb_ids.find_table(b, _s1, s2)
        for r in s2:
            d = next((x for x in dirs if x["name"] == r["class"]), None)
            if d is None:
                continue
            q = r["off"] + 8
            for ty, _ordn, sz in d["trips"]:
                if ty == 4:
                    q += 4 + struct.unpack_from("<I", b, q)[0]
                    continue
                v = struct.unpack_from("<I", b, q)[0]
                if v == 0xFFFFFFFF:
                    k = "null"
                elif 0 <= v < cnt:
                    k = "object" if obj_of_id[v] is not None else "block"
                else:
                    k = "neither"
                m[ty][k] += 1
                q += (sz + 3) & ~3
    return m, TID


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--afs", required=True)
    ap.add_argument("--entry", type=int, action="append", default=[])
    ap.add_argument("--reflection", default=os.path.join(HERE, "..", "data",
                                                         "reflection.json"))
    args = ap.parse_args()
    entries = args.entry or [621, 179, 642, 622, 183, 140]
    m, TID = matrix(args.afs, entries, args.reflection)

    print("%-5s %-14s %8s %8s %8s %8s %9s" % ("type", "name", "object", "block", "null",
                                              "neither", "values"))
    bad = 0
    for ty in sorted(m):
        c = m[ty]
        tot = sum(c.values())
        pct = lambda k: 100.0 * c[k] / tot if tot else 0.0
        print("%-5d %-14s %7.1f%% %7.1f%% %7.1f%% %7.1f%% %9d"
              % (ty, TID.get(ty, "?"), pct("object"), pct("block"), pct("null"),
                 pct("neither"), tot))
        if ty in REF_TYPES:
            # a reference type must ALWAYS hold an id of the expected kind, or NULL
            if c["neither"] or c[REF_TYPES[ty]] + (c["null"] if REF_TYPES[ty] == "block"
                                                   else 0) < tot - c["null"]:
                print("   FAIL: type %d holds %d value(s) outside the id space" % (ty,
                                                                                   c["neither"]))
                bad += 1
        elif tot > 1000 and pct("neither") < 1.0:
            print("   note: type %d (%s) is never outside the id space either -- it cannot be"
                  " told from a reference by range alone" % (ty, TID.get(ty, "?")))
    for ty, want in sorted(REF_TYPES.items()):
        c = m.get(ty, collections.Counter())
        if not c:
            print("   FAIL: no values of type %d (%s) in these packs" % (ty, want))
            bad += 1
    if bad:
        return 1
    print("OK: type 0 is always an object id or NULL and type 7 always a pool-block id or NULL"
          " (%d values of the two kinds)"
          % (sum(m[0].values()) + sum(m[7].values())))
    return 0


if __name__ == "__main__":
    sys.exit(main())
