"""listing.py — instruction listings of a retail function and of a compiled candidate, and the debug
records MWCC writes under `-g`. Shared by tools/frameslots.py and tools/residual_census.py.

A listing is a list of `Insn(offset, mnemonic, operands, callee, target)`: `offset` counts bytes from
the function start, `callee` names a `jal` target (from symbols.txt for retail, from the object's
R_MIPS_26 relocation for a candidate), `target` is a branch's destination as a byte offset from the
function start. Retail comes from the image, or from the split's `asm/<name>.s` comments when a whole
corpus is read; a candidate is compiled the way tools/check.py builds it (tools/project.py
`compile_unit`: its definition under its unit profile) and read from the object without relocations
applied, which is enough for stack offsets and masked shapes.

`debug_records` reads the DWARF 1 sections b52 writes with `-g` (one `.debug` and one `.line`
section per function, measured on the core profile): the function's parameters and locals in
declaration order, each with its location (`("sp", offset)` for a frame slot, `("reg", name)` for a
register, None when the record has no location), and the line table (byte offset -> line of the file
the function is defined in; inlined code reports lines of the file it came from, which the record
does not name). `-g` leaves the code unchanged on the bodies measured; `compile_pair` still compares
the two bodies and reports when they differ, so a record is never applied to code it does not describe.
"""
import collections
import os
import re
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import cc  # noqa: E402
import project  # noqa: E402
import units  # noqa: E402
import verify  # noqa: E402

ROOT = verify.ROOT
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
REGS = ("zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra")

Insn = collections.namedtuple("Insn", "offset mnemonic operands callee target")
Debug = collections.namedtuple("Debug", "file variables lines")
Variable = collections.namedtuple("Variable", "name kind location")   # kind: param | local

_OBJDUMP_LINE = re.compile(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)$")
_ASM_LINE = re.compile(r"/\* ([0-9a-f]{8}): (\S+)\s*(.*?) \*/")
_JAL = re.compile(r"^0x([0-9a-f]+)$")
_BRANCH_TARGET = re.compile(r"(?:^|,)0x([0-9a-f]+)$")
_MEMORY = re.compile(r"^(-?\d+)\((\w+)\)$")
_REGISTER = re.compile(r"\b(?:zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|\$?f\d+)\b")
BRANCHES = {"b", "beq", "bne", "beqz", "bnez", "bgez", "bgtz", "blez", "bltz", "bal", "bgezal", "bltzal",
            "beql", "bnel", "beqzl", "bnezl", "bgezl", "bgtzl", "blezl", "bltzl", "bc1t", "bc1f", "bc1tl",
            "bc1fl", "j"}
WIDTHS = {"lb": 1, "lbu": 1, "sb": 1, "lh": 2, "lhu": 2, "sh": 2, "lw": 4, "lwu": 4, "sw": 4, "lwl": 4,
          "lwr": 4, "swl": 4, "swr": 4, "lwc1": 4, "swc1": 4, "ld": 8, "sd": 8, "ldl": 8, "ldr": 8, "sdl": 8,
          "sdr": 8, "ldc1": 8, "sdc1": 8, "lq": 16, "sq": 16, "lqc2": 16, "sqc2": 16}
STORES = {m for m in WIDTHS if m.startswith("s")}
# registers kept by name in a register-aware shape: their role is fixed by the ABI
FIXED = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "gp", "sp", "fp", "ra"}


def symbols(path=SYMBOLS):
    """({name: (va, size)}, {va: (name, size)}) from symbols.txt."""
    return verify.load_symbols(path)


def memory_operand(insn):
    """(offset, base register) of a load or store, or None."""
    if insn.mnemonic not in WIDTHS:
        return None
    m = _MEMORY.match(insn.operands.rsplit(",", 1)[-1])
    return (int(m.group(1)), m.group(2)) if m else None


def registers(insn):
    """The register operands of an instruction, in operand order."""
    return _REGISTER.findall(insn.operands)


SHIFTS = {"sll", "srl", "sra", "dsll", "dsrl", "dsra", "dsll32", "dsrl32", "dsra32"}


def token(insn):
    """One instruction with its registers and immediates masked: the mnemonic, `.sp`/`.gp` on a
    load or store through the frame or the small-data base, `<`/`>` on a branch backwards or forwards,
    and a constant shift's amount (`dsll32/0` zero-extends, `dsll32/9` masks a 23-bit field)."""
    mem = memory_operand(insn)
    if mem:
        return insn.mnemonic + (".sp" if mem[1] == "sp" else ".gp" if mem[1] == "gp" else "")
    if insn.target is not None:
        return insn.mnemonic + ("<" if insn.target <= insn.offset else ">")
    if insn.mnemonic in SHIFTS:
        return "%s/%d" % (insn.mnemonic, int(insn.operands.rsplit(",", 1)[-1], 0))
    return insn.mnemonic


def shape(insns, with_registers=False):
    """The masked tokens of `insns`; `with_registers` appends each instruction's registers renamed by
    first appearance in the window (`S0`, `S1` for saved registers, `T0` for other temporaries, `F0`
    for floating-point ones; the ABI registers in FIXED keep their names), so a register-only
    difference has a shape too."""
    names, out = {}, []
    for insn in insns:
        tok = token(insn)
        if with_registers:
            regs = []
            for reg in registers(insn):
                if reg not in FIXED and reg not in names:
                    kind = "S" if re.match(r"s[0-8]$", reg) else "F" if "f" in reg else "T"
                    names[reg] = "%s%d" % (kind, sum(1 for v in names.values() if v[0] == kind))
                regs.append(names.get(reg, reg))
            tok += ":" + ",".join(regs)
        out.append(tok)
    return out


def disassemble(words, va=0):
    """[(mnemonic, operands)] of little-endian words placed at `va` (R5900 objdump)."""
    path = os.path.join(cc.scratch_dir(), "listing_%s.bin" % verify.TMP_TAG())
    with open(path, "wb") as fh:
        fh.write(b"".join(struct.pack("<I", w) for w in words))
    out = subprocess.run(["mipsel-linux-gnu-objdump", "-D", "-z", "-b", "binary", "-m", "mips:5900", "-EL",
                          "--adjust-vma", hex(va), path], capture_output=True, text=True, check=True).stdout
    os.remove(path)
    rows = {}
    for line in out.splitlines():
        m = _OBJDUMP_LINE.match(line)
        if m:
            rows[int(m.group(1), 16)] = (m.group(3), m.group(4).strip())
    return [rows.get(va + 4 * i, ("?", "")) for i in range(len(words))]


def _insn(offset, mnemonic, operands, callee, va):
    m = _BRANCH_TARGET.search(operands) if mnemonic in BRANCHES else None
    return Insn(offset, mnemonic, operands, callee, int(m.group(1), 16) - va if m else None)


def _retail_callee(mnemonic, operands, by_va):
    m = _JAL.match(operands) if mnemonic == "jal" else None
    return by_va[int(m.group(1), 16)][0] if m and int(m.group(1), 16) in by_va else None


def retail_listing(va, elf=verify.ELF_DEFAULT, symbols_path=SYMBOLS):
    """The retail function at `va` as a listing, read from the image."""
    _, by_va = symbols(symbols_path)
    _name, size = by_va[va]
    data = verify.va_bytes(verify.read_elf(elf), va, size)
    words = [struct.unpack_from("<I", data, 4 * i)[0] for i in range(size // 4)]
    return [_insn(4 * i, mn, ops, _retail_callee(mn, ops, by_va), va)
            for i, (mn, ops) in enumerate(disassemble(words, va))]


def asm_listing(path, by_va):
    """A retail listing from the split's `asm/<name>.s` comments (no disassembler run)."""
    out, va = [], None
    with open(path) as fh:
        for line in fh:
            m = _ASM_LINE.search(line)
            if m:
                va = int(m.group(1), 16) if va is None else va
                mn, ops = m.group(2), m.group(3).strip()
                out.append(_insn(4 * len(out), mn, ops, _retail_callee(mn, ops, by_va), va))
    return out


def compile_function(name, source, out, extra_flags=""):
    """Compile `name` from `source` as tools/check.py does (into `out`); ValueError on failure.
    tools/project.py `compile_unit` builds a function that has a provisional per-function override under
    that override; check.py tries the unit profile first, so for those few the two can differ."""
    if project.compile_unit(project.DEFAULT_VERSION, name, os.path.abspath(source), out,
                            extra_flags=extra_flags, quiet=True) or not os.path.exists(out):
        raise ValueError("%s: %s does not compile" % (source, name))
    return out


def body(obj, name):
    """The raw `.text` bytes of `name` in a relocatable object."""
    off, size, ndx = verify.object_sym(obj, name)
    if size is None or not isinstance(ndx, int):
        raise ValueError("%s defines no %s" % (obj, name))
    return verify.object_section(obj, ".text", ndx)[off:off + size]


def object_listing(obj, name):
    """The candidate body of `name` in `obj` as a listing, callees from its R_MIPS_26 relocations."""
    off, size, ndx = verify.object_sym(obj, name)
    text = body(obj, name)
    callees = {o - off: sym for _sec, o, kind, sym, _add in verify.object_relocs(obj, target_section=ndx)
               if kind == verify.R_26 and off <= o < off + size}
    words = [struct.unpack_from("<I", text, 4 * i)[0] for i in range(size // 4)]
    return [_insn(4 * i, mn, ops, callees.get(4 * i), 0)
            for i, (mn, ops) in enumerate(disassemble(words))]


def compile_pair(name, source):
    """-> (listing, Debug or None, note): the candidate as check.py builds it, and its `-g` records
    when the `-g` body is the same code."""
    plain = os.path.join(cc.scratch_dir(), "frames_%s.o" % verify.TMP_TAG())
    debug = os.path.join(cc.scratch_dir(), "frames_g_%s.o" % verify.TMP_TAG())
    for path in (plain, debug):
        if os.path.exists(path):
            os.remove(path)
    compile_function(name, source, plain)
    listing = object_listing(plain, name)
    try:
        compile_function(name, source, debug, "-g")
        same = body(plain, name) == body(debug, name)
    except ValueError as error:
        return listing, None, "no -g records: %s" % error
    if not same:
        return listing, None, "no -g records: the -g body differs from the plain one"
    records = debug_records(debug, name)
    if records is None:
        return listing, None, "no -g records (not an MWCC DWARF 1 object)"
    if records.file and os.path.basename(records.file).startswith(units.TMP_PREFIX):
        # the one-function split units.standalone compiled keeps the source's lines
        records = records._replace(file=os.path.relpath(os.path.abspath(source), ROOT))
    return listing, records, ""


# ---- MWCC DWARF 1 -----------------------------------------------------------------------------
_TAG_PARAM, _TAG_LOCAL, _TAG_GLOBAL_SUB, _TAG_SUB, _TAG_UNIT = 0x05, 0x0C, 0x06, 0x14, 0x11
_AT_NAME, _AT_LOCATION, _AT_LOW_PC = 0x0038, 0x0023, 0x0111


def _entries(data):
    """[(tag, {attribute: value})] of one DWARF 1 `.debug` section (null entries skipped)."""
    out, at = [], 0
    while at + 4 <= len(data):
        length, = struct.unpack_from("<I", data, at)
        if length < 8:
            at += max(length, 4)
            continue
        tag, = struct.unpack_from("<H", data, at + 4)
        p, end, attrs = at + 6, at + length, {}
        while p < end:
            attr, = struct.unpack_from("<H", data, p)
            p += 2
            form = attr & 0xF
            if form in (1, 2, 6):
                value, = struct.unpack_from("<I", data, p)
                p += 4
            elif form == 5:
                value, = struct.unpack_from("<H", data, p)
                p += 2
            elif form == 7:
                value, = struct.unpack_from("<Q", data, p)
                p += 8
            elif form in (3, 4):
                width = 2 if form == 3 else 4
                n, = struct.unpack_from("<H" if width == 2 else "<I", data, p)
                value = data[p + width:p + width + n]
                p += width + n
            elif form == 8:
                stop = data.index(b"\0", p)
                value = data[p:stop].decode("latin1")
                p = stop + 1
            else:
                raise ValueError("DWARF 1 form %d" % form)
            attrs[attr] = value
        out.append((tag, attrs))
        at = end
    return out


def _location(block):
    """A DWARF 1 location expression -> ("sp", offset) | ("reg", name) | ("addr", 0) | None."""
    stack, p = [], 0
    while p < len(block):
        op = block[p]
        if op in (1, 2, 3, 4):
            value, = struct.unpack_from("<i", block, p + 1)
            stack.append((op, value))
            p += 5
        elif op == 7 and len(stack) >= 2:
            (_, k), base = stack.pop(), stack.pop()
            stack.append(("sum", base, k))
            p += 1
        else:
            return None
    if len(stack) != 1:
        return None
    top = stack[0]
    if top[0] == 1 and 0 <= top[1] < 32:
        return ("reg", REGS[top[1]])
    if top[0] == "sum" and top[1][0] == 2 and top[1][1] == 29:
        return ("sp", top[2])
    if top[0] == 3:
        return ("addr", 0)
    return None


def _repo_path(name):
    """A compiler-recorded path (`Z:\\...\\src\\x.inc`) -> repository-relative when inside it."""
    path = name.replace("\\", "/")
    if re.match(r"^[A-Za-z]:/", path):
        path = path[2:]
    rel = os.path.relpath(path, ROOT)
    return path if rel.startswith("..") else rel


def _relocations_by_target(tables):
    """{target section index: [(offset, type, symbol name, 0)]} of every REL section, the names read
    raw (verify's readelf-compatible reader refuses names readelf would print oddly)."""
    rows, data, out = tables.rows, tables.data, {}
    for row in rows:
        if row[1] != 9 or not row[5]:
            continue
        symtab = rows[row[6]]
        strtab = rows[symtab[6]]
        strings = data[strtab[4]:strtab[4] + strtab[5]]
        entries = out.setdefault(row[7], [])
        for at in range(row[4], row[4] + row[5], 8):
            offset, info = struct.unpack_from("<II", data, at)
            sym_at = symtab[4] + 16 * (info >> 8)
            st_name, _value, _size, sym_info, _other, shndx = struct.unpack_from("<IIIBBH", data, sym_at)
            if st_name:
                name = strings[st_name:strings.index(b"\0", st_name)].decode("latin1")
            elif sym_info & 15 == 3 and shndx < len(tables.names):
                name = tables.names[shndx]
            else:
                name = ""
            entries.append((offset, info & 0xFF, name, 0))
    return out


def debug_records(obj, name):
    """The `-g` records of `name` in `obj` -> Debug(file, [Variable], [(offset, line)]) or None."""
    tables = verify._elf_tables(obj)
    if tables is None:
        return None
    by_target = _relocations_by_target(tables)
    variables, lines, unit = None, [], None
    for index, section in enumerate(tables.names):
        relocs = by_target.get(index, ())
        if section == ".debug" and variables is None and any(sym == name for _o, _k, sym, _a in relocs):
            row = tables.rows[index]
            entries = _entries(tables.data[row[4]:row[4] + row[5]])
            # a function's own unit has its code range; the file's global unit does not
            if not entries or entries[0][0] != _TAG_UNIT or _AT_LOW_PC not in entries[0][1]:
                continue
            unit = entries[0][1].get(_AT_NAME)
            variables = [Variable(a.get(_AT_NAME, "?"), "param" if tag == _TAG_PARAM else "local",
                                  _location(a[_AT_LOCATION]) if _AT_LOCATION in a else None)
                         for tag, a in entries if tag in (_TAG_PARAM, _TAG_LOCAL)]
        elif section == ".line" and not lines and any(o == 4 and sym == name for o, _k, sym, _a in relocs):
            row = tables.rows[index]
            data = tables.data[row[4]:row[4] + row[5]]
            length, = struct.unpack_from("<I", data, 0)
            for at in range(8, min(length, len(data)) - 9, 10):
                line, _pos, delta = struct.unpack_from("<IHI", data, at)
                if line:
                    lines.append((delta, line))
    if variables is None:
        return None
    return Debug(_repo_path(unit) if unit else None, variables, lines)


def line_at(debug, offset):
    """The source line of the code at byte `offset`, or None."""
    best = None
    for start, line in debug.lines:
        if start <= offset:
            best = line
    return best


def definition_site(path, name):
    """(file, line) of `name`'s definition: `path` itself or one of the fragments it includes."""
    import srctext
    rel = os.path.relpath(path, ROOT) if os.path.isabs(path) else path
    for candidate in [rel] + srctext.included(os.path.join(ROOT, rel)):
        with open(os.path.join(ROOT, candidate), errors="replace") as fh:
            text = fh.read()
        for found, start, _end in units.definitions(text):
            if found == name:
                return candidate, text.count("\n", 0, start) + 1
    return rel, None
