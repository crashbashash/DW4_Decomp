"""Emitted-object metadata: switch tables, exception data and profile-twin duplicates.

The fixture is one owner function (a switch with a guarded scope, so the compiler
emits a jump table, an exception index record, an exception table and an
out-of-line destructor). Retail bytes come from linking the original compiler
object with GNU ld, never from the verifier or the extraction code.
"""
import contextlib
import io
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import exceptions as exception_records
import linkgen
import unitcompilers
import unitflags
import unitobjects
import units
import verify


class EmittedMetadata(unittest.TestCase):
    OWNER, DUP, INDEX, TABLE, EXC = 0x180000, 0x180200, 0x180400, 0x180440, 0x180500
    EXTERNALS = {"Drop": 0x180300, "Tick": 0x180310, "fixture_delete": 0x180320}
    END = 0x180600
    SOURCE = '''
extern "C" void Drop(int *);
extern "C" void Tick(int);
class Guard {
public:
    int *value;
    Guard(int *p):value(p) {}
    ~Guard() { if(value) Drop(value); }
};
extern "C" int fixture_owner(int *p, int c) {
    Guard guard(p);
    switch(c) {
    case 0: Tick(1); return 3;
    case 1: Tick(2); return 5;
    case 2: Tick(7); return 9;
    case 3: Tick(c); return 11;
    case 4: Tick(4); return 13;
    case 5: Tick(8); return 17;
    }
    return 0;
}
'''
    ALT = "-O1"

    def compile(self, name, flags):
        out = self.root / name
        subprocess.run([verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, "-c", *flags.split(),
                        str(self.source), "-o", str(out)], check=True, capture_output=True,
                       env=dict(os.environ, MWCIncludes=str(self.root)))
        return out

    def link(self, obj, placements, tag):
        """GNU-link selected sections of `obj`; -> {section index: bytes}."""
        headers = verify.elf_section_headers(str(obj))
        names = {i: f".s{i}" for i, (n, h) in enumerate(headers)
                 if n in (".text", ".rodata", ".exceptix", ".exception") and h[5]}
        verify.rename_object_sections(str(obj), names)
        script = self.root / f"{tag}.ld"
        lines = [f"{n} = 0x{a:x};" for n, a in
                 dict(self.EXTERNALS, __dl__FPv=self.EXTERNALS["fixture_delete"],
                      **{self.dtor: self.DUP}).items()]
        lines.append("SECTIONS {")
        lines += [f".out{i} 0x{a:x} : {{ *({names[i]}) }}" for i, a in placements.items()]
        lines.append("/DISCARD/ : { *(.s*) *(.mwcats) *(.comment) *(.reginfo) } }")
        script.write_text("\n".join(lines))
        elf = self.root / f"{tag}.elf"
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-T", str(script),
                        str(obj), "-o", str(elf)], check=True, capture_output=True)
        return {i: verify.object_section(str(elf), f".out{i}") for i in placements}

    def make_image(self, dup_flags):
        main = self.compile("main.o", self.flags)
        alt = self.compile("alt.o", dup_flags)
        syms, _ = verify.object_syms(str(main))
        headers = verify.elf_section_headers(str(main))
        self.dtor = next(name for name in syms if name.startswith("__dt__"))
        owner = syms["fixture_owner"][0]
        index = [i for i, (n, h) in enumerate(headers) if n == ".exceptix" and h[5]][0]
        table = next(i for i, (n, h) in enumerate(headers) if n == ".exception" and h[5])
        rodata = next(i for i, (n, h) in enumerate(headers) if n == ".rodata" and h[5])
        self.owner_size, self.dtor_size = syms["fixture_owner"][2], syms[self.dtor][2]
        self.table_length, self.jump_bytes = headers[table][1][5], headers[rodata][1][5]
        asyms, _ = verify.object_syms(str(alt))
        alt_text = asyms[self.dtor][0]
        parts = self.link(main, {owner: self.OWNER, rodata: self.TABLE,
                                 index: self.INDEX, table: self.EXC}, "main")
        dup = self.link(alt, {alt_text: self.DUP}, "alt")[alt_text]
        image = bytearray(self.END - verify.VADDR_BASE + verify.FILE_BASE)
        def put(address, data):
            start = address - verify.VADDR_BASE + verify.FILE_BASE
            image[start:start + len(data)] = data
        put(self.OWNER, parts[owner]); put(self.TABLE, parts[rodata])
        put(self.INDEX, parts[index]); put(self.EXC, parts[table]); put(self.DUP, dup)
        for address in self.EXTERNALS.values():
            put(address, struct.pack("<2I", 0x03e00008, 0))
        self.expected = {a: bytes(image[a - verify.VADDR_BASE + verify.FILE_BASE:][:n])
                         for a, n in ((self.OWNER, self.owner_size), (self.TABLE, self.jump_bytes),
                                      (self.DUP, len(dup)))}
        self.dup_size = len(dup)
        image[:6] = b"\x7fELF\x01\x01"
        reginfo = len(image)
        image.extend(struct.pack("<6I", 0, 0, 0, 0, 0, 0x210000))
        strings = b"\0.shstrtab\0.reginfo\0"
        strings_at = len(image)
        image.extend(strings)
        image.extend(b"\0" * (-len(image) % 4))
        shoff = len(image)
        image.extend(bytes(40))
        image.extend(struct.pack("<10I", 1, 3, 0, 0, strings_at, len(strings), 0, 0, 1, 0))
        image.extend(struct.pack("<10I", 11, 0x70000006, 0, 0, reginfo, 24, 0, 0, 4, 0))
        struct.pack_into("<I", image, 0x20, shoff)
        struct.pack_into("<HHH", image, 0x2e, 40, 3, 1)
        path = self.root / "fixture.elf"
        path.write_bytes(image)
        return path

    def setUp(self):
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, verify.MWCC_DEFAULT)):
            self.skipTest("private compiler unavailable")
        if not shutil.which("mipsel-linux-gnu-ld"):
            self.skipTest("GNU MIPS tools unavailable")
        self.temp = tempfile.TemporaryDirectory(prefix="dw4-metadata-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.source = self.root / "fixture.cpp"
        self.source.write_text(self.SOURCE)
        include = "-I" + str(Path(verify.ROOT) / "include")
        self.flags = "-O3,p " + include
        self.alt_flags = self.ALT + " " + include
        self.symbols = self.root / "symbols.txt"
        self.flag_file = self.root / "flags.tsv"
        self.rebuild(self.alt_flags)
        self.registry = self.root / "objects.json"
        self.good = {hex(self.OWNER): {
            "emitted": {}, "duplicates": {self.dtor: hex(self.DUP)},
            "externals": {"__dl__FPv": hex(self.EXTERNALS["fixture_delete"])},
            "exceptions": {"index": hex(self.INDEX), "table": hex(self.EXC),
                           "table_size": hex(self.table_length)}}}
        self.write_registry(self.good)
        self.tables = {self.OWNER: [(self.TABLE, self.jump_bytes // 4)]}

    def rebuild(self, dup_flags):
        """Retail image whose duplicate copy was built with `dup_flags`."""
        self.image = self.make_image(dup_flags)
        rows = [(self.OWNER, self.owner_size, "fixture_owner"),
                (self.DUP, self.dup_size, "fixture_dtor_copy")]
        rows += [(a, 8, n) for n, a in self.EXTERNALS.items()]
        self.symbols.write_text("".join(f"{va:08x} {size:06x} {name}\n"
                                         for va, size, name in sorted(rows)))
        self.write_flags(dup_flags)

    def write_flags(self, dup_flags):
        self.flag_file.write_text(f"{hex(self.OWNER)}\t{self.flags}\n{hex(self.DUP)}\t{dup_flags}\n")
        unitflags._CACHE.clear()

    def write_registry(self, value):
        self.registry.write_text(json.dumps(value))
        unitobjects.load.cache_clear()

    def check(self, image=None, tables=None, verbose=False):
        return verify.verify_one(self.OWNER, str(self.source), elf=str(image or self.image),
            symbols=str(self.symbols), unit_flags=str(self.flag_file),
            unit_objects=str(self.registry), jumptables=self.tables if tables is None else tables,
            verbose=verbose)

    def corrupted(self, address, bit=1):
        image = bytearray(self.image.read_bytes())
        image[address - verify.VADDR_BASE + verify.FILE_BASE] ^= bit
        path = self.root / f"corrupt-{address:x}.elf"
        path.write_bytes(image)
        return path

    def test_tables_exception_data_and_profile_duplicate_match(self):
        ok, report = self.check()
        self.assertTrue(ok, report)
        for text in ("1 complete bodies".replace("1", "2"), "jump table 0x180440",
                     "exception index (fixture_owner) 0x180400", "exception table (fixture_owner) 0x180500",
                     "DEFERRED duplicate", "under '" + self.alt_flags):
            self.assertIn(text, report)
        main = self.compile("again.o", self.flags)
        syms, _ = verify.object_syms(str(main))
        # The fixture only exercises deferral if the two profiles really differ.
        self.assertNotEqual(verify.object_section(str(main), ".text", syms[self.dtor][0]),
                            self.expected_dup())

    def expected_dup(self):
        return self.expected[self.DUP]

    def test_same_profile_duplicate_is_compared_in_the_main_object(self):
        self.rebuild(self.flags)
        ok, report = self.check()
        self.assertTrue(ok, report)
        self.assertNotIn("DEFERRED", report)
        self.assertIn("MATCH duplicate", report)

    def test_each_corrupted_retail_region_is_rejected(self):
        for label, address in (("jump table", self.TABLE), ("exception index", self.INDEX),
                               ("exception table", self.EXC + 5), ("duplicate", self.DUP + 8),
                               ("emitted", self.OWNER + 8)):
            ok, report = self.check(image=self.corrupted(address))
            self.assertFalse(ok, label)
            self.assertIn("DIFFER", report)

    def test_padding_is_bounded(self):
        for size in (self.table_length + 4, self.table_length + 8):
            registry = json.loads(json.dumps(self.good))
            registry[hex(self.OWNER)]["exceptions"]["table_size"] = hex(size)
            self.write_registry(registry)
            ok, report = self.check()
            self.assertFalse(ok, report)
            self.assertIn("exception table size differs", report)
            self.assertIn("exc=differ cat=code-only", report)

    def test_metadata_without_a_retail_record_is_extra_not_rejected(self):
        # No `exceptions` row and no retail record for the owner: the bodies are still
        # compared (and match); the record the object emits is debt, not a rejection.
        registry = json.loads(json.dumps(self.good))
        del registry[hex(self.OWNER)]["exceptions"]
        self.write_registry(registry)
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertNotIn("rejected", report)
        self.assertIn("exc=extra cat=code-only", report)
        self.assertIn("MATCH emitted 0x180000 fixture_owner", report)
        self.assertIn("emits a record for 0x180000 fixture_owner, but retail keeps none", report)

    def test_retail_record_from_the_recovered_table_needs_no_row(self):
        # The same owner record given by an exceptions.txt beside the symbol map (what
        # tools/exceptions.py recovers from the real image) verifies without a row.
        registry = json.loads(json.dumps(self.good))
        del registry[hex(self.OWNER)]["exceptions"]
        self.write_registry(registry)
        table = self.root / "exceptions.txt"
        table.write_text(exception_records.format_table(
            [(self.OWNER, self.INDEX, self.EXC, self.table_length)]))
        exception_records.load.cache_clear()
        self.addCleanup(exception_records.load.cache_clear)
        try:
            ok, report = self.check()
        finally:
            table.unlink()
            exception_records.load.cache_clear()
        self.assertTrue(ok, report)
        self.assertIn("exc=ok cat=match", report)
        self.assertIn("exception index (fixture_owner) 0x180400", report)

    def test_row_disagreeing_with_the_recovered_table_is_rejected(self):
        table = self.root / "exceptions.txt"
        table.write_text(exception_records.format_table(
            [(self.OWNER, self.INDEX + 12, self.EXC, self.table_length)]))
        exception_records.load.cache_clear()
        self.addCleanup(exception_records.load.cache_clear)
        try:
            ok, report = self.check()
        finally:
            table.unlink()
            exception_records.load.cache_clear()
        self.assertFalse(ok)
        self.assertIn("declared exception metadata disagrees with config/SLUS-20836/exceptions.txt", report)

    def test_unowned_metadata_fails_closed(self):
        self.write_registry(self.good)
        ok, report = self.check(tables={})
        self.assertFalse(ok)
        self.assertIn("no jump table is recorded", report)
        ok, report = self.check(tables={self.OWNER: [(self.TABLE, 5)]})
        self.assertFalse(ok)
        self.assertIn("expected 20", report)
        bad_address = json.loads(json.dumps(self.good))
        bad_address[hex(self.OWNER)]["exceptions"]["index"] = hex(self.INDEX + 4)
        self.write_registry(bad_address)
        self.assertFalse(self.check()[0])

    def test_undeclared_exception_record_names_its_function(self):
        obj = self.compile("named.o", self.flags)
        headers = verify.elf_section_headers(str(obj))
        syms, _ = verify.object_syms(str(obj))
        records = {"fixture_owner": (self.OWNER, 0, 0), self.dtor: (self.DUP, 0, 0)}
        attributed = verify.group_exception_sections(str(obj), headers, syms, records)
        self.assertEqual(set(attributed), {"fixture_owner", self.dtor})
        self.assertIsNotNone(attributed["fixture_owner"][1])      # the owner has a table
        with self.assertRaisesRegex(ValueError, "unowned function " + self.dtor):
            verify.group_exception_sections(str(obj), headers, syms, {"fixture_owner": (self.OWNER, 0, 0)})

    def test_duplicate_must_exist_and_be_declared(self):
        registry = json.loads(json.dumps(self.good))
        registry[hex(self.OWNER)]["duplicates"] = {"MissingCopy": hex(self.DUP)}
        self.write_registry(registry)
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertIn("missing emitted function MissingCopy", report)
        registry[hex(self.OWNER)]["duplicates"] = {self.dtor: hex(self.OWNER)}
        self.write_registry(registry)
        with self.assertRaisesRegex(ValueError, "multiple compiler bodies"):
            unitobjects.load(str(self.registry))
        registry[hex(self.OWNER)]["emitted"] = {}
        registry[hex(self.OWNER)]["duplicates"] = {}
        self.write_registry(registry)
        # externals bound out of line + the exception record naming them: a valid row
        # (the retail unit's RAII helpers are not emitted copies)
        unitobjects.load.cache_clear()
        self.assertEqual(len(unitobjects.load(str(self.registry))), 1)
        without_record = json.loads(json.dumps(registry))
        del without_record[hex(self.OWNER)]["exceptions"]
        self.write_registry(without_record)
        unitobjects.load.cache_clear()
        with self.assertRaisesRegex(ValueError, "requires emitted or duplicate"):
            unitobjects.load(str(self.registry))
        registry[hex(self.OWNER)]["externals"] = {}
        self.write_registry(registry)
        unitobjects.load.cache_clear()
        with self.assertRaisesRegex(ValueError, "requires emitted or duplicate"):
            unitobjects.load(str(self.registry))

    def test_linkgen_places_owner_and_table_and_drops_discarded_metadata(self):
        entries = [(self.OWNER, self.owner_size, "code", "fixture_owner"),
                   (self.DUP, self.dup_size, "code", "fixture_dtor_copy"),
                   (self.TABLE, self.jump_bytes, "jtbl", f"jtbl_{self.TABLE:08x} fixture_owner")]
        entries += [(a, 8, "code", n) for n, a in self.EXTERNALS.items()]
        rows, cursor = [], verify.VADDR_BASE
        for va, size, kind, name in sorted(entries):
            if cursor < va:
                rows.append(f"{cursor:08x} {va-cursor:06x} data gap_{cursor:08x}\n")
            rows.append(f"{va:08x} {size:06x} {kind} {name}\n")
            cursor = va + size
        rows.append(f"{cursor:08x} {self.END-cursor:06x} data tail\n")
        layout = self.root / "layout.txt"
        layout.write_text("".join(rows))
        jumps = self.root / "jumptables.txt"
        jumps.write_text(f"{self.OWNER:08x} {self.TABLE:08x} {self.jump_bytes // 4:04x}\n")
        index = units.scan(str(self.root), symbols=str(self.symbols), unit_objects=str(self.registry))
        self.assertEqual(index["fixture_owner"], str(self.source))
        script, linked = self.root / "generated.ld", self.root / "generated.elf"
        self.out = io.StringIO()
        def run(image, output):
            with patch.object(linkgen.unitfiles, "scan", return_value=index), \
                 patch.object(unitflags, "flags_for", return_value=self.flags), \
                 patch.object(unitflags, "DEFAULT_PATH", str(self.flag_file)), \
                 patch.object(verify, "JUMPTABLES", str(jumps)), \
                 contextlib.redirect_stdout(self.out), contextlib.redirect_stderr(self.out):
                verify.load_jumptables.cache_clear()
                return linkgen.main(["--all", "--layout", str(layout), "--elf", str(image),
                    "--symbols", str(self.symbols), "--unit-objects", str(self.registry),
                    "--out", str(self.root / "objects"), "--ld", str(output), "--jobs", "2"])
        self.assertEqual(run(self.image, script), 0, self.out.getvalue())
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-G0", "-T", str(script),
                        "-o", str(linked)], check=True, capture_output=True)
        text = verify.object_section(str(linked), ".text")
        image = self.image.read_bytes()
        self.assertEqual(text, image[verify.FILE_BASE:verify.FILE_BASE + len(text)])
        placed = [name for name, h in verify.elf_section_headers(
            str(self.root / "objects" / f"u_{self.OWNER:08x}.o")) if h[2] & 2 and h[5]]
        # the owner's reproduced record and table are kept, renamed by retail address, and placed
        self.assertEqual(sorted(placed), [".exception.dw4_%08x" % self.EXC, ".exceptix.dw4_%08x" % self.INDEX,
                                          ".rodata", ".text"])
        self.assertIn("1 records placed from C (1 tables", self.out.getvalue())
        # a retail table that differs is debt (exc=differ), not a rejection: the code is
        # linked, retail's bytes stay for the metadata, and linkgen counts the unit
        differing = self.root / "differing.ld"
        self.out = io.StringIO()
        self.assertEqual(run(self.corrupted(self.EXC + 4), differing), 0, self.out.getvalue())
        self.assertIn("1 whose shape differs", self.out.getvalue())
        placed = [name for name, h in verify.elf_section_headers(
            str(self.root / "objects" / f"u_{self.OWNER:08x}.o")) if h[2] & 2 and h[5]]
        self.assertEqual(sorted(placed), [".rodata", ".text"])


if __name__ == "__main__":
    unittest.main()
