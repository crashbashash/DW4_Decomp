#!/usr/bin/env python3
"""verify_texpack.py — diff the C texture-pack reader against the repository's decoder.

The port's `dw4asset texpack` and DW4_Decomp/scripts/igb_texpack.py implement the same
rules, so they must agree on every texture's ids and block offsets, and
on the decoded pixels.  This is the texture half of `make check`.

  tools/verify_texpack.py [--tool build/dw4asset] [--afs <NDMW.AFS>] [entries...]
"""
import argparse
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_AFS = os.path.join(PORT, "..", "..", "local/extracted", "NDMW.AFS")
DEFAULT_REPO = os.path.join(PORT, "..")
ENTRIES = [625, 626, 618, 619, 632, 639]

ROW = re.compile(r"^\s+(\S+)\s+(\d+)x(\d+)\s+image id (\d+)\s+0x([0-9a-f]+)\s+"
                 r"\(grid\)\s+palette id (\d+)\s+0x([0-9a-f]+)")
HEAD = re.compile(r"(\d+) clut \+ (\d+) image blocks \+ (\d+) pad, pool 0x([0-9a-f]+) "
                  r"\.\. 0x([0-9a-f]+); id table @0x([0-9a-f]+), (\d+) ids "
                  r"\(block class (\d+), object class (\d+)\), (\d+) textures")


def rows(text):
    out = {}
    for line in text.splitlines():
        m = ROW.match(line)
        if m:
            out[m.group(1)] = (int(m.group(2)), int(m.group(3)), int(m.group(4)),
                               int(m.group(5), 16), int(m.group(6)), int(m.group(7), 16))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4asset"))
    ap.add_argument("--afs", default=DEFAULT_AFS)
    ap.add_argument("--repo", default=DEFAULT_REPO)
    ap.add_argument("entries", nargs="*", type=int)
    args = ap.parse_args()
    entries = args.entries or ENTRIES

    sys.path.insert(0, os.path.join(args.repo, "scripts"))
    import igb_texpack as TP

    afs = open(args.afs, "rb").read()
    checked = texts = 0
    for entry in entries:
        off, size = int.from_bytes(afs[8 + 8 * entry:12 + 8 * entry], "little"), \
            int.from_bytes(afs[12 + 8 * entry:16 + 8 * entry], "little")
        b = afs[off:off + size]
        recs = TP.find_records(b)
        info = TP.header_layout(b, recs)
        c = subprocess.run([args.tool, "texpack", "--afs", args.afs, "--entry", str(entry),
                            "--list"], capture_output=True, text=True)
        if info is None:
            # a pack the reader is allowed to refuse: it must refuse, not guess
            if c.returncode == 0:
                print("  entry %d: C accepted a pack with no describable pool" % entry)
                return 1
            print("  entry %-4d refused by both (no describable pool)  ok" % entry)
            continue
        if c.returncode != 0:
            print("  entry %d: C refused a pack the Python decodes" % entry)
            print(c.stdout + c.stderr)
            return 1
        m = HEAD.search(c.stdout)
        if not m:
            print("  entry %d: cannot read the C summary line" % entry)
            return 1
        base, npads = info[0], info[1]
        pads = set(TP.choose_pads(b, recs, base, npads))
        layout, _, _ = TP.build_layout(b, recs, base, pads)
        L = {}
        for i, kind, sz, o, w, h in layout:
            if kind != "pad":
                L.setdefault(i, (kind, sz, o, w, h))
        pal = TP.resolve_palettes(b, recs)
        want = {}
        for d in TP.image_records(b):
            p = pal[d["image"]]
            want[d["name"]] = (d["w"], d["h"], d["image"], L[d["image"]][2], p, L[p][2])
        got = rows(c.stdout)
        if want != got:
            print("  entry %d: layout differs" % entry)
            for k in sorted(set(want) | set(got)):
                if want.get(k) != got.get(k):
                    print("     %-16s python %s | C %s" % (k, want.get(k), got.get(k)))
            return 1
        # pixel-exact: decode the first texture with both and compare the bytes
        name = sorted(want)[0]
        tmp = "/tmp/dw4_texpack_%d.raw" % entry
        subprocess.run([args.tool, "texpack", "--afs", args.afs, "--entry", str(entry),
                        "--decode", name, "--out", tmp], capture_output=True, check=True)
        d = [x for x in TP.image_records(b) if x["name"] == name][0]
        _w, _h, px = TP.decode_rgba(b, layout, d["image"], pal[d["image"]])
        cpx = open(tmp, "rb").read()
        os.unlink(tmp)
        if cpx != px:
            print("  entry %d: %s decodes differently (%d vs %d bytes)"
                  % (entry, name, len(cpx), len(px)))
            return 1
        print("  entry %-4d %3d textures: ids and block offsets agree, %s pixel-exact"
              % (entry, len(want), name))
        checked += 1
        texts += len(want)
    print("verify_texpack: %d pack(s), %d texture(s), C == Python" % (checked, texts))
    return 0


if __name__ == "__main__":
    sys.exit(main())
