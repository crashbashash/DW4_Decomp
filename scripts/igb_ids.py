#!/usr/bin/env python3
"""igb_ids.py — resolve an igBinary pack's `igObjectRef` ids offline.

A pack (one AFS entry / `.igb`) stores its objects in **two** chains: section 1 is
the memory/object directory (`igObjectDirEntry` + `igMemoryDirEntry`) and section 2
holds the game objects.  Between them sits the **id remap table**:

    {u32 tableBytes}{u32 idCount}   followed by idCount × u16

Each u16 indexes section 1.  Entries that land on an `igObjectDirEntry` are the
pack's **objects** — and they are in the same order as section-2's records, so the
k-th object entry is section-2 record k.  Entries that land on an `igMemoryDirEntry`
are the objects' **memory blocks** (the extra ids).  The table position including the
memory entries is the **global id** an `igObjectRef` field stores, so

    id -> (k-th object entry) -> section-2 record k

with no load replay needed: every reference in a pack resolves inside its own table.

  igb_ids.py NDMW.AFS --blob 0x21307000                 # table summary + self-check
  igb_ids.py NDMW.AFS --blob 0x21307000 --id 916        # resolve one id
  igb_ids.py NDMW.AFS --blob 0x21307000 --check-refs    # every ref must resolve
"""
import argparse
import os
import struct
import sys
from collections import Counter

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import igb_inst  # noqa: E402


def sections(b, reflection):
    """(section1, section2) — the two multi-record chains, in file order."""
    dirs, _ = igb_inst.parse_directory(b)
    chains = [c for c in igb_inst.find_chains(b, dirs, reflection) if len(c) > 1]
    chains.sort(key=lambda c: c[0]["off"])
    if len(chains) < 2:
        raise SystemExit("expected two object chains, found %d" % len(chains))
    return dirs, chains[0], chains[1], chains


def field_map(r):
    return {k: v for k, v, _t in r["fields"]}


def find_table(b, s1, s2):
    """Locate and validate the id remap table in the gap before section 2.

    Returns (offset, idCount, obj_of_id) where obj_of_id[i] is the section-2 record
    index for table position i, or None for a memory entry.
    """
    lo, hi = s1[-1]["end"], s2[0]["off"]
    for p in range(lo, max(lo, hi) - 8, 2):
        tb, cnt = struct.unpack_from("<II", b, p)
        if not (8 <= tb <= len(b) - p) or not (0 < cnt < 200000):
            continue
        if p + 8 + 2 * cnt > len(b):
            continue
        vals = [struct.unpack_from("<H", b, p + 8 + 2 * i)[0] for i in range(cnt)]
        if max(vals) >= len(s1):
            continue
        obj_of_id, obj = [], []
        for i, v in enumerate(vals):
            r = s1[v]
            obj_of_id.append(None)
            if r["class"] == "igObjectDirEntry":
                obj.append((i, field_map(r)["_typeMetaIndex"]))
        if [c for _i, c in obj] != [r["classIndex"] for r in s2]:
            continue
        for k, (i, _c) in enumerate(obj):
            obj_of_id[i] = k
        return p, cnt, obj_of_id
    raise SystemExit("no validated id remap table in 0x%x..0x%x" % (lo, hi))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file")
    ap.add_argument("--blob", required=True, help="file offset of the pack")
    ap.add_argument("--reflection",
                    default=os.path.join(HERE, "..", "data", "reflection.json"))
    ap.add_argument("--id", type=lambda s: int(s, 0), help="resolve one global id")
    ap.add_argument("--check-refs", action="store_true",
                    help="resolve every igObjectRef in every record")
    a = ap.parse_args()

    lo = int(a.blob, 0)
    data = open(a.file, "rb").read()
    size, where = igb_inst.blob_extent(data, lo)
    b = data[lo:lo + (size or len(data) - lo)]
    reflection = igb_inst.load_reflection(a.reflection)
    dirs, s1, s2, chains = sections(b, reflection)

    p, cnt, obj_of_id = find_table(b, s1, s2)
    nobj = sum(1 for x in obj_of_id if x is not None)
    print("pack 0x%08x (%s): section1 %d dir entries, section2 %d records"
          % (lo, where, len(s1), len(s2)))
    print("id remap table @+0x%x: %d ids (%d objects + %d memory blocks); "
          "object order == record order"
          % (p, cnt, nobj, cnt - nobj))

    if a.id is not None:
        if not 0 <= a.id < cnt:
            raise SystemExit("id %d out of range 0..%d" % (a.id, cnt - 1))
        k = obj_of_id[a.id]
        if k is None:
            v = struct.unpack_from("<H", b, p + 8 + 2 * a.id)[0]
            f = field_map(s1[v])
            print("id %d -> MEMORY block: dir entry %d, _memSize=%s _memTypeIndex=%s"
                  % (a.id, v, f.get("_memSize"), f.get("_memTypeIndex")))
        else:
            r = s2[k]
            print("id %d -> section2 record %d  %s  name=%r" % (a.id, k, r["class"], r["name"]))
            for fn, val, _t in r["fields"]:
                print("     %-24s %s" % (fn, val))
        return 0

    if a.check_refs:
        resolved = bad = 0
        byfield = {}
        for k, r in enumerate(s2):
            for fn, val, ty in r["fields"]:
                if ty != 0 or not isinstance(val, int) or val < 0 or val == 0xFFFFFFFF:
                    continue
                if val >= cnt:
                    bad += 1
                    print("  id %d out of table range (record %d %s.%s)" % (val, k, r["class"], fn))
                    continue
                t = obj_of_id[val]
                target = "memory" if t is None else s2[t]["class"]
                byfield.setdefault((r["class"], fn), Counter())[target] += 1
                resolved += 1
        print("refs resolved: %d, out of range: %d" % (resolved, bad))
        print("target class per field (should be one class each):")
        for (cls, fn), c in sorted(byfield.items()):
            print("  %-28s %-22s %s" % (cls, fn, dict(c)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
