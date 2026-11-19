#!/usr/bin/env python3
"""whole_file_rows.py — derive the whole-file rows of a stock library from retail.

A stock file keeps its upstream text, so the rows that tie it to retail are measured, never typed
(docs/engine/emitted-functions.md, "Whole-file units"). Each listed file is compiled with the
unit's profile, then:

  members    each `.text` function is found in the retail range by its bytes, relocated fields
             masked; a name symbols.txt already places wins, and a `--at name=va` settles a
             function that fits more than one retail start. The file's static initializer (its
             `.init`) is the function of the static-initializer table it fits, outside the range
  duplicates a compiled function outside the range that a member still calls, that a vtable or
             other datum the file keeps names, or that an exception table names: the retail
             linker kept another file's copy, found at the address the retail call, data or table
             word holds, and what that copy reaches is walked in turn. A copy kept from a unit of
             another profile (a profile twin) must be reproduced as tools/verify.py checks it: the
             same source compiled under that unit's profile, at the retail extent
  stripped   any other compiled function with no retail copy: the retail linker dropped it
  data       each datum a member, a duplicate, a kept datum or an exception table references (a
             type string only a `throw()` specification names), its address read back from the
             retail relocation fields. A named datum is a `data` row; an anonymous one (`@183`,
             `table$14`: MWCC numbers them across the whole translation unit, headers included)
             is its address in `anon`, and tools/verify.py binds it from its references. A float
             or double literal has no row: each reference reads the pool entry its retail
             instruction names, which must hold the literal's bytes (verify.fold_literals), and
             one literal may be read at several entries
  externals  each call out of the file, read from the retail `jal` of a member or of a duplicate's
             retail copy, and each function out of the file an exception table names (a cleanup
             destructor no member calls), read from the retail table word
  symbol     the owner's compiler name when symbols.txt names it otherwise: a C++ file's mangled
             owner, or a `static` several files define (`setup`, which symbols.txt calls
             `setup_libosd`)

A retail function in the range that no compiled function reproduces stops the run with its name:
the compile is wrong, and writing rows would hide it behind `stripped`. A source file that is still
being recovered (`--partial`) lacks some of its functions: a retail function in the range that no
compiled function reproduces is then reported and keeps linking from the retail image, provided
the file defines nothing of that name; one such file's units.tsv row covers the whole range, so the
functions at its edges keep the file's profile.

A C++ file (`--cxx`) keeps its mangled names in the rows and writes the plain ones to `--names`. A
cross-file reference the compiler-name map binds (config/SLUS-20836/compiler-names.tsv, tools/compiler_names.py:
a member another unit's row places) gets no `externals` row, nor a `data` row when the file does not define the
datum; any other cross-file reference stays an external. The map is read without the rows this run replaces, so
a name only they bound (a call into the file's own range through a view's member name) stays an external.
`--write` then regenerates the map, so a converted class's defining unit is written first and the units that
call it after. The range's present rows settle what they settled before, so regenerating an unchanged unit writes
its row unchanged and a conversion's row diff is what the conversion changed (stable_row):

  * a compiler name they bind keeps its address (tools/memberize.py renames a converted member's key, and empty
    virtual functions fit many starts), and a name they strip is dropped (C++ files);
  * the static initializer's entry is theirs when the file's initializer fits several table entries;
  * retail functions of the range no compiled function reproduces, none of which they placed, link from retail
    as they did (the run is `--partial` without saying so); one they placed stops the run, a wrong compile;
  * a `data` or `externals` name they listed stays while the object still names it, one they left out that binds
    without a row (data-names.tsv, symbols.txt, the compiler-name map) stays out, a name gone from the object
    goes; the owner's `symbol` they wrote stays; a field with their content keeps their order.

`--drop` keeps a function out of the
range when it fits a start another function owns: stock `lua_dofile` and `lua_dobuffer` fit one retail start,
and only a call target tells them apart; two inline destructors of one shape do too, and the one a member still
reaches becomes a duplicate.

`--unit-va <va>` measures the whole-file unit of units.tsv that holds `va`: its source (the file under src/ its
unit name ends with, or `--source`), range, compiler, flags and exception mode come from its row, and `--write`
replaces its unit-objects.json row only, leaving units.tsv as it is. This is how the rows of a DW4 unit whose
functions became C++ members are written: never by hand.

A file with no retail function is data-only when the retail linker kept data of it
(docs/engine/emitted-functions.md, "Data-only units"): each of its data sections is placed where another
file's row, of this run or of unit-objects.json, reads a name it defines, and the row is keyed by the first.
Its `stripped` names are its compiled functions and those of `--reference <stem>=<object>`, its library
object (an SDK archive member); none may have a copy anywhere in the retail code, relocated words masked.
A file none of whose data is reached was dropped whole and gets no row. A data-only file's units.tsv row
covers its first data section and goes after the code rows.

The rows go to stdout as JSON. `--write` merges them into unit-objects.json, replacing the
whole-file rows inside the range and each row of a function the file now places (a row of a
function the file leaves out stays), and replaces the units.tsv rows inside the range with one per
file. The rows are written in address order. `--names` writes a `.tsv` for
tools/apply_names.py, which is what moves `FUN_` names to the library's own.

Usage:
  whole_file_rows.py --src src/third_party/zlib --files adler32 crc32 --range 0x221870 0x2252d8 \\
      --compiler combat --flags "-O4,p -sdatathreshold 2 -lang c -I- -Isrc/third_party/libc" \\
      --unit zlib [--write] [--names config/SLUS-20836/names/zlib.tsv]
  whole_file_rows.py --unit-va 0x44b860 --cxx [--write]
  whole_file_rows.py --src src/sony/libsdr --files sdr_main sdr_cb --range 0x118fe0 0x1194c0 \\
      --compiler ee-gcc-2.9 --flags "-O2 -G0 -ffunction-sections -Iinclude" --unit sony_libsdr \\
      --reference sdr_cb=<the SDK's libsdr.a member sdr_cb.o> [--write]
"""
import argparse
import collections
import glob
import json
import os
import re
import struct
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cc
import compiler_names
import exceptions
import unitprofiles
import unitobjects
import verify

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
R_32, R_26, R_HI16, R_LO16, R_GPREL16 = 2, 4, 5, 6, 7
FIELD_MASK = {R_32: 0xffffffff, R_26: 0x03ffffff, R_HI16: 0xffff, R_LO16: 0xffff, R_GPREL16: 0xffff}


def sext(value):
    return value - 0x10000 if value & 0x8000 else value


class Retail:
    def __init__(self, elf):
        self.image = verify.read_elf(elf)
        self.gp = verify.reginfo_gp(elf)

    def word(self, va):
        return struct.unpack("<I", verify.va_bytes(self.image, va, 4))[0]


class Function:
    """One compiled `.text` section: its words and the mask of the fields the linker fills."""

    def __init__(self, name, section, obj, headers):
        self.name, self.section = name, section
        raw = verify.object_section(obj, headers[section][0], section)
        self.raw = raw
        self.relocs = verify.object_relocs(obj, target_section=section)
        self.words = struct.unpack("<%dI" % (len(raw) // 4), raw)
        masks = [0xffffffff] * len(self.words)
        for _section, offset, kind, _symbol, _addend in self.relocs:
            masks[offset // 4] &= ~FIELD_MASK.get(kind, 0xffffffff) & 0xffffffff
        self.masks = masks

    def fits(self, retail, va):
        return all(retail.word(va + 4 * i) & m == w & m
                   for i, (w, m) in enumerate(zip(self.words, self.masks)))


def compile_file(wibo, compiler, flags, source, out):
    argv = cc.compile_argv(wibo, compiler, flags, source, out)
    done = subprocess.run(argv, cwd=ROOT, capture_output=True, text=True)
    if done.returncode:
        sys.exit("%s: compile failed\n%s%s" % (source, done.stdout, done.stderr))
    verify.trim_padded_names(out)


def text_functions(obj):
    syms, _ = verify.object_syms(obj)
    headers = verify.elf_section_headers(obj)
    out = {}
    for name, (section, value, size) in syms.items():
        if isinstance(section, int) and section < len(headers) and headers[section][0] == ".text" \
                and value == 0 and size:
            out[name] = Function(name, section, obj, headers)
    return syms, headers, out


def static_initializer(obj, syms, headers, retail, forced, settled=None):
    """(name, Function, retail address) of the file's static initializer, or None. It is the retail
    function of the static-initializer table its bytes fit, relocated fields masked, or the one
    `--at` names; of several that fit, the one the range's previous row places (`settled`)."""
    try:
        found = verify.static_initializer(obj, headers, syms)
    except ValueError as error:
        sys.exit("%s: %s" % (obj, error))
    if not found:
        return None
    name, section, _ctor = found
    function = Function(name, section, obj, headers)
    lo, hi = verify.STATIC_INITIALIZERS
    entries = [forced[name]] if name in forced else [retail.word(at) for at in range(lo, hi, 4)]
    hits = [va for va in entries if function.fits(retail, va)]
    if len(hits) > 1 and (settled or {}).get(name) in hits:
        hits = [settled[name]]
    if len(hits) != 1:
        sys.exit("%s fits %s of the static-initializer table: fix the compile or settle with --at %s=VA"
                 % (name, "/".join("0x%x" % va for va in hits) or "no entry", name))
    return name, function, hits[0]


class Twins:
    """The duplicates' copies as retail built them ("Profile twins", docs/engine/emitted-functions.md).

    Retail keeps the copy the linker saw first, compiled under the profile of the unit at its
    address (verify.duplicate_profiles). When that profile is not the file's, the same source is
    compiled under it, as verify_emitted_unit does, and that compile's copy is the one retail must
    hold, with the retail extent. Under the file's own profile the file's copy is the one."""

    def __init__(self, profile, source, tmp, config, wibo):
        self.profile, self.source, self.tmp, self.wibo = profile, source, tmp, wibo
        self.tables = dict(units=os.path.join(config, "units.tsv"),
                           unit_flags=os.path.join(config, "unit-flags.tsv"),
                           unit_compilers=os.path.join(config, "unit-compilers.tsv"),
                           symbols=os.path.join(config, "symbols.txt"))
        self.extents = verify.load_symbols(self.tables["symbols"])[1]
        self.objects, self.copies = {}, {}

    def __call__(self, name, address):
        """The copy of `name` retail must hold at `address`, or None for the file's own copy."""
        if (name, address) not in self.copies:
            self.copies[name, address] = self.copy(name, address)
        return self.copies[name, address]

    def copy(self, name, address):
        group = collections.namedtuple("Duplicates", "duplicates")(((name, address),))
        try:
            profiles = verify.duplicate_profiles(group, self.profile, **self.tables)
        except ValueError as error:
            sys.exit("%s at 0x%x: %s" % (name, address, error))
        if not profiles:
            return None
        (profile,) = profiles
        flags = unitprofiles.command_flags(profile)
        if profile not in self.objects:
            stem = os.path.splitext(os.path.basename(self.source))[0]
            obj = os.path.join(self.tmp, "twin%d_%s.o" % (len(self.objects), stem))
            compile_file(self.wibo, profile.compiler, flags, self.source, obj)
            self.objects[profile] = text_functions(obj)[2]
        copy = self.objects[profile].get(name)
        extent = self.extents[address][1] if address in self.extents else None
        if copy is None or len(copy.raw) != extent:
            sys.exit("%s: %s compiled under '%s' is %s bytes and retail's copy at 0x%x is %s"
                     % (self.source, name, flags, len(copy.raw) if copy else "no", address, extent))
        return copy


def locate(functions, retail, starts, placed, dropped=()):
    """{name: va} for the functions with a retail copy. A function that fits several starts is
    settled by the others: a file keeps its functions in order, and each start is used once."""
    found, open_ = {}, {}
    for name, function in functions.items():
        if name in dropped:
            continue
        if name in placed:
            if not function.fits(retail, placed[name]):
                sys.exit("%s does not reproduce its retail copy at 0x%x: fix the compile"
                         % (name, placed[name]))
            found[name] = placed[name]
            continue
        hits = [va for va in starts if function.fits(retail, va)]
        if len(hits) == 1:
            found[name] = hits[0]
        elif hits:
            open_[name] = hits
    clash = [v for v, n in collections.Counter(found.values()).items() if n > 1]
    if clash:
        sys.exit("one retail start fits two functions: %s; settle with --at or --drop"
                 % ", ".join("0x%x %s" % (v, "/".join(n for n in found if found[n] == v)) for v in clash))
    while open_:
        taken = set(found.values())
        settled = {n: [v for v in hits if v not in taken] for n, hits in open_.items()}
        # a function whose every retail copy belongs to a byte-identical twin was stripped
        settled = {n: hits for n, hits in settled.items() if hits}
        open_ = {n: h for n, h in open_.items() if n in settled}
        if not open_:
            break
        single = {n: hits[0] for n, hits in settled.items() if len(hits) == 1}
        if not single:
            sys.exit("ambiguous: %s; settle with --at name=va"
                     % ", ".join("%s at %s" % (n, "/".join("0x%x" % v for v in h)) for n, h in settled.items()))
        found.update(single)
        open_ = {n: h for n, h in open_.items() if n not in single}
    return found


def reach(function_at, retail, syms, headers, obj, functions, records, names, hi, twins=None, sections=()):
    """(data, duplicates, externals) of one file: what its placed members reach in retail.

    The walk starts at each member's body and its retail exception table and follows every
    relocation, as verify keeps a section live (verify.dead_data):
      a compiled function outside the file is a duplicate: an inline destructor a member calls, a
      virtual function a reached vtable names, a cleanup an exception table names. The retail
      linker kept another file's copy, at the address the retail `jal`, `lui`/`addiu` pair or data
      word holds, and that copy must fit there: the compiled one, or the profile twin
      `twins(name, address)` returns when another unit's profile built it. Its body and table are
      walked in turn, so a body a kept vtable names is never `stripped` (verify.unreferenced)
      a datum is read back from the retail relocation fields and its section walked in turn: a
      vtable, an RTTI record, a type string only an exception table names
      a call out of the file is an external, read from the retail `jal`; a call only a duplicate
      makes (`operator delete` in an inline destructor) has no member's `jal` to be read from
    A twin is read for its calls and the functions it reaches only: its data are the twin object's,
    compared under that profile. A function an exception table names and nothing in the file
    defines is table_externals'. A data-only file has no member: its walk starts at its kept data
    `sections`, [(retail address, section index)]."""
    tables = exception_tables(syms, headers, obj, functions)
    data, duplicates, externals, seen, work = {}, {}, {}, set(), []

    def walk_section(base, index):
        work.append((base, verify.object_section(obj, headers[index][0], index),
                     verify.object_relocs(obj, target_section=index),
                     "table" if headers[index][0] == ".exception" else "data", index))

    def walk_body(name, address, copy):
        own = copy is functions[name]
        work.append((address, copy.raw, copy.relocs, "data" if own else "twin", (name, address)))
        if own:     # a twin's record and table belong to its unit's compile, as in verify
            for table_va, index in table_fields({name: address}, tables, records):
                walk_section(table_va, index)

    for name, va in function_at.items():
        walk_body(name, va, functions[name])
    for base, index in sections:
        walk_section(base, index)
    while work:
        base, raw, relocs, mode, key = work.pop()
        if key in seen:
            continue
        seen.add(key)
        for index, (_section, offset, kind, name, _addend) in enumerate(relocs):
            if name in function_at or kind == R_LO16:
                continue
            field = retail.word(base + offset)
            own = struct.unpack_from("<I", raw, offset)[0]
            if name in functions:
                if kind == R_26:
                    address = (base & 0xf0000000) | ((field & 0x3ffffff) << 2)
                elif kind == R_32:
                    address = (field - own) & 0xffffffff
                elif kind == R_HI16:
                    address = pair_address(retail, base, raw, relocs, index, field, own)
                else:
                    sys.exit("%s: relocation type %d against function %s" % (obj, kind, name))
                if duplicates.get(name, address) != address:
                    sys.exit("%s: %s reads as 0x%x and 0x%x" % (obj, name, duplicates[name], address))
                if name not in duplicates:
                    copy = (twins(name, address) if twins else None) or functions[name]
                    if not copy.fits(retail, address):
                        sys.exit("%s: %s is reached at 0x%x, which holds other code" % (obj, name, address))
                    duplicates[name] = address
                    walk_body(name, address, copy)
                continue
            home = syms.get(name, (None,))[0]
            if (mode == "twin" and kind != R_26) or (mode == "table" and not isinstance(home, int)):
                continue
            if name in names and (kind == R_26 or names[name] < hi):
                continue
            if isinstance(home, int) and headers[home][0] in verify.LITERAL_SECTIONS:
                continue        # a literal has no row: literals() proves each reference
            if kind == R_26:
                target = (base & 0xf0000000) | ((field & 0x3ffffff) << 2)
                if externals.get(name, target) != target:
                    sys.exit("%s: %s reads as 0x%x and 0x%x" % (obj, name, externals[name], target))
                externals[name] = target
                continue
            if kind == R_HI16:
                address = pair_address(retail, base, raw, relocs, index, field, own)
            elif kind == R_GPREL16:
                address = (retail.gp + sext(field & 0xffff) - sext(own & 0xffff)) & 0xffffffff
            elif kind == R_32:
                address = (field - own) & 0xffffffff
            else:
                sys.exit("%s: relocation type %d against %s" % (obj, kind, name))
            if name in names:
                continue
            if data.get(name, address) != address:
                sys.exit("%s: %s reads as 0x%x and 0x%x" % (obj, name, data[name], address))
            data[name] = address
            if isinstance(home, int):
                walk_section(address - syms[name][1], home)
    return data, duplicates, externals


def unmapped(externals, data, syms, mapped, obj):
    """(externals, data) less the references the compiler-name map binds: every external, and each datum the
    object does not define (a defined datum keeps its row, which places it). The map and the retail reference
    must agree on the address."""
    def keep(name, address, defined):
        if name not in mapped or defined:
            return True
        if mapped[name][0] != address:
            sys.exit("%s: %s reads as 0x%x, and the compiler-name map binds it at 0x%x"
                     % (obj, name, address, mapped[name][0]))
        return False
    return ({name: address for name, address in externals.items() if keep(name, address, False)},
            {name: address for name, address in data.items()
             if keep(name, address, isinstance(syms.get(name, (None,))[0], int))})


def unit_row(units_path, va):
    """(lo, hi, unit name, @compiler id, flags, exception mode) of the whole-file units.tsv row holding `va`."""
    with open(units_path) as fh:
        rows = [line.rstrip("\n").split("\t") for line in fh]
    for fields in rows:
        if not fields[0].startswith("0x") or len(fields) < 8:
            continue
        lo, hi = int(fields[0], 16), int(fields[1], 16)
        if lo <= va < hi:
            if fields[7] != "whole file":
                sys.exit("0x%x is in %s, which is not a whole-file unit" % (va, fields[2]))
            return lo, hi, fields[2], fields[3], fields[4], fields[5]
    sys.exit("no units.tsv row holds 0x%x" % va)


def unit_source(name, src=os.path.join(ROOT, "src")):
    """The one .c/.cpp file under `src` whose stem the unit name `<library>_<stem>` ends with."""
    found = [path for ext in (".c", ".cpp") for path in glob.glob(os.path.join(src, "**", "*" + ext), recursive=True)
             if name.endswith("_" + os.path.splitext(os.path.basename(path))[0])]
    longest = max((len(os.path.basename(p)) for p in found), default=0)
    found = [p for p in found if len(os.path.basename(p)) == longest]
    if len(found) != 1:
        sys.exit("unit %s: %s; name its file with --source" % (name, "files " + ", ".join(sorted(found))
                                                                if found else "no source file"))
    return found[0]


def data_rows(data):
    """A row's `data` and `anon` from reach's {name: address}: a named datum keeps its name, an
    anonymous one is listed by its retail address alone, as verify.bind_anonymous binds it."""
    anon = collections.defaultdict(list)
    for name, address in data.items():
        if unitobjects.is_anonymous(name):
            anon[address].append(name)
    shared = {address: names for address, names in anon.items() if len(names) > 1}
    if shared:
        address, names = sorted(shared.items())[0]
        sys.exit("anonymous data %s are all read at 0x%x" % (" and ".join(sorted(names)), address))
    return ({name: "0x%08x" % address for name, address in sorted(data.items())
             if not unitobjects.is_anonymous(name)},
            ["0x%08x" % address for address in sorted(anon)])


def pair_address(retail, base, raw, relocs, index, field, own):
    """The address the `lui` of relocation `index` and its low half name in retail, less the
    compiled addend."""
    name = relocs[index][3]
    low = next(r for r in relocs[index + 1:] if r[2] == R_LO16 and r[3] == name)
    retail_low = retail.word(base + low[1])
    own_low = struct.unpack_from("<I", raw, low[1])[0]
    return (((field & 0xffff) << 16) + sext(retail_low & 0xffff)
            - ((own & 0xffff) << 16) - sext(own_low & 0xffff)) & 0xffffffff


def literals(function_at, duplicates, retail, syms, headers, obj, functions, data, deferred=()):
    """Prove the float and double literals the kept bodies read, as verify folds them
    (verify.fold_literals): each reference reads the pool entry its retail instruction names, and
    that entry must hold exactly the literal's bytes. The retail linker gave each reference its own
    pool lookup, so one literal can be read at several entries, and a literal has no `data` row.
    The stripped bodies and the data only they reach are dropped with them, as in verify; a
    duplicate built under another profile (`deferred`) is no body here, as in verify."""
    kept = {name: va for name, va in list(function_at.items()) + list(duplicates.items())
            if name not in deferred}
    live = {functions[name].section for name in list(function_at) + list(duplicates)}
    stripped = {f.section for name, f in functions.items() if name not in function_at and name not in duplicates}
    declared = {syms[name][0] for name in data if isinstance(syms.get(name, (None,))[0], int)}
    dead = stripped | verify.dead_data(obj, headers, syms, live, declared)
    with tempfile.TemporaryDirectory(prefix="dw4-whole-file-literals-") as tmp:
        copy = os.path.join(tmp, os.path.basename(obj))
        shutil.copyfile(obj, copy)
        _folded, errors = verify.fold_literals(copy, kept, retail.image, retail.gp, dead)
    if errors:
        sys.exit("%s: %s" % (obj, errors[0]))


def exception_tables(syms, headers, obj, functions):
    """{name: `.exception` section} of the compiled functions that have a table."""
    compiled = {name: (None, f.section, len(f.raw)) for name, f in functions.items()}
    return {name: table for name, (_index, table)
            in verify.group_exception_sections(obj, headers, syms, compiled).items() if table is not None}


def table_fields(placed, tables, records):
    """[(retail table va, `.exception` section)] of the placed bodies whose retail record has a table."""
    return [(records[va][1], tables[name]) for name, va in placed.items()
            if name in tables and va in records and records[va][1]]


def table_externals(placed, retail, syms, headers, obj, functions, records, names, data, externals, starts):
    """`externals` with the functions out of the file that an exception table of a member or
    duplicate names and nothing in the file defines: a cleanup destructor that is declared only and
    that no member calls (`__dt__10igNodeViewFv` in a GetVTable whose base subobject is torn down on
    unwind). The address is the retail table word less the compiled addend, as verify resolves the
    table word, and it must start a retail function in `starts`; verify then compares the table bytes."""
    out = dict(externals)
    for base, section in table_fields(placed, exception_tables(syms, headers, obj, functions), records):
        raw = verify.object_section(obj, headers[section][0], section)
        for _section, offset, kind, name, _addend in verify.object_relocs(obj, target_section=section):
            if (name in functions or name in names or name in data
                    or isinstance(syms.get(name, (None,))[0], int)):
                continue
            if kind != R_32:
                sys.exit("%s: exception table relocation type %d against %s" % (obj, kind, name))
            address = (retail.word(base + offset) - struct.unpack_from("<I", raw, offset)[0]) & 0xffffffff
            if address not in starts:
                sys.exit("%s: exception table names %s at 0x%x, which starts no retail function"
                         % (obj, name, address))
            if out.get(name, address) != address:
                sys.exit("%s: %s reads as 0x%x and 0x%x" % (obj, name, out[name], address))
            out[name] = address
    return out


def unrecovered(missing, defined):
    """The names of the retail functions a partial file has no source for, or None when the file
    defines one of them: a definition that reproduces no retail copy is a wrong compile, not a
    function still to be written."""
    names = [m[0] if isinstance(m, tuple) else m for m in missing]
    if any(name in defined for name in names):
        return None
    return names


def object_functions(obj):
    """{name: (bytes, relocated word offsets)} of each sized function of an object's executable sections:
    a compile's own (one section per function) or a reference library object's (one `.text` for all)."""
    syms, _ = verify.object_syms(obj)
    headers = verify.elf_section_headers(obj)
    out = {}
    for name, (section, value, size) in syms.items():
        if not (isinstance(section, int) and 0 < section < len(headers) and headers[section][1][2] & 4 and size):
            continue
        raw = verify.object_section(obj, headers[section][0], section)[value:value + size]
        relocated = {(offset - value) & ~3 for _s, offset, _k, _n, _a in verify.object_relocs(obj, target_section=section)
                     if value <= offset < value + size}
        out[name] = (raw, relocated)
    return out


def retail_copies(raw, relocated, retail, lo, hi):
    """The word-aligned addresses in [lo, hi) whose words are `raw`'s, the words at the `relocated`
    offsets masked: where retail keeps a copy of a function."""
    pattern = b"".join(b"...." if at in relocated else re.escape(raw[at:at + 4]) for at in range(0, len(raw), 4))
    code = verify.va_bytes(retail.image, lo, hi - lo)
    return [lo + m.start() for m in re.finditer(b"(?=" + pattern + b")", code, re.DOTALL) if m.start() % 4 == 0]


def data_only_row(source, obj, syms, headers, functions, retail, addresses, dropped, code, records, known, hi,
                  src_root=os.path.join(ROOT, "src")):
    """(key, row, units.tsv span) of a file the retail linker kept data of and no function, or None when
    no datum it defines has a known retail address (the linker dropped the whole file).

    `addresses` gives the retail address of the names other files' rows read from retail, and each
    data section holding one is placed there; a section none of them reaches went with the code.
    `dropped`, [(name, object_functions entry)], holds the file's functions, the compiled ones and those
    of its library object (`--reference`): none may have a copy anywhere in the retail `code` range,
    relocated words masked, and the kept data may name none. The rows are keyed by the first kept
    datum, which must start its section, and the units.tsv span is that section."""
    placed = {}
    for name, (section, value, _size) in sorted(syms.items()):
        if (name in addresses and isinstance(section, int) and 0 < section < len(headers)
                and headers[section][1][2] & 2 and not headers[section][1][2] & 4):
            if placed.setdefault(section, addresses[name] - value) != addresses[name] - value:
                sys.exit("%s: %s reads as 0x%x, against its section's other data" % (source, name, addresses[name]))
    if not placed:
        return None
    if not dropped:
        sys.exit("%s: a data-only file names the functions the retail linker dropped: give its library object "
                 "with --reference" % source)
    for name, (raw, relocated) in dropped:
        found = retail_copies(raw, relocated, retail, *code)
        if found:
            sys.exit("%s: %s has a retail copy at 0x%x: a file the linker kept a function of is not data-only"
                     % (source, name, found[0]))
    data, duplicates, _externals = reach({}, retail, syms, headers, obj, functions, records, known, hi,
                                         sections=sorted((address, section) for section, address in placed.items()))
    if duplicates:
        sys.exit("%s: its kept data names %s: the retail linker keeps a function kept data names"
                 % (source, ", ".join(sorted(duplicates))))
    for section, address in placed.items():
        start = sorted(n for n, (s, v, _z) in syms.items()
                       if s == section and v == 0 and not n.startswith(".") and not unitobjects.is_anonymous(n))
        if not start:
            sys.exit("%s: no name starts the data section at 0x%x to key its row" % (source, address))
        # an ee-gcc section symbol (`@data`) names a whole section; an MWCC datum is its own section
        data[next((n for n in start if n.startswith("@")), start[0])] = address
    named, anon = data_rows(data)
    key = min(placed.values())
    first = next(section for section, address in placed.items() if address == key)
    row = {"whole_file": True, "data": named}
    if anon:
        row["anon"] = anon
    row["stripped"] = sorted({name for name, _function in dropped})
    row["source"] = os.path.relpath(os.path.abspath(source), src_root)
    if row["source"].startswith(".."):
        sys.exit("%s: a data-only unit's source is a file under %s" % (source, src_root))
    return "0x%08x" % key, row, (key, key + headers[first][1][5])


def units_rows(path, lo, hi, rows):
    """units.tsv with `rows` in place of everything inside [lo, hi); a row across `lo` is cut. Rows past
    every unit (a data-only unit's span lies in the data) go at the end."""
    out, placed = [], False
    for line in open(path):
        fields = line.split("\t")
        if fields[0].startswith("0x") and len(fields) > 3:
            start, end = int(fields[0], 16), int(fields[1], 16)
            if not placed and start >= lo:
                out += rows
                placed = True
            if lo <= start < hi and end <= hi:
                continue
            if start < lo < end:
                tail = list(fields)
                fields[1] = "0x%08x" % lo
                line = "\t".join(fields)
                if end > hi:
                    tail[0] = "0x%08x" % hi
                    out += [line] + rows
                    placed = True
                    line = "\t".join(tail)
            elif lo <= start < hi:
                fields[0] = "0x%08x" % hi
                line = "\t".join(fields)
        out.append(line)
    if not placed:
        out += rows
    open(path, "w").writelines(out)


def merge_rows(overlay, lo, hi, rows):
    """unit-objects.json `overlay` with `rows` in place of the rows they supersede inside [lo, hi):
    each whole-file row, and each row that places a function the new rows place (a function's own
    row before it joined its file). A row of a function the file does not define, such as a held-out
    function a partial file leaves to its own source, stays."""
    placed = {int(key, 16) for key in rows} | {int(va, 16) for row in rows.values()
                                               for va in row.get("emitted", {}).values()}
    for key in [k for k in overlay if lo <= int(k, 16) < hi]:
        row = overlay[key]
        if row.get("whole_file") or placed & ({int(key, 16)} | {int(va, 16) for va in row.get("emitted", {}).values()}):
            del overlay[key]
    overlay.update(rows)
    return overlay


def overlay_addresses(path):
    """{name: retail address} of the data the rows of unit-objects.json name, where every row naming it
    agrees; a section symbol (`@data`) is each object's own and is left out."""
    seen = collections.defaultdict(set)
    with open(path) as fh:
        rows = json.load(fh)
    for row in rows.values():
        for name, address in row.get("data", {}).items():
            if not name.startswith("@"):
                seen[name].add(int(address, 0))
    return {name: addresses.pop() for name, addresses in seen.items() if len(addresses) == 1}


def previous_rows(path, lo, hi):
    """{key: row} of the whole-file rows of unit-objects.json inside [lo, hi): what the range's last run wrote."""
    if not os.path.exists(path):
        return {}
    with open(path) as fh:
        return {key: row for key, row in json.load(fh).items() if row.get("whole_file") and lo <= int(key, 16) < hi}


def previous_places(previous):
    """{name: va} of the functions the previous rows place: each row's `symbol` at its key and its `emitted`
    names (a static initializer's too, outside the range)."""
    out = {}
    for key, row in previous.items():
        if row.get("symbol"):
            out.setdefault(row["symbol"], int(key, 16))
        for name, va in (row.get("emitted") or {}).items():
            if isinstance(va, str):
                out.setdefault(name, int(va, 16))
    return out


def settled_partial(missing, previous):
    """Whether the retail functions at `missing` (addresses no compiled function reproduces) were left to link
    from retail by the previous rows: there are previous rows and none of them placed any of those addresses
    (the range's last run was `--partial` for exactly these). A function a previous row placed and the compile
    no longer reproduces is a wrong compile, never settled this way."""
    if not missing or not previous:
        return False
    covered = {int(key, 16) for key in previous} | set(previous_places(previous).values())
    return not any(va in covered for va in missing)


def stable_row(row, old, owner, syms, resolves):
    """`row` as the range's previous row `old` spelled what still holds, so that a regenerated row differs from
    it only where the compile changed:

      data, externals  an entry `old` had keeps its name and address while the object still has that name
                       (defines or references it); an entry `old` had not, for a name the object does not
                       define and `resolves(name)` binds at the same address without a row (data-names.tsv,
                       symbols.txt, the compiler-name map), stays out as before; an entry whose name is gone
                       from the object goes
      symbol           the `symbol` `old` wrote for the owner (`owner`, its compiled name) stays
    the fields in `old`'s order, and a field with `old`'s content in `old`'s order (a list it did not sort). Without
    `old`, `row` as it is."""
    if old is None:
        return row
    out = dict(row)
    for field in ("data", "externals"):
        new, before = dict(row.get(field) or {}), old.get(field) or {}
        for name, va in list(new.items()):
            defined = isinstance(syms.get(name, (None,))[0], int)
            if name not in before and not defined and resolves(name) == int(va, 16):
                del new[name]
        for name, va in before.items():
            if name not in new and name in syms:
                new[name] = va
        if new:
            out[field] = dict(sorted(new.items()))
        else:
            out.pop(field, None)
    if "symbol" not in out and old.get("symbol") == owner:
        out["symbol"] = owner
    for field, value in out.items():
        before = old.get(field)
        if isinstance(value, list) and isinstance(before, list) and sorted(value) == sorted(before):
            out[field] = before
        elif isinstance(value, dict) and value == before:
            out[field] = before
    order = list(old) + [f for f in out if f not in old]
    return {f: out[f] for f in order if f in out}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", help="the folder holding the stock files")
    ap.add_argument("--ext", default=".c")
    ap.add_argument("--files", nargs="+", help="file stems")
    ap.add_argument("--range", nargs=2, metavar=("LO", "HI"), type=lambda v: int(v, 0))
    ap.add_argument("--compiler", help="an @compiler id of units.tsv")
    ap.add_argument("--flags", help="the unit's complete flag string")
    ap.add_argument("--exceptions", default="off")
    ap.add_argument("--unit", help="unit name prefix, `<unit>_<file>`")
    ap.add_argument("--unit-va", type=lambda v: int(v, 0),
                    help="measure the whole-file units.tsv unit holding this address, from its row")
    ap.add_argument("--source", help="with --unit-va: the unit's file, when its name does not find it")
    ap.add_argument("--at", action="append", default=[], metavar="NAME=VA")
    ap.add_argument("--drop", action="append", default=[], metavar="NAME",
                    help="a function that fits a retail start another owns: a duplicate when reached, else stripped")
    ap.add_argument("--config", default=os.path.join(ROOT, "config", "SLUS-20836"))
    ap.add_argument("--elf", default=os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
    ap.add_argument("--wibo", default=os.path.join(ROOT, "local", "wibo"))
    ap.add_argument("--cxx", action="store_true", help="the object's names are mangled: keep symbols.txt plain")
    ap.add_argument("--partial", action="store_true",
                    help="the file is still being recovered: retail functions it lacks link from retail")
    ap.add_argument("--reference", action="append", default=[], metavar="STEM=OBJECT",
                    help="a file's library object (an SDK archive member): its functions are the ones a data-only "
                         "file lost, each searched for in retail")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--names", help="write the name rows for tools/apply_names.py here")
    a = ap.parse_args(argv)

    units_path = os.path.join(a.config, "units.tsv")
    if a.unit_va is not None:
        if any(v is not None for v in (a.src, a.files, a.range, a.compiler, a.flags, a.unit)):
            ap.error("--unit-va takes the source, range and profile from units.tsv")
        lo, hi, unit_name, a.compiler, a.flags, a.exceptions = unit_row(units_path, a.unit_va)
        source = os.path.abspath(a.source) if a.source else unit_source(unit_name)
        a.src, (stem, a.ext) = os.path.dirname(source), os.path.splitext(os.path.basename(source))
        a.files, a.range = [stem], (lo, hi)
    elif a.source or any(v is None for v in (a.src, a.files, a.range, a.compiler, a.flags, a.unit)):
        ap.error("give --unit-va, or all of --src, --files, --range, --compiler, --flags and --unit")
    lo, hi = a.range
    compilers = {p[1]: p[2] for p in (l.rstrip("\n").split("\t") for l in open(units_path))
                 if p[0] == "@compiler"}
    compiler = os.path.join(ROOT, compilers[a.compiler])
    profile = unitprofiles.Profile(compiler, a.flags, a.exceptions)
    by_name, by_va = verify.load_symbols(os.path.join(a.config, "symbols.txt"))
    mapped = {}
    if a.cxx:
        # the map as the other rows bind it: a name only the rows this run replaces bind (a call into the file's
        # own range through a view's member name) stays an external of the new row
        others = [g for g in unitobjects.load(os.path.join(a.config, "unit-objects.json"))
                  if not (g.whole_file and lo <= g.owner < hi)]
        mapped = {name: (va, retail) for name, va, retail in compiler_names.build(
            others, by_va, verify.data_symbols(os.path.join(a.config, "symbols.txt")))}
    retail = Retail(a.elf)
    records = exceptions.load(exceptions.config_path(os.path.join(a.config, "symbols.txt")))
    starts = sorted(va for va in by_va if lo <= va < hi)
    forced = {n: int(v, 0) for n, v in (item.split("=") for item in a.at)}
    placed = {n: by_name[n][0] for n in by_name if lo <= by_name[n][0] < hi}
    # the range's present rows: what they settled is settled again (an ambiguous start, the static initializer's
    # table entry, the retail functions a partial file links from retail, the data names they spelled)
    previous = previous_rows(os.path.join(a.config, "unit-objects.json"), lo, hi)
    settled = previous_places(previous)
    if a.cxx:
        # a compiler name they bind (tools/memberize.py renames a converted member's key) keeps its address,
        # since members of one shape (empty virtual functions) fit several starts, and a function they strip is
        # dropped, since byte-identical inline copies (one shape of destructor) fit the start one of them owns
        for name, va in settled.items():
            if lo <= va < hi:
                placed.setdefault(name, va)
        for row in previous.values():
            a.drop.extend(name for name in row.get("stripped") or () if name not in forced)
    placed.update(forced)
    data_names = verify.data_symbols(os.path.join(a.config, "symbols.txt"))

    def resolves(name):
        """The address a name binds at with no row of this unit's: a symbols.txt function, a data-names.tsv
        datum, a compiler name another unit's row binds."""
        for table in (by_name, mapped):
            if name in table:
                return table[name][0]
        return data_names.get(name)

    references = dict(item.split("=", 1) for item in a.reference)
    # the retail address of each datum other files name, for a file the linker kept the data of only
    addresses = overlay_addresses(os.path.join(a.config, "unit-objects.json"))
    rows, spans, data_spans, names, owned = {}, [], [], {}, {}
    with tempfile.TemporaryDirectory(prefix="dw4-whole-file-rows-") as tmp:
        compiled = []
        for stem in a.files:
            obj = os.path.join(tmp, stem + ".o")
            source = os.path.join(a.src, stem + a.ext)
            compile_file(a.wibo, compiler, unitprofiles.command_flags(profile), source, obj)
            syms, headers, functions = text_functions(obj)
            at = locate(functions, retail, [v for v in starts if v not in owned], placed, a.drop)
            owned.update({va: name for name, va in at.items()})
            # the static initializer is a member at its retail address, after all `.text`
            initializer = static_initializer(obj, syms, headers, retail, forced, settled)
            if initializer and not at:
                sys.exit("%s: only its static initializer has a retail copy" % source)
            if initializer:
                functions[initializer[0]] = initializer[1]
                at[initializer[0]] = initializer[2]
            compiled.append((stem, obj, syms, headers, functions, at,
                             Twins(profile, source, tmp, a.config, a.wibo), initializer and initializer[0]))
        missing = [by_va[v] for v in starts if v not in owned]
        if not a.partial and settled_partial([v for v in starts if v not in owned], previous):
            a.partial = True        # the previous rows left exactly these to link from retail
        lacking = unrecovered(missing, {n for c in compiled for n in c[4]}) if a.partial else None
        if lacking:
            print("partial: %d retail functions without source link from retail: %s"
                  % (len(lacking), ", ".join(lacking)), file=sys.stderr)
            missing = []
        if missing:
            sys.exit("no compiled function reproduces %s: fix the compile, the range or the extents"
                     % ", ".join(str(m) for m in missing))
        known = dict(((n, v) for n, (v, _s) in by_name.items()))
        if not a.cxx:
            known.update({name: va for va, name in owned.items()})
        data_only = []
        for stem, obj, syms, headers, functions, at, twins, initializer in compiled:
            if not at:
                data_only.append((stem, obj, syms, headers, functions))
                continue
            data, duplicates, externals = reach(at, retail, syms, headers, obj, functions, records, known, hi,
                                                twins)
            twinned = {name for name, va in duplicates.items() if twins(name, va)}
            literals(at, duplicates, retail, syms, headers, obj, functions, data, twinned)
            externals = table_externals({**at, **{n: v for n, v in duplicates.items() if n not in twinned}},
                                        retail, syms, headers, obj, functions, records, known, data,
                                        externals, by_va)
            members = sorted((va, name) for name, va in at.items())
            externals, kept = unmapped(externals, data, syms, mapped, obj)
            named, anon = data_rows(kept)
            row = {"whole_file": True,
                   "emitted": {name: "0x%08x" % va for va, name in members[1:]},
                   "data": named}
            if anon:
                row["anon"] = anon
            if duplicates:
                row["duplicates"] = {k: "0x%08x" % v for k, v in sorted(duplicates.items())}
            stripped = sorted(n for n in functions if n not in at and n not in duplicates)
            if stripped:
                row["stripped"] = stripped
            if externals:
                row["externals"] = {k: "0x%08x" % v for k, v in sorted(externals.items())}
            if by_va.get(members[0][0], (members[0][1],))[0] != members[0][1]:
                # a mangled owner, or a `static` several files define that symbols.txt names apart
                row["symbol"] = members[0][1]
            key = "0x%08x" % members[0][0]
            row = stable_row(row, previous.get(key), members[0][1], syms, resolves)
            rows[key] = row
            # the file's code ends with its last `.text` member; its `.init` sits after all `.text`
            last = max((va, name) for va, name in members if name != initializer)
            spans.append((members[0][0], last[0] + len(functions[last[1]].raw), stem))
            names.update({name: va for va, name in members if name != initializer})
            print("%-10s members %3d duplicates %3d stripped %3d data %3d externals %3d"
                  % (stem, len(members), len(duplicates), len(stripped), len(data), len(externals)),
                  file=sys.stderr)
            addresses.update({name: va for name, va in data.items()
                              if not name.startswith("@") and not unitobjects.is_anonymous(name)})
        code = (min(by_va), max(va + size for va, (_name, size) in by_va.items()))
        for stem, obj, syms, headers, functions in data_only:
            source = os.path.join(a.src, stem + a.ext)
            dropped = list(object_functions(obj).items())
            if stem in references:
                dropped += list(object_functions(references[stem]).items())
            found = data_only_row(source, obj, syms, headers, functions, retail, {**addresses, **forced}, dropped,
                                  code, records, known, hi)
            if found is None:
                print("%-10s no retail function: the linker dropped the file" % stem, file=sys.stderr)
                continue
            key, row, (start, end) = found
            rows[key] = row
            data_spans.append((start, end, stem))
            print("%-10s data-only: data %3d stripped %3d" % (stem, len(row["data"]) + len(row.get("anon", [])),
                                                              len(row["stripped"])), file=sys.stderr)

    if a.partial and len(spans) == 1:
        # one file still being recovered owns its whole range, the edges it has no source for too
        spans = [(lo, hi, spans[0][2])]
    print(json.dumps(rows, indent=1))
    if a.names:
        with open(a.names, "w") as fh:
            for name, va in sorted(names.items(), key=lambda kv: kv[1]):
                fh.write("0x%08x\t%s\n" % (va, name.split("__F")[0] if a.cxx else name))
    if a.write:
        path = os.path.join(a.config, "unit-objects.json")
        overlay = merge_rows(json.load(open(path)), lo, hi, rows)
        with open(path, "w") as fh:
            # in address order, a data-only row after the code
            json.dump(dict(sorted(overlay.items(), key=lambda row: int(row[0], 16))), fh, indent=2)
            fh.write("\n")
        if a.unit_va is None:
            line = "0x%08x\t0x%08x\t%s_%s\t%s\t%s\t%s\t-\twhole file\n"
            units_rows(units_path, lo, hi, [line % (start, end, a.unit, stem, a.compiler, a.flags, a.exceptions)
                                            for start, end, stem in sorted(spans)])
            for start, end, stem in data_spans:
                units_rows(units_path, start, end,
                           [line % (start, end, a.unit, stem, a.compiler, a.flags, a.exceptions)])
        # the rows bind compiler names: the map other units resolve them through follows them
        unitobjects.load.cache_clear()
        names_path, count = compiler_names.write(os.path.join(a.config, "symbols.txt"), path)
        print("compiler names: %d -> %s" % (count, names_path), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
