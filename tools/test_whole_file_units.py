"""Whole-file units: a stock source compiled whole, its data compared with retail."""
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

import cc
import eegcc_compile
import exceptions
import unitobjects
import unitprofiles
import units
import verify
import whole_file_rows

SOURCE = '''
char *fixture_keep(v)
    int v;
{
    return v ? "kept string" : 0;
}

char *fixture_drop(v)
    int v;
{
    return v ? "dropped string" : 0;
}

int fixture_second(a)
    int a;
{
    return a + 1;
}
'''


class Overlay(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.registry = self.root / "objects.json"
        self.symbols = self.root / "symbols.txt"
        self.symbols.write_text("00180000 000010 one\n00180100 000010 two\n")

    def load(self, row):
        self.registry.write_text(json.dumps({"0x00180000": row}))
        unitobjects.load.cache_clear()
        return unitobjects.load(self.registry)

    def test_a_lone_function_needs_no_other_row(self):
        group, = self.load({"whole_file": True})
        self.assertTrue(group.whole_file)

    def test_stripped_names_need_not_be_destructors(self):
        group, = self.load({"whole_file": True, "stripped": ["zError"]})
        self.assertEqual(group.stripped, ("zError",))
        with self.assertRaisesRegex(ValueError, "destructor"):
            self.load({"emitted": {"two": "0x00180100"}, "stripped": ["zError"]})

    def test_data_belongs_to_a_whole_file_unit(self):
        group, = self.load({"whole_file": True, "data": {"@45": "0x00190000"}})
        self.assertEqual(group.data, (("@45", 0x190000),))
        with self.assertRaises(ValueError):
            self.load({"emitted": {"two": "0x00180100"}, "data": {"@45": "0x00190000"}})

    def test_a_datum_can_start_on_any_byte(self):
        group, = self.load({"whole_file": True, "data": {"@45": "0x00190001"}})
        self.assertEqual(group.data, (("@45", 0x190001),))

    def test_ifdef_alternatives_are_one_definition(self):
        (self.root / "lib.c").write_text("#ifdef A\nint one(void) { return 1; }\n#else\n"
                                         "int one(void) { return 2; }\n#endif\n")
        scan = dict(symbols=str(self.symbols), unit_objects=str(self.registry))
        self.assertEqual(units.scan(str(self.root), **scan), {"one": str(self.root / "lib.c")})
        (self.root / "other.c").write_text("int one(void) { return 3; }\n")
        with self.assertRaisesRegex(ValueError, "already defined"):
            units.scan(str(self.root), **scan)

    def test_a_whole_file_is_never_split(self):
        source = self.root / "lib.c"
        source.write_text("int one(a)\nint a;\n{ return a; }\nint two(void) { return 2; }\n")
        self.load({"whole_file": True, "emitted": {"two": "0x00180100"}})
        path, temporary = units.standalone(str(source), "two", symbols=str(self.symbols),
                                           unit_objects=str(self.registry))
        self.assertEqual((path, temporary), (str(source), None))

    def test_members_may_share_the_owners_file_only(self):
        self.load({"whole_file": True, "emitted": {"two": "0x00180100"}})
        arguments = dict(symbols=str(self.symbols), path=str(self.registry))
        self.assertEqual(unitobjects.augment_sources({"one": "a.c", "two": "a.c"}, **arguments),
                         {"one": "a.c", "two": "a.c"})
        with self.assertRaisesRegex(ValueError, "explicit and emitted"):
            unitobjects.augment_sources({"one": "a.c", "two": "b.c"}, **arguments)


class Objects(unittest.TestCase):
    OWNER, MEMBER, DATA, DROPPED, DROPPED_DATA = 0x180000, 0x180100, 0x180200, 0x180300, 0x180400

    def setUp(self):
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, verify.MWCC_DEFAULT)):
            self.skipTest("private compiler unavailable")
        if not shutil.which("mipsel-linux-gnu-ld"):
            self.skipTest("GNU MIPS tools unavailable")
        self.temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.obj = self.compile(SOURCE, "fixture")
        syms, _ = verify.object_syms(str(self.obj))
        headers = verify.elf_section_headers(str(self.obj))
        kept = syms["fixture_keep"][0]
        self.datum = next(r[3] for r in verify.object_relocs(str(self.obj), target_section=kept)
                          if r[3].startswith("@"))
        dropped = next(r[3] for r in verify.object_relocs(str(self.obj), target_section=syms["fixture_drop"][0])
                       if r[3].startswith("@"))
        self.text = verify.object_section(str(self.obj), ".data", syms[self.datum][0])
        # Link the object with GNU ld, without the verifier, for the bytes retail would hold.
        placed = {"fixture_keep": self.OWNER, "fixture_second": self.MEMBER, self.datum: self.DATA,
                  "fixture_drop": self.DROPPED, dropped: self.DROPPED_DATA}
        linked = self.root / "linked.o"
        shutil.copyfile(self.obj, linked)
        names = {syms[name][0]: f".place{syms[name][0]}" for name in placed}
        verify.rename_object_sections(str(linked), names)
        script = self.root / "fixture.ld"
        rows = [f".out{syms[name][0]} 0x{address:x} : {{ *({names[syms[name][0]]}) }}"
                for name, address in placed.items()]
        script.write_text("SECTIONS {\n" + "\n".join(rows) + "\n/DISCARD/ : { *(.mwcats) *(.comment) *(.reginfo) } }\n")
        out = self.root / "fixture.out"
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-T", str(script), str(linked),
                        "-o", str(out)], check=True, capture_output=True)
        image = bytearray([0xa5]) * (0x180500 - verify.VADDR_BASE + verify.FILE_BASE)
        for name in ("fixture_keep", "fixture_second", self.datum):
            section = syms[name][0]
            body = verify.object_section(str(out), f".out{section}")
            start = placed[name] - verify.VADDR_BASE + verify.FILE_BASE
            image[start:start + len(body)] = body
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
        self.image = self.root / "fixture.elf"
        self.image.write_bytes(image)
        self.symbols = self.root / "symbols.txt"
        self.symbols.write_text(f"{self.OWNER:08x} {syms['fixture_keep'][2]:06x} fixture_keep\n"
                                f"{self.MEMBER:08x} {syms['fixture_second'][2]:06x} fixture_second\n")
        self.registry = self.root / "objects.json"
        self.headers = headers

    def compile(self, source, name):
        path, obj = self.root / f"{name}.c", self.root / f"{name}.o"
        path.write_text(source)
        subprocess.run([verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, "-c", "-O4,p", "-sdatathreshold", "1",
                        "-lang", "c", "-Cpp_exceptions", "off", str(path), "-o", str(obj)],
                       check=True, capture_output=True, env=dict(os.environ, MWCIncludes=str(self.root)))
        return obj

    def group(self, data=None):
        self.registry.write_text(json.dumps({hex(self.OWNER): {
            "whole_file": True, "emitted": {"fixture_second": hex(self.MEMBER)},
            "stripped": ["fixture_drop"],
            "data": {self.datum: hex(self.DATA)} if data is None else data}}))
        return unitobjects.group_for(self.OWNER, self.registry)

    def verify(self, obj, group):
        return verify.verify_emitted_object(str(obj), group, str(self.image), str(self.symbols), jumptables={})

    def test_declared_data_matches_and_dead_data_needs_no_row(self):
        ok, report, records = self.verify(self.obj, self.group())
        self.assertTrue(ok, report)
        self.assertIn(f"MATCH data .data 0x{self.DATA:x}", report)

    def test_a_changed_datum_differs(self):
        obj = self.compile(SOURCE.replace("kept string", "kept strinG"), "changed")
        ok, report, _records = self.verify(obj, self.group())
        self.assertFalse(ok)
        self.assertIn(f"DIFFER data .data 0x{self.DATA:x}", report)

    def test_a_wrong_address_differs(self):
        ok, report, _records = self.verify(self.obj, self.group({self.datum: hex(self.DATA + 16)}))
        self.assertFalse(ok, report)

    def test_a_reached_datum_must_be_declared(self):
        ok, report, _records = self.verify(self.obj, self.group({}))
        self.assertFalse(ok)
        self.assertIn("unowned code or runtime data", report)

    def test_isolated_body_references_retail_data(self):
        group = self.group()
        _ok, _report, records = self.verify(self.obj, group)
        isolated = self.root / "isolated.o"
        shutil.copyfile(self.obj, isolated)
        verify.isolate_emitted_body(str(isolated), self.OWNER, records, group, str(self.symbols))
        syms, _ = verify.object_syms(str(isolated))
        self.assertEqual(syms[f"DAT_{self.DATA:08x}"][0], "UND")
        allocated = [name for name, h in verify.elf_section_headers(str(isolated)) if h[2] & 2 and h[5]]
        self.assertEqual(allocated, [".text"])


class Rows(unittest.TestCase):
    """tools/whole_file_rows.py: placing compiled functions in retail."""

    class Function:
        def __init__(self, word):
            self.word = word

        def fits(self, retail, va):
            return retail[va] == self.word

    def test_a_partial_file_lets_its_missing_functions_link_from_retail(self):
        self.assertEqual(whole_file_rows.unrecovered([("cvFsInit", 196), ("cvFsMakeDir", 188)],
                                                     {"cvFsError", "splitPath"}),
                         ["cvFsInit", "cvFsMakeDir"])

    def test_a_partial_file_may_not_define_a_function_it_fails_to_reproduce(self):
        self.assertIsNone(whole_file_rows.unrecovered([("cvFsMakeDir", 188)], {"cvFsMakeDir"}))

    def test_unique_and_ambiguous_starts(self):
        retail = {0x100: 1, 0x110: 2, 0x120: 2}
        functions = {"a": self.Function(1), "b": self.Function(2), "gone": self.Function(9)}
        with self.assertRaisesRegex(SystemExit, "ambiguous: b"):
            whole_file_rows.locate(functions, retail, sorted(retail), {})
        placed = whole_file_rows.locate(functions, retail, sorted(retail), {"b": 0x120})
        self.assertEqual(placed, {"a": 0x100, "b": 0x120})

    def test_a_named_function_must_fit_its_start(self):
        with self.assertRaisesRegex(SystemExit, "does not reproduce its retail copy at 0x100"):
            whole_file_rows.locate({"a": self.Function(2)}, {0x100: 1}, [0x100], {"a": 0x100})

    def test_byte_identical_twin_is_stripped(self):
        retail = {0x100: 1}
        functions = {"kept": self.Function(1), "twin": self.Function(1)}
        placed = whole_file_rows.locate(functions, retail, [0x100], {"kept": 0x100}, ("twin",))
        self.assertEqual(placed, {"kept": 0x100})

    def test_two_functions_on_one_start_stop_the_run(self):
        functions = {"a": self.Function(1), "b": self.Function(1)}
        with self.assertRaisesRegex(SystemExit, "one retail start fits two"):
            whole_file_rows.locate(functions, {0x100: 1}, [0x100], {})

    def test_units_rows_cut_the_row_around_the_range(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "units.tsv"
            path.write_text("# head\n0x100\t0x400\tblock\tb\tf\toff\t-\tx\n0x400\t0x500\tnext\tb\tf\toff\t-\tx\n")
            whole_file_rows.units_rows(path, 0x200, 0x300, ["0x200\t0x300\tnew\tb\tg\toff\t-\tx\n"])
            lines = path.read_text().splitlines()
        self.assertEqual([line.split("\t")[:3] for line in lines[1:]],
                         [["0x100", "0x00000200", "block"], ["0x200", "0x300", "new"],
                          ["0x00000300", "0x400", "block"], ["0x400", "0x500", "next"]])


class CxxRows(unittest.TestCase):
    def test_literal_relocation_reads_as_gprel(self):
        self.assertEqual(verify.TYPES["R_MIPS_LITERAL"], verify.R_GPREL16)

    def test_owner_symbol_is_kept(self):
        with tempfile.TemporaryDirectory() as tmp:
            overlay = Path(tmp) / "objects.json"
            overlay.write_text(json.dumps({"0x00100000": {"whole_file": True, "symbol": "first__FPv"}}))
            unitobjects.load.cache_clear()
            self.addCleanup(unitobjects.load.cache_clear)
            group, = unitobjects.load(str(overlay))
        self.assertEqual(group.symbol, "first__FPv")


class ExceptionsOn(unittest.TestCase):
    """A recovered MWCC C++ file with exceptions on, checked against retail: each member's record
    and table are kept, and a destructor the retail linker kept from another file is a duplicate."""
    OWNER = 0x3a17c0
    SOURCE = Path(verify.ROOT) / "src/game/beWeapon.cpp"

    def setUp(self):
        self.elf = Path(verify.ROOT) / "orig/SLUS-20836/SLUS_208.36"
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, self.elf, self.SOURCE)):
            self.skipTest("private compiler or retail image unavailable")
        unitobjects.load.cache_clear()
        self.group = unitobjects.group_for(self.OWNER)
        self.profile = unitprofiles.resolve(self.OWNER, verify.FLAGS_DEFAULT, verify.MWCC_DEFAULT).profile
        temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-exc-")
        self.addCleanup(temp.cleanup)
        self.obj = Path(temp.name) / "unit.o"
        subprocess.run(cc.compile_argv(verify.WIBO_DEFAULT, self.profile.compiler,
                                       unitprofiles.command_flags(self.profile), str(self.SOURCE),
                                       str(self.obj)), cwd=verify.ROOT, check=True, capture_output=True)

    def test_members_keep_their_exception_records(self):
        self.assertEqual(self.profile.exceptions, "on")
        ok, report, records = verify.verify_emitted_object(
            str(self.obj), self.group, str(self.elf), os.path.join(verify.ROOT, "config/SLUS-20836/symbols.txt"))
        self.assertTrue(ok, report)
        self.assertIn("exc=ok cat=match", report.splitlines()[0])
        self.assertTrue(records.exception_placements)

    def test_a_reached_copy_elsewhere_is_a_duplicate(self):
        syms, headers, functions = whole_file_rows.text_functions(str(self.obj))
        placed = {name: address for name, address in ((self.group.symbol, self.OWNER),) + self.group.emitted}
        by_name, by_va = verify.load_symbols(os.path.join(verify.ROOT, "config/SLUS-20836/symbols.txt"))
        last = max(placed.values())
        _data, found, _externals = whole_file_rows.reach(
            placed, whole_file_rows.Retail(str(self.elf)), syms, headers, str(self.obj), functions,
            exceptions.load(), {name: va for name, (va, _size) in by_name.items()}, last + by_va[last][1])
        self.assertEqual(found, dict(self.group.duplicates))


class LiteralAtTwoEntries(unittest.TestCase):
    """The retail linker gives each literal *reference* a pool entry as it walks the program, and a
    newer entry of another value in the same hash slot makes a later reference to an equal value
    get a new entry: two members of one file read one compiled literal at two pool addresses. The
    rows and verify resolve each reference from its retail instruction (verify.fold_literals)."""
    SOURCE = "float lit_first(float x) { return x * 0.3f; }\nfloat lit_second(float x) { return x + 0.3f; }\n"
    FIRST, SECOND = 0x180000, 0x180100
    GP, ENTRY_A, OTHER, ENTRY_B = 0x55c870, 0x554900, 0x554904, 0x554908

    def setUp(self):
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, verify.MWCC_DEFAULT)):
            self.skipTest("private compiler unavailable")
        temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-literal-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        source, self.obj = self.root / "lits.c", self.root / "lits.o"
        source.write_text(self.SOURCE)
        subprocess.run([verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, "-c", "-O4,s", "-sdatathreshold", "2",
                        "-lang", "c", "-Cpp_exceptions", "off", str(source), "-o", str(self.obj)],
                       check=True, capture_output=True, env=dict(os.environ, MWCIncludes=str(self.root)))
        self.syms, self.headers, self.functions = whole_file_rows.text_functions(str(self.obj))
        literal = {self.syms[r[3]][0] for f in self.functions.values() for r in f.relocs}
        self.assertEqual([self.headers[i][0] for i in literal], [".lit4"])
        self.value = verify.object_section(str(self.obj), ".lit4", literal.pop())
        self.placed = {"lit_first": self.FIRST, "lit_second": self.SECOND}
        self.symbols = self.root / "symbols.txt"
        self.symbols.write_text("".join(f"{va:08x} {len(self.functions[n].raw):06x} {n}\n"
                                        for n, va in self.placed.items()))

    def retail(self, second_value=None):
        """A retail image: lit_first reads the literal at ENTRY_A, lit_second at ENTRY_B, with
        another value between them, as retail's 5e-7 sits at 0x5548ec and 0x55495c."""
        image = bytearray(0x554a00 - verify.VADDR_BASE + verify.FILE_BASE)
        at = lambda va: va - verify.VADDR_BASE + verify.FILE_BASE
        for name, entry in (("lit_first", self.ENTRY_A), ("lit_second", self.ENTRY_B)):
            function = self.functions[name]
            words = list(function.words)
            for _section, offset, kind, _symbol, _addend in function.relocs:
                self.assertEqual(kind, verify.R_GPREL16)       # R_MIPS_LITERAL reads as GPREL16
                words[offset // 4] = (words[offset // 4] & ~0xffff) | ((entry - self.GP) & 0xffff)
            image[at(self.placed[name]):at(self.placed[name]) + 4 * len(words)] = struct.pack(
                "<%dI" % len(words), *words)
        image[at(self.ENTRY_A):at(self.ENTRY_A) + 4] = self.value
        image[at(self.OTHER):at(self.OTHER) + 4] = struct.pack("<f", -1e-6)
        image[at(self.ENTRY_B):at(self.ENTRY_B) + 4] = second_value or self.value
        image[:6] = b"\x7fELF\x01\x01"
        reginfo = len(image)
        image.extend(struct.pack("<6I", 0, 0, 0, 0, 0, self.GP))
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
        path = self.root / ("retail%d.elf" % len(list(self.root.glob("retail*.elf"))))
        path.write_bytes(image)
        return path

    def rows(self, elf):
        retail = whole_file_rows.Retail(str(elf))
        data, _duplicates, externals = whole_file_rows.reach(self.placed, retail, self.syms, self.headers,
                                                             str(self.obj), self.functions, {}, {},
                                                             self.SECOND + 0x100)
        whole_file_rows.literals(self.placed, {}, retail, self.syms, self.headers, str(self.obj),
                                 self.functions, data)
        return data, externals

    def verify(self, elf, data=None):
        registry = self.root / "objects.json"
        registry.write_text(json.dumps({hex(self.FIRST): {
            "whole_file": True, "emitted": {"lit_second": hex(self.SECOND)}, "data": data or {}}}))
        unitobjects.load.cache_clear()
        self.addCleanup(unitobjects.load.cache_clear)
        group = unitobjects.group_for(self.FIRST, registry)
        obj = self.root / "verified.o"
        shutil.copyfile(self.obj, obj)
        ok, report, records = verify.verify_emitted_object(str(obj), group, str(elf), str(self.symbols),
                                                           jumptables={})
        return ok, report, records, group, obj

    def test_one_literal_read_at_two_entries_is_one_unit(self):
        elf = self.retail()
        self.assertEqual(self.rows(elf), ({}, {}))
        ok, report, records, group, obj = self.verify(elf)
        self.assertTrue(ok, report)
        # each linked member reads its own entry: the folded immediates are retail's words
        for name, va in self.placed.items():
            isolated = self.root / f"{name}.o"
            shutil.copyfile(obj, isolated)
            verify.isolate_emitted_body(str(isolated), va, records, group, str(self.symbols))
            text = verify.object_section(str(isolated), ".text")
            self.assertEqual(text, verify.va_bytes(verify.read_elf(str(elf)), va, len(text)))
            self.assertEqual(verify.object_relocs(str(isolated)), [])

    def test_an_entry_without_the_literals_bytes_stops_both(self):
        elf = self.retail(second_value=struct.pack("<f", 0.25))
        with self.assertRaisesRegex(SystemExit, "is not the retail pool entry at 0x554908"):
            self.rows(elf)
        ok, report, _records, _group, _obj = self.verify(elf)
        self.assertFalse(ok)
        self.assertIn("is not the retail pool entry at 0x554908", report)

    def test_a_literal_has_no_data_row(self):
        name = next(r[3] for r in self.functions["lit_first"].relocs)
        ok, report, _records, _group, _obj = self.verify(self.retail(), {name: hex(self.ENTRY_A)})
        self.assertFalse(ok)
        self.assertIn("is a compiler literal", report)


class ProfileTwin(unittest.TestCase):
    """A duplicate the retail linker kept from a unit of another profile: in the messenger file (-O3,p,
    exceptions on), beMessenger_RegisterReceiver reaches the StringRef destructor at 0x130720, an -O4,s
    copy from the Attrs library. As tools/verify.py checks it, the same source compiled under that unit's
    profile must reproduce it there; the file's own copy cannot. Placed alone, the member also reaches
    the group holder's destructor, a copy the file places at 0x38d7a0 under its own profile."""
    OWNER, NAME, COPY, DESTRUCTOR = 0x38d560, "beMessenger_RegisterReceiver", 0x130720, "__dt__9StringRefFv"
    HOLDER = "__dt__34igSmartPointer<16beMessengerGroup>Fv"
    SOURCE = Path(verify.ROOT) / "src/game/beMessenger.cpp"
    CONFIG = Path(verify.ROOT) / "config/SLUS-20836"

    def setUp(self):
        self.elf = Path(verify.ROOT) / "orig/SLUS-20836/SLUS_208.36"
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, self.elf, self.SOURCE)):
            self.skipTest("private compiler or retail image unavailable")
        self.profile = unitprofiles.resolve(self.OWNER, verify.FLAGS_DEFAULT, verify.MWCC_DEFAULT).profile
        temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-twin-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.obj = self.root / "unit.o"
        subprocess.run(cc.compile_argv(verify.WIBO_DEFAULT, self.profile.compiler,
                                       unitprofiles.command_flags(self.profile), str(self.SOURCE),
                                       str(self.obj)), cwd=verify.ROOT, check=True, capture_output=True)

    def duplicates(self, config=CONFIG):
        syms, headers, functions = whole_file_rows.text_functions(str(self.obj))
        twins = whole_file_rows.Twins(self.profile, str(self.SOURCE), str(self.root), str(config),
                                      verify.WIBO_DEFAULT)
        return whole_file_rows.reach(
            {self.NAME: self.OWNER}, whole_file_rows.Retail(str(self.elf)), syms, headers, str(self.obj),
            functions, exceptions.load(), self.names(), self.OWNER + 4, twins)[1]

    def names(self):
        return {name: address for name, (address, _size) in verify.load_symbols(
            str(self.CONFIG / "symbols.txt"))[0].items()}

    def config(self, flags, mode):
        """The profile tables, with the unit holding the copy built under `flags` and `mode`."""
        config = self.root / "config"
        config.mkdir()
        for name in ("unit-flags.tsv", "unit-compilers.tsv", "symbols.txt"):
            shutil.copyfile(self.CONFIG / name, config / name)
        lines = []
        for line in (self.CONFIG / "units.tsv").read_text().splitlines(keepends=True):
            fields = line.split("\t")
            if fields[0].startswith("0x") and int(fields[0], 16) <= self.COPY < int(fields[1], 16):
                fields[4:6] = [flags, mode]
            lines.append("\t".join(fields))
        (config / "units.tsv").write_text("".join(lines))
        return config

    def test_a_twin_is_compiled_under_its_own_units_profile(self):
        found = self.duplicates()
        self.assertEqual(found[self.DESTRUCTOR], self.COPY)
        emitted = dict(unitobjects.group_for(self.OWNER).emitted)
        self.assertEqual(found, {self.DESTRUCTOR: self.COPY, self.HOLDER: emitted[self.HOLDER]})

    def test_a_copy_under_the_files_profile_is_not_recompiled(self):
        with self.assertRaisesRegex(SystemExit, "0x130720, which holds other code"):
            self.duplicates(self.config(self.profile.flags, self.profile.exceptions))

    def test_a_twin_that_differs_stops_the_run(self):
        with self.assertRaisesRegex(SystemExit, "is 148 bytes and retail's copy at 0x130720 is 116"):
            self.duplicates(self.config("-O1 -sdatathreshold 2 -Iinclude", "off"))

    def test_a_call_only_the_duplicates_make_is_an_external(self):
        syms, headers, functions = whole_file_rows.text_functions(str(self.obj))
        self.assertNotIn("__dl__FPv", {r[3] for r in functions[self.NAME].relocs})
        twins = whole_file_rows.Twins(self.profile, str(self.SOURCE), str(self.root), str(self.CONFIG),
                                      verify.WIBO_DEFAULT)
        _data, _duplicates, externals = whole_file_rows.reach(
            {self.NAME: self.OWNER}, whole_file_rows.Retail(str(self.elf)), syms, headers, str(self.obj),
            functions, exceptions.load(), self.names(), self.OWNER + 4, twins)
        self.assertEqual(externals, dict(unitobjects.group_for(self.OWNER).externals))


class TableExternals(unittest.TestCase):
    """beTransformSync_GetVTable: retail's exception table names the igNodeView destructor
    (0x195a90) as the cleanup of its base subobject, and no member calls it. The rows must still
    bind it, from the retail table word, or the table relocation is unresolved in verify."""
    OWNER, NAME, CLEANUP = 0x3410c0, "beTransformSync_GetVTable", "__dt__10igNodeViewFv"
    SOURCE = '''
extern "C" {
extern int DAT_005284f0[4];
extern int DAT_005397d0[4];
extern void *DAT_00586dc8[4];
int beTransformSync_GetVTable(void);
}
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
struct SyncTransformListField { int *p; SyncTransformListField() { p = 0; } ~SyncTransformListField(); };
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct TransformSyncVtable { TransformSyncVtable(int **slot) { *slot = DAT_005397d0; } };
struct igNodeView : igObjectView {
    int name, bound, parentList, flags, handle, childList;
    igNodeView() { name = 0; bound = 0; parentList = 0; childList = 0; }
    ~igNodeView();
};
struct igTransformView : igNodeView, igTransformVtable {
    igMatrix44fView m;
    int target, mvm, transformInput;
    igTransformView() : igTransformVtable(&vtable) { mvm = 0; transformInput = 0; }
    ~igTransformView();
};
struct TransformSyncView : igTransformView, TransformSyncVtable {
    SyncTransformListField syncTransformList;
    TransformSyncView() : TransformSyncVtable(&vtable) { }
    ~TransformSyncView() { vtable = DAT_005397d0; }
};
int beTransformSync_GetVTable(void) {
    TransformSyncView transform;
    return *(int *)((char *)&transform + *(int *)((char *)DAT_00586dc8[0] + 916));
}
'''
    EXTERNALS = {"__ct__12igObjectViewFv": 0x2fef20, "__ct__15igMatrix44fViewFv": 0x190380,
                 "__dt__10igNodeViewFv": 0x195a90, "__dt__15igTransformViewFv": 0x1962d0,
                 "__dt__22SyncTransformListFieldFv": 0x341160}

    def setUp(self):
        self.elf = Path(verify.ROOT) / "orig/SLUS-20836/SLUS_208.36"
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, self.elf)):
            self.skipTest("private compiler or retail image unavailable")
        self.symbols = os.path.join(verify.ROOT, "config/SLUS-20836/symbols.txt")
        profile = unitprofiles.resolve(self.OWNER, verify.FLAGS_DEFAULT, verify.MWCC_DEFAULT).profile
        self.assertEqual(profile.exceptions, "on")
        temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-table-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        source = self.root / "unit.cpp"
        source.write_text(self.SOURCE)
        self.obj = self.root / "unit.o"
        subprocess.run(cc.compile_argv(verify.WIBO_DEFAULT, profile.compiler,
                                       unitprofiles.command_flags(profile), str(source), str(self.obj)),
                       cwd=verify.ROOT, check=True, capture_output=True)

    def rows(self):
        """(data, externals, stripped) as whole_file_rows.main derives them for the one member."""
        syms, headers, functions = whole_file_rows.text_functions(str(self.obj))
        retail = whole_file_rows.Retail(str(self.elf))
        by_name, by_va = verify.load_symbols(self.symbols)
        names = {name: address for name, (address, _size) in by_name.items()}
        placed, records = {self.NAME: self.OWNER}, exceptions.load()
        data, duplicates, externals = whole_file_rows.reach(placed, retail, syms, headers, str(self.obj),
                                                            functions, records, names,
                                                            self.OWNER + by_va[self.OWNER][1])
        self.assertEqual(duplicates, {})
        externals = whole_file_rows.table_externals(placed, retail, syms, headers, str(self.obj), functions,
                                                    records, names, data, externals, by_va)
        return data, externals, sorted(n for n in functions if n not in placed)

    def test_a_cleanup_only_the_table_names_is_an_external(self):
        _data, externals, _stripped = self.rows()
        self.assertEqual(externals, self.EXTERNALS)

    def verify(self, drop=()):
        data, externals, stripped = self.rows()
        overlay = self.root / "objects.json"
        overlay.write_text(json.dumps({"0x%08x" % self.OWNER: {
            "whole_file": True, "symbol": self.NAME, "stripped": stripped,
            "data": {k: "0x%08x" % v for k, v in data.items()},
            "externals": {k: "0x%08x" % v for k, v in externals.items() if k not in drop}}}))
        unitobjects.load.cache_clear()
        self.addCleanup(unitobjects.load.cache_clear)
        group, = unitobjects.load(str(overlay))
        ok, report, _records = verify.verify_emitted_object(str(self.obj), group, str(self.elf), self.symbols)
        return ok, report

    def test_the_derived_row_verifies_the_table_exactly(self):
        ok, report = self.verify()
        self.assertTrue(ok, report)
        self.assertIn("exc=ok cat=match", report.splitlines()[0])
        self.assertIn("MATCH exception table (beTransformSync_GetVTable) 0x54302c 15B", report)

    def test_without_the_cleanup_external_the_table_differs(self):
        ok, report = self.verify(drop=(self.CLEANUP,))
        self.assertFalse(ok)
        self.assertIn("unresolved relocation '__dt__10igNodeViewFv'", report)


class RuntimeRows(unittest.TestCase):
    """The MWCC runtime files, exceptions on. New.cpp's `throw(std::bad_alloc)` specification names a
    type string that only its exception table reaches. NMWException.cpp's `operator new` throws a
    `std::bad_alloc`, passing its destructor's address (a `lui`/`addiu` pair) and storing its vtable;
    the vtables name the other `std::exception` and `std::bad_alloc` virtual functions, which no member
    calls. The retail linker kept New.cpp's copies, so all four are duplicates, never `stripped`."""
    NEW, NMW = (0x100390, 0x1007e0, "New"), (0x1007e0, 0x100cb0, "NMWException")

    def setUp(self):
        self.elf = Path(verify.ROOT) / "orig/SLUS-20836/SLUS_208.36"
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, self.elf)):
            self.skipTest("private compiler or retail image unavailable")
        self.symbols = os.path.join(verify.ROOT, "config/SLUS-20836/symbols.txt")
        temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-runtime-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        unitobjects.load.cache_clear()
        self.addCleanup(unitobjects.load.cache_clear)

    def reach(self, unit):
        lo, hi, stem = unit
        profile = unitprofiles.resolve(lo, verify.FLAGS_DEFAULT, verify.MWCC_DEFAULT).profile
        self.assertEqual(profile.exceptions, "on")
        obj = self.root / f"{stem}.o"
        subprocess.run(cc.compile_argv(verify.WIBO_DEFAULT, profile.compiler, unitprofiles.command_flags(profile),
                                       os.path.join(verify.ROOT, f"src/runtime/{stem}.cpp"), str(obj)),
                       cwd=verify.ROOT, check=True, capture_output=True)
        group = unitobjects.group_for(lo)
        syms, headers, functions = whole_file_rows.text_functions(str(obj))
        names = {name: va for name, (va, _size) in verify.load_symbols(self.symbols)[0].items()}
        placed = {group.symbol: lo, **dict(group.emitted)}
        rows = whole_file_rows.reach(placed, whole_file_rows.Retail(str(self.elf)), syms, headers, str(obj),
                                     functions, exceptions.load(), names, hi)
        return rows, group, obj, syms, headers, functions

    def named_by_text(self, obj, headers):
        return {r[3] for i, (name, _h) in enumerate(headers) if name == ".text"
                for r in verify.object_relocs(str(obj), target_section=i)}

    def test_a_datum_only_an_exception_table_names_has_a_row(self):
        (data, _duplicates, _externals), group, obj, syms, headers, functions = self.reach(self.NEW)
        table = whole_file_rows.exception_tables(syms, headers, str(obj), functions)["__default_new_handler__3stdFv"]
        label, = [r[3] for r in verify.object_relocs(str(obj), target_section=table) if r[3].startswith("@")]
        self.assertNotIn(label, self.named_by_text(obj, headers))
        self.assertEqual(data[label], 0x4d1c30)
        self.assertEqual(data, dict(group.data))

    def test_functions_only_a_kept_vtable_names_are_duplicates(self):
        (data, duplicates, _externals), group, obj, _syms, headers, functions = self.reach(self.NMW)
        self.assertEqual(duplicates, {"__dt__Q23std9exceptionFv": 0x100670, "what__Q23std9exceptionCFv": 0x1006c0,
                                      "__dt__Q23std9bad_allocFv": 0x100770, "what__Q23std9bad_allocCFv": 0x1007d0})
        self.assertEqual(duplicates, dict(group.duplicates))
        self.assertEqual(data, dict(group.data))
        members = {name for name, _va in group.emitted} | {group.symbol}
        named = {(r[3], r[2]) for name in members for r in functions[name].relocs if r[3] in duplicates}
        self.assertEqual(named, {("__dt__Q23std9bad_allocFv", whole_file_rows.R_HI16),
                                 ("__dt__Q23std9bad_allocFv", whole_file_rows.R_LO16)})

    def test_a_body_a_kept_vtable_names_cannot_be_stripped(self):
        _rows, group, obj, *_ = self.reach(self.NMW)
        overlay = self.root / "objects.json"
        overlay.write_text(json.dumps({"0x%08x" % group.owner: {
            "whole_file": True, "symbol": group.symbol,
            "emitted": {name: "0x%08x" % va for name, va in group.emitted},
            "stripped": sorted(name for name, _va in group.duplicates),
            "data": {name: "0x%08x" % va for name, va in group.data}}}))
        unitobjects.load.cache_clear()
        stripped, = unitobjects.load(str(overlay))
        ok, report, _records = verify.verify_emitted_object(str(obj), stripped, str(self.elf), self.symbols)
        self.assertFalse(ok)
        self.assertIn("a referenced body cannot have been dead-stripped", report)
        ok, report, _records = verify.verify_emitted_object(str(obj), group, str(self.elf), self.symbols)
        self.assertTrue(ok, report)


class SharedStaticOwner(unittest.TestCase):
    """libkernl's libosd.c starts with `static setup`, a name exit.c and alarm.c define too, which
    symbols.txt calls `setup_libosd`: the row keeps the source's name as `symbol`."""
    COMPILER = os.path.join(verify.ROOT, "local", "ee-gcc2.9-991111-01", "bin", "ee-gcc")

    def test_the_owners_source_name_is_the_rows_symbol(self):
        elf = Path(verify.ROOT) / "orig/SLUS-20836/SLUS_208.36"
        if not all(Path(p).exists() for p in (self.COMPILER, elf)):
            self.skipTest("private compiler or retail image unavailable")
        out = io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()):
            whole_file_rows.main(["--src", os.path.join(verify.ROOT, "src/sony/libkernl"), "--files", "libosd",
                                  "--range", "0x114220", "0x1143a0", "--compiler", "ee-gcc-2.9",
                                  "--flags", "-O2 -G0 -ffunction-sections -Iinclude", "--unit", "sony_libkernl"])
        row = json.loads(out.getvalue())["0x00114220"]
        self.assertEqual(row["symbol"], "setup")
        self.assertEqual(verify.load_symbols(os.path.join(verify.ROOT, "config/SLUS-20836/symbols.txt"))[1][0x114220][0],
                         "setup_libosd")
        self.assertEqual(row["emitted"]["Copy"], "0x00114230")


class MergeRows(unittest.TestCase):
    def test_a_held_out_functions_row_survives(self):
        overlay = {"0x00100000": {"whole_file": True, "emitted": {"b": "0x00100100"}},
                   "0x00100200": {"emitted": {"held_helper": "0x00100240"}},
                   "0x00100300": {"emitted": {"joined_helper": "0x00100340"}},
                   "0x00100800": {"emitted": {"other": "0x00100840"}}}
        rows = {"0x00100000": {"whole_file": True, "emitted": {"b": "0x00100100", "joined": "0x00100300"}}}
        merged = whole_file_rows.merge_rows(overlay, 0x100000, 0x100400, rows)
        self.assertEqual(sorted(merged), ["0x00100000", "0x00100200", "0x00100800"])
        self.assertEqual(merged["0x00100000"], rows["0x00100000"])

    def test_a_stale_whole_file_row_goes(self):
        overlay = {"0x00100100": {"whole_file": True, "emitted": {"c": "0x00100200"}}}
        rows = {"0x00100000": {"whole_file": True, "emitted": {"b": "0x00100100"}}}
        self.assertEqual(whole_file_rows.merge_rows(overlay, 0x100000, 0x100400, rows), rows)


class SharedStatics(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="dw4-statics-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        (self.root / "src").mkdir()
        (self.root / "src/a.c").write_text("int a_owner(void) { return 0; }\nstatic int shared(void) { return 1; }\n")
        (self.root / "src/b.c").write_text("static int shared(void) { return 2; }\n")
        self.symbols = self.root / "symbols.txt"

    def scan(self, rows, symbols):
        self.symbols.write_text(symbols)
        overlay = self.root / "objects.json"
        overlay.write_text(json.dumps(rows))
        unitobjects.load.cache_clear()
        unitobjects.names.cache_clear()
        return units.scan(str(self.root / "src"), str(self.symbols), str(overlay))

    def test_whole_file_row_places_the_retail_function(self):
        row = {"0x00100000": {"whole_file": True, "emitted": {"shared": "0x00100010"}}}
        index = self.scan(row, "00100000 000010 a_owner\n00100010 000010 shared\n")
        self.assertTrue(index["shared"].endswith("src/a.c"))

    def test_name_retail_lacks_belongs_to_neither(self):
        self.assertNotIn("shared", self.scan({}, "00100000 000010 a_owner\n"))

    def test_real_clash_still_refused(self):
        with self.assertRaisesRegex(ValueError, "already defined"):
            self.scan({}, "00100000 000010 a_owner\n00100010 000010 shared\n")


class BssData(unittest.TestCase):
    """A file's own `.bss` statics: one `@bss` data row, compared with the zeros retail's loader fills."""
    OWNER, MEMBER, DATA = 0x180000, 0x180100, 0x190000
    COMPILER = os.path.join(verify.ROOT, "local", "ee-gcc2.9-991111-01", "bin", "ee-gcc")
    SOURCE = ("static int state[4];\n"
              "static int other[2];\n"
              "int fixture_read(void) { return state[2] + other[1]; }\n"
              "int fixture_write(int v) { state[1] = v; return 0; }\n")

    def setUp(self):
        if not Path(self.COMPILER).exists():
            self.skipTest("private compiler unavailable")
        if not shutil.which("mipsel-linux-gnu-ld"):
            self.skipTest("GNU MIPS tools unavailable")
        temp = tempfile.TemporaryDirectory(prefix="dw4-whole-file-bss-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        source, self.obj = self.root / "fixture.c", self.root / "fixture.o"
        source.write_text(self.SOURCE)
        self.assertEqual(eegcc_compile.main([self.COMPILER, "-O2", "-G0", "-ffunction-sections",
                                             str(source), str(self.obj)]), 0)
        syms, _ = verify.object_syms(str(self.obj))
        self.assertEqual(syms["@bss"][1], 0)
        # Link the object with GNU ld, without the verifier, for the bytes retail would hold.
        placed = {"fixture_read": self.OWNER, "fixture_write": self.MEMBER, "@bss": self.DATA}
        linked = self.root / "linked.o"
        shutil.copyfile(self.obj, linked)
        names = {syms[name][0]: f".place{syms[name][0]}" for name in placed}
        verify.rename_object_sections(str(linked), names)
        script = self.root / "fixture.ld"
        rows = [f".out{syms[name][0]} 0x{address:x} : {{ *({names[syms[name][0]]}) }}"
                for name, address in placed.items()]
        script.write_text("SECTIONS {\n" + "\n".join(rows) + "\n/DISCARD/ : { *(.mdebug) *(.reginfo) } }\n")
        out = self.root / "fixture.out"
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-T", str(script), str(linked),
                        "-o", str(out)], check=True, capture_output=True)
        filesz = 0x180200 - verify.VADDR_BASE
        image = bytearray([0xa5]) * (filesz + verify.FILE_BASE)
        for name in ("fixture_read", "fixture_write"):
            body = verify.object_section(str(out), f".out{syms[name][0]}")
            start = placed[name] - verify.VADDR_BASE + verify.FILE_BASE
            image[start:start + len(body)] = body
        image[:6] = b"\x7fELF\x01\x01"
        # one loaded segment: the code from the file, then zeros up to its memory size (the `.bss`)
        struct.pack_into("<I", image, 0x1c, 0x34)
        struct.pack_into("<8I", image, 0x34, 1, verify.FILE_BASE, verify.VADDR_BASE, verify.VADDR_BASE,
                         filesz, self.DATA + 0x100 - verify.VADDR_BASE, 7, 0x80)
        struct.pack_into("<HH", image, 0x2a, 32, 1)
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
        self.image = self.root / "fixture.elf"
        self.image.write_bytes(image)
        self.symbols = self.root / "symbols.txt"
        self.symbols.write_text(f"{self.OWNER:08x} {syms['fixture_read'][2]:06x} fixture_read\n"
                                f"{self.MEMBER:08x} {syms['fixture_write'][2]:06x} fixture_write\n")
        self.registry = self.root / "objects.json"

    def verify(self, data):
        self.registry.write_text(json.dumps({hex(self.OWNER): {
            "whole_file": True, "emitted": {"fixture_write": hex(self.MEMBER)}, "data": {"@bss": hex(data)}}}))
        group = unitobjects.group_for(self.OWNER, self.registry)
        return verify.verify_emitted_object(str(self.obj), group, str(self.image), str(self.symbols), jumptables={})

    def test_a_nobits_section_reads_as_zeros(self):
        syms, _ = verify.object_syms(str(self.obj))
        section = syms["@bss"][0]
        size = verify.elf_section_headers(str(self.obj))[section][1][5]
        self.assertEqual(verify.object_section(str(self.obj), ".bss", section), bytes(size))

    def test_loaded_bytes_fill_zeros_past_the_file(self):
        image = self.image.read_bytes()
        self.assertEqual(verify.loaded_bytes(image, 0x1801fe, 4), image[0x8027e:0x80280] + bytes(2))
        self.assertEqual(verify.loaded_bytes(image, self.DATA + 0xfc, 8), bytes(4))

    def test_statics_at_their_retail_address_match(self):
        ok, report, _records = self.verify(self.DATA)
        self.assertTrue(ok, report)
        self.assertIn(f"MATCH data .bss 0x{self.DATA:x}", report)

    def test_statics_over_file_bytes_differ(self):
        ok, report, _records = self.verify(self.OWNER + 0x80)
        self.assertFalse(ok)
        self.assertIn(f"DIFFER data .bss 0x{self.OWNER + 0x80:x}", report)

    def test_each_isolated_member_links(self):
        _ok, _report, records = self.verify(self.DATA)
        group = unitobjects.group_for(self.OWNER, self.registry)
        for address, other in ((self.OWNER, "fixture_write"), (self.MEMBER, "fixture_read")):
            member = self.root / f"member_{address:x}.o"
            shutil.copyfile(self.obj, member)
            verify.isolate_emitted_body(str(member), address, records, group, str(self.symbols),
                                        source=str(self.obj))
            script = self.root / f"member_{address:x}.ld"
            script.write_text(f"DAT_{self.DATA:08x} = 0x{self.DATA:x};\n{other} = 0x{self.OWNER + self.MEMBER - address:x};\n"
                              f"SECTIONS {{\n.text 0x{address:x} : {{ *(.text) }}\n/DISCARD/ : {{ *(.reginfo) }}\n}}\n")
            linked = subprocess.run(["mipsel-linux-gnu-ld", "-T", str(script), "-G0", "--no-warn-mismatch",
                                     "-o", str(self.root / f"member_{address:x}.elf"), str(member)],
                                    capture_output=True, text=True)
            self.assertEqual(linked.returncode, 0, linked.stderr)


if __name__ == "__main__":
    unittest.main()
