"""Data-only units: a file the retail linker kept the data of and none of its functions."""
import contextlib
import io
import json
import os
from pathlib import Path
import shutil
import struct
import tempfile
import unittest
from unittest import mock

import check
import eegcc_compile
import unitobjects
import verify
import whole_file_rows

COMPILER = os.path.join(verify.ROOT, "local", "ee-gcc2.9-991111-01", "bin", "ee-gcc")
FLAGS = ["-O2", "-G0", "-ffunction-sections"]
DATA_SOURCE = "int fixture_table[3] = {1, 2, 3};\nstatic int fixture_state = -1;\n"
DROPPED_FUNCTION = "int fixture_dropped(int v) { return v + fixture_state + fixture_table[1]; }\n"


def image_with(blobs, end):
    """A retail-shaped image: file bytes from VADDR_BASE to `end` holding `blobs` ({va: bytes}), the rest
    0xa5, and the `.reginfo` the verifier reads gp from."""
    image = bytearray([0xa5]) * (end - verify.VADDR_BASE + verify.FILE_BASE)
    for va, blob in blobs.items():
        start = va - verify.VADDR_BASE + verify.FILE_BASE
        image[start:start + len(blob)] = blob
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
    return bytes(image)


class Overlay(unittest.TestCase):
    DATA = 0x190000

    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="dw4-data-only-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.registry = self.root / "objects.json"
        self.symbols = self.root / "symbols.txt"
        self.symbols.write_text("00180000 000010 one\n")

    def load(self, rows):
        self.registry.write_text(json.dumps(rows))
        unitobjects.load.cache_clear()
        return unitobjects.load(self.registry)

    def row(self, **extra):
        return {"whole_file": True, "data": {"@data": hex(self.DATA)}, "stripped": ["fixture_dropped"],
                "source": "lib/fixture.c", **extra}

    def test_a_row_keyed_by_its_own_datum_is_data_only(self):
        group, = self.load({hex(self.DATA): self.row()})
        self.assertTrue(group.data_only)
        self.assertEqual((group.source, group.members), ("lib/fixture.c", ()))
        self.assertIs(unitobjects.group_for(self.DATA, self.registry), group)
        self.assertEqual(unitobjects.data_only_units(self.registry), (group,))

    def test_a_row_keyed_by_a_function_is_not(self):
        group, = self.load({"0x00180000": {"whole_file": True, "data": {"@data": hex(self.DATA)}}})
        self.assertFalse(group.data_only)
        self.assertEqual(group.members, (0x180000,))

    def test_it_names_its_dropped_functions_and_its_source(self):
        for missing in ("stripped", "source"):
            row = self.row()
            del row[missing]
            with self.assertRaisesRegex(ValueError, "data-only row"):
                self.load({hex(self.DATA): row})
        for source in ("/abs/fixture.c", "../fixture.c", "lib/fixture.h"):
            with self.assertRaisesRegex(ValueError, "source"):
                self.load({hex(self.DATA): self.row(source=source)})

    def test_it_places_no_function(self):
        for field, value in (("emitted", {"one": "0x00180000"}), ("symbol", "fixture"),
                             ("duplicates", {"one": "0x00180000"})):
            with self.assertRaisesRegex(ValueError, "places no function"):
                self.load({hex(self.DATA): self.row(**{field: value})})

    def test_only_a_data_only_row_names_its_source(self):
        with self.assertRaisesRegex(ValueError, "only a data-only row"):
            self.load({"0x00180000": {"whole_file": True, "source": "lib/fixture.c"}})

    def test_no_function_definition_locates_it(self):
        self.load({hex(self.DATA): self.row(), "0x00180000": {"whole_file": True}})
        self.assertEqual(unitobjects.augment_sources({"one": "a.c"}, str(self.symbols), str(self.registry)),
                         {"one": "a.c"})


class Fixture(unittest.TestCase):
    """A data-only file compiled with the Sony EE GCC, against an image whose data holds its bytes."""
    CODE, DATA = 0x180000, 0x190000

    def setUp(self):
        if not Path(COMPILER).exists():
            self.skipTest("private compiler unavailable")
        if not shutil.which("mipsel-linux-gnu-objcopy"):
            self.skipTest("GNU MIPS tools unavailable")
        temp = tempfile.TemporaryDirectory(prefix="dw4-data-only-")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        (self.root / "src" / "lib").mkdir(parents=True)
        self.registry = self.root / "objects.json"
        self.symbols = self.root / "symbols.txt"
        self.symbols.write_text(f"{self.CODE:08x} 000040 fixture_code\n")
        self.images = 0
        self.make_image()

    def compile(self, text, name="fixture"):
        source, obj = self.root / "src" / "lib" / f"{name}.c", self.root / f"{name}.o"
        source.write_text(text)
        self.assertEqual(eegcc_compile.main([COMPILER, *FLAGS, str(source), str(obj)]), 0)
        return obj

    def make_image(self, data=struct.pack("<4i", 1, 2, 3, -1), code=bytes(64)):
        # verify.read_elf caches an image by path: each variant is a new file
        self.images += 1
        self.image = self.root / f"fixture{self.images}.elf"
        self.image.write_bytes(image_with({self.CODE: code, self.DATA: data}, self.DATA + 0x100))

    def group(self, data=None, stripped=("fixture_dropped",), key=None):
        data = {"@data": hex(self.DATA)} if data is None else data
        self.registry.write_text(json.dumps({hex(key or self.DATA): {
            "whole_file": True, "data": data, "stripped": list(stripped), "source": "lib/fixture.c"}}))
        unitobjects.load.cache_clear()
        return unitobjects.group_for(key or self.DATA, self.registry)

    def verify(self, obj, group):
        return verify.verify_emitted_object(str(obj), group, str(self.image), str(self.symbols), jumptables={})


class Objects(Fixture):
    def test_the_compiler_names_a_data_only_section(self):
        syms, _ = verify.object_syms(str(self.compile(DATA_SOURCE)))
        self.assertEqual(syms["@data"][1:], (0, 0))
        self.assertEqual(syms["fixture_table"][1], 0)

    def test_its_data_matches_retail(self):
        ok, report, records = self.verify(self.compile(DATA_SOURCE), self.group())
        self.assertTrue(ok, report)
        self.assertTrue(report.startswith("MATCH data-only unit: 1 data sections, 1 functions dropped cat=match"),
                        report)
        self.assertIn(f"MATCH data .data 0x{self.DATA:x} 16B", report)
        self.assertEqual(list(records.data_placements.values()), [(self.DATA, 16, ".data", False)])

    def test_a_changed_datum_differs(self):
        self.make_image(data=struct.pack("<4i", 1, 2, 3, 0))
        ok, report, records = self.verify(self.compile(DATA_SOURCE), self.group())
        self.assertFalse(ok)
        self.assertIn(f"DIFFER data .data 0x{self.DATA:x} 16B", report)
        self.assertIsNone(records)

    def test_the_row_is_keyed_by_its_first_datum(self):
        group = self.group(data={"@data": hex(self.DATA), "@rodata": hex(self.DATA + 0x40)}, key=self.DATA + 0x40)
        ok, report, _records = self.verify(self.compile(DATA_SOURCE + "const int fixture_limit = 7;\n"), group)
        self.assertFalse(ok)
        self.assertIn("keyed by the retail address of its first datum", report)

    def test_a_dropped_function_retail_keeps_is_refused(self):
        ok, report, _records = self.verify(self.compile(DATA_SOURCE), self.group(stripped=("fixture_code",)))
        self.assertFalse(ok)
        self.assertIn("stripped function fixture_code is the retail function at 0x180000", report)

    def test_a_dropped_function_the_source_defines_is_searched_for_in_retail(self):
        obj = self.compile(DATA_SOURCE + DROPPED_FUNCTION)
        ok, report, _records = self.verify(obj, self.group())
        self.assertTrue(ok, report)
        syms, _ = verify.object_syms(str(obj))
        self.make_image(code=verify.object_section(str(obj), ".text", syms["fixture_dropped"][0]))
        ok, report, _records = self.verify(obj, self.group())
        self.assertFalse(ok)
        self.assertIn("stripped body fixture_dropped has a retail copy at 0x180000", report)

    def test_a_function_the_row_does_not_strip_is_unowned_code(self):
        ok, report, _records = self.verify(self.compile(DATA_SOURCE + DROPPED_FUNCTION), self.group(stripped=("other",)))
        self.assertFalse(ok)
        self.assertIn("unowned code", report)

    def test_the_link_places_the_verified_data(self):
        obj = self.compile(DATA_SOURCE)
        group = self.group()
        _ok, _report, records = self.verify(obj, group)
        placed = self.root / "data.o"
        verify.isolate_unit_data(str(obj), str(placed), records, group, str(self.symbols),
                                 {section: address for section, (address, *_rest) in records.data_placements.items()})
        section = ".dw4_data_%08x" % self.DATA
        self.assertEqual(verify.object_section(str(placed), section), struct.pack("<4i", 1, 2, 3, -1))


class Check(Fixture):
    """tools/check.py verifies a data-only unit from its row, alone and in a whole run."""

    def setUp(self):
        super().setUp()
        self.compile(DATA_SOURCE)
        self.group()
        compilers = [line for line in Path(verify.ROOT, "config", "SLUS-20836", "units.tsv").read_text().splitlines(True)
                     if line.startswith("@compiler\tee-gcc-2.9\t")]
        self.units = self.root / "units.tsv"
        self.units.write_text(compilers[0] + "0x%08x\t0x%08x\tlib_fixture\tee-gcc-2.9\t%s\toff\t-\twhole file\n"
                              % (self.DATA, self.DATA + 16, " ".join(FLAGS)))
        self.common = ["--elf", str(self.image), "--symbols", str(self.symbols), "--unit-objects", str(self.registry),
                       "--units", str(self.units), "--no-cache"]

    def run_check(self, *argv):
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            rc = check.main([*argv, *self.common])
        return rc, out.getvalue()

    def test_one_unit_by_its_key(self):
        rc, out = self.run_check("--function", hex(self.DATA), "--cand", str(self.root / "src" / "lib" / "fixture.c"))
        self.assertEqual(rc, 0, out)
        self.assertIn(f"MATCH data .data 0x{self.DATA:x} 16B", out)

    def test_a_whole_run_counts_its_data_apart_from_the_functions(self):
        (self.root / "asm").mkdir()
        rc, out = self.run_check("--src", str(self.root / "src"), "--asm", str(self.root / "asm"))
        self.assertEqual(rc, 0, out)
        self.assertIn("data-only: 1 units the retail linker kept the data of and no function, 1 match "
                      "(16 bytes of data; in no function count)", out)
        self.assertIn("cover : 0/1 decompiled", out)

    def test_a_missing_source_fails_the_run(self):
        (self.root / "asm").mkdir()
        os.remove(self.root / "src" / "lib" / "fixture.c")
        rc, out = self.run_check("--src", str(self.root / "src"), "--asm", str(self.root / "asm"))
        self.assertEqual(rc, 1)
        self.assertIn("data-only 0x%08x lib/fixture.c: its source" % self.DATA, out)

    def test_changed_since_checks_only_the_units_the_change_reaches(self):
        (self.root / "asm").mkdir()
        (self.root / "src" / "lib" / "fixture.h").write_text("/* the fixture's header */\n")
        (self.root / "src" / "lib" / "other.h").write_text("/* nobody includes this */\n")
        self.compile('#include "fixture.h"\n' + DATA_SOURCE)
        for header, reached in (("other.h", False), ("fixture.h", True)):
            changed = {os.path.relpath(self.root / "src" / "lib" / header, check.ROOT), "tools/check.py"}
            with mock.patch.object(check.changedunits, "changed_files", return_value=changed) as changed_files:
                rc, out = self.run_check("--src", str(self.root / "src"), "--asm", str(self.root / "asm"),
                                         "--changed-since", "main")
            changed_files.assert_called_once_with("main", check.ROOT)
            self.assertEqual(rc, 0, out)
            self.assertIn("changed: 2 files since main reach %d source files (0 functions); not followed, run the full "
                          "check for: tools/check.py" % reached, out)
            self.assertEqual("data-only: 1 units" in out, reached, out)


class Rows(Fixture):
    """tools/whole_file_rows.py measures a data-only row from the addresses other files read."""

    def measure(self, text, dropped, addresses=None):
        obj = self.compile(text)
        syms, headers, functions = whole_file_rows.text_functions(str(obj))
        retail = whole_file_rows.Retail(str(self.image))
        return whole_file_rows.data_only_row(
            str(self.root / "src" / "lib" / "fixture.c"), str(obj), syms, headers, functions, retail,
            {"fixture_table": self.DATA} if addresses is None else addresses, dropped,
            (self.CODE, self.CODE + 64), {}, {}, self.CODE + 64, src_root=str(self.root / "src"))

    def reference(self):
        return list(whole_file_rows.object_functions(str(self.compile(DATA_SOURCE + DROPPED_FUNCTION, "reference")))
                    .items())

    def test_the_row_is_measured(self):
        key, row, span = self.measure(DATA_SOURCE, self.reference())
        self.assertEqual(key, "0x%08x" % self.DATA)
        self.assertEqual(row, {"whole_file": True, "data": {"@data": "0x%08x" % self.DATA},
                               "stripped": ["fixture_dropped"], "source": "lib/fixture.c"})
        self.assertEqual(span, (self.DATA, self.DATA + 16))

    def test_no_known_datum_means_the_file_was_dropped(self):
        self.assertIsNone(self.measure(DATA_SOURCE, self.reference(), addresses={}))

    def test_the_dropped_functions_must_be_named(self):
        with self.assertRaisesRegex(SystemExit, "--reference"):
            self.measure(DATA_SOURCE, [])

    def test_a_dropped_function_with_a_retail_copy_stops_the_run(self):
        dropped = self.reference()
        self.make_image(code=dropped[0][1][0])
        with self.assertRaisesRegex(SystemExit, "fixture_dropped has a retail copy at 0x180000"):
            self.measure(DATA_SOURCE, dropped)

    def test_retail_copies_mask_the_relocated_words(self):
        raw = bytes(range(16))
        self.make_image(code=raw[:4] + b"\xff" * 4 + raw[8:])
        retail = whole_file_rows.Retail(str(self.image))
        self.assertEqual(whole_file_rows.retail_copies(raw, {4}, retail, self.CODE, self.CODE + 64), [self.CODE])
        self.assertEqual(whole_file_rows.retail_copies(raw, set(), retail, self.CODE, self.CODE + 64), [])

    def test_a_units_row_past_every_unit_goes_at_the_end(self):
        units = self.root / "units.tsv"
        units.write_text("@compiler\tx\tlocal/x\t" + "0" * 64 + "\n0x00180000\t0x00180010\tlib_code\tx\t-O2\toff\t-\twhole file\n")
        line = "0x%08x\t0x%08x\tlib_fixture\tx\t-O2\toff\t-\twhole file\n" % (self.DATA, self.DATA + 16)
        whole_file_rows.units_rows(str(units), self.DATA, self.DATA + 16, [line])
        whole_file_rows.units_rows(str(units), self.DATA, self.DATA + 16, [line])
        self.assertEqual(units.read_text().splitlines()[-2:],
                         ["0x00180000\t0x00180010\tlib_code\tx\t-O2\toff\t-\twhole file", line.rstrip("\n")])


if __name__ == "__main__":
    unittest.main()
