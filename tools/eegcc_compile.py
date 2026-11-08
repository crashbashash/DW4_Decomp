#!/usr/bin/env python3
"""eegcc_compile.py — compile one C file to an object with the Sony EE GCC 2.96.

The Sony-built libraries in the retail image (libdma, libpad, libmpeg, the CRI middleware; see
docs/engine/sd-prologue.md) cannot come out of MWCC. The pinned compiler is the 32-bit
`ee-gcc` 2.96-ee-001003-1 build kept under `local/`. Its `-c` mode crashes inside `cc1` when it writes
its own temporary assembly, so the object is built in two steps, `-S` and then the sibling `ee-as`.

A `.S` source is a hand-written assembly file (config/assembly-sources.tsv): it is preprocessed by
the same driver and assembled by the same `ee-as`, with no compiler pass and no debug records.

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


def assembler_env():
    """`ee-as` copies an expanded macro with an overlapping memcpy, which glibc's SSSE3 version gets
    wrong at some alignments. Turn the vector versions off, so the choice does not
    depend on the CPU, and give every allocation its own mapping, so the alignment does not depend on
    the C library. DW4_EE_AS_SHIM names a library that makes the copy itself safe (docker/)."""
    env = dict(os.environ, GLIBC_TUNABLES="glibc.cpu.hwcaps=-SSSE3,-SSE2:glibc.malloc.mmap_threshold=0")
    shim = os.environ.get("DW4_EE_AS_SHIM")
    if shim:
        if not os.path.exists(shim):
            raise SystemExit("eegcc_compile: DW4_EE_AS_SHIM names a missing file: " + shim)
        env["LD_PRELOAD"] = shim
    return env


def main(argv):
    compiler, flags, source, out = argv[0], argv[1:-2], argv[-2], argv[-1]
    bindir = os.path.dirname(os.path.abspath(compiler))
    with tempfile.TemporaryDirectory(prefix="eegcc_") as tmp:
        asm = os.path.join(tmp, "unit.s")
        asflags = [f[4:].replace(",", " ").split() for f in flags if f.startswith("-Wa,")]
        asflags = [x for g in asflags for x in g]
        flags = [f for f in flags if not f.startswith("-Wa,")]
        assembly = source.endswith(".S")
        if any(f in ("-g", "-g2", "-g3") for f in flags) and not assembly:
            asflags = ["-g"] + asflags
        asflags = [f for f in flags if f.startswith("-G") and f[2:].isdigit()] + asflags
        if assembly:
            cpp = [f for f in flags if f.startswith(("-I", "-D", "-U"))]
            r = subprocess.run([compiler, "-E", *cpp, source, "-o", asm], capture_output=True, text=True)
        else:
            r = subprocess.run([compiler, "-S", *flags, source, "-o", asm],
                               capture_output=True, text=True)
        if r.returncode:
            sys.stderr.write(r.stdout + r.stderr)
            return 1
        # 2.96 keeps its assembler beside ee-gcc; the 2.9-ee releases keep it at ee/bin/as
        assembler = os.path.join(bindir, "ee-as")
        if not os.path.exists(assembler):
            assembler = os.path.join(os.path.dirname(bindir), "ee", "bin", "as")
        r = subprocess.run([assembler, *asflags, "-o", out, asm],
                           capture_output=True, text=True, env=assembler_env())
        if r.returncode:
            sys.stderr.write(r.stdout + r.stderr)
            return 1
    fix_symtab_info(out)
    if "-ffunction-sections" in flags:
        separate_text_sections(out)
    return 0


def separate_text_sections(path):
    """Rename each `.text.<function>` to `.text`, keeping the sections apart.

    A whole-file unit's object carries one `.text` section per function, the shape MWCC writes and
    the shape tools/verify.py and tools/linkgen.py read; `-ffunction-sections` gives gcc's
    `.text.<function>` names, and objcopy keeps same-named sections separate."""
    headers = subprocess.run(["mipsel-linux-gnu-objdump", "-h", path],
                             capture_output=True, text=True, check=True).stdout.split("\n")
    names = [f[1] for f in (line.split() for line in headers)
             if len(f) > 1 and f[1].startswith(".text.")]
    if names:
        # gcc's own `.text` is empty here; drop it so the function sections are the only ones
        data = [f[1] for f in (line.split() for line in headers)
                if len(f) > 2 and f[1] in DATA_SECTIONS and int(f[2], 16)]
        subprocess.run(["mipsel-linux-gnu-objcopy", "--remove-section", ".text",
                        *[a for n in names for a in ("--rename-section", n + "=.text")],
                        *[a for d in data for a in ("--add-symbol", "@%s=%s:0,local,object" % (d[1:], d))],
                        path], check=True)
        retarget_section_relocs(path)


# data sections whose references `ee-as` resolves through the section symbol
DATA_SECTIONS = (".rodata", ".data", ".sdata", ".bss", ".sbss")


def retarget_section_relocs(path):
    """Point a relocation against a section symbol at a named symbol at offset zero of that section.

    `ee-as` resolves a reference inside the object through the section symbol. With one section per
    function every code section symbol is now called `.text`, so a call names its target only by
    section index: the function symbol at offset zero names it again. A data section's references
    go to the `@<section>` symbol separate_text_sections adds, a name the whole-file rows and the
    link can rename (a section symbol cannot be). ELF32, little endian, REL relocations (the addend
    stays in the instruction)."""
    with open(path, "r+b") as fh:
        data = bytearray(fh.read())
        shoff, = struct.unpack_from("<I", data, 0x20)
        shentsize, shnum = struct.unpack_from("<HH", data, 0x2E)
        sections = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
        symtab = next(i for i, s in enumerate(sections) if s[1] == 2)
        sym_off, sym_size, sym_ent = sections[symtab][4], sections[symtab][5], sections[symtab][9]
        syms = [struct.unpack_from("<IIIBBH", data, sym_off + k * sym_ent) for k in range(sym_size // sym_ent)]
        strtab = sections[sections[symtab][6]][4]

        def name(offset):
            return data[strtab + offset:data.index(0, strtab + offset)].decode()

        text = {i for i, s in enumerate(sections) if s[1] == 1 and s[2] & 0x4}   # PROGBITS, executable
        section_sym = {k: s[5] for k, s in enumerate(syms) if s[3] & 0xf == 3}
        function_at = {s[5]: k for k, s in enumerate(syms)
                       if s[3] & 0xf == 2 and s[1] == 0 and s[5] in text}
        function_at.update({s[5]: k for k, s in enumerate(syms)
                            if s[1] == 0 and s[5] not in text and name(s[0]).startswith("@")})
        for s in sections:
            if s[1] != 9 or s[6] != symtab:                                     # SHT_REL
                continue
            for k in range(s[5] // 8):
                at = s[4] + 8 * k
                info, = struct.unpack_from("<I", data, at + 4)
                target = section_sym.get(info >> 8)
                if target is not None and target in function_at:
                    struct.pack_into("<I", data, at + 4, (function_at[target] << 8) | (info & 0xff))
        fh.seek(0)
        fh.write(data)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
