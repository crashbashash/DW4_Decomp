#!/usr/bin/env python3
"""whole_file_rows.py — derive the whole-file rows of a stock library from retail.

A stock file keeps its upstream text, so the rows that tie it to retail are measured, never typed
(docs/engine/emitted-functions.md, "Whole-file units"). Each listed file is compiled with the
unit's profile, then:

  members    each `.text` function is found in the retail range by its bytes, relocated fields
             masked; a name symbols.txt already places wins, and a `--at name=va` settles a
             function that fits more than one retail start
  stripped   a compiled function with no retail copy: the retail linker dropped it
  data       each referenced datum's address, read back from the retail relocation fields
  externals  each call out of the file, read from the retail `jal`

A retail function in the range that no compiled function reproduces stops the run with its name:
the compile is wrong, and writing rows would hide it behind `stripped`.

A C++ file (`--cxx`) keeps its mangled names in the rows and writes the plain ones to `--names`,
and cross-file references stay externals. `--drop` strips a function that fits a start another
function owns: stock `lua_dofile` and `lua_dobuffer` fit one retail start, and only a call target
tells them apart.

The rows go to stdout as JSON. `--write` merges them into unit-objects.json and replaces the
units.tsv rows inside the range with one per file. `--names` writes a `.tsv` for
tools/apply_names.py, which is what moves `FUN_` names to the library's own.

Usage:
  whole_file_rows.py --src src/third_party/zlib --files adler32 crc32 --range 0x221870 0x2252d8 \\
      --compiler combat --flags "-O4,p -sdatathreshold 2 -lang c -I- -Isrc/third_party/libc" \\
      --unit zlib [--write] [--names config/SLUS-20836/names/zlib.tsv]
"""
import argparse
import collections
import json
import os
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cc
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


def text_functions(obj):
    syms, _ = verify.object_syms(obj)
    headers = verify.elf_section_headers(obj)
    out = {}
    for name, (section, value, size) in syms.items():
        if isinstance(section, int) and section < len(headers) and headers[section][0] == ".text" \
                and value == 0 and size:
            out[name] = Function(name, section, obj, headers)
    return syms, headers, out


def locate(functions, retail, starts, placed, dropped=()):
    """{name: va} for the functions with a retail copy. A function that fits several starts is
    settled by the others: a file keeps its functions in order, and each start is used once."""
    found, open_ = {}, {}
    for name, function in functions.items():
        if name in dropped:
            continue
        if name in placed:
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


def data_rows(function_at, retail, syms, headers, obj, functions, names, hi):
    """(data, externals) of one file, walking from its kept functions through the data they reach."""
    data, externals, seen = {}, {}, set()
    work = [(va, functions[name].section) for name, va in function_at.items()]
    while work:
        base, section = work.pop()
        if section in seen:
            continue
        seen.add(section)
        raw = verify.object_section(obj, headers[section][0], section)
        relocs = verify.object_relocs(obj, target_section=section)
        for index, (_section, offset, kind, name, _addend) in enumerate(relocs):
            if name in functions or (name in names and (kind == R_26 or names[name] < hi)):
                continue
            field = retail.word(base + offset)
            own = struct.unpack_from("<I", raw, offset)[0]
            if kind == R_26:
                externals[name] = (base & 0xf0000000) | ((field & 0x3ffffff) << 2)
                continue
            if kind == R_HI16:
                low = next(r for r in relocs[index + 1:] if r[2] == R_LO16 and r[3] == name)
                retail_low = retail.word(base + low[1])
                own_low = struct.unpack_from("<I", raw, low[1])[0]
                address = (((field & 0xffff) << 16) + sext(retail_low & 0xffff)
                           - ((own & 0xffff) << 16) - sext(own_low & 0xffff))
            elif kind == R_LO16:
                continue
            elif kind == R_GPREL16:
                address = retail.gp + sext(field & 0xffff) - sext(own & 0xffff)
            elif kind == R_32:
                address = field - own
            else:
                sys.exit("%s: relocation type %d against %s" % (obj, kind, name))
            address &= 0xffffffff
            if name in names:
                continue
            if data.get(name, address) != address:
                sys.exit("%s: %s reads as 0x%x and 0x%x" % (obj, name, data[name], address))
            data[name] = address
            home = syms.get(name, (None,))[0]
            if isinstance(home, int):
                work.append((address - syms[name][1], home))
    return data, externals


def units_rows(path, lo, hi, rows):
    """units.tsv with `rows` in place of everything inside [lo, hi); a row across `lo` is cut."""
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
    open(path, "w").writelines(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", required=True, help="the folder holding the stock files")
    ap.add_argument("--ext", default=".c")
    ap.add_argument("--files", nargs="+", required=True, help="file stems")
    ap.add_argument("--range", nargs=2, required=True, metavar=("LO", "HI"), type=lambda v: int(v, 0))
    ap.add_argument("--compiler", required=True, help="an @compiler id of units.tsv")
    ap.add_argument("--flags", required=True, help="the unit's complete flag string")
    ap.add_argument("--exceptions", default="off")
    ap.add_argument("--unit", required=True, help="unit name prefix, `<unit>_<file>`")
    ap.add_argument("--at", action="append", default=[], metavar="NAME=VA")
    ap.add_argument("--drop", action="append", default=[], metavar="NAME",
                    help="a function that fits a retail start another owns: it is stripped")
    ap.add_argument("--config", default=os.path.join(ROOT, "config", "SLUS-20836"))
    ap.add_argument("--elf", default=os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
    ap.add_argument("--wibo", default=os.path.join(ROOT, "local", "wibo"))
    ap.add_argument("--cxx", action="store_true", help="the object's names are mangled: keep symbols.txt plain")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--names", help="write the name rows for tools/apply_names.py here")
    a = ap.parse_args(argv)

    lo, hi = a.range
    units_path = os.path.join(a.config, "units.tsv")
    compilers = {p[1]: p[2] for p in (l.rstrip("\n").split("\t") for l in open(units_path))
                 if p[0] == "@compiler"}
    compiler = os.path.join(ROOT, compilers[a.compiler])
    by_name, by_va = verify.load_symbols(os.path.join(a.config, "symbols.txt"))
    retail = Retail(a.elf)
    starts = sorted(va for va in by_va if lo <= va < hi)
    forced = {n: int(v, 0) for n, v in (item.split("=") for item in a.at)}
    placed = {n: by_name[n][0] for n in by_name if lo <= by_name[n][0] < hi}
    placed.update(forced)

    rows, spans, names, owned = {}, [], {}, {}
    with tempfile.TemporaryDirectory(prefix="dw4-whole-file-rows-") as tmp:
        compiled = []
        for stem in a.files:
            obj = os.path.join(tmp, stem + ".o")
            mwcc_off = a.exceptions == "off" and not cc.is_eegcc(compiler)
            compile_file(a.wibo, compiler, a.flags + (" -Cpp_exceptions off" if mwcc_off else ""),
                         os.path.join(a.src, stem + a.ext), obj)
            syms, headers, functions = text_functions(obj)
            at = locate(functions, retail, [v for v in starts if v not in owned], placed, a.drop)
            owned.update({va: name for name, va in at.items()})
            compiled.append((stem, obj, syms, headers, functions, at))
        missing = [by_va[v] for v in starts if v not in owned]
        if missing:
            sys.exit("no compiled function reproduces %s: fix the compile, the range or the extents"
                     % ", ".join(str(m) for m in missing))
        known = dict(((n, v) for n, (v, _s) in by_name.items()))
        if not a.cxx:
            known.update({name: va for va, name in owned.items()})
        for stem, obj, syms, headers, functions, at in compiled:
            if not at:
                print("%-10s no retail function: the linker dropped the file" % stem, file=sys.stderr)
                continue
            data, externals = data_rows(at, retail, syms, headers, obj, functions, known, hi)
            members = sorted((va, name) for name, va in at.items())
            row = {"whole_file": True,
                   "emitted": {name: "0x%08x" % va for va, name in members[1:]},
                   "data": {k: "0x%08x" % v for k, v in sorted(data.items())}}
            stripped = sorted(n for n in functions if n not in at)
            if stripped:
                row["stripped"] = stripped
            if externals:
                row["externals"] = {k: "0x%08x" % v for k, v in sorted(externals.items())}
            if a.cxx:
                row["symbol"] = members[0][1]
            rows["0x%08x" % members[0][0]] = row
            last = members[-1]
            spans.append((members[0][0], last[0] + len(functions[last[1]].raw), stem))
            names.update({name: va for va, name in members})
            print("%-10s members %3d stripped %3d data %3d externals %3d"
                  % (stem, len(members), len(stripped), len(data), len(externals)), file=sys.stderr)

    print(json.dumps(rows, indent=1))
    if a.names:
        with open(a.names, "w") as fh:
            for name, va in sorted(names.items(), key=lambda kv: kv[1]):
                fh.write("0x%08x\t%s\n" % (va, name.split("__F")[0] if a.cxx else name))
    if a.write:
        path = os.path.join(a.config, "unit-objects.json")
        overlay = json.load(open(path))
        for key in [k for k in overlay if lo <= int(k, 16) < hi]:
            del overlay[key]
        overlay.update(rows)
        with open(path, "w") as fh:
            json.dump(overlay, fh, indent=2)
            fh.write("\n")
        units_rows(units_path, lo, hi,
                   ["0x%08x\t0x%08x\t%s_%s\t%s\t%s\t%s\t-\twhole file\n"
                    % (start, end, a.unit, stem, a.compiler, a.flags, a.exceptions)
                    for start, end, stem in sorted(spans)])
    return 0


if __name__ == "__main__":
    sys.exit(main())
