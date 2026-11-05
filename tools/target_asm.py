"""target_asm.py — relocatable retail assembly for objdiff's target objects.

objdiff compares a unit's compiled (base) object with a target object. asm/<name>.s keeps
every retail word as a plain `.word`, so a call or an address pair has no relocation there
while the compiled object has one, and objdiff would count every such instruction as a
difference. This writes the same retail words with the relocations restored: the symbolic
disassembly of tools/m2c_one.py names each call target (`jal NAME`) and each address pair
(`%hi(SYM)` / `%lo(SYM)`, `%gp_rel(SYM)`), and for those instructions the word is emitted
with its relocated field zeroed after a `.reloc` directive, so the assembled object holds the
exact retail bytes once relocated, with the same symbols the compiler references.

Retail cannot say how the source spelled an address: `s_TEXTCTL_0051b3c0` or `DAT_0051b3c0`,
`dpadd` or `__adddf3`, an array base plus an offset or the element's own address, a relocation or
a literal. objdiff compares those spellings, so with `--base` a word takes the compiled object's
spelling when that word, relocated, is retail's. The address still comes from retail: a word that
relocates to anything else keeps the disassembly's spelling and objdiff reports it.

    python3 tools/target_asm.py OUT.s NAME... [--base OBJECT]
"""
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import unitobjects
import verify

LINE = re.compile(r"^/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)$")
HI = re.compile(r"%hi\(([^)+]+)(?:\+(0x[0-9a-fA-F]+|\d+))?\)")
LO = re.compile(r"%lo\(([^)+]+)(?:\+(0x[0-9a-fA-F]+|\d+))?\)")
GP = re.compile(r"%gp_rel\(([^)+]+)(?:\+(0x[0-9a-fA-F]+|\d+))?\)")
JUMPS = {"jal", "j"}

PRELUDE = """\t.set noat
\t.set noreorder
\t.section .text
"""

_CTX = {}


def _context(symbols, elf):
    if not _CTX:
        import automatch as am
        import m2c_one
        syms = am.load_symbols(symbols)
        _CTX.update(img=open(elf, "rb").read(), syms={n: (v, s) for v, s, n in syms},
                    names={v: n for v, s, n in syms}, gp=m2c_one.load_gp(elf),
                    bounds=m2c_one.load_bounds(elf))
    return _CTX


def spellings(raw, relocs, resolve, gp, retail):
    """{offset: (relocation or None, word)} for the words of `raw` that relocate to `retail`
    (a function of the offset). A relocation is `(type name, symbol)`."""
    patched, _, unresolved = verify.apply_relocs(raw, relocs, resolve, gp)
    if patched is None:
        return {}
    skipped = {entry[0] for entry in unresolved}
    kinds = {value: key for key, value in verify.TYPES.items()}
    kinds[verify.R_GPREL16] = "R_MIPS_GPREL16"          # TYPES maps R_MIPS_LITERAL here too
    relocated = {off: (kinds[kind], name) for _section, off, kind, name, _addend in relocs}
    out = {}
    for off in range(0, len(raw) - 3, 4):
        word = struct.unpack_from("<I", raw, off)[0]
        if off not in skipped and struct.unpack_from("<I", patched, off)[0] == retail(off):
            out[off] = (relocated.get(off), word)
    return out


def compiled_symbol(name, va, syms):
    """`name`'s symbol in the compiled object: a C++ whole-file row keeps the mangled one."""
    group = unitobjects.group_for(va)
    if group is not None and name not in syms:
        if group.owner == va and group.symbol:
            return group.symbol
        return next((symbol for symbol, address in group.emitted if address == va), name)
    return name


def base_spellings(base, name, va, symbols, ctx):
    """`spellings` of `name` in the compiled object `base`, or {} when it does not hold it."""
    syms, _ = verify.object_syms(base)
    found = syms.get(compiled_symbol(name, va, syms))
    if found is None or not isinstance(found[0], int):
        return {}
    section, offset = found[0], found[1]
    if offset:
        return {}
    headers = verify.elf_section_headers(base)
    raw = verify.object_section(base, headers[section][0], section)
    by_name, _ = verify.load_symbols(symbols)

    def resolve(symbol):
        try:
            return verify.sym_address(symbol, by_name, symbols)
        except verify.SymbolError:
            return None

    def retail(off):
        return struct.unpack("<I", verify.va_bytes(ctx["image"], va + off, 4))[0]

    return spellings(raw, verify.object_relocs(base, target_section=section), resolve, ctx["gp"], retail)


def function_asm(name, symbols, elf, base=None):
    """Relocatable retail assembly for one function: `.reloc` + masked `.word` per relocation."""
    import automatch as am
    import m2c_one
    ctx = _context(symbols, elf)
    va, size = ctx["syms"][name]
    ctx.setdefault("image", verify.read_elf(elf))
    compiled = base_spellings(base, name, va, symbols, ctx) if base else {}
    table = am.disassemble(ctx["img"], va, va + size)
    text = m2c_one.asm_for(va, name, size, table, ctx["names"], bounds=ctx["bounds"],
                           gp=ctx["gp"], ee_abi=False)
    out = ["\t.globl %s" % name, "\t.type %s, @function" % name, "\t.align 2", "%s:" % name]
    for line in text.splitlines():
        m = LINE.match(line.strip())
        if not m:
            continue
        address, word, mnemonic, operands = int(m.group(1), 16), int(m.group(2), 16), m.group(3), m.group(4)
        if address >= va + size:            # m2c's listing runs on past the symbol's extent
            break
        if address - va in compiled:
            spelled, word = compiled[address - va]
            if spelled:
                out.append("\t.reloc ., %s, %s" % spelled)
            out.append("\t.word 0x%08x  /* %s %s */" % (word, mnemonic, operands.replace("*/", "")))
            continue
        reloc = None
        for rx, kind, mask in ((HI, "R_MIPS_HI16", 0xffff0000), (LO, "R_MIPS_LO16", 0xffff0000),
                               (GP, "R_MIPS_GPREL16", 0xffff0000)):
            found = rx.search(operands)
            if found:
                addend = int(found.group(2), 0) if found.group(2) else 0
                reloc = (kind, found.group(1) + ("+%d" % addend if addend else ""), word & mask)
                break
        if reloc is None and mnemonic in JUMPS and not operands.startswith((".", "$")):
            target = operands.split()[0]
            if target in ctx["syms"]:
                reloc = ("R_MIPS_26", target, word & 0xfc000000)
        if reloc:
            out.append("\t.reloc ., %s, %s" % (reloc[0], reloc[1]))
            word = reloc[2]
        out.append("\t.word 0x%08x  /* %s %s */" % (word, mnemonic, operands.replace("*/", "")))
    out.append("\t.size %s, . - %s" % (name, name))
    return "\n".join(out) + "\n"


def write(out, names, symbols=None, elf=None, base=None):
    symbols = symbols or os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
    elf = elf or os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
    os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
    with open(out, "w") as fh:
        fh.write(PRELUDE)
        for name in names:
            fh.write(function_asm(name, symbols, elf, base))


if __name__ == "__main__":
    args = sys.argv[1:]
    compiled = None
    if "--base" in args:
        at = args.index("--base")
        compiled = args[at + 1]
        del args[at:at + 2]
    write(args[0], args[1:], base=compiled)
