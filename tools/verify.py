#!/usr/bin/env python3
"""
verify.py — verify a candidate C function against the retail binary, WITH relocations.

This is the tool that makes non-trivial functions matchable. `check.py` compares
raw object bytes, which only works for self-contained leaf functions, because an
unlinked object stores *relocations* rather than addresses: `lui at,0 /
lw v0,8(at)` plus R_MIPS_HI16/LO16 against a symbol, not `lui at,0x56 /
lw v0,-8392(at)`. That is ~99% of the binary, so without relocation handling the
decomp can only ever match leaf functions.

What it does:
  1. compiles the candidate with the original compiler (MWCCPS2 3.0 via wibo),
  2. reads the object's relocations (readelf -r),
  3. resolves each symbol to a retail address — functions from
     config/SLUS-20836/symbols.txt, data from an address-bearing name (`D_0056df30`,
     `DAT_0056df30`, `g_0056df30`, ...), which is the bootstrap convention,
  4. applies the relocations to the object's bytes,
  5. diffs the result against retail, instruction by instruction.

`gp` is solved rather than supplied: for each GP-relative relocation the retail
immediate implies `gp = symbol + addend - immediate`, and if those agree across
every GP-relative operand then `gp` is known. (It has to be solved — `__start`
does `move gp, a0`, so the value is not in the ELF.)

Usage:
  verify.py 0x246780 cand.c                  # single function
  verify.py 0x246780 cand.c --verbose        # show every instruction
  verify.py 0x246780 cand.c --flags "-O3"

Exit status: 0 match, 1 mismatch, 2 error.
"""
import argparse
import bisect
import os
import re
import struct
import threading
import subprocess
import sys

import cc
import exceptions as exception_records
import units
import unitcompilers
import unitobjects
import unitprofiles
from functools import lru_cache

VADDR_BASE, FILE_BASE = 0x100000, 0x80
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_DEFAULT = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
MWCC_DEFAULT = os.environ.get(
    "DW4_MWCC", os.path.join(ROOT, "local", "mwcps2", "3.0-011126", "mwccps2.exe"))
WIBO_DEFAULT = os.environ.get("DW4_WIBO", os.path.join(ROOT, "local", "wibo"))
FLAGS_DEFAULT = "-O3 -Iinclude"

R_HI16, R_LO16, R_26, R_32, R_GPREL16 = 0x05, 0x06, 0x04, 0x02, 0x07

# Every scratch path carries the PID **and** the thread id. `verify_one` used fixed
# names, which is why the docs said "never call it from threads" — but two
# *processes* collide just the same, and that showed up as a bogus
# `struct.error: ... actual buffer size is 18` when a per-function loop ran beside
# `make check`. Namespacing the scratch files makes the tools safe to run
# concurrently.
def TMP_TAG():
    """A scratch-file tag unique to this *call's* thread.

    It has to be a function, not a module constant: a constant froze the importing
    thread's id, so a thread pool (m2c_batch --jobs) would have every worker write the
    same scratch path. `getpid` keeps separate processes apart, `get_ident` the
    threads within one.
    """
    return "%d_%d" % (os.getpid(), threading.get_ident())
TYPES = {"R_MIPS_HI16": R_HI16, "R_MIPS_LO16": R_LO16, "R_MIPS_26": R_26,
         "R_MIPS_32": R_32, "R_MIPS_GPREL16": R_GPREL16, "R_MIPS_LITERAL": R_GPREL16}
# The one address-in-name rule, shared with tools/linkgen.py (which used to accept
# `{6,8}` digits without a boundary while this file took `{5,8}` with one): the
# trailing 6-8 hex digits of a name, separated from the rest by a non-hex
# character. Every retail address has six to eight digits (0x100000 and up).
ADDR_IN_NAME = re.compile(r"(?:^|[^0-9a-fA-F])([0-9a-fA-F]{6,8})$")
# The bootstrap spelling proper: eight digits of an EE address (`_00586dc8`). Only a
# mapped name in this form is held to its claim; `__adddf3` ends in six hex-looking
# letters but is the runtime helper's real name.
BOOTSTRAP_NAME = re.compile(r"(?:^|[^0-9a-fA-F])(0[01][0-9a-fA-F]{6})$")
# Bootstrap names say what they point at: a `FUN_`/`thunk_` name is a function and
# may resolve only to a recorded function start; a data name (`D_`, `DAT_`, `g_`,
# `GPR_`, `PTR_`, ...) may resolve only to an address that is not inside any
# function's code. A name of neither style is a function start or data, never an
# address inside a function body (see `sym_address`).
FUNCTION_STYLE = re.compile(r"^(?:thunk_)*FUN_")
DATA_STYLE = re.compile(r"^(?:D|DAT|g|s|GPR|PTR|UNK|FLOAT|DOUBLE|BYTE|WORD|DWORD|QWORD|data|str)_")
JUMPTABLES = "config/SLUS-20836/jumptables.txt"


# ---- the section census --------------------------------------------------------
# Every section name an object of the relink may carry, each with the one reason it is
# either compared with retail or deliberately ignored. tools/test_section_census.py scans
# build/link/u_*.o and fails on any name outside these two tables; tools/check.py prints
# the census after a whole-tree run. A pattern entry is a compiled regex.
COMPARED_SECTIONS = {
    ".text": "the function body or a raw retail unit: compared word for word, placed by the link",
    ".rodata": "a switch jump table: compared with the retail table of config/SLUS-20836/jumptables.txt, placed",
    re.compile(r"^\.rodata\.dw4_[0-9a-f]{8}$"): "one of several jump tables of a unit, renamed by "
                                                  "linkgen for placement: compared like .rodata",
    ".exceptix": "the C++ exception index record: compared with config/SLUS-20836/exceptions.txt's retail record, placed",
    ".exception": "the C++ exception table: compared with the retail table, placed",
    re.compile(r"^\.exceptix\.dw4_[0-9a-f]{8}$"): "a group member's exception record kept by "
                                                   "isolate_emitted_body, renamed by retail address: compared, placed",
    re.compile(r"^\.exception\.dw4_[0-9a-f]{8}$"): "a group member's exception table kept by "
                                                    "isolate_emitted_body, renamed by retail address: compared, placed",
    ".data": "ee-gcc emits it empty; verify fails any content as an unowned allocated section",
    ".bss": "ee-gcc emits it empty; verify fails any content as an unowned allocated section",
    "": "the null section header every ELF carries",
    ".symtab": "ELF symbol table: not loaded",
    ".strtab": "ELF string table: not loaded",
    ".shstrtab": "ELF section-name table: not loaded",
    ".rel.text": "relocations of .text: applied by verify before comparing, consumed by ld",
    ".rel.rodata": "relocations of a jump table: applied before comparing, consumed by ld",
    re.compile(r"^\.rel\.rodata\.dw4_[0-9a-f]{8}$"): "relocations of a renamed jump table: applied, consumed by ld",
    ".rel.exceptix": "relocations of the exception record: applied before comparing, consumed by ld",
    ".rel.exception": "relocations of the exception table: applied before comparing, consumed by ld",
    re.compile(r"^\.rel\.exceptix\.dw4_[0-9a-f]{8}$"): "relocations of a group member's renamed exception "
                                                        "record: applied before comparing, consumed by ld",
    re.compile(r"^\.rel\.exception\.dw4_[0-9a-f]{8}$"): "relocations of a group member's renamed exception "
                                                         "table: applied before comparing, consumed by ld",
    ".rela.text": "ee-gcc RELA relocations of .text: applied before comparing, consumed by ld",
    ".rela.rodata": "ee-gcc RELA relocations of a jump table: applied, consumed by ld",
    ".mwcats": "MWCC's catalogue of the unit's functions: not loaded, discarded by the link script",
    ".rel.mwcats": "relocations of .mwcats: not loaded, discarded with it",
    ".comment": "compiler version string: not loaded, discarded by the link script",
    ".reginfo": "ee-gcc register-use summary: not loaded, discarded (gp comes from the retail .reginfo)",
    ".mdebug": "ee-gcc debug tag: not loaded, no content",
    ".mdebug.eabi64": "ee-gcc ABI tag: not loaded, no content",
}
# Sections the oracle knows it does not yet compare. None today: every allocated section
# of every object is compared or fails verification.
DEBT_SECTIONS = {}
EMPTY_ONLY_SECTIONS = {".data", ".bss"}


def section_role(name):
    """"compared", "debt" or None for a section name (see COMPARED_SECTIONS)."""
    for table, role in ((COMPARED_SECTIONS, "compared"), (DEBT_SECTIONS, "debt")):
        for key in table:
            if key == name if isinstance(key, str) else key.match(name):
                return role
    return None


def section_census(objects):
    """Scan relocatable objects -> (counts by name, [(object, name)] unknown, [(object, name, size)] empty-only
    sections with content). Names matching a pattern entry are counted under the pattern's glob
    (`.rodata.dw4_*`)."""
    counts, unknown, filled = {}, [], []
    for path in objects:
        for name, header in elf_section_headers(path):
            role = section_role(name)
            key = name
            for pattern in COMPARED_SECTIONS:
                if not isinstance(pattern, str) and pattern.match(name):
                    key = re.sub(r"\[0-9a-f\]\{8\}", "*", pattern.pattern).strip("^$").replace("\\", "")
            counts[key] = counts.get(key, 0) + 1
            if role is None:
                unknown.append((path, name))
            elif name in EMPTY_ONLY_SECTIONS and header[5]:
                filled.append((path, name, header[5]))
    return counts, unknown, filled


class SymbolError(ValueError):
    """A relocation symbol or definition whose name cannot be resolved honestly.

    `kind` says what the refusal is debt for (tools/check.py's categories):
    "name" — the name is wrong for a real address (a data name on a function
    start, a mapped name whose eight-digit suffix is not its address);
    "gap"  — a `FUN_` name for code no recorded function covers (symbol-map gap);
    "extent" — the address is inside another function's recorded extent.
    """
    def __init__(self, message, kind):
        super().__init__(message)
        self.kind = kind


def jumptables_path(symbols="config/SLUS-20836/symbols.txt"):
    """config/SLUS-20836/jumptables.txt beside the symbol map (so --symbols still works)."""
    cand = os.path.join(os.path.dirname(os.path.abspath(symbols)), "jumptables.txt")
    return cand if os.path.exists(cand) else JUMPTABLES


def profile_input_files(unit_flags=None, unit_compilers=None, units=None):
    """Explicit profile tables and pinned executables required in callers' cache keys.

    The per-unit cache key (buildcache.unit_profile_sha) covers the default tables row
    by row. Alternate tables must additionally cover their compiler files, including
    ones outside local/mwcps2. Resolve relative paths exactly as the profile loaders
    do, against the repo.
    """
    paths = [os.path.abspath(os.path.join(ROOT, p))
             for p in (unit_flags, unit_compilers, units) if p is not None]
    if unit_compilers is not None:
        for executable, _digest in unitcompilers.load(unit_compilers).values():
            paths.append(os.path.join(ROOT, executable))
    if units is not None:
        for executable, _digest in unitprofiles.load(units).compilers.values():
            paths.append(os.path.join(ROOT, executable))
    return tuple(sorted(set(paths)))


# The categories whose code bytes equal retail (tools/check.py): what a profile has to
# reproduce for a function to count as compiled by it.
CODE_REPRODUCED = {"match", "code-only", "name-defect", "inventory-gap"}


def code_reproduced(report):
    """True when a verify report's head says the code bytes equal retail (whatever else is owed)."""
    head = report.partition("\n")[0]
    found = re.search(r"\bcat=([\w-]+)", head)
    return bool(found) and found.group(1) in CODE_REPRODUCED


def describe_profile(profile):
    """`local/mwcps2/combat/mwccps2.exe '-O3,p -Iinclude -Cpp_exceptions off'` for a report line."""
    compiler = profile.compiler
    if os.path.isabs(compiler) and compiler.startswith(ROOT + os.sep):
        compiler = os.path.relpath(compiler, ROOT)
    return "%s '%s'" % (compiler, unitprofiles.command_flags(profile))


@lru_cache(maxsize=8)
def load_jumptables(path=None):
    """config/SLUS-20836/jumptables.txt -> {fn_va: [(jtbl_va, count)]} (see tools/jumptables.py).

    Cached: `verify_one` needs it for every candidate, and re-parsing the file is
    pure GIL-bound work a `--jobs` thread pool cannot overlap (`lru_cache` is
    itself thread-safe). The mapping is read-only by contract.
    """
    path = path or JUMPTABLES
    out = {}
    if not os.path.exists(path):
        return out
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.setdefault(int(p[0], 16), []).append((int(p[1], 16), int(p[2], 16)))
    return out


@lru_cache(maxsize=8)
def read_elf(path):
    """The whole retail image, cached by path (bytes, so trivially shareable)."""
    with open(path, "rb") as fh:
        return fh.read()


def va_bytes(img, va, n):
    return img[va - VADDR_BASE + FILE_BASE:va - VADDR_BASE + FILE_BASE + n]


def load_symbols(path):
    """config/SLUS-20836/symbols.txt -> {name: (va, size)} plus {(va): name}. Cached per path.

    `verify_one` calls this once per candidate (up to three times with the address
    modes), and parsing 16k lines is enough to dominate a sweep's Python time. The
    two mappings are read-only by contract. Cached by absolute path, so a caller
    that changes directory (the fixture tests do) cannot poison another's entry.
    """
    return _load_symbols(os.path.abspath(path))


@lru_cache(maxsize=8)
def _load_symbols(path):
    by_name, by_va = {}, {}
    if not os.path.exists(path):
        return by_name, by_va      # a fixture without a map: nothing resolves by name
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        parts = ln.split()
        va, sz, nm = int(parts[0], 16), int(parts[1], 16), parts[2]
        by_name[nm] = (va, sz)
        by_va[va] = (nm, sz)
    return by_name, by_va


def function_extents(path):
    """config/SLUS-20836/symbols.txt -> (sorted starts, [(start, end, name)]) for `code_owner`."""
    return _function_extents(os.path.abspath(path))


@lru_cache(maxsize=8)
def _function_extents(path):
    _, by_va = load_symbols(path)
    rows = sorted((va, va + size, name) for va, (name, size) in by_va.items())
    return [row[0] for row in rows], rows


def code_owner(address, symbols="config/SLUS-20836/symbols.txt"):
    """(function start, name) of the recorded function whose code holds `address`, or None."""
    starts, rows = function_extents(symbols)
    i = bisect.bisect_right(starts, address) - 1
    if i >= 0 and rows[i][0] <= address < rows[i][1]:
        return rows[i][0], rows[i][2]
    return None


def address_in_name(name):
    """The retail address a bootstrap name carries (`D_0056df30` -> 0x56df30), or None."""
    m = ADDR_IN_NAME.search(name)
    return int(m.group(1), 16) if m else None


_DATA_SYMBOLS = {}
_STRING_NAMES = {}


def data_symbols(symbols="config/SLUS-20836/symbols.txt"):
    """{name: va} for the recovered data names, from the data-names.tsv beside `symbols`.

    `function-symbol` rows are left out: those names live in the symbol map, and a row kept after
    a function's rename must not resolve. A name given two addresses, or a row whose name spells
    another address, stops the run rather than picking one.
    """
    path = os.path.join(ROOT, os.path.dirname(symbols), "data-names.tsv")
    if path in _DATA_SYMBOLS:
        return _DATA_SYMBOLS[path]
    out = {}
    if os.path.exists(path):
        with open(path) as fh:
            for ln in fh:
                if not ln.startswith("0x"):
                    continue
                va, name, rule = ln.rstrip("\n").split("\t")[:3]
                if rule == "function-symbol":
                    continue
                va = int(va, 16)
                spelled = BOOTSTRAP_NAME.search(name)
                if spelled and int(spelled.group(1), 16) != va:
                    raise ValueError(f"{path}: {name} is recorded at 0x{va:x} but spells {spelled.group(1)}")
                if out.setdefault(name, va) != va:
                    raise ValueError(f"{path}: {name} has two addresses, 0x{out[name]:x} and 0x{va:x}")
    _DATA_SYMBOLS[path] = out
    return out


def is_string_name(name, symbols="config/SLUS-20836/symbols.txt"):
    """True when data-names.tsv records `name` as a string. A string's name has no prefix to mark
    it as data, so its row does: it may never resolve into code."""
    path = os.path.join(ROOT, os.path.dirname(symbols), "data-names.tsv")
    if path not in _STRING_NAMES:
        names = set()
        if os.path.exists(path):
            with open(path) as fh:
                for ln in fh:
                    fields = ln.rstrip("\n").split("\t")
                    if ln.startswith("0x") and fields[2] in ("string-literal", "class-name"):
                        names.add(fields[1])
        _STRING_NAMES[path] = names
    return name in _STRING_NAMES[path]


def spelled_address(name, symbols="config/SLUS-20836/symbols.txt"):
    """The retail address a name stands for without the symbol map: its data-names.tsv row, else
    the address it carries (`D_0056df30` -> 0x56df30), else None."""
    base = name.split("+")[0].strip()
    table = data_symbols(symbols)
    return table[base] if base in table else address_in_name(base)


def sanitize(nm):
    return re.sub(r"[^A-Za-z0-9_]", "_", nm)


def object_text(obj):
    return object_section(obj, ".text")


def elf_section_headers(path):
    """Indexed (name, ELF32 section-header tuple) records, preserving duplicates."""
    with open(path, "rb") as fh:
        data = fh.read()
    if data[:6] != b"\x7fELF\x01\x01":
        raise ValueError("expected little-endian ELF32: " + str(path))
    shoff, = struct.unpack_from("<I", data, 0x20)
    entsize, count, strings = struct.unpack_from("<HHH", data, 0x2e)
    rows = [struct.unpack_from("<10I", data, shoff + i * entsize) for i in range(count)]
    names = data[rows[strings][4]:rows[strings][4] + rows[strings][5]]
    return [(names[row[0]:names.find(b"\0", row[0])].decode("latin1"), row) for row in rows]


def object_section(obj, sname, index=None):
    """Raw bytes of a section in a relocatable object (b"" if absent).

    A `switch` puts its jump table in `.rodata`, so `.rodata` has to be read and
    compared too — checking only `.text` would call a switch function matched while
    its table was never looked at (see docs/engine/m2c-bulk.md).
    """
    if index is not None:
        name, header = elf_section_headers(obj)[index]
        if name != sname:
            raise ValueError("section index/name mismatch")
        with open(obj, "rb") as fh:
            fh.seek(header[4])
            return fh.read(header[5])
    out = os.path.join(cc.scratch_dir(), "verify_%s_%s.bin" % (TMP_TAG(), re.sub(r"\W", "_", sname)))
    if os.path.exists(out):
        os.remove(out)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-j", sname, "-O", "binary", obj, out],
                   capture_output=True)
    return open(out, "rb").read() if os.path.exists(out) else b""


def object_syms(obj):
    """Symbol table of an object -> ({name: (ndx, value, size)}, {ndx: section}).

    Local symbols matter here: MWCC names an anonymous jump table `@21` and
    relocates the dispatcher against it, so resolving that relocation needs the
    symbol's defining section (see `object_section_base`).
    """
    secs, syms = {}, {}
    out = subprocess.run(["mipsel-linux-gnu-readelf", "-SW", obj],
                         capture_output=True, text=True).stdout
    for ln in out.splitlines():
        f = ln.replace("[", " ").replace("]", " ").split()
        if len(f) >= 3 and f[0].isdigit():
            try:
                secs[int(f[0])] = f[1]      # "5 .rodata PROGBITS ..." -> index 5
            except ValueError:
                pass
    out = subprocess.run(["mipsel-linux-gnu-readelf", "-sW", obj],
                         capture_output=True, text=True).stdout
    for ln in out.splitlines():
        f = ln.split()
        if len(f) < 8 or not f[0].rstrip(":").isdigit():
            continue
        try:
            ndx = int(f[-2])
        except ValueError:
            ndx = f[-2]                      # UND, ABS, ...
        # readelf prints Value in hex but Size in decimal. A single-function
        # section used to hide the wrong radix by truncating the oversized slice.
        # Processor-specific bindings print as several tokens. The section
        # index and undecorated name are always the final two columns.
        syms[f[-1]] = (ndx, int(f[1], 16), int(f[2], 10))
    return syms, secs


def jump_table_sections(obj, tables):
    """Map each MWCC table section index to its retail address and byte size.

    MWCC emits a separate .rodata section per switch, including repeated names.
    Section order follows the retail compiler's table order. Require a one-to-one
    size match; code relocations and every table byte must still verify separately.
    Padding between retail table sections belongs to the surrounding raw layout.
    """
    sections = [(index, header[5]) for index, (name, header)
                in enumerate(elf_section_headers(obj)) if name == ".rodata" and header[5]]
    tables = sorted(tables)
    if sections and not tables:
        raise ValueError("object has .rodata but no jump table is recorded")
    if len(sections) != len(tables):
        raise ValueError("compiled .rodata sections %d, recorded jump tables %d"
                         % (len(sections), len(tables)))
    result = []
    for (index, size), (address, count) in zip(sections, tables):
        if size != count * 4:
            raise ValueError("jump table 0x%x: section %d has %d bytes, expected %d"
                             % (address, index, size, count * 4))
        result.append((index, address, size))
    return result


def rename_object_sections(obj, names):
    """Rename generated object sections by index, preserving bytes and ownership.

    objcopy's name-based selection cannot distinguish duplicate .rodata names.
    Append a replacement section-name string table and change only sh_name and
    its string table's file offset/size. Symbol indices and relocation sh_info
    remain unchanged, so GNU ld can place the tables independently.
    """
    headers = elf_section_headers(obj)
    with open(obj, "rb") as fh:
        data = bytearray(fh.read())
    shoff, = struct.unpack_from("<I", data, 0x20)
    entsize, count, strings_index = struct.unpack_from("<HHH", data, 0x2e)
    strings_header = headers[strings_index][1]
    strings = bytearray(data[strings_header[4]:strings_header[4] + strings_header[5]])
    for index, name in sorted(names.items()):
        if not 0 <= index < count or not name or "\0" in name:
            raise ValueError("invalid generated section rename")
        name_offset = len(strings)
        strings.extend(name.encode("ascii") + b"\0")
        struct.pack_into("<I", data, shoff + index * entsize, name_offset)
    struct.pack_into("<II", data, shoff + strings_index * entsize + 16, len(data), len(strings))
    data.extend(strings)
    with open(obj, "wb") as fh:
        fh.write(data)


def object_sym(obj, name):
    """(value, size, section_index) of a named symbol in an object."""
    syms, _secs = object_syms(obj)
    if name in syms:
        ndx, value, size = syms[name]
        return value, size, ndx
    return None, None, None


def object_relocs(obj, target_section=None):
    """-> [(section, offset, type, symbol, addend)] over every relocation section.

    `section` is the *target* section name (`.text`, `.rodata`, …): the jump table
    is relocated by its own `.rel.rodata` against the function symbol, so a caller
    that only looked at `.rel.text` would never see those.
    """
    # MWCC emits one section named .text per function. The relocation section's
    # sh_info, not its repeated .rel.text name or offsets, identifies its owner.
    targets = ({header[4]: header[7] for _, header in elf_section_headers(obj)
                if header[1] in (4, 9)} if target_section is not None else None)
    out = subprocess.run(["mipsel-linux-gnu-readelf", "-rW", obj],
                         capture_output=True, text=True).stdout
    rows, cur = [], None
    for ln in out.splitlines():
        if ln.startswith("Relocation section"):
            m = re.search(r"'\.rel(?:a)?([^']*)'", ln)
            cur = m.group(1) if m else None
            if targets is not None:
                at = re.search(r"at offset 0x([0-9a-fA-F]+)", ln)
                if at is None or targets.get(int(at[1], 16)) != target_section:
                    cur = None
            continue
        f = ln.split()
        if cur is None or len(f) < 4 or not re.match(r"^[0-9a-f]+$", f[0]):
            continue
        tname = f[2]
        name = f[7] if len(f) > 7 else f[4]
        if tname not in TYPES:
            # Dropping it silently would compare bytes the relocation never patched
            # and could call an unpatched word a match. Every type MWCC and ee-gcc
            # emit for this target is in TYPES; anything else is an error.
            raise ValueError(f"unsupported relocation type {tname} against {name!r} "
                             f"at +0x{int(f[0], 16):x} in .rel{cur}")
        addend = 0
        m = re.search(r"\+\s*(\d+)\s*$", ln)
        if m:
            addend = int(m.group(1))
        rows.append((cur, int(f[0], 16), TYPES[tname], name, addend))
    # Preserve ELF relocation order. MWCC can place a loop's HI16 at a higher
    # address than its paired LO16; sorting by offset destroys that pairing.
    return rows


def function_relocs(relocs, offset, size):
    """Select .text relocations and rebase them to a sliced function symbol.

    C++ helpers can precede/follow the target. Preserve ELF table order, since
    an HI16 can have a larger instruction offset than its paired LO16.
    """
    return [(section, at - offset, kind, name, addend)
            for section, at, kind, name, addend in relocs
            if section == ".text" and offset <= at and at + 4 <= offset + size]


def reginfo_gp(path):
    """gp from the ELF's .reginfo section.

    MIPS .reginfo is 24 bytes: gprmask, cprmask[4], then gp_value. This is the
    authoritative gp — the PS2 loader reads it and passes it in a0, which is why
    __start can just `move gp, a0` (0x001001c0). Sanity check: gp - 32112 ==
    0x00554b00, the first byte of .sbss, so the small-data region starts exactly
    where gp says it should.
    """
    img = read_elf(path)
    # find .reginfo via the section header table
    e_shoff, = struct.unpack_from("<I", img, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", img, 0x2e)
    shstr = struct.unpack_from("<IIIIIIIIII", img, e_shoff + e_shstrndx * e_shentsize)
    shstr_off = shstr[4]
    for i in range(e_shnum):
        sh = struct.unpack_from("<IIIIIIIIII", img, e_shoff + i * e_shentsize)
        nm = img[shstr_off + sh[0]:img.find(b"\0", shstr_off + sh[0])].decode("latin1")
        if nm == ".reginfo":
            return struct.unpack_from("<I", img, sh[4] + 20)[0]
    return None


@lru_cache(maxsize=None)
def compiler_runtime_symbols():
    """{name: va} for the MWCC runtime helpers, from config/SLUS-20836/compiler-runtime-symbols.tsv."""
    out = {}
    with open(os.path.join(ROOT, "config", "SLUS-20836", "compiler-runtime-symbols.tsv")) as fh:
        for ln in fh:
            if ln.startswith("#") or not ln.strip():
                continue
            nm, va = ln.split()
            out[nm] = int(va, 16)
    return out


def sym_address(name, sym_by_name, symbols="config/SLUS-20836/symbols.txt"):
    """Retail address for a relocation's symbol, or None; `SymbolError` when dishonest.

    Functions come from the layout; recovered data names from data-names.tsv; anything
    else from an address-bearing name (the bootstrap convention: `D_0056df30`,
    `DAT_0056df30`, `g_0056df30`, `FUN_00100240`). A name in none of these cannot be
    resolved yet — that is what a fuller symbol map would fix.

    The name's own claims are checked against `symbols` (the map `sym_by_name`
    was loaded from), the one resolver shared with tools/linkgen.py:

    * a mapped name that carries an address must carry its own (`thunk_FUN_x`
      names its target by convention and is exempt);
    * a `FUN_`/`thunk_` name resolves only to a recorded function start;
    * a data-style name (`D_`, `DAT_`, `g_`, `GPR_`, `PTR_`, ...) or a string in
      data-names.tsv resolves only to an address outside every function's code;
    * any other name resolves to a function start or to data, never to an
      address inside a function body (`Foo_002d3074` for a call to 0x2d3070+4);
    * no range check: scratchpad, hardware register and kernel addresses are
      honest targets, and the function-extent rules above are the real test.

    What bytes cannot tell: a name that is NOT in the map, carries the right
    function-start address and merely calls the function something else
    (`whatever_002d3070`) still resolves — see
    docs/engine/compiler-object-verification.md, "Known limits".
    """
    if name in sym_by_name:
        va = sym_by_name[name][0]
        found = BOOTSTRAP_NAME.search(name)
        claimed = int(found.group(1), 16) if found else None
        if claimed is not None and claimed != va and not name.startswith("thunk_"):
            raise SymbolError(f"{name} is at 0x{va:x} in the symbol map but its name says 0x{claimed:x}", "name")
        return va
    if name in compiler_runtime_symbols():
        return compiler_runtime_symbols()[name]
    base = name.split("+")[0].strip()
    claimed = spelled_address(base, symbols)
    if claimed is None:
        return None
    # No address bound: the EE's scratchpad (0x70000000), hardware registers
    # (0x10000000...) and kernel area (below 0x100000) are all honest targets.
    owner = code_owner(claimed, symbols)
    if FUNCTION_STYLE.match(base):
        if owner is None or owner[0] != claimed:
            raise SymbolError(f"{base} names 0x{claimed:x}, which is not a recorded function start"
                              + (f" (inside {owner[1]})" if owner
                                 else " (no recorded function covers it: a symbol-map gap)"),
                              "extent" if owner else "gap")
    elif DATA_STYLE.match(base) or is_string_name(base, symbols):
        if owner is not None:
            raise SymbolError(f"data name {base} points at 0x{claimed:x} inside the code of "
                              f"{owner[1]} (0x{owner[0]:x})", "name" if owner[0] == claimed else "extent")
    elif owner is not None and owner[0] != claimed:
        raise SymbolError(f"{base} names 0x{claimed:x} inside the code of {owner[1]} "
                          f"(0x{owner[0]:x}), not a function start", "extent")
    return claimed


def category(code_ok, refusals, exc_status):
    """tools/check.py's one-of category for a verified unit (see its docstring).

    `refusals` are the SymbolErrors the resolver recorded; `exc_status` is the
    exception-metadata status ("ok" or "-" pass). Precedence: a byte or shape
    difference is a mismatch whatever else is wrong; an inventory gap outranks
    a name defect, which outranks unproven exception metadata.
    """
    if not code_ok:
        return "mismatch"
    kinds = {error.kind for error in refusals}
    if kinds & {"gap", "extent"}:
        return "inventory-gap"
    if kinds:
        return "name-defect"
    if exc_status not in ("ok", "-"):
        return "code-only"
    return "match"


def apply_relocs(text, relocs, resolve, gp):
    """Patch a copy of `text`. Returns (patched, gp_needed, unresolved)."""
    buf = bytearray(text)
    pend_hi, unresolved = [], []

    def patch(off, imm, mask, shift):
        w = struct.unpack_from("<I", buf, off)[0]
        w = (w & ~(mask << shift)) | ((imm & mask) << shift)
        struct.pack_into("<I", buf, off, w)

    for _sec, off, rtype, name, addend in relocs:
        if off + 4 > len(buf):
            # A relocation beyond the compiled section (a candidate whose object carries
            # no/short `.text`, e.g. an empty object after a heavy compile) — record it
            # unresolved instead of raising, so one bad candidate cannot abort a sweep.
            unresolved.append((off, name))
            if rtype == R_LO16:
                pend_hi = []
            continue
        if rtype == R_HI16:
            pend_hi.append((off, name))
            continue
        target = resolve(name)
        if target is None:
            unresolved.append((off, name))
            # keep going so other relocations still get applied
            if rtype == R_LO16:
                pend_hi = []
            continue
        if rtype == R_LO16:
            # the LO instruction's own immediate carries the addend
            raw = struct.unpack_from("<I", buf, off)[0] & 0xffff
            a = addend + (raw - 0x10000 if raw & 0x8000 else raw)
            s = target + a
            patch(off, s & 0xffff, 0xffff, 0)
            lo = s & 0xffff
            lo_signed = lo - 0x10000 if lo & 0x8000 else lo
            hi = ((s - lo_signed) >> 16) & 0xffff
            for hoff, hname in pend_hi:
                if hname == name:
                    patch(hoff, hi, 0xffff, 0)
            pend_hi = [(o, n) for o, n in pend_hi if n != name]
        elif rtype == R_26:
            w = struct.unpack_from("<I", buf, off)[0]
            patch(off, ((target + addend) >> 2) & 0x3FFFFFF, 0x3FFFFFF, 0)
        elif rtype == R_32:
            # MIPS relocatable objects are REL, not RELA: the addend lives in the
            # field itself (this is how a jump table entry points at a case body).
            cur = struct.unpack_from("<I", buf, off)[0]
            struct.pack_into("<I", buf, off, (target + addend + cur) & 0xffffffff)
        elif rtype == R_GPREL16:
            if gp is None:
                return None, None, [(off, name, target, addend)]
            patch(off, (target + addend - gp) & 0xffff, 0xffff, 0)
    for off, name in pend_hi:
        unresolved.append((off, name))
    return bytes(buf), None, unresolved


def solve_gp(text, relocs, resolve, retail, base_va):
    """Infer gp from the retail immediates of the GP-relative operands."""
    gps = []
    for _sec, off, rtype, name, addend in relocs:
        if rtype != R_GPREL16:
            continue
        if off + 4 > len(retail):
            # The object is larger than the retail function (a candidate that cannot
            # match anyway), so there is no retail word to read the immediate from.
            # Skipping keeps this a mismatch instead of an exception that aborts a
            # whole sweep.
            continue
        target = resolve(name)
        if target is None:
            continue
        raw = struct.unpack_from("<I", retail, off)[0] & 0xffff
        imm = raw - 0x10000 if raw & 0x8000 else raw
        gps.append(target + addend - imm)
    if not gps:
        return None, 0
    if len(set(gps)) == 1:
        return gps[0], len(gps)
    return None, len(gps)


def defined_outside(syms, headers, spans, exempt=()):
    """Defined symbols whose name stands for an address outside the object's own bodies.

    A candidate that DEFINES `g_objectSystem_00586dc8` instead of referencing it
    smuggles the datum: its relocations then resolve to the object's own copy and
    the bytes still compare equal. `spans` are the retail [start, end) extents the
    object legitimately owns; `exempt` are the body names it is expected to define
    (a `thunk_FUN_x` body names its target, not itself). Returns [(name, claimed)].
    """
    names = {name for name, _ in headers}
    out = []
    for name, (section, _value, _size) in syms.items():
        if not isinstance(section, int) or name in names or name in exempt or name.startswith("."):
            continue
        claimed = spelled_address(name)
        if claimed is None or any(start <= claimed < end for start, end in spans):
            continue
        out.append((name, claimed))
    return out


def stripped_bodies(obj, headers, syms, group, sections, image, by_va):
    """{name: section} for the group's `stripped` destructor bodies (config/SLUS-20836/unit-objects.json).

    MWCC emits an out-of-line copy of an inline destructor even when every use is
    inlined; the retail linker dead-stripped such a copy, so no retail function holds
    it. A stripped body is accepted only when it is a complete `.text` section of its
    own, no retail function has its bytes (relocated words masked; a retail copy must be
    named as a duplicate instead; not asked of a whole-file unit) and nothing else in the
    object references it (checked by `unreferenced`). It is never compared and never linked.
    """
    out = {}
    if not group.stripped:
        return out
    lo = min(by_va)
    hi = max(address + size for address, (_name, size) in by_va.items())
    retail = va_bytes(image, lo, hi - lo)
    for name in group.stripped:
        section, value, size = syms.get(name, (None, None, None))
        if not isinstance(section, int) or not 0 < section < len(headers):
            raise ValueError(f"stripped body {name} is not defined by the object")
        label, header = headers[section]
        if (label != ".text" or value != 0 or size != header[5] or not size or size % 4
                or not header[2] & 4 or section in sections or section in out.values()):
            raise ValueError(f"stripped body {name} is not a complete .text section of its own")
        if group.whole_file:
            # A stock getter is any getter once its relocated words are masked. The name earns
            # no credit and is never linked, so a retail copy just stays its own function.
            out[name] = section
            continue
        raw = object_section(obj, ".text", section)
        relocated = {offset // 4 for _s, offset, _k, _n, _a in object_relocs(obj, target_section=section)}
        words = [raw[i:i + 4] for i in range(0, size, 4)]
        pattern = b"".join(b"...." if i in relocated else re.escape(w) for i, w in enumerate(words))
        for found in re.finditer(pattern, retail, re.DOTALL):
            if found.start() % 4 == 0:
                raise ValueError(f"stripped body {name} has a retail copy at "
                                 f"0x{lo + found.start():x}; name it as a duplicate")
        out[name] = section
    return out


def dead_data(obj, headers, syms, bodies, declared):
    """Data sections of a whole-file unit that no placed body or declared datum reaches.

    The retail linker dropped them with the functions that used them. They are never linked,
    and a datum a placed body does reach stays allocated, so it must be declared or the object
    is rejected.
    """
    live = set(bodies) | set(declared)
    work = list(live)
    while work:
        for _s, _offset, _k, symbol, _a in object_relocs(obj, target_section=work.pop()):
            target = syms.get(symbol, (None,))[0]
            if isinstance(target, int) and target not in live:
                live.add(target)
                work.append(target)
    return {i for i, (_name, h) in enumerate(headers)
            if h[2] & 2 and not h[2] & 4 and h[5] and i not in live}


def unreferenced(obj, headers, names, dropped):
    """Reject a stripped body that any kept section of the object still references."""
    if not names:
        return
    for index, (_label, header) in enumerate(headers):
        if index in dropped or not header[5] or not header[2] & 2:
            continue
        for _s, offset, _k, symbol, _a in object_relocs(obj, target_section=index):
            if symbol in names:
                raise ValueError(f"stripped body {symbol} is referenced at +0x{offset:x} of section "
                                 f"{index}; a referenced body cannot have been dead-stripped")


def group_exception_sections(obj, headers, syms, records):
    """Attribute every `.exceptix` record and `.exception` table of a compiler unit to a member.

    MWCC emits one 12-byte index record per function body, relocated at word 0 against
    the function and, when the function has cleanup actions, at word 2 against a label
    in the body's own `.exception` table section. Returns
    {compiler_name: (index_section, table_section or None)}. A record of a function the
    overlay does not own (an inline member that was not inlined), a second record for a
    member, a malformed record or a table no record points at raise ValueError: those
    are shapes the retail metadata cannot be compared against.
    """
    index = [i for i, (n, h) in enumerate(headers) if n == ".exceptix" and h[5]]
    tables = {i for i, (n, h) in enumerate(headers) if n == ".exception" and h[5]}
    out, claimed = {}, set()
    for section in index:
        if headers[section][1][5] != 12:
            raise ValueError("exception index section is not one 12-byte record")
        relocations = object_relocs(obj, target_section=section)
        first = [r for r in relocations if r[1] == 0]
        if len(first) != 1 or first[0][2] != R_32 or first[0][4] != 0:
            raise ValueError("exception index record is not relocated against its function")
        name = first[0][3]
        if name not in records:
            raise ValueError(f"exception index record of an unowned function {name} "
                             "(a body the compiler emitted that the overlay does not own, "
                             "for example an inline member that was not inlined)")
        if name in out:
            raise ValueError(f"two exception index records for {name}")
        table = None
        for _sec, offset, kind, symbol, _addend in relocations:
            if offset == 8:
                defining = syms.get(symbol, (None,))[0]
                if kind != R_32 or defining not in tables or defining in claimed:
                    raise ValueError(f"exception record of {name} does not point at its own .exception table")
                table = defining
                claimed.add(defining)
        out[name] = (section, table)
    if tables - claimed:
        raise ValueError("an .exception table no index record points at")
    return out


def expected_exception_records(group, symbols):
    """{member address: (index_va, table_va or None, table_size)} retail keeps for a group.

    The source is config/SLUS-20836/exceptions.txt (tools/exceptions.py). An ``exceptions`` row in
    config/SLUS-20836/unit-objects.json is an optional assertion for the owner: it must agree with
    the recovered table when both exist, and it stands in for the table when none is
    recovered (a fixture with its own symbol map).
    """
    retail = exception_records.load(exception_records.config_path(symbols))
    expected = {address: retail[address] for address in group.members if address in retail}
    if group.exceptions:
        index_at, table_at, table_size = group.exceptions
        ends = sorted([(index_at, index_at + 12), (table_at, table_at + table_size)])
        if ends[0][1] > ends[1][0]:
            raise ValueError("exception index and table extents overlap")
        if group.owner in expected and expected[group.owner] != group.exceptions:
            raise ValueError("declared exception metadata disagrees with config/SLUS-20836/exceptions.txt "
                             f"(retail index 0x{expected[group.owner][0]:x}, table "
                             f"{'0x%x' % expected[group.owner][1] if expected[group.owner][1] else 'none'})")
        if group.owner not in expected and retail:
            raise ValueError(f"declared exception metadata at 0x{index_at:x}, but retail keeps "
                             f"no index record for 0x{group.owner:x}")
        expected[group.owner] = group.exceptions
    return expected


class Records(dict):
    """The verified members of a compiler unit, {compiler_name: (address, section, size)},
    plus `exception_placements`: {compiler_name: (index_section, index_va, table_section or
    None, table_va or None, table_size)} for every placed member whose retail exception
    metadata the object reproduces, so `isolate_emitted_body` can keep those sections."""
    exception_placements = {}


def duplicate_tables(group, jumptables):
    """Switch tables of the verify-only duplicates of an ownership group.

    A duplicate (a callee compiled first in the owner's unit so the compiler knows its
    register use) brings its own `.rodata` jump table into the object. It is compared
    against the retail table of the duplicate's address like the owner's tables and then
    dropped with the duplicate: only the independently placed unit owns the table.
    """
    return [table for _, address in group.duplicates for table in jumptables.get(address, [])]


def verify_emitted_object(obj, group, elf, symbols, gp_override=None, verbose=False,
                          requested=None, jumptables=None, deferred=()):
    """Verify every explicitly owned body before any per-function extraction.

    Code sections must be exactly the owner, its placed emitted members and its
    verify-only duplicates. Other allocated data is accepted only when the overlay
    gives it a retail identity: the owner's switch tables (config/SLUS-20836/jumptables.txt),
    with an ``exceptions`` declaration the owner's exception index record and table, and
    in a whole-file unit each ``data`` row. Each is compared byte for byte, relocations
    applied, with retail. A whole-file unit's switch tables are ``data`` rows too.
    Runtime data and exception tables without such a declaration fail closed
    rather than becoming unplaced orphan sections.

    ``deferred`` names duplicates whose retail copy came from a unit built with a
    different compiler profile; their bytes cannot equal this object's, so only
    their presence as a complete section is required here. `verify_emitted_unit`
    then compiles the same source with that unit's own profile and compares them
    there; nothing is skipped without such a second, exact comparison.
    """
    by_name, by_va = load_symbols(symbols)
    headers = elf_section_headers(obj)
    syms, _ = object_syms(obj)
    image = read_elf(elf)
    if jumptables is None:
        jumptables = load_jumptables(jumptables_path(symbols))
    try:
        members = ([(group.symbol or by_va[group.owner][0], group.owner)] + list(group.emitted)
                   + list(group.duplicates))
        aliases = dict(group.externals)
        if any(address not in by_va for address in group.members + tuple(aliases.values())):
            raise ValueError("emitted body or external alias has no retail function")
        records, sections = {}, set()
        for compiler_name, address in members:
            section, value, size = syms.get(compiler_name, (None, None, None))
            if not isinstance(section, int) or not 0 < section < len(headers):
                raise ValueError(f"missing emitted function {compiler_name}")
            label, header = headers[section]
            expected = size if compiler_name in deferred else by_va[address][1]
            if (label != ".text" or value != 0 or size != expected
                    or header[5] != expected or not header[2] & 4 or section in sections):
                raise ValueError(f"emitted extent differs for {compiler_name}: object symbol "
                                 f"{size} bytes in a section of {header[5]}, retail {by_va[address][1]}")
            records[compiler_name] = (address, section, size)
            sections.add(section)
        tables = [] if group.whole_file else jump_table_sections(
            obj, sorted(jumptables.get(group.owner, []) + duplicate_tables(group, jumptables)))
        table_sections = {index for index, _, _ in tables}
        data_addresses = dict(group.data)
        data_sections = {}      # section -> retail address of its first byte
        for name, address in group.data:
            section, value, _ = syms.get(name, (None, None, None))
            if isinstance(section, int) and data_sections.setdefault(section, address - value) != address - value:
                raise ValueError(f"data symbol {name} disagrees with its section's retail address")
        stripped = stripped_bodies(obj, headers, syms, group, sections, image, by_va)
        # Every exception record and table belongs to a member; they are compared with
        # config/SLUS-20836/exceptions.txt below (never a reason to reject before the byte compare).
        # A stripped body's own record and table are dropped with it.
        exc_all = group_exception_sections(obj, headers, syms, {**records, **stripped})
        exc_sections = {name: pair for name, pair in exc_all.items() if name not in stripped}
        dropped = set(stripped.values()) | {i for name in stripped for i in exc_all.get(name, ())
                                            if i is not None}
        dead = dead_data(obj, headers, syms, sections, data_sections) if group.whole_file else set()
        dropped |= dead
        unreferenced(obj, headers, set(stripped), dropped)
        exc_expected = expected_exception_records(group, symbols)
        allocated = {i for i, (_, h) in enumerate(headers) if h[2] & 2 and h[5] and i not in dropped}
        executable = {i for i, (_, h) in enumerate(headers) if h[2] & 4 and h[5] and i not in dropped}
        named_text = {i for i, (name, h) in enumerate(headers)
                      if name == ".text" and h[5] and i not in dropped}
        auxiliary = (table_sections | set(data_sections)
                     | {i for pair in exc_sections.values() for i in pair if i is not None})
        if (allocated != sections | auxiliary or executable != sections
                or named_text != sections):
            raise ValueError("unowned code or runtime data in emitted object")
        for alias, address in aliases.items():
            if alias in syms and syms[alias][0] != "UND":
                raise ValueError(f"external alias {alias} is defined by the object")
            known = sym_address(alias, by_name, symbols)
            if known is not None and known != address:
                raise ValueError(f"external alias {alias} conflicts with the symbol map")
        spans = sorted((address, address + size) for address, _, size in records.values())
        if any(end > following for (_, end), (following, _) in zip(spans, spans[1:])):
            raise ValueError("emitted retail function extents overlap")
        smuggled = defined_outside(syms, headers, spans, exempt=set(records) | set(stripped))
        if smuggled:
            raise ValueError(f"object defines {smuggled[0][0]}, which names retail address "
                             f"0x{smuggled[0][1]:x} outside its own bodies (a candidate may only "
                             "reference that datum)")
    except (KeyError, ValueError) as error:
        return False, f"emitted object rejected: {error}", None
    # the retail table address of every .exception section the object carries, for the resolver
    exc_table_va = {table: exc_expected[records[name][0]][1]
                    for name, (_index, table) in exc_sections.items()
                    if table is not None and records[name][0] in exc_expected
                    and exc_expected[records[name][0]][1] is not None}

    gp = gp_override if gp_override is not None else reginfo_gp(elf)
    success, reports = True, []
    requested = group.owner if requested is None else requested

    table_addresses = {index: address for index, address, _ in tables}
    dishonest = {}     # symbol -> why the shared resolver refused it (reported, fails)

    def resolver(section=None, address=None):
        def resolve(name):
            if name in records:
                return records[name][0]
            if name in aliases:
                return aliases[name]
            if name in data_addresses:
                return data_addresses[name]
            if name in syms and isinstance(syms[name][0], int):
                defining, value, _ = syms[name]
                # Local labels may resolve within this body. Cross-body calls
                # must use an explicitly owned member symbol, not a hidden label.
                if section is not None and defining == section:
                    return address + value
                if defining in exc_table_va:
                    return exc_table_va[defining] + value
                if defining in table_addresses:
                    return table_addresses[defining] + value
                return None
            try:
                return sym_address(name, by_name, symbols)
            except SymbolError as error:
                # Still compare the bytes at the address the name spells (what the
                # relink provides), so a naming defect is told apart from a mismatch.
                dishonest[name] = error
                return spelled_address(name, symbols)
        return resolve

    for compiler_name, (address, section, size) in records.items():
        if compiler_name in deferred:
            reports.append(f"DEFERRED duplicate 0x{address:x} {compiler_name} {size}B "
                           "(compared under the profile of its retail unit)")
            continue
        raw = object_section(obj, ".text", section)
        relocations = object_relocs(obj, target_section=section)
        patched, _, unresolved = apply_relocs(raw, relocations, resolver(section, address), gp)
        if patched is None:
            return False, "emitted object rejected: could not resolve gp", None
        retail = va_bytes(image, address, size)
        good = patched == retail and len(retail) == size and not unresolved
        success = success and good
        kind = "duplicate" if any(name == compiler_name for name, _ in group.duplicates) else "emitted"
        reports.append(f"{'MATCH' if good else 'DIFFER'} {kind} 0x{address:x} "
                       f"{compiler_name} {size}B {len(relocations)} relocs")
        for offset, name in unresolved:
            reports.append(f"  unresolved relocation {name!r} at +0x{offset:x}")
        if patched is not None:
            for at in range(0, size, 4):
                got, want = patched[at:at + 4], retail[at:at + 4]
                if verbose or got != want:
                    if address == requested:
                        prefix = "   " + ("  " if got == want else "!!")
                    else:
                        prefix = f"  body 0x{address:x} "
                    reports.append(f"{prefix}[{at // 4}] retail {want[::-1].hex()} ours {got[::-1].hex()}")

    def compare_data(label, section, kind, address, length, pad=0):
        """Relocated object data against retail bytes; `pad` zero bytes may follow."""
        raw = object_section(obj, kind, section)
        relocations = object_relocs(obj, target_section=section)
        patched, _, unresolved = apply_relocs(raw, relocations, resolver(), gp)
        retail = va_bytes(image, address, length + pad)
        good = (patched is not None and not unresolved and len(raw) == length
                and patched == retail[:length] and not any(retail[length:]))
        reports.append(f"{'MATCH' if good else 'DIFFER'} {label} 0x{address:x} {length}B")
        for offset, name in unresolved:
            reports.append(f"  unresolved relocation {name!r} at +0x{offset:x}")
        if patched is not None and not good:
            targets = {offset: symbol for _s, offset, rkind, symbol, _a in relocations if rkind == R_32}
            for at in range(0, min(length, len(patched)), 4):
                if patched[at:at + 4] != retail[at:at + 4]:
                    reports.append(f"  {label} [{at // 4}] retail {retail[at:at + 4][::-1].hex()} "
                                   f"ours {patched[at:at + 4][::-1].hex()}")
                    if at in targets:
                        # a relocated word: name both targets so the source side can re-point
                        # the duplicate (a table's destructor address is the common case)
                        ours, theirs = struct.unpack_from("<I", patched, at)[0], struct.unpack_from("<I", retail, at)[0]
                        reports.append(f"  {label} [{at // 4}] is a relocated address: ours 0x{ours:x} "
                                       f"({targets[at]}), retail 0x{theirs:x} "
                                       f"({by_va[theirs][0] if theirs in by_va else 'not a recorded function'})")
        return good

    for section, address, size in tables:
        success = compare_data("jump table", section, ".rodata", address, size) and success
    for section, address in sorted(data_sections.items()):
        label, header = headers[section]
        success = compare_data(f"data {label}", section, label, address, header[5]) and success

    # ---- the exception metadata, member by member (as the standalone path does) -------
    # A placed body (owner, emitted) must reproduce retail's record and table exactly:
    # emitted where retail has none is `extra`, absent where retail has one `missing`,
    # different `differ`. A verify-only duplicate is compared only when both exist: its
    # copy is discarded with its body and its retail record belongs to the placing unit.
    duplicates = {name for name, _ in group.duplicates}
    statuses, placements = [], {}
    for name, (address, _section, _size) in records.items():
        expected = exc_expected.get(address)
        emitted = exc_sections.get(name)
        if name in deferred or (expected is None and emitted is None):
            continue
        if expected is None:
            if name not in duplicates:
                statuses.append("extra")
                reports.append(f"  exception metadata: the object emits a record for 0x{address:x} {name}, "
                               "but retail keeps none (its unit was compiled without exception metadata)")
            continue
        index_at, table_at, table_size = expected
        if emitted is None:
            if name not in duplicates:
                statuses.append("missing")
                reports.append(f"  exception metadata: retail keeps an index record at 0x{index_at:x} for "
                               f"0x{address:x} {name} that the object does not produce (its unit was C++ "
                               "with exceptions on)")
            continue
        index_section, table_section = emitted
        if (table_at is None) != (table_section is None):
            statuses.append("differ")
            reports.append(f"DIFFER exception metadata 0x{address:x} {name}: retail record is "
                           f"{'packed' if table_at is None else 'a table of %d bytes' % table_size}, the object "
                           f"emits {'no' if table_section is None else 'a'} table")
            continue
        good = compare_data(f"exception index ({name})", index_section, ".exceptix", index_at, 12)
        if table_at is not None:
            length = headers[table_section][1][5]
            pad = table_size - length
            if not 0 <= pad <= 3:
                good = False
                reports.append(f"DIFFER exception table 0x{table_at:x} ({name}): exception table size differs "
                               f"from its section ({length} bytes against a retail slot of {table_size})")
            else:
                good = compare_data(f"exception table ({name})", table_section, ".exception", table_at,
                                    length, pad) and good
        statuses.append("ok" if good else "differ")
        if good and name not in duplicates:
            placements[name] = (index_section, index_at, table_section, table_at, table_size)
    exc_status = next((s for s in ("differ", "missing", "extra") if s in statuses), "ok" if statuses else "-")
    for name, error in sorted(dishonest.items()):
        reports.append(f"  symbol {name!r}: {error}")
    # `exc=` and `cat=` tell tools/check.py how the retail exception metadata fared
    # and which category the unit falls in. The records are returned whenever the
    # bodies and jump tables are exact, so linkgen can still place the code and
    # keep retail's bytes for metadata it does not reproduce.
    kind = category(success, dishonest.values(), exc_status)
    token = (f" exc={exc_status}" if exc_status != "-" else "") + f" cat={kind}"
    report = (("MATCH" if kind == "match" else "DIFFER")
              + f" emitted object: {len(records)} complete bodies{token}\n")
    result = Records(records)
    result.exception_placements = placements
    result.data_sections = set(data_sections) | dead
    return kind == "match", report + "\n".join(reports), result if success else None


def duplicate_profiles(group, profile, unit_flags=None, unit_compilers=None, units=None,
                       symbols="config/SLUS-20836/symbols.txt"):
    """Duplicates built by a different unit profile -> {Profile: [symbol]}.

    Retail keeps one copy of a function several units instantiate: the first the
    linker saw. That copy's bytes depend on *its* unit's profile (config/SLUS-20836/units.tsv
    at the copy's address, or the copy's own provisional override), not on the
    owner's, so it is compared against a compile of the same source under that
    profile.
    """
    result = {}
    for name, address in group.duplicates:
        own = unitprofiles.resolve(address, FLAGS_DEFAULT, MWCC_DEFAULT, units=units,
                                   unit_flags=unit_flags, unit_compilers=unit_compilers, symbols=symbols)
        own = own.override or own.profile
        if not unitprofiles.same_profile(own, profile):
            result.setdefault(own, []).append(name)
    return result


def verify_emitted_unit(obj, group, elf, symbols, profile, recompile,
                        gp_override=None, verbose=False, requested=None, jumptables=None,
                        unit_flags=None, unit_compilers=None, units=None):
    """`verify_emitted_object` plus the exact comparison of profile-deferred duplicates.

    `profile` is the unitprofiles.Profile `obj` was compiled with.
    ``recompile(compiler, flags, out)`` builds the same translation unit with
    another profile's compiler and command flags and returns whether `out` exists.
    Every deferred duplicate must then be a complete, correctly sized `.text` body
    equal to its retail unit after relocation. Any failure rejects the whole unit.
    """
    try:
        profiles = duplicate_profiles(group, profile, unit_flags, unit_compilers, units, symbols)
    except ValueError as error:
        return False, f"emitted object rejected: {error}", None
    deferred = {name for names in profiles.values() for name in names}
    good, report, records = verify_emitted_object(obj, group, elf, symbols, gp_override, verbose,
                                                  requested, jumptables, deferred=deferred)
    if not records and not good and not report.startswith("DIFFER"):
        return good, report, records
    by_name, by_va = load_symbols(symbols)
    image = read_elf(elf)
    gp = gp_override if gp_override is not None else reginfo_gp(elf)
    aliases = dict(group.externals)
    lines, success, twins_ok, twin_refusals = [], good, True, []
    for number, (twin_profile, names) in enumerate(sorted(profiles.items())):
        twin_flags = unitprofiles.command_flags(twin_profile)
        twin = os.path.join(cc.scratch_dir(), "twin_%s_%d.o" % (TMP_TAG(), number))
        if os.path.exists(twin):
            os.remove(twin)
        try:
            if not recompile(twin_profile.compiler, twin_flags, twin) or not os.path.exists(twin):
                return False, report + f"\nDIFFER duplicate profile '{twin_flags}' does not compile", None
            headers, (syms, _) = elf_section_headers(twin), object_syms(twin)
            addresses = dict(group.duplicates)
            for name in names:
                address = addresses[name]
                section, value, size = syms.get(name, (None, None, None))
                expected = by_va[address][1]
                if (not isinstance(section, int) or headers[section][0] != ".text" or value != 0
                        or size != expected or headers[section][1][5] != expected
                        or not headers[section][1][2] & 4):
                    lines.append(f"DIFFER duplicate 0x{address:x} {name}: extent {size} "
                                 f"under '{twin_flags}', retail {expected}")
                    success = twins_ok = False
                    continue

                def resolve(symbol, section=section, address=address):
                    if symbol in addresses:
                        return addresses[symbol]
                    if symbol in aliases:
                        return aliases[symbol]
                    if symbol in syms and isinstance(syms[symbol][0], int):
                        return address + syms[symbol][1] if syms[symbol][0] == section else None
                    try:
                        return sym_address(symbol, by_name, symbols)
                    except SymbolError as error:
                        lines.append(f"  symbol {symbol!r}: {error}")
                        twin_refusals.append(error)
                        return spelled_address(symbol, symbols)

                patched, _, unresolved = apply_relocs(
                    object_section(twin, ".text", section),
                    object_relocs(twin, target_section=section), resolve, gp)
                retail = va_bytes(image, address, expected)
                ok = patched == retail and not unresolved
                success, twins_ok = success and ok, twins_ok and ok
                lines.append(f"{'MATCH' if ok else 'DIFFER'} duplicate 0x{address:x} {name} "
                             f"{expected}B under '{twin_flags}'")
                for offset, symbol in unresolved:
                    lines.append(f"  unresolved relocation {symbol!r} at +0x{offset:x}")
                if patched is not None and not ok:
                    for at in range(0, expected, 4):
                        if patched[at:at + 4] != retail[at:at + 4]:
                            lines.append(f"  body 0x{address:x} [{at // 4}] retail "
                                         f"{retail[at:at + 4][::-1].hex()} ours {patched[at:at + 4][::-1].hex()}")
        finally:
            if os.path.exists(twin):
                os.remove(twin)
    head, _, rest = report.partition("\n")
    # A twin that differs makes the unit a mismatch; a twin's naming refusal is at
    # least a name defect. Rewrite the head's verdict and category accordingly.
    found = re.search(r"cat=(\S+)", head)
    kind = found.group(1) if found else "mismatch"
    if not twins_ok:
        kind = "mismatch"
    elif twin_refusals and kind in ("match", "code-only", "name-defect"):
        kind = category(True, twin_refusals, "-")
    success = success and twins_ok and not twin_refusals
    head = ("MATCH" if kind == "match" else "DIFFER") + head[head.index(" "):]
    head = re.sub(r"cat=\S+", "cat=" + kind, head) if found else head + f" cat={kind}"
    return kind == "match", "\n".join([head, rest] + lines) if lines else (head + "\n" + rest), \
        records if (records is not None and twins_ok) else None


def isolate_emitted_body(obj, requested, records, group, symbols):
    """Select one already-verified member; every other member has its own unit.

    Only symbol/section metadata changes. Retained instructions and relocations
    are preserved, and references to other owned members become external calls.
    """
    _, by_va = load_symbols(symbols)
    selected = next(name for name, (address, _, _) in records.items() if address == requested)
    selected_section = records[selected][1]
    payload = object_section(obj, ".text", selected_section)
    relocations = object_relocs(obj, target_section=selected_section)
    headers = elf_section_headers(obj)
    # stripped bodies (verified unreferenced by verify_emitted_object) are removed with
    # the siblings; their symbols become undefined and nothing relocates against them
    defined, _ = object_syms(obj)
    stripped_sections = {defined[name][0] for name in group.stripped
                         if name in defined and isinstance(defined[name][0], int)}
    # a whole-file unit's data stays retail's: the object keeps references to it, not copies
    data_names = {name for name, _ in group.data}
    stripped_sections |= getattr(records, "data_sections", set())
    with open(obj, "rb") as original:
        data = bytearray(original.read())
    for _, h in headers:
        if h[1] != 2:  # SHT_SYMTAB
            continue
        strings = headers[h[6]][1]
        table = data[strings[4]:strings[4] + strings[5]]
        for offset in range(h[4], h[4] + h[5], h[9]):
            name_offset, = struct.unpack_from("<I", data, offset)
            end = table.find(b"\0", name_offset)
            name = table[name_offset:end].decode("latin1")
            if name not in records and name not in group.stripped and name not in data_names:
                continue
            # MWCC's binding 13 is compiler-specific. Explicitly owned symbols
            # become ordinary globals for GNU ld; code bytes remain untouched.
            data[offset + 12] = (1 << 4) | (data[offset + 12] & 15)
            if name != selected:
                struct.pack_into("<II", data, offset + 4, 0, 0)
                struct.pack_into("<H", data, offset + 14, 0)  # SHN_UNDEF
    with open(obj, "wb") as output:
        output.write(data)
    # The selected member's exception record and table are kept when verify_emitted_object
    # found them equal to retail (renamed by retail address so linkgen can pin them there,
    # like a standalone unit's); every other copy is discarded and retail's bytes stay.
    # Switch tables are placed only with the owner that jumps through them.
    kept = {}
    placement = getattr(records, "exception_placements", {}).get(selected)
    if placement:
        index_section, index_at, table_section, table_at, _size = placement
        kept[index_section] = ".exceptix.dw4_%08x" % index_at
        if table_section is not None:
            kept[table_section] = ".exception.dw4_%08x" % table_at
    dup_tables = set()
    if group.duplicates:
        jumptables = load_jumptables(jumptables_path(symbols))
        owned = sorted(jumptables.get(group.owner, []) + duplicate_tables(group, jumptables))
        dup_addresses = set(duplicate_tables(group, jumptables))
        dup_tables = {index for index, address, _ in jump_table_sections(obj, owned)
                      if any(address == a for a, _count in dup_addresses)}
    discarded = {i for i, (name, h) in enumerate(headers) if h[5] and i not in kept and (
        i in stripped_sections or name in (".exceptix", ".exception")
        or (name == ".rodata" and (requested != group.owner or i in dup_tables)))}
    rename_object_sections(obj, {**{section: ".text" if section == selected_section
                                    else f".text.owned_{section}"
                                    for _, section, _ in records.values()},
                                 **{i: f".text.owned_{i}" for i in discarded}, **kept})
    # Removing the verified siblings preserves undefined symbols in MWCC
    # objects; objcopy's --only-section path incorrectly drops some of them.
    arguments = ["mipsel-linux-gnu-objcopy", "--remove-section=.text.owned_*",
                 "--remove-section=.mwcats"]
    renames = {name: by_va[address][0] for name, (address, _, _) in records.items()}
    renames.update({name: by_va[address][0] for name, address in group.externals})
    renames.update({name: "DAT_%08x" % address for name, address in group.data})
    for old, new in renames.items():
        if old != new:
            arguments += ["--redefine-sym", f"{old}={new}"]
    subprocess.run(arguments + [obj], check=True, capture_output=True)
    final_headers = elf_section_headers(obj)
    allocated = [name for name, h in final_headers if h[2] & 2 and h[5]]
    if any(name not in (".text", ".rodata") and name not in kept.values() for name in allocated):
        raise ValueError("emitted body extraction left unplaced allocated data")
    text = [(i, h) for i, (name, h) in enumerate(final_headers) if name == ".text" and h[5]]
    if len(text) != 1 or text[0][1][5] != records[selected][2]:
        raise ValueError("emitted body extraction changed its extent")
    if object_section(obj, ".text", text[0][0]) != payload:
        raise ValueError("emitted body extraction changed instruction bytes")
    expected = [(section, offset, kind, renames.get(name, name), addend)
                for section, offset, kind, name, addend in relocations]
    if object_relocs(obj, target_section=text[0][0]) != expected:
        raise ValueError("emitted body extraction changed relocation ownership or order")


def compile_error(output):
    """The compiler's diagnostics on one line. The `File:` line is dropped: it holds a host path."""
    kept = []
    for line in output.splitlines():
        text = line.lstrip("# ").rstrip()
        if (line.startswith("###") or text.startswith(("File:", "Errors caused")) or not text.strip("-^ ")
                or re.fullmatch(r"(Error|Warning):\s*\^*", text)):
            continue
        kept.append(text)
    return " | ".join(kept) or "no output"


def verify_one(va, source, flags=FLAGS_DEFAULT, elf=ELF_DEFAULT,
               symbols="config/SLUS-20836/symbols.txt", mwcc=MWCC_DEFAULT, wibo=WIBO_DEFAULT,
               gp_override=None, verbose=False, jumptables=None,
               unit_flags=None, unit_compilers=None, unit_objects=None, units=None):
    """Verify one candidate against retail. -> (ok: bool, report: str)

    Shared by `main`, `tools/check.py`, `automatch.py`, `m2c_batch.py` and
    `permuter_one.py`, so `make check` is relocation-aware for every function
    rather than only for leaf functions.

    A `switch` compiles its jump table into `.rodata`, which is placed at the retail
    table address (config/SLUS-20836/jumptables.txt, from tools/jumptables.py). That table is
    compared here too, and an object that carries `.rodata` for a function with no
    recorded table is a **failure**: otherwise a switch function could "verify" on
    its code alone while its table was never looked at, and the relink would orphan
    it.

    The compiler, flags and exception mode are the function's **unit profile**
    (config/SLUS-20836/units.tsv, tools/unitprofiles.py; `units` selects another table, and
    outside every unit the caller's `flags` and `mwcc` apply). A per-function row in
    config/SLUS-20836/unit-flags.tsv / config/SLUS-20836/unit-compilers.tsv (`unit_flags`, `unit_compilers`
    select other tables) is a provisional override: it is compiled only after the
    unit profile failed to reproduce the code bytes, and a function that matches
    only that way is reported `cat=foreign-profile` (debt, never a match).
    Registered emitted members inherit their owner's profile and verify every body
    in that compiler unit before returning success.
    """
    img = read_elf(elf)
    by_name, by_va = load_symbols(symbols)
    if va not in by_va:
        return False, f"0x{va:x} is not in {symbols}"
    name, size = by_va[va]
    group = unitobjects.group_for(va, unit_objects)
    owner = group.owner if group else va
    try:
        resolution = unitprofiles.resolve(owner, flags, mwcc, units=units, unit_flags=unit_flags,
                                          unit_compilers=unit_compilers, symbols=symbols)
    except ValueError as error:
        return False, f"compile failed: {error}"
    retail = va_bytes(img, va, size)
    if jumptables is None:
        jumptables = load_jumptables(jumptables_path(symbols))
    tabs = sorted(jumptables.get(va, []))
    env = dict(os.environ, MWCIncludes=os.path.dirname(os.path.abspath(source)))

    def attempt(profile):
        """Compile `source` under `profile` and verify it -> (ok, report)."""
        profile = unitprofiles.for_source(profile, source, flags, mwcc)
        cmd_flags = unitprofiles.command_flags(profile)
        obj = os.path.join(cc.scratch_dir(), "cand_%s.o" % TMP_TAG())
        if os.path.exists(obj):
            os.remove(obj)
        r = subprocess.run(cc.compile_argv(wibo, profile.compiler, cmd_flags, source, obj),
                           capture_output=True, text=True, env=env)
        if not os.path.exists(obj):
            return False, "compile failed: " + compile_error(r.stdout + r.stderr)
        if group:
            def recompile(twin_compiler, twin_flags, out):
                subprocess.run(cc.compile_argv(wibo, twin_compiler, twin_flags, source, out),
                               capture_output=True, text=True, env=env)
                return os.path.exists(out)

            good, report, _ = verify_emitted_unit(
                obj, group, elf, symbols, profile, recompile, gp_override, verbose, va,
                jumptables, unit_flags, unit_compilers, units)
            return good, report
        # what the head line shows of the profile: the flags when they are not the caller's
        # defaults, the compiler when it is not the caller's
        notes = []
        if cmd_flags.split() != flags.split():
            notes.append("flags '%s'" % cmd_flags)
        if os.path.realpath(profile.compiler) != os.path.realpath(
                mwcc if os.path.isabs(mwcc) else os.path.join(ROOT, mwcc)):
            notes.append("compiler %s" % describe_profile(profile).split(" '")[0])
        try:
            return _verify_standalone(obj, va, name, size, retail, img, by_name, symbols, tabs,
                                      notes, gp_override, elf, verbose)
        except ValueError as error:
            # An unsupported relocation type or a malformed object: a failure with its
            # reason, never a silent skip (and never an exception that aborts a sweep).
            return False, f"DIFFER 0x{va:06x} {name} {size}B: {error}"

    ok, report = attempt(resolution.profile)
    if resolution.override is not None and not code_reproduced(report):
        ok_over, report_over = attempt(resolution.override)
        if code_reproduced(report_over):
            return False, foreign_profile_report(report_over, report, resolution)
        report += ("\n   provisional override (%s) does not reproduce the code bytes either"
                   % describe_profile(resolution.override))
    elif resolution.override is not None:
        head, _, rest = report.partition("\n")
        report = (head + " override=unused\n   provisional override (%s) is not needed: the unit profile "
                  "reproduces the code bytes; delete its row(s)" % describe_profile(resolution.override)
                  + ("\n" + rest if rest else ""))
    elif resolution.redundant:
        head, _, rest = report.partition("\n")
        report = (head + " override=redundant\n   per-function row(s) repeat the unit profile; delete them"
                  + ("\n" + rest if rest else ""))
    return ok, report


def foreign_profile_report(report_over, report_unit, resolution):
    """The report of a function whose code bytes match only under its provisional override.

    The head is the override compile's (its `exc=`/`orphan=` tokens describe the
    object the relink will place) with the verdict DIFFER and `cat=foreign-profile`;
    the first body line names both profiles, then the unit-profile attempt's own
    lines follow, indented, so the reader sees what the unit's compiler produced.
    """
    head, _, rest = report_over.partition("\n")
    head = "DIFFER" + head[len("MATCH ") if head.startswith("MATCH ") else len("DIFFER"):]
    head = re.sub(r"\bcat=[\w-]+", "cat=foreign-profile", head)
    if "cat=" not in head:
        head += " cat=foreign-profile"
    head += " override=foreign"
    unit = resolution.unit.name if resolution.unit is not None else "(no unit: the caller's defaults)"
    lines = [head,
             "   foreign-profile: the code bytes are reproduced only under the provisional override (%s); "
             "under the unit profile of %s (%s) they are not" % (
                 describe_profile(resolution.override), unit, describe_profile(resolution.profile))]
    unit_lines = report_unit.splitlines()
    lines += ["      unit profile: " + ln.strip() for ln in unit_lines[:12]]
    if len(unit_lines) > 12:
        lines.append("      unit profile: ... %d more line(s)" % (len(unit_lines) - 12))
    if rest:
        lines += rest.splitlines()
    return "\n".join(lines)


def _verify_standalone(obj, va, name, size, retail, img, by_name, symbols, tabs,
                       notes, gp_override, elf, verbose):
    """The non-group half of `verify_one`: one compiled body against retail.

    Everything the object carries must have a retail identity: its one `.text`
    body, the recorded jump tables (config/SLUS-20836/jumptables.txt) and, when retail keeps
    an exception index record for the function (config/SLUS-20836/exceptions.txt), the
    `.exceptix` record and `.exception` table — each compared byte for byte with
    relocations applied, like the group path in `verify_emitted_object`. Any other
    allocated section, a defined symbol that names a retail address outside the
    body, a dishonest relocation name or exception metadata retail contradicts
    (emitted where retail has no record, or absent where retail has one) is a
    failure with a message.
    """
    off, symsize, ndx = object_sym(obj, name)
    if symsize is None or not isinstance(ndx, int):
        return False, f"object defines no symbol {name!r}"
    headers = elf_section_headers(obj)
    if not 0 <= ndx < len(headers) or headers[ndx][0] != ".text":
        return False, f"object symbol {name!r} is not defined in .text"
    all_text = object_section(obj, ".text", ndx)
    if symsize <= 0 or off + symsize > len(all_text):
        return False, f"object symbol {name!r} has an invalid .text extent"
    object_relocs(obj)      # rejects unsupported relocation types in any section
    text = all_text[off:off + symsize]
    text_sections = [header for section, header in headers if section == ".text" and header[5]]
    text_bytes = sum(header[5] for header in text_sections)
    isolated = off == 0 and len(text_sections) == 1 and text_bytes == symsize
    table_errors = []
    try:
        table_sections = jump_table_sections(obj, tabs)
    except ValueError as error:
        table_sections = []
        table_errors.append("   " + str(error))
    table_bases = {index: address for index, address, _size in table_sections}
    tbl_lo = tabs[0][0] if tabs else None

    # Place the selected symbol at its retail VA (section base VA - off), and
    # our `.rodata` at the retail jump-table address. That is what makes a relocation
    # against a *local* symbol (MWCC's anonymous table, `@21`) resolvable at all.
    obj_syms, obj_secs = object_syms(obj)
    index_sections = [i for i, (n, h) in enumerate(headers) if n == ".exceptix" and h[5]]
    table_sections_exc = [i for i, (n, h) in enumerate(headers) if n == ".exception" and h[5]]
    record = exception_records.load(exception_records.config_path(symbols)).get(va)
    exc_table_va = record[1] if record else None
    dishonest = {}

    def resolve(nm):
        # The object's own definitions first: MWCC's local labels (`@21`, `@ET@FUN_x`)
        # carry the function's name, so a name lookup would hand the exception
        # record's table pointer the function's address.
        if nm in obj_syms and isinstance(obj_syms[nm][0], int):
            sndx, value, _sz = obj_syms[nm]
            sec = obj_secs.get(sndx)
            if sec == ".rodata":
                return table_bases[sndx] + value if sndx in table_bases else None
            if sec == ".text":
                return va + value - off if sndx == ndx else None
            if sec == ".exception" and exc_table_va is not None and len(table_sections_exc) == 1:
                return exc_table_va + value if sndx == table_sections_exc[0] else None
            return None
        try:
            base = sym_address(nm, by_name, symbols)
        except SymbolError as error:
            # Still compare the bytes at the address the name spells (what the
            # relink provides), so a naming defect is told apart from a mismatch.
            dishonest[nm] = error
            return spelled_address(nm, symbols)
        if base is not None:
            return base
        if nm == ".rodata" and len(table_bases) == 1:
            return list(table_bases.values())[0]
        return None

    gp = gp_override if gp_override is not None else reginfo_gp(elf)
    text_rel = function_relocs(object_relocs(obj, target_section=ndx), off, symsize)
    _solved, ngp = solve_gp(text, text_rel, resolve, retail, va)
    patched, _, unresolved = apply_relocs(text, text_rel, resolve, gp)
    if patched is None:
        return False, "could not resolve gp"

    words_a = [struct.unpack_from("<I", patched, 4 * i)[0] for i in range(len(patched) // 4)]
    words_b = [struct.unpack_from("<I", retail, 4 * i)[0] for i in range(size // 4)]
    bad = [i for i in range(min(len(words_a), len(words_b))) if words_a[i] != words_b[i]]
    ok = (isolated and not bad and len(words_a) == len(words_b) and not unresolved
          and len(text) == size and not table_errors)

    # ---- every allocated section must have a retail identity -----------------
    owned = {ndx} | set(table_bases) | set(index_sections) | set(table_sections_exc)
    unowned = [(n, h[5]) for i, (n, h) in enumerate(headers)
               if h[2] & 2 and h[5] and i not in owned]
    smuggled = defined_outside(obj_syms, headers, [(va, va + size)], exempt={name})
    ok = ok and not unowned and not smuggled

    # ---- the jump table -----------------------------------------------------
    tbl_report = list(table_errors)
    for section_index, table_address, want in table_sections:
        rodata = object_section(obj, ".rodata", section_index)
        tbl_rel = object_relocs(obj, target_section=section_index)
        got, _, unres2 = apply_relocs(rodata, tbl_rel, resolve, gp)
        got = got if got is not None else b""
        retail_tbl = va_bytes(img, table_address, want)
        good = len(got) == want and got == retail_tbl and not unres2
        if good:
            tbl_report.append("   jump table 0x%06x: %d entries, %d bytes, matches retail"
                              % (table_address, want // 4, want))
        else:
            ok = False
            tbl_report.append("   jump table 0x%06x differs (section %d)"
                              % (table_address, section_index))
            for off_, nm in (unres2 or []):
                tbl_report.append("   jump table: unresolved relocation against %r at "
                                  "+0x%x" % (nm, off_))
            for i in range(0, min(len(got), want), 4):
                if got[i:i + 4] != retail_tbl[i:i + 4]:
                    tbl_report.append("      [%2d] retail %s  ours %s"
                                      % (i // 4, retail_tbl[i:i + 4][::-1].hex(),
                                         got[i:i + 4][::-1].hex()))

    # ---- the exception metadata ---------------------------------------------
    exc_status, exc_report = _compare_exception_metadata(
        obj, headers, name, va, record, index_sections, table_sections_exc, resolve, gp, img)
    kind = category(ok, dishonest.values(), exc_status)
    ok = kind == "match"

    bits = [f"0x{va:06x} {name}", f"{size}B", f"{len(text_rel)} relocs"] + list(notes or ())
    if gp:
        bits.append(f"gp=0x{gp:x}")
    if tabs:
        bits.append("jtbl 0x%06x/%d" % (tbl_lo, sum(t[1] for t in tabs)))
    if exc_status != "-":
        bits.append(f"exc={exc_status}")
    if exc_status in ("extra", "differ"):
        # bytes the relink cannot place at a retail slot (it links them outside .text);
        # aligned as ld will lay them out, so linkcheck's orphan gate can bound them
        bits.append("orphan=%d" % sum(-(-h[5] // max(h[8], 1)) * max(h[8], 1)
                                      for i in index_sections + table_sections_exc
                                      for h in [headers[i][1]]))
    bits.append(f"cat={kind}")
    lines = [("MATCH " if ok else "DIFFER") + " " + " ".join(bits)]
    if len(text) != size:
        lines.append(f"   size: retail {size}, ours {len(text)}")
    if not isolated:
        lines.append("   object has %d additional .text bytes (symbol section %d, offset 0x%x); "
                     "per-function linking requires an isolated body"
                     % (text_bytes - symsize, ndx, off))
    for section_name, length in unowned:
        lines.append(f"   unowned allocated section {section_name} ({length} bytes): a candidate may "
                     "carry only its code, its recorded jump tables and its exception metadata")
    for symbol, claimed in smuggled:
        lines.append(f"   object defines {symbol}, which names retail address 0x{claimed:x} outside "
                     "the function (a candidate may only reference that datum)")
    for off_, nm in unresolved:
        lines.append(f"   unresolved relocation against {nm!r} at +0x{off_:x}")
    for nm, error in sorted(dishonest.items()):
        lines.append(f"   symbol {nm!r}: {error}")
    lines += tbl_report
    lines += exc_report
    if verbose:
        for i in range(len(words_a)):
            mark = "  " if i < len(words_b) and words_a[i] == words_b[i] else "!!"
            lines.append(f"   {mark}[{i:3}] retail {words_b[i] if i < len(words_b) else 0:08x}"
                         f"  ours {words_a[i]:08x}")
    else:
        for i in bad:
            lines.append(f"   [{i:3}] retail {words_b[i]:08x}  ours {words_a[i]:08x}")
    return ok, "\n".join(lines)


def _compare_exception_metadata(obj, headers, name, va, record, index_sections, table_sections,
                                resolve, gp, img):
    """Compare a standalone unit's `.exceptix` record and `.exception` table with retail.

    `record` is the retail (index_va, table_va or None, table_size) from
    config/SLUS-20836/exceptions.txt, or None when retail keeps no record for the function.
    Returns (status, report lines) with status one of:

      "-"        neither retail nor the object has exception metadata;
      "ok"       the record (and table, if any) equals retail;
      "extra"    the object emits metadata retail never kept (the retail unit was
                 compiled without it: `-Cpp_exceptions off`, or it was C);
      "missing"  retail keeps a record the object does not produce (the retail
                 unit was C++ with exceptions on);
      "differ"   both exist but the shape or the bytes differ.
    """
    emitted = index_sections or table_sections
    if record is None and not emitted:
        return "-", []
    if record is None:
        shape = ", ".join(f"{headers[i][0]} {headers[i][1][5]} bytes"
                          for i in index_sections + table_sections)
        return "extra", [f"   exception metadata: the object emits {shape}, but retail keeps no "
                         f"index record for 0x{va:x} (its unit was compiled without exception "
                         "metadata: `-Cpp_exceptions off`, or as C)"]
    index_at, table_at, table_size = record
    what = f"packed" if table_at is None else f"table 0x{table_at:x} {table_size} bytes"
    if not emitted:
        return "missing", [f"   exception metadata: retail keeps an index record at 0x{index_at:x} "
                           f"({what}) that the object does not produce (its unit was C++ with "
                           "exceptions on)"]
    lines = []
    if len(index_sections) != 1 or headers[index_sections[0]][1][5] != 12:
        return "differ", [f"   exception metadata: expected one 12-byte .exceptix record, found "
                          + ", ".join(str(headers[i][1][5]) for i in index_sections)]
    index = index_sections[0]
    relocations = object_relocs(obj, target_section=index)
    first = [r for r in relocations if r[1] == 0]
    if len(first) != 1 or first[0][2] != R_32 or first[0][3] != name or first[0][4] != 0:
        return "differ", [f"   exception metadata: the .exceptix record is not relocated against {name}"]
    if (table_at is None) != (not table_sections) or len(table_sections) > 1:
        return "differ", [f"   exception metadata: retail record at 0x{index_at:x} is {what}, the "
                          f"object emits {len(table_sections)} .exception section(s)"]
    status = "ok"
    got, _, unresolved = apply_relocs(object_section(obj, ".exceptix", index), relocations, resolve, gp)
    want = va_bytes(img, index_at, 12)
    if got == want and not unresolved:
        lines.append(f"   exception index 0x{index_at:x}: matches retail ({what})")
    else:
        status = "differ"
        lines.append(f"   exception index 0x{index_at:x} differs: retail {want.hex()} ours "
                     f"{(got or b'').hex()}")
        for offset, symbol in unresolved or ():
            lines.append(f"   exception index: unresolved relocation against {symbol!r} at +0x{offset:x}")
    if table_at is not None:
        section = table_sections[0]
        raw = object_section(obj, ".exception", section)
        pad = table_size - len(raw)
        got, _, unresolved = apply_relocs(raw, object_relocs(obj, target_section=section), resolve, gp)
        want = va_bytes(img, table_at, table_size)
        if 0 <= pad <= 3 and got == want[:len(raw)] and not any(want[len(raw):]) and not unresolved:
            lines.append(f"   exception table 0x{table_at:x}: {len(raw)} bytes, matches retail")
        else:
            status = "differ"
            lines.append(f"   exception table 0x{table_at:x} differs: retail {table_size} bytes, "
                         f"ours {len(raw)}")
            for offset, symbol in unresolved or ():
                lines.append(f"   exception table: unresolved relocation against {symbol!r} at +0x{offset:x}")
            for i in range(0, min(len(got or b''), table_size), 4):
                if got[i:i + 4] != want[i:i + 4]:
                    lines.append("      [%2d] retail %s  ours %s"
                                 % (i // 4, want[i:i + 4][::-1].hex(), got[i:i + 4][::-1].hex()))
    return status, lines


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("address")
    ap.add_argument("source")
    ap.add_argument("--flags", default=FLAGS_DEFAULT)
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF", ELF_DEFAULT))
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--mwcc", default=os.environ.get("DW4_MWCC", MWCC_DEFAULT))
    ap.add_argument("--wibo", default=os.environ.get("DW4_WIBO", WIBO_DEFAULT))
    ap.add_argument("--gp", type=lambda s: int(s, 0), default=None)
    ap.add_argument("--unit-flags", default=None,
                    help="per-unit flag override table (default config/SLUS-20836/unit-flags.tsv)")
    ap.add_argument("--unit-compilers", default=None,
                    help="content-pinned compiler table (default config/SLUS-20836/unit-compilers.tsv)")
    ap.add_argument("--unit-objects", default=None,
                    help="explicit emitted-body ownership (default config/SLUS-20836/unit-objects.json)")
    ap.add_argument("--units", default=None,
                    help="unit profile table (default config/SLUS-20836/units.tsv, or units.tsv beside --symbols)")
    ap.add_argument("--verbose", action="store_true")
    a = ap.parse_args(argv)
    va = int(a.address, 0)
    source, tmp = a.source, None
    # A translation unit defines many functions; verify the one at this address by
    # splitting it out first (tools/units.py).  A one-function file is used as-is.
    if os.path.exists(source) and len(units.definitions(open(source).read())) > 1:
        _by_name, by_va = load_symbols(a.symbols)
        nm = by_va.get(va, (None,))[0]
        if nm is None:
            print("verify: 0x%x is not in %s" % (va, a.symbols), file=sys.stderr)
            return 2
        source, tmp = units.standalone(a.source, nm, symbols=a.symbols,
                                       unit_objects=a.unit_objects)
    try:
        ok, report = verify_one(va, source, flags=a.flags, elf=a.elf,
                                symbols=a.symbols, mwcc=a.mwcc, wibo=a.wibo,
                                gp_override=a.gp, verbose=a.verbose,
                                unit_flags=a.unit_flags, unit_compilers=a.unit_compilers,
                                unit_objects=a.unit_objects, units=a.units)
    finally:
        if tmp:
            os.remove(tmp)
    print(report)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
