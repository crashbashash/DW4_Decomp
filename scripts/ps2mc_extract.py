#!/usr/bin/env python3
"""
ps2mc_extract.py — list/extract saves from a PS2 memory card image using the
`ps2mc` library (handles both ECC-included and PCSX2-style ECC-less .ps2 files).

Usage:
  python3 ps2mc_extract.py list    <card.ps2>
  python3 ps2mc_extract.py extract <card.ps2> <outdir> [--only SUBSTR]
"""
import os
import struct
import sys

SB_MAGIC = b"Sony PS2 Memory Card Format "
SB_SIZE = 340


class Ps2mcFlat:
    """ECC-less (PCSX2 .ps2) variant: 512-byte pages, no 16-byte spare."""

    def __new__(cls, f):
        from ps2mc.ps2mc import Ps2mc

        class _Flat(Ps2mc):
            def read_page(self, n):
                self.file.seek(self.page_size * n)
                return self.file.read(self.page_size)

            def write_page(self, n, data):
                self.file.seek(self.page_size * n)
                self.file.write(data)

        return _Flat(f)


def open_card(path):
    from ps2mc.ps2mc import Ps2mc

    size = os.path.getsize(path)
    with open(path, "rb") as f:
        sb = f.read(SB_SIZE)
    if not sb.startswith(SB_MAGIC):
        raise SystemExit(f"{path}: not a PS2 memory card image (bad superblock magic)")

    page_len, ppc, ppb = struct.unpack_from("<HHH", sb, 40)
    clusters = struct.unpack_from("<L", sb, 48)[0]
    spare = (page_len // 128) * 4
    flat_size = clusters * ppc * page_len
    ecc_size = clusters * ppc * (page_len + spare)

    f = open(path, "rb")
    if size == ecc_size:
        kind = "ECC"
        mc = Ps2mc(f)
    elif size == flat_size:
        kind = "flat/ECC-less"
        mc = Ps2mcFlat(f)
    else:
        # fall back: prefer ps2mc default
        kind = f"unknown size {size} (expected {ecc_size} or {flat_size})"
        f.seek(0)
        mc = Ps2mc(f)
    return mc, kind


def walk(mc, entry, prefix, out):
    for e in mc.find_sub_entries(entry):
        if not e.is_exists():
            continue
        path = f"{prefix}/{e.name}"
        if e.is_dir():
            out.append(("DIR", path, 0))
            walk(mc, e, path, out)
        elif e.is_file():
            out.append(("FILE", path, e.length))


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 1
    cmd, card = sys.argv[1], sys.argv[2]
    mc, kind = open_card(card)
    print(f"# {card}: {kind} (page={mc.page_size} spill={mc.pages_per_cluster} "
          f"alloc_offset={mc.alloc_offset})", file=sys.stderr)

    out = []
    walk(mc, mc.get_root_entry(), "", out)

    if cmd == "list":
        for k, p, s in out:
            print(f"  [dir]  {p}" if k == "DIR" else f"  {s:9d}  {p}")
        print(f"\n{sum(1 for x in out if x[0]=='FILE')} files")
        return 0

    if cmd == "extract":
        if len(sys.argv) < 4:
            print("extract needs <outdir>")
            return 1
        outdir = sys.argv[3]
        only = sys.argv[sys.argv.index("--only") + 1] if "--only" in sys.argv else None

        # re-walk collecting entries
        stack = [(mc.get_root_entry(), "")]
        n = 0
        while stack:
            parent, prefix = stack.pop()
            for e in mc.find_sub_entries(parent):
                if not e.is_exists():
                    continue
                p = f"{prefix}/{e.name}"
                if e.is_dir():
                    stack.append((e, p))
                elif e.is_file():
                    if only and only not in p:
                        continue
                    dest = os.path.join(outdir, p.lstrip("/"))
                    os.makedirs(os.path.dirname(dest), exist_ok=True)
                    data = mc.read_data_cluster(e)
                    with open(dest, "wb") as w:
                        w.write(data)
                    print(f"  wrote {len(data):9d}  {dest}")
                    n += 1
        print(f"\nextracted {n} files -> {outdir}")
        return 0

    print(f"unknown command: {cmd}")
    return 1


if __name__ == "__main__":
    sys.exit(main())
