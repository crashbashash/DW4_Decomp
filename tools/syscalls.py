#!/usr/bin/env python3
"""syscalls.py — recover the EE kernel syscall stubs → `config/SLUS-20836/syscalls.txt`.

The PS2 EE kernel is entered with the `syscall` instruction, the number in `$v1`.
Every kernel routine the game calls is linked in as a 16-byte stub:

    li $v1, <number>        # addiu $v1, $zero, <number>
    syscall                 # 0x0000000c
    jr $ra
    nop

80 such stubs are in the binary, at 0x0010aae0..0x00114070 — `_Exit` (4), `SleepThread`
(50), `FlushCache` (100), the `sceSif*` family, and the `i*`/`_i*` interrupt-control
variants, which use the 0xFF80..0xFFFF range (e.g. `iResumeThread` = 65478).

**These are Sony SDK (`libkernel`) code, not game source.** The game's C called
`_Exit(0)`; the implementation came from the SDK's own assembly, which is proprietary
and not in this repo. There is therefore no game C to recover for them, and no C
spelling is even available: MWCC's integrated assembler rejects the `syscall` mnemonic
in an inline-asm block (`unexpected end of line`), so the bytes cannot be reproduced
from `src/` either. They are recorded here — number, address, name — and the m2c
pipeline **skips** them (`status = sdk` in the worklist) rather than scoring them as
compile failures. Three functions *use* a syscall inline but are not stubs (`entry`,
`FUN_0010bd90`, `FUN_0010bea8`); they are recorded with number `-` and are not skipped.

Usage:
  syscalls.py                    # report
  syscalls.py --write            # write config/SLUS-20836/syscalls.txt
  syscalls.py --syscall 50       # all stubs for one number
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
SYMBOLS_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
OUT_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "syscalls.txt")

FILE_BASE, VADDR_BASE = 0x80, 0x100000
SYSCALL_WORD = 0x0000000C
JR_RA = 0x03E00008
JR_RA_OPS = (0x03E00008, 0x03400008)          # jr $ra (R5900 allows the `e` variants)


def words(img, va, size):
    off = FILE_BASE + (va - VADDR_BASE)
    return [struct.unpack_from("<I", img, off + 4 * i)[0] for i in range(size // 4)]


def is_stub(w):
    """The 16-byte kernel-stub shape; -> the syscall number, or None."""
    if len(w) != 4 or w[1] != SYSCALL_WORD or w[2] not in JR_RA_OPS or w[3] != 0:
        return None
    if (w[0] >> 26) != 0x09:                  # addiu
        return None
    if ((w[0] >> 21) & 0x1F) != 0 or ((w[0] >> 16) & 0x1F) != 3:
        return None                           # must be v1, zero
    return w[0] & 0xFFFF


def load_symbols(path):
    out = []
    for ln in open(path):
        if ln.startswith("#"):
            continue
        p = ln.split()
        if len(p) >= 3:
            out.append((int(p[0], 16), int(p[1], 16), p[2]))
    return out


def scan(elf=ELF_DEFAULT, symbols=SYMBOLS_DEFAULT):
    """-> (stubs, inline): [(va, size, num, name)] and [(va, size, name, word_index)]."""
    img = open(elf, "rb").read()
    stubs, inline = [], []
    for va, size, name in load_symbols(symbols):
        w = words(img, va, size)
        if SYSCALL_WORD not in w:
            continue
        num = is_stub(w)
        if num is not None:
            stubs.append((va, size, num, name))
        else:
            inline.append((va, size, name, w.index(SYSCALL_WORD)))
    return stubs, inline


def load(path=OUT_DEFAULT):
    """{va: number} of the skipped stubs, for the pipeline."""
    if not os.path.exists(path):
        return {}
    out = {}
    for ln in open(path):
        if ln.startswith("#"):
            continue
        p = ln.split()
        if len(p) >= 3 and p[2] != "-":
            out[int(p[0], 16)] = int(p[2], 10)
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--symbols", default=SYMBOLS_DEFAULT)
    ap.add_argument("--out", default=OUT_DEFAULT)
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--syscall", type=lambda s: int(s, 0), default=None,
                    help="list the stubs for one syscall number")
    a = ap.parse_args(argv)

    stubs, inline = scan(a.elf, a.symbols)
    if a.syscall is not None:
        for va, size, num, name in stubs:
            if num == a.syscall:
                print("%08x %4d %s" % (va, size, name))
        return 0

    lo = {n for _, _, n, _ in stubs if 0xFF80 <= n}
    print("syscall stubs : %d (%d bytes, %d distinct numbers; %d in the 0xFF80.. range)"
          % (len(stubs), sum(s for _, s, _, _ in stubs), len({n for _, _, n, _ in stubs}), len(lo)))
    print("inline users  : %d  (%s)"
          % (len(inline), ", ".join("%s@0x%x" % (n, v) for v, _s, n, _i in inline)))
    if not a.write:
        print("(dry run; pass --write to emit %s)" % a.out)
        return 0
    with open(a.out, "w") as fh:
        fh.write("# va size syscall name — GENERATED by tools/syscalls.py; do not edit.\n"
                 "# The EE kernel's statically-linked syscall stubs: `li $v1,N; syscall; jr $ra; nop`.\n"
                 "# Sony SDK (libkernel) code, not game source — the m2c pipeline skips these\n"
                 "# (worklist status `sdk`). `-` marks a function that uses a syscall inline.\n")
        for va, size, num, name in sorted(stubs + [(v, s, 0, n) for v, s, n, _ in inline]):
            n = num if num else "-"
            fh.write("%08x %04x %5s %s\n" % (va, size, n, name))
    print("wrote %s (%d rows)" % (a.out, len(stubs) + len(inline)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
