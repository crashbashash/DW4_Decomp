#!/usr/bin/env python3
"""eegcc_compile.py — compile one C file to an object with the Sony EE GCC 2.96.

The Sony-built libraries in the retail image (libdma, libpad, libmpeg, the CRI middleware; see
docs/engine/sd-prologue.md) cannot come out of MWCC. The pinned compiler is the 32-bit
`ee-gcc` 2.96-ee-001003-1 build kept under `local/`. Its `-c` mode crashes inside `cc1` when it writes
its own temporary assembly, so the object is built in two steps, `-S` and then the sibling `ee-as`.

Usage: eegcc_compile.py <ee-gcc> <flags...> <source> <object>
"""
import os
import struct
import subprocess
import sys
import tempfile


def fix_symtab_info(path):
    """Set .symtab's sh_info to the real count of leading local symbols.

    The 2.96-era `ee-as` counts only the section symbols as local but also writes the
    `gcc2_compiled.` and `__gnu_compiled_c` marker symbols before the globals; GNU ld then rejects
    the object ("local symbol at index N (>= sh_info)"). ELF32, little endian.
    """
    with open(path, "r+b") as fh:
        data = bytearray(fh.read())
        shoff, = struct.unpack_from("<I", data, 0x20)
        shentsize, shnum = struct.unpack_from("<HH", data, 0x2E)
        for i in range(shnum):
            base = shoff + i * shentsize
            sh_type, = struct.unpack_from("<I", data, base + 4)
            if sh_type != 2:                       # SHT_SYMTAB
                continue
            offset, size = struct.unpack_from("<II", data, base + 0x10)
            entsize, = struct.unpack_from("<I", data, base + 0x24)
            locals_ = 0
            for k in range(size // entsize):
                info = data[offset + k * entsize + 12]
                if info >> 4 == 0:                 # STB_LOCAL
                    locals_ = k + 1
                else:
                    break
            struct.pack_into("<I", data, base + 0x1C, locals_)
        fh.seek(0)
        fh.write(data)


def main(argv):
    compiler, flags, source, out = argv[0], argv[1:-2], argv[-2], argv[-1]
    bindir = os.path.dirname(os.path.abspath(compiler))
    with tempfile.TemporaryDirectory(prefix="eegcc_") as tmp:
        asm = os.path.join(tmp, "unit.s")
        asflags = [f[4:].replace(",", " ").split() for f in flags if f.startswith("-Wa,")]
        asflags = [x for g in asflags for x in g]
        flags = [f for f in flags if not f.startswith("-Wa,")]
        if any(f in ("-g", "-g2", "-g3") for f in flags):
            asflags = ["-g"] + asflags
        asflags = [f for f in flags if f.startswith("-G") and f[2:].isdigit()] + asflags
        r = subprocess.run([compiler, "-S", *flags, source, "-o", asm],
                           capture_output=True, text=True)
        if r.returncode:
            sys.stderr.write(r.stdout + r.stderr)
            return 1
        r = subprocess.run([os.path.join(bindir, "ee-as"), *asflags, "-o", out, asm],
                           capture_output=True, text=True)
        if r.returncode:
            sys.stderr.write(r.stdout + r.stderr)
            return 1
    fix_symtab_info(out)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
