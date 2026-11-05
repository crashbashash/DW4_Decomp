#!/usr/bin/env python3
"""afs_manifest_names.py — every AFS entry's name, from the root manifest NDMW.IGB.

`NDMW.IGB` is not only a container: decoded as igBinary it is the game's **virtual
filesystem**, and two of its 20 classes carry the whole thing (finding #444):

    beNDMWAfsSetupData   `_name` "ndmw.afs" / "area.afs", `_fileCount` 972 / 1382
    igAdxAfsFile         `_name`, `_ptNumber` (which archive), `_fileNumber` (which entry)

So the archive is `NDMW.AFS` for `_ptNumber` 0 and `AREA.AFS` for 1, and a name resolves
to an (archive, entry) pair with no guessing.  Checked against facts already recorded:
`(0, 140)` is `stag0102.igb` (finding #434 identified AFS entry 140 as the stag0102
manifest) and `(1, 0)` is `aeu_opening.sfd`, an MPEG whose AREA entry 0 starts `00 00 01
ba`.  The manifest names all 1,382 AREA entries and 697 of NDMW's 972.

Usage:
    scripts/afs_manifest_names.py [NDMW.IGB]            # `name<TAB>archive<TAB>entry`
    scripts/afs_manifest_names.py --entry 140           # the name of one AFS entry
    scripts/afs_manifest_names.py --grep stag01         # names matching a substring
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import igb_inst  # noqa: E402

SLOT_NAME, SLOT_PTNUMBER, SLOT_FILENUMBER = 2, 4, 5
PARTS = {0: "NDMW.AFS", 1: "AREA.AFS"}


def entries(path, reflection={}):
    """[(name, archive, entry)] from the manifest's igAdxAfsFile records."""
    b = open(path, "rb").read()
    dirs, _ = igb_inst.parse_directory(b)
    chain = igb_inst.find_chains(b, dirs, reflection)[0]
    out = []
    for r in chain:
        if r["class"] != "igAdxAfsFile":
            continue
        trips = dirs[r["classIndex"]]["trips"]
        by_ord = {t[1]: r["fields"][i][1] for i, t in enumerate(trips)}
        name = (by_ord.get(SLOT_NAME) or "").rstrip("\x00")
        pt, entry = by_ord.get(SLOT_PTNUMBER), by_ord.get(SLOT_FILENUMBER)
        if not name or pt is None or entry is None:
            continue
        out.append((name, PARTS.get(pt, "pt%d" % pt), entry))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("igb", nargs="?", default=os.environ.get("DW4_IGB", "NDMW.IGB"))
    ap.add_argument("--entry", type=int, help="print the name(s) for one archive entry")
    ap.add_argument("--archive", default="NDMW.AFS")
    ap.add_argument("--grep", help="only names containing this substring")
    args = ap.parse_args()

    if not os.path.exists(args.igb):
        raise SystemExit("no %s — pass the path or set DW4_IGB" % args.igb)
    rows = entries(args.igb)

    if args.entry is not None:
        for name, arch, entry in sorted(rows, key=lambda r: r[0]):
            if entry == args.entry and arch == args.archive:
                print(name)
        return
    for name, arch, entry in sorted(rows, key=lambda r: (r[1], r[2])):
        if args.grep and args.grep not in name:
            continue
        print("%s\t%s\t%d" % (name, arch, entry))


if __name__ == "__main__":
    main()
