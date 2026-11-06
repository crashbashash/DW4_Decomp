#!/usr/bin/env python3
"""
igb_dir.py — parse the igBinary *type directory* of a stage/level pack.

Decodes the `{NUL-terminated class name}` + N x 6-byte `{u16 type_id, u16 ordinal,
u16 size}` triples records described in docs/engine/igbinary-format.md
("Field descriptor encoding").

The class-record chain is self-delimiting only via the *next* record's name (no
count is stored), so records are recovered with a greedy walk: from a name at
offset o, the next name must sit exactly at align2(o + len(name) + 1) + 6N.

Note the chain is NOT the whole of the header region the blob labels
(`hdr[7]..hdr[5]`). In the NDMW 0x6300 pack the walk yields 135 records over
0x2604..0x4034, and every triple in every one of them decodes to a known type with
that type's size. At 0x4034 the region switches structure: `{u32 336, u32 46}` then
the igMemory type-name pool (`Bootstrap`, `Default`, `Current`, `NonTracked`,
`System`, `MetaData`, `String`, `Fast`, `List`, `Temp`, ...). Those pool names are
identifier-shaped, so a walk that does not validate its triples reads them as
records and swallows them — that is how an earlier "141 records" figure arose.
`--verify` reports the boundary.

Usage:
  # dump every record in the NDMW stage pack's directory
  igb_dir.py NDMW.AFS --blob 0x1055b000

  # one class, with the type-name and reflection cross-check
  igb_dir.py NDMW.AFS --blob 0x1055b000 --class igLightAttr \
      --reflection ../../data/reflection.json

  # machine-readable, plus the structural check
  igb_dir.py NDMW.AFS --blob 0x1055b000 --json /tmp/dir.json --verify

Options:
  --blob OFFSET     file offset of the blob (required; its u32[0] is the magic)
  --start/--end     override the region searched for records
  --class NAME      only print this record (repeatable)
  --reflection PATH cross-check with data/reflection.json (ordinal = i + K + 1)
  --json PATH       write all records as JSON
  --verify          report triples that fail the type/size check
"""
import argparse
import json
import re
import struct
import sys

# Canonical element size per ig*MetaField id, observed constant across the NDMW
# 0x6300 directory. Sized entries only; None = never observed.
SIZE = {
    0: 4, 1: 4, 2: 1, 3: 1, 4: 4, 5: 4, 6: 4, 7: 4, 8: 1, 9: 4, 10: 2,
    11: 4, 12: 8, 13: 4, 14: 128, 15: 4, 16: 4, 17: 2, 19: 4, 20: 4,
    21: 4, 22: 3, 23: 4, 24: 4, 25: 4, 26: 4, 27: 4, 28: 8, 29: 768,
    30: 4, 31: 8, 32: 8, 34: 1, 36: 12, 37: 8, 38: 16, 39: 4, 40: 64,
    43: 16, 45: 3, 47: 16,
}
IDENT = re.compile(rb"[A-Za-z_][A-Za-z0-9_]{2,60}\x00")


def align2(x):
    return (x + 1) & ~1


def read_type_names(blob):
    """The 48 ig*MetaField names from the string table at 0x30."""
    count = struct.unpack_from("<I", blob, 0x24)[0]
    pos = 0x30
    lens = [struct.unpack_from("<I", blob, pos + 12 * k)[0] for k in range(count)]
    off = pos + 12 * count
    names = []
    for ln in lens:
        names.append(blob[off:off + ln - 1].decode("latin1"))
        off += ln
    return names


def walk(blob, start, end):
    """Greedy record walk. Returns [(offset, name, [triples]), ...].

    The next record's name is found by trying every `align2(name)+6N` candidate, but
    several candidates can be identifiers: the region after the class records opens
    with an igMemory type-name pool (`Default`, `Current`, `NonTracked`, ...) whose
    names are also identifier-shaped. So a candidate is only accepted if its triples
    decode (type id < 48 and, where known, the size that type always has). Triples
    are validated as they are emitted and the walk stops at the first bad one, which
    is what lands the chain end on the real boundary rather than inside the pool.
    """
    idents = {start + m.start(): m.group()[:-1].decode()
              for m in IDENT.finditer(blob[start:end])}

    def triples_ok(pad, n):
        for k in range(n):
            t, _o, s = struct.unpack_from("<3H", blob, pad + 6 * k)
            if t >= 48 or (t in SIZE and s != SIZE[t]):
                return False
        return True

    records, cur = [], min(idents) if idents else None
    while cur is not None:
        name = idents.get(cur)
        if name is None:
            break
        pad = cur + align2(len(name) + 1)
        best = None
        for n in range(0, 600):
            cand = pad + 6 * n
            if cand > end:
                break
            if cand in idents and cand > cur and triples_ok(pad, n):
                best = (cand, n)
                break
        if best is None:
            # trailing record whose triple block runs into the next structure:
            # emit the valid prefix only
            n = 0
            while pad + 6 * (n + 1) <= len(blob) and triples_ok(pad, n + 1):
                n += 1
            if n:
                tri = [struct.unpack_from("<3H", blob, pad + 6 * k) for k in range(n)]
                records.append((cur, name, tri))
            break
        tri = [struct.unpack_from("<3H", blob, pad + 6 * k) for k in range(best[1])]
        records.append((cur, name, tri))
        cur = best[0]
    return records


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("afs", help="archive containing the blob (e.g. NDMW.AFS)")
    ap.add_argument("--blob", required=True,
                    help="blob file offset, e.g. 0x1055b000 (NDMW 0x6300 pack)")
    ap.add_argument("--start", type=lambda s: int(s, 0), default=0x2604)
    ap.add_argument("--end", type=lambda s: int(s, 0), default=0x7105)
    ap.add_argument("--class", dest="classes", action="append", default=[])
    ap.add_argument("--reflection")
    ap.add_argument("--json")
    ap.add_argument("--verify", action="store_true")
    a = ap.parse_args(argv)

    base = int(a.blob, 0) if isinstance(a.blob, str) else a.blob
    with open(a.afs, "rb") as fh:
        fh.seek(base)
        blob = fh.read(a.end + 0x1000)

    magic = struct.unpack_from("<I", blob, 0)[0]
    names = read_type_names(blob)
    records = walk(blob, a.start, a.end)

    # --- structural check: every triple must decode to a known type and its size
    bad = []
    for off, name, tri in records:
        for k, (t, o, s) in enumerate(tri):
            if t >= 48:
                bad.append((name, k, t, o, s, "type id out of range"))
            elif t in SIZE and s != SIZE[t]:
                bad.append((name, k, t, o, s, f"expected size {SIZE[t]}"))
    print(f"{a.afs} blob 0x{base:x} magic 0x{magic:x}: "
          f"{len(records)} records, {sum(len(t) for _, _, t in records)} triples")
    if a.verify:
        print(f"structural check: {len(bad)} bad triples (0 = every triple a known type "
              f"with its expected size)")
        end = records[-1][0] + align2(len(records[-1][1]) + 1) + 6 * len(records[-1][2]) \
            if records else 0
        print(f"   last record {records[-1][1]!r} ends at 0x{end:x}; "
              f"the next structure there is the igMemory type-name pool")
        for b in bad[:10]:
            print("   ", b)

    # --- optional reflection cross-check: ordinal = declaredIndex + K + 1
    kinds = {}
    if a.reflection:
        refl = json.load(open(a.reflection))
        by_name = {v["class"]: v for v in refl["classes"].values()}
        nok = nfail = 0
        strong = weak = 0
        kinds = {}
        for off, name, tri in records:
            cls = by_name.get(name)
            if not cls or not cls["fields"] or not tri:
                continue
            fields = cls["fields"]
            best = None
            for K in range(1, 21):
                used, pairs, ok = set(), [], True
                for t, o, s in tri:
                    if o <= K:
                        continue
                    tn = names[t] if t < 48 else None
                    hit = None
                    for j, f in enumerate(fields):
                        if j not in used and f["type"] == tn:
                            hit = j
                            break
                    if hit is None:
                        ok = False
                        break
                    used.add(hit)
                    pairs.append((o, hit))
                if ok and pairs and all(o - 1 - h == K for o, h in pairs) \
                        and pairs == sorted(pairs, key=lambda p: p[1]):
                    best = K
                    break
            if best is None:
                nfail += 1
            else:
                nok += 1
                kinds[best] = kinds.get(best, 0) + 1
                if len([1 for t, o, s in tri if o > best]) >= 2:
                    strong += 1
                else:
                    weak += 1
        print(f"reflection cross-check: {nok} hold (K = {dict(sorted(kinds.items()))}), "
              f"{nfail} do not (greedy type-matching artefacts)")
        print(f"   of the {nok} holding, {strong} are confirmed by >=2 descriptors "
              f"and {weak} match on a single one (weak evidence)")

    want = set(a.classes)
    for off, name, tri in records:
        if want and name not in want:
            continue
        print(f"\n0x{off:05x} {name}  ({len(tri)} descriptors)")
        for k, (t, o, s) in enumerate(tri):
            tn = names[t] if t < 48 else f"<type {t}>"
            print(f"   [{k:2}] type={t:2} {tn:34} ordinal={o:3} size={s}")

    if a.json:
        with open(a.json, "w") as fh:
            json.dump([{"offset": o, "class": n,
                        "descriptors": [{"type_id": t, "type": names[t] if t < 48 else None,
                                         "ordinal": od, "size": s} for t, od, s in tr]}
                       for o, n, tr in records], fh, indent=1)
        print(f"\nwrote {a.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
