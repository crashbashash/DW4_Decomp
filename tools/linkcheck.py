#!/usr/bin/env python3
"""
linkcheck.py — compare a relinked section against the retail binary.

The end-to-end test of the whole build: assemble/compile every layout unit, link
them into one section, and require the 4,541,184 bytes to match `game.elf` exactly.

  make link    # linkgen --all, ld, then this
  linkcheck.py build/game.elf

After the BYTE-IDENTICAL verdict a second line bounds the orphans: bytes the link
placed outside .text must all be `.exceptix`/`.exception` and total no more than
the orphan debt `make check` recorded in data/check-categories.tsv.

Exit status: 0 identical and orphans within the recorded debt, 1 otherwise, 2 error.
"""
import argparse
import os
import re
import struct
import subprocess
import sys

SECTION_LO = 0x100000
SECTION_SZ = 0x454B00
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")


def elf_sections(elf):
    """[(name, type, flags, addr, offset, size)] from the ELF32 little-endian section headers.

    Parsed here rather than through readelf so the build-option tests (synthetic ELFs,
    hosted CI without binutils) and the oracle runner read the same headers.
    """
    with open(elf, "rb") as fh:
        data = fh.read()
    if len(data) < 0x34 or data[:4] != b"\x7fELF":
        return []                                   # not an ELF (the build-option tests use stubs)
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    if not shoff or not shnum or shstrndx >= shnum:
        return []
    def header(i):
        return struct.unpack_from("<IIIIII", data, shoff + i * shentsize)   # name type flags addr offset size
    str_off = header(shstrndx)[4]
    rows = []
    for i in range(shnum):
        name_off, sh_type, flags, addr, off, size = header(i)
        end = data.index(b"\0", str_off + name_off)
        name = data[str_off + name_off:end].decode("ascii", "replace")
        rows.append((name, sh_type, flags, addr, off, size))
    return rows


def section_bytes(elf, name=".text"):
    """(vma, bytes) for a named section, read at its file offset (NOT via objcopy,
    which pads an -O binary to the VMA)."""
    for sec, _type, _flags, addr, off, size in elf_sections(elf):
        if sec == name:
            with open(elf, "rb") as fh:
                fh.seek(off)
                return addr, fh.read(size)
    return None, None


def orphan_sections(elf):
    """[(name, size)] of allocated PROGBITS output sections other than .text in the linked ELF.

    Those are compiler outputs the link script did not place: data the byte
    compare below never sees. `make check` reports the units they come from
    (exc=extra for exception metadata); this names them so the gap is visible.
    """
    return [(name, size) for name, sh_type, flags, _addr, _off, size in elf_sections(elf)
            if sh_type == 1 and flags & 2 and name != ".text"]


ORPHAN_SECTIONS = (".exceptix", ".exception")
CATEGORIES_TSV = os.path.join(ROOT, "data", "check-categories.tsv")


def recorded_orphan_debt(path=CATEGORIES_TSV):
    """(bytes, units) of exception metadata `make check` recorded as unplaceable.

    tools/check.py appends `; orphan N bytes` to the diagnostic of every unit whose
    `.exceptix`/`.exception` the relink cannot put at a retail slot (exc=extra or
    exc=differ). Their sum bounds what may be linked outside .text.
    """
    total = units = 0
    if not os.path.exists(path):
        return 0, 0
    for ln in open(path, errors="replace"):
        if ln.startswith("#"):
            continue
        m = re.search(r"; orphan (\d+) bytes", ln)
        if m:
            total += int(m.group(1))
            units += 1
    return total, units


def orphan_gate(linked):
    """Print the orphan line; 0 when every orphan is exception metadata within the recorded debt."""
    orphans = orphan_sections(linked)
    debt, units = recorded_orphan_debt()
    total = sum(size for _, size in orphans)
    parts = ", ".join("%s %d" % (name, size) for name, size in orphans) or "none"
    foreign = [name for name, _ in orphans if name not in ORPHAN_SECTIONS]
    ok = not foreign and total <= debt
    print("linkcheck: orphans: %d bytes linked outside .text (%s) %s recorded debt %d bytes "
          "(%d exc=extra/differ units in %s)  %s"
          % (total, parts, "<=" if total <= debt else ">", debt, units,
             os.path.relpath(CATEGORIES_TSV, ROOT), "OK" if ok else "REFUSED"))
    for name in foreign:
        print("linkcheck: orphan section %s is not exception metadata: a compiler output with no retail "
              "slot that make check does not account for" % name, file=sys.stderr)
    if total > debt:
        print("linkcheck: more bytes orphaned than make check recorded: run make check, or a unit's "
              "metadata was not placed", file=sys.stderr)
    return 0 if ok else 1


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("linked", nargs="?", default="build/game.elf")
    ap.add_argument("--retail", "--elf", dest="retail",
                    default=os.environ.get("DW4_ELF", ELF_DEFAULT))
    ap.add_argument("--section-start", type=lambda s: int(s, 0), default=SECTION_LO)
    ap.add_argument("--section-size", type=lambda s: int(s, 0), default=SECTION_SZ)
    a = ap.parse_args(argv if argv is not None else [])
    linked, retail_elf = a.linked, a.retail
    if a.section_start < 0x100000 or a.section_size <= 0 or a.section_start + a.section_size > 0x100000000:
        ap.error("invalid section bounds for the supported retail mapping")
    if not os.path.exists(linked):
        print(f"linkcheck: no such file: {linked}", file=sys.stderr)
        return 2

    vma, ours = section_bytes(linked)
    if ours is None:
        print("linkcheck: linked file has no .text", file=sys.stderr)
        return 2
    img = open(retail_elf, "rb").read()
    offset = a.section_start - 0x100000 + 0x80
    retail = img[offset:offset + a.section_size]
    if len(retail) != a.section_size:
        print("linkcheck: selected section runs past the retail image", file=sys.stderr)
        return 2

    print(f"linked .text: vma=0x{vma:x} size={len(ours)}   retail: {len(retail)}")
    if vma != a.section_start:
        print(f"linkcheck: VMA MISMATCH: expected 0x{a.section_start:x}", file=sys.stderr)
        return 1
    if len(ours) != len(retail):
        print(f"linkcheck: SIZE MISMATCH by {len(ours) - len(retail)} bytes")
        return 1
    bad = [i for i in range(len(ours)) if ours[i] != retail[i]]
    if not bad:
        print("linkcheck: BYTE-IDENTICAL — the relinked section matches retail exactly")
        # Second gate: what the link put OUTSIDE the compared section. Only exception
        # metadata `make check` recorded as unplaceable may be there, and no more of it.
        return orphan_gate(linked)
    print(f"linkcheck: {len(bad)} differing bytes ({100.0*len(bad)/len(ours):.2f}%)")
    for i in bad[:8]:
        print(f"   VA 0x{a.section_start+i:06x}: ours {ours[i:i+4].hex()}  retail {retail[i:i+4].hex()}")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
