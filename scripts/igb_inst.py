#!/usr/bin/env python3
"""igb_inst.py — decode the igBinary *instance* records (the object data section).

  igb_inst.py NDMW.AFS --blob 0x1055b000            # every record in the pack
  igb_inst.py NDMW.AFS --blob 0x1055b000 --class beGeneraterData
  igb_inst.py NDMW.AFS --blob 0x1055b000 --json /tmp/inst.json
  igb_inst.py NDMW.AFS --blob 0x1055b000 --pool    # dump the memory/content pool

`igb_dir.py` decodes a pack's *type directory* (what each class looks like); this
decodes the *instances* (the values). Together they read a stage's authored data —
generator rows and drop rows — with no emulator and no live game.

THE ENCODING

A pack's object data is a run of records:

    {u32 classIndex}{u32 recordSize}{value for every descriptor, in ordinal order}

  * `classIndex` indexes the type directory (`igb_dir.py` order, 0-based), so a
    record names its own class.
  * `recordSize` is the whole record's byte length, which makes the decode
    self-checking: a correct decode lands exactly on it. That check is what
    validates the whole scheme — it is not fitted to anything.
  * there is **no separate name field**. The first descriptor is slot 2 of the
    class; for a named class that slot is the inherited `igString` name, so the
    stream reads `{classIndex}{recordSize}{strLen}{name bytes}…` and the word that
    looks like a third header word is simply that string's length. Classes whose
    slot 2 is an `igInt` (the list/data classes) have no name at all.

Value widths, little-endian, and every value occupies its slot:

    igBool/igChar/igUnsignedChar  1, PADDED TO 4   igShort/igUnsignedShort  2, padded to 4
    igInt/igEnum/igFloat, refs    4                igLong/igDouble          8
    igVec2f 8   igVec3f 12   igVec4f 16   igMatrix44f 64
    any string  {u32 len}{bytes}   len = align4(strlen+1), bytes padded to len

Records start at a **2-mod-4** file offset, which is why a plain u32 read of the
section looks like a small-integer table with 16-bit-shifted values.

WHY IT IS A *CHAIN*, NOT A SCAN

Records tile the object data with no gaps — objects a record references are stored
as records too, immediately alongside — so the decoder walks forward while each
record lands exactly on its own size word. A failure marks the end of the region,
never a gap. Entry 183 of `NDMW.AFS` decodes **266 records in one chain**, every one
size-exact, and 301 across the pack's two chains.

WHAT THE REFERENCES ARE — AND WHY THEY CANNOT BE RESOLVED FROM THE FILE

`igObjectRef` fields hold small integers (a generator's `_genePosList` /
`_geneRotYRadianList` / `_playerDataList` read 208/210/211) and so do the `igMemoryRef`
`_data` fields of the list classes (13…320). Neither is a byte offset into the pack and
neither is an index in file order — no base makes the referenced classes come out right.
They are **load-time ordinals**: assigned as the loader creates objects, in an order the
file does not record, with sharing/deduplication for identical objects (six generators
share one empty rotation list). Two things confirm it: `beGeneraterDataList._data` holds
the twelve generators' own ids in one run, and every object's refs are *lower* than its
own id — i.e. referenced objects are created before their referrer.

The *contents* they point at are in the file, though. After the object stream comes a
content pool that holds the list contents — spawn positions and rotations, e.g.
`(-55.0, 40.0, -405.0) (15.0, 40.0, -435.0) (15.0, 40.0, -405.0)` and `-1.5708` (≈ −π/2) —
`--pool` dumps it. Pairing each list to its exact array needs the load-time mapping.

### THE LIST CONTENTS — the pool, and what `_data` means

After the object stream comes a **content pool** holding every list's contents. A list
record reads `{count, count, _data}`, and `_data` is an **ordering key**: lay the lists
out in ascending `_data` order, back to back, each occupying `count × itemsize` bytes,
and the pool is reconstructed **exactly** — no padding, ending precisely at the pack end
(entry 622: 229 lists, 7,112 bytes needed, 7,112 bytes present; 82/82 `igVec3fList`
triples are real coordinates, 1,196/1,196 object-list entries are in id range).

`--lists` lays the pool out that way and decodes each list's contents.

`igObjectRef` fields are a **different** thing and **do** resolve offline: the id indexes
the pack's remap table (between the two object sections), which this module's companion
`igb_ids.py` reads — see `docs/engine/igbinary-format.md` §*References are pack-local ids*.
"""
import argparse
import json
import os
import re
import struct
import sys
from collections import Counter

# canonical element size per ig*MetaField type id (see igb_dir.py /)
CANON = {0: 4, 1: 4, 2: 1, 3: 1, 4: 4, 5: 4, 6: 4, 7: 4, 8: 1, 9: 4, 10: 2, 11: 4,
         12: 8, 13: 4, 14: 128, 15: 4, 16: 4, 17: 2, 19: 4, 20: 4, 21: 4, 22: 4,
         23: 4, 24: 4, 25: 4, 26: 4, 27: 4, 28: 8, 29: 768, 30: 4, 31: 8, 32: 8,
         34: 1, 36: 12, 37: 8, 38: 16, 39: 4, 40: 64, 43: 16, 45: 3, 47: 16}
TID2REF = {0: 'igObjectRef', 1: 'igInt', 2: 'igBool', 3: 'igChar', 4: 'igString',
           5: 'igRawRef', 6: 'igEnum', 7: 'igMemoryRef', 8: 'igUnsignedChar',
           9: 'igUnsignedInt', 10: 'igUnsignedShort', 11: 'igStruct', 12: 'igLong',
           13: 'igUnsignedLong', 16: 'igFloat', 17: 'igShort', 31: 'igDouble',
           36: 'igVec3f', 37: 'igVec2f', 38: 'igVec4f', 39: 'igVec4uc',
           40: 'igMatrix44f', 45: 'igVec3uc', 47: 'igCharMetrics'}
IDENT = re.compile(rb"^[A-Za-z_][A-Za-z0-9_:]{1,60}$")


def align4(x):
    return (x + 3) & ~3


def walk_directory(b, start, limit):
    """Validated class-record walk: `{name NUL}{pad to even}{6-byte triples}` repeated.

    No count is stored, so a record's end is found by searching forward for the next
    identifier at `align2(name)+6N` whose triples all decode (`type id < 48`).  The
    triple's own size field is *not* checked against a global table: it is per-*pack*
    (type 13 is 4 bytes in the small stage packs and 8 in the big model packs), which
    is what `CANON` used to get wrong and what stopped the model packs at a suffix of
    their class list.  The final class has no next class to sit at a 6-aligned offset
    — its triples run straight into the igMemory type-name pool — so a valid prefix is
    emitted for it and the walk ends.  The result's length matches the blob header's
    class count (`hdr[3]`)."""
    idents = {m.start(): m.group()[:-1]
              for m in re.finditer(rb"[A-Za-z_][A-Za-z0-9_:]{2,60}\x00", b[start:limit])}
    idents = {start + k: v for k, v in idents.items()}

    def triples_ok(pad, n):
        for k in range(n):
            t, o, _s = struct.unpack_from("<3H", b, pad + 6 * k)
            if t >= 48 or not 1 <= o < 4096:
                return False
        return True

    out, cur = [], min(idents) if idents else None
    while cur is not None:
        nm = idents.get(cur)
        if nm is None:
            break
        pad = (cur + len(nm) + 2) & ~1
        best = None
        for n in range(0, 600):
            cand = pad + 6 * n
            if cand > limit:
                break
            if cand in idents and cand > cur and triples_ok(pad, n):
                best = (cand, n)
                break
        if best is None:
            n = 0
            while pad + 6 * (n + 1) <= len(b) and triples_ok(pad, n + 1):
                n += 1
            if n:
                out.append({"name": nm.decode(), "off": cur,
                            "trips": [struct.unpack_from("<3H", b, pad + 6 * k)
                                      for k in range(n)]})
            break
        out.append({"name": nm.decode(), "off": cur,
                    "trips": [struct.unpack_from("<3H", b, pad + 6 * k)
                              for k in range(best[1])]})
        cur = best[0]
    return out, (out[-1]["off"] if out else start)


def parse_directory(b, start=None, limit=None):
    """`{name NUL}{pad to even}{6-byte triples}`, repeated. Returns (records, end);
    the list index *is* the classIndex an instance refers to."""
    limit = limit or len(b)
    if start is None:
        start = find_directory_start(b)
    return walk_directory(b, start, limit)


def find_directory_start(b):
    """Locate the class-record run.

    A directory always opens with the base class `igObject`, so candidates are the
    `\x00igObject\x00` anchors; the one whose validated walk yields the most classes
    wins.  Scoring by walked class count (rather than by raw probe offsets) matters on
    the big packs: several later `igObject`-shaped anchors parse as a *suffix* of the
    directory and would otherwise be chosen."""
    cands = [m.start() + 1 for m in re.finditer(rb"\x00igObject\x00", b[:0x8000])]
    if not cands:
        raise SystemExit("could not locate a type directory in this blob")
    best, bestn = cands[0], -1
    for c in cands:
        recs, _ = walk_directory(b, c, min(len(b), c + 0x8000))
        if len(recs) > bestn:
            best, bestn = c, len(recs)
    return best


def find_K(cls, trips, reflection):
    """The class's inherited-slot count — used only to name fields. Storage does not
    need it: a record carries a value for every descriptor, markers included."""
    fs = (reflection.get(cls) or {}).get("fields") or []
    if not fs:
        return None
    for K in range(0, 14):
        ok, n = True, 0
        for ty, ordn, _sz in trips:
            if ordn <= K:
                continue
            i = ordn - 1 - K
            if not 0 <= i < len(fs) or TID2REF.get(ty) != fs[i]["type"].replace("MetaField", ""):
                ok = False
                break
            n += 1
        if ok and n > 0:
            return K
    return None


def load_reflection(path):
    if not path or not os.path.exists(path):
        return {}
    d = json.load(open(path))
    return {c["class"].split("::")[-1]: c for c in d["classes"].values()}


def decode_record(b, p, dirs, reflection):
    """Decode one instance record at `p`, or None if `p` is not a record start.
    The `recordSize` check is what makes this self-validating."""
    if p + 8 > len(b):
        return None
    cl, size = struct.unpack_from("<2I", b, p)
    if cl >= len(dirs) or size < 8 or p + size > len(b):
        return None
    rec = dirs[cl]
    fs = (reflection.get(rec["name"]) or {}).get("fields") or []
    K = find_K(rec["name"], rec["trips"], reflection) or 0
    q, vals, name = p + 8, [], None
    for ty, ordn, _sz in rec["trips"]:
        i = ordn - 1 - K
        if ordn <= K:
            fname = "_name" if ty == 4 else "slot%d" % ordn
        else:
            fname = fs[i]["name"] if 0 <= i < len(fs) else "slot%d" % ordn
        if ty == 4:
            if q + 4 > len(b):
                return None
            n = struct.unpack_from("<I", b, q)[0]
            if n % 4 or n > 8192 or q + 4 + n > len(b):
                return None
            if n and b[q + 4 + n - 1] != 0:
                return None
            s = b[q + 4:q + 4 + n - 1].decode("latin1") if n else ""
            if name is None:
                name = s
            vals.append([fname, s, ty])
            q += 4 + n
            continue
        # the descriptor states its own width; it is padded to a 4-byte slot.  Use
        # `_sz` rather than a fixed per-type table because it is per-*pack* (type 13
        # is 4 bytes in the small stage packs, 8 in the big model packs).
        w = align4(_sz)
        if q + w > len(b):
            return None
        if ty == 36:
            vals.append([fname, [round(x, 4) for x in struct.unpack_from("<3f", b, q)], ty])
        elif ty == 38:
            vals.append([fname, [round(x, 4) for x in struct.unpack_from("<4f", b, q)], ty])
        elif ty == 16:
            vals.append([fname, round(struct.unpack_from("<f", b, q)[0], 4), ty])
        elif ty in (2, 3, 8, 34):
            vals.append([fname, b[q], ty])
        elif ty in (12, 31):
            vals.append([fname, struct.unpack_from("<q" if ty == 12 else "<d", b, q)[0], ty])
        elif ty in (10, 17):
            vals.append([fname, struct.unpack_from("<H" if ty == 10 else "<h", b, q)[0], ty])
        else:
            vals.append([fname, struct.unpack_from("<I", b, q)[0], ty])
        q += w
    if q - p != size:
        return None
    return {"off": p, "class": rec["name"], "classIndex": cl, "size": size,
            "name": name, "fields": vals, "end": q}


def find_chains(b, dirs, reflection, lo=0x800):
    """Every maximal contiguous record chain in the blob, longest first. Records tile
    without gaps, so a chain is maximal and a failure to decode ends it.

    Two traps the old single-pass version fell into, both measured on `NDMW.AFS`:

      * **The scan stepped by two bytes** from an even `lo`.  The stage packs happen to
        start their records at `2 mod 4`, but the character-model packs (`p_*.igb`,
        e.g. entry 861) start at the other parity, so half the offsets -- and *every*
        record -- were never tried.  The first record of entry 861 is at `0x260f`, odd.
      * **After a chain it jumped `p = q` to the chain's end**, which skips a start that
        lies inside a short false chain.  Both are gone here: every offset is tried, and
        a record start is a *chain* start only when no other record ends on it.

    Walking only the chain starts keeps this O(bytes) rather than quadratic.  A chain
    wholly contained in another (a false start inside a record that still rejoins the
    run) is dropped, so the result is the set of maximal chains."""
    hi = len(b)
    hits = []
    for p in range(lo, hi - 8):
        cl, size = struct.unpack_from("<2I", b, p)
        if cl < len(dirs) and 8 <= size <= 8192 and p + size <= hi:
            if decode_record(b, p, dirs, reflection):
                hits.append((p, p + size))
    ends = {e for _p, e in hits}
    chains = []
    for p, _e in hits:
        if p in ends:
            continue
        recs, q = [], p
        while True:
            r = decode_record(b, q, dirs, reflection)
            if r is None:
                break
            recs.append(r)
            q = r["end"]
        chains.append(recs)
    keep, far = [], -1
    for c in sorted(chains, key=lambda c: c[0]["off"]):
        if c[0]["off"] < far:
            continue
        keep.append(c)
        far = max(far, c[-1]["end"])
    keep.sort(key=len, reverse=True)
    return keep


def blob_extent(data, blob):
    """(size, note). For an AFS container the entry containing `blob` bounds the pack
    (sections follow the object stream, so the walk must stop at the entry)."""
    if data[:4] == b"AFS\x00":
        n = struct.unpack_from("<I", data, 4)[0]
        for i in range(n):
            off, size = struct.unpack_from("<II", data, 8 + 8 * i)
            if off == blob:
                return size, "AFS entry %d" % i
    return None, "not an AFS blob start"


ITEM_SIZE = {'igVec3fList': 12, 'igFloatList': 4, 'beGeneraterPlayerDataList': 4,
             'beGeneraterItemDataList': 4, 'beGeneraterItemDataOneList': 4,
             'beGeneraterDataList': 4, 'beBaseInfoRamList': 4, 'igInfoList': 4,
             'igDataList': 4, 'igObjectList': 4, 'igNamedObjectList': 4}


def list_records(chain):
    """[(data_key, count, class, chainIndex, record)] for every list record in the chain."""
    out = []
    for i, r in enumerate(chain):
        if r["class"] in ITEM_SIZE:
            cnt = next((v for k, v, ty in r["fields"] if k == "slot2"), None)
            dk = next((v for k, v, ty in r["fields"] if k == "slot4"), None)
            if isinstance(cnt, int) and isinstance(dk, int):
                out.append((dk, cnt, r["class"], i, r))
    return sorted(out)


def dump_lists(b, chain, limit=None):
    """Lay the pool out in `_data` order and decode each list's contents."""
    p = chain[-1]["end"]
    recs = list_records(chain)
    need = sum(c * ITEM_SIZE[cls] for _, c, cls, _, _ in recs)
    print("content pool +0x%x .. +0x%x (%d bytes); lists need %d bytes"
          % (p, len(b), len(b) - p, need))
    for dk, cnt, cls, i, r in recs[:limit or len(recs)]:
        size = ITEM_SIZE[cls]
        if cls == 'igVec3fList':
            vals = [tuple(round(x, 2) for x in struct.unpack_from("<3f", b, p + 12 * k))
                    for k in range(min(cnt, 4))]
        elif cls in ('igFloatList',):
            vals = [round(struct.unpack_from("<f", b, p + 4 * k)[0], 4) for k in range(min(cnt, 8))]
        else:
            vals = [struct.unpack_from("<I", b, p + 4 * k)[0] for k in range(min(cnt, 8))]
        print("  idx %-5d +0x%04x %-28s count=%-4d _data=%-6d pool[0x%05x] %s%s"
              % (i, r["off"], cls, cnt, dk, p, vals,
                 " ..." if cnt > len(vals) else ""))
        p += cnt * size
    return p


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("file")
    ap.add_argument("--blob", required=True, help="file offset of the blob (its u32[0] is the magic)")
    ap.add_argument("--end", type=lambda s: int(s, 0), default=None)
    ap.add_argument("--dir-start", type=lambda s: int(s, 0), default=None)
    ap.add_argument("--class", dest="cls", help="only records of this class")
    ap.add_argument("--slot", type=int, default=None, help="only records with this classIndex")
    ap.add_argument("--pool", action="store_true",
                    help="dump the content pool that follows the object stream")
    ap.add_argument("--lists", action="store_true",
                    help="lay the pool out in `_data` order and decode every list's contents")
    ap.add_argument("--reflection", default=os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                        "..", "data", "reflection.json"))
    ap.add_argument("--json", dest="json_out")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()

    blob = int(a.blob, 0)
    data = open(a.file, "rb").read()
    size, where = blob_extent(data, blob)
    end = a.end or (blob + size if size else len(data))
    b = data[blob:end]
    if len(b) < 0x40:
        raise SystemExit("blob at 0x%x is too short (%d bytes; %s)" % (blob, len(b), where))
    hdr = struct.unpack_from("<12I", b, 0)
    if not a.quiet:
        print("blob 0x%08x  %d bytes (%s)  hdr: %s"
              % (blob, len(b), where, " ".join("%x" % v for v in hdr)))

    reflection = load_reflection(a.reflection)
    dirs, dend = parse_directory(b, a.dir_start)
    if not a.quiet:
        print("type directory: %d classes, +0x%x .. +0x%x, %d carry triples"
              % (len(dirs), dirs[0]["off"], dend, sum(1 for r in dirs if r["trips"])))

    chains = find_chains(b, dirs, reflection)
    if not chains:
        raise SystemExit("no record chain found")
    recs = chains[0]
    if not a.quiet:
        print("chains: %s (longest first); walking the longest"
              % [(hex(r[0]["off"]), len(r)) for r in chains[:4]])
        print("records: %d, %d bytes, +0x%x .. +0x%x, all size-exact"
              % (len(recs), sum(r["size"] for r in recs), recs[0]["off"], recs[-1]["end"]))
        tail = b[recs[-1]["end"]:]
        print("content pool after the stream: +0x%x .. +0x%x (%d bytes)"
              % (recs[-1]["end"], len(b), len(tail)))

    if a.pool:
        p0 = recs[-1]["end"]
        for r in range(p0, len(b), 16):
            bs = b[r:r + 16]
            print("  +%04x %s  %s" % (r, " ".join("%02x" % v for v in bs),
                  "".join(chr(v) if 32 <= v < 127 else "." for v in bs)))
        return

    if a.lists:
        dump_lists(b, recs)
        return

    sel = recs
    if a.cls:
        sel = [r for r in sel if a.cls in r["class"]]
    if a.slot is not None:
        sel = [r for r in sel if r["classIndex"] == a.slot]

    if a.json_out:
        json.dump(sel, open(a.json_out, "w"))
        if not a.quiet:
            print("wrote %d records to %s" % (len(sel), a.json_out))
    elif a.cls or a.slot is not None:
        for r in sel:
            print("\n+0x%04x  %s  %r  (%d bytes)" % (r["off"], r["class"], r["name"], r["size"]))
            for k, v, ty in r["fields"]:
                print("     %-26s %-14s %s" % (k, TID2REF.get(ty, ty), v))
    else:
        for c, n in Counter(r["class"] for r in recs).most_common():
            print("  %-34s %4d" % (c, n))
        print("\n(--class NAME to dump fields, --pool for the content pool)")


if __name__ == "__main__":
    main()
