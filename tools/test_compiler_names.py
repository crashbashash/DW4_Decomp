#!/usr/bin/env python3
"""tools/compiler_names.py: the compiler-name map, and the readers that resolve through it."""
import io
import json
import os
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import compiler_names  # noqa: E402
import unitobjects  # noqa: E402
import verify  # noqa: E402
import whole_file_rows  # noqa: E402

GUI, INSIGHT, VIEWER = 0x44b860, 0x230f50, 0x458680
ROWS = {
    # the defining unit places the members under their compiler names
    "0x%08x" % GUI: {"whole_file": True, "emitted": {
        "arkRegisterInternal__10igRendererFv": "0x0044c770",
        "setVisualContext__10igRendererFP15igVisualContext": "0x00457ca0"},
        "data": {"_Meta__10igRenderer": "0x0058c208", "g_plain": "0x0058c300"},
        "duplicates": {"getClassMeta__10igRendererFv": "0x00231010"}},
    "0x%08x" % INSIGHT: {"whole_file": True, "symbol": "markRegistered__14InsightLibraryFv",
                         "emitted": {"getClassMeta__10igRendererFv": "0x00231010",
                                     "__dt__6HolderFv": "0x00231100", "plain_member": "0x00231200"},
                         # an externals row that agrees with the map is redundant, not a conflict
                         "externals": {"setVisualContext__10igRendererFP15igVisualContext": "0x00457ca0"}},
    # a file-local helper class of the same name is another function: the name stays per unit
    "0x%08x" % VIEWER: {"whole_file": True, "emitted": {"__dt__6HolderFv": "0x00458700"}},
}
SYMBOLS = {0x44b860: "GuiLibrary_MarkRegistered", 0x44c770: "igRenderer_Register",
           0x457ca0: "igRenderer_SetVisualContext", 0x230f50: "InsightLibrary_MarkRegistered",
           0x231010: "FUN_00231010", 0x231100: "Holder_Destroy", 0x231200: "plain_member",
           0x458680: "ViewerLibrary_MarkRegistered", 0x458700: "Holder2_Destroy"}
DATA_NAMES = {"g_igRenderer_metaObject": 0x58c208}


def groups(rows=ROWS):
    with tempfile.TemporaryDirectory() as d:
        path = os.path.join(d, "unit-objects.json")
        Path(path).write_text(json.dumps(rows))
        unitobjects.load.cache_clear()
        try:
            return unitobjects.load(path)
        finally:
            unitobjects.load.cache_clear()


class Build(unittest.TestCase):
    def rows(self):
        return compiler_names.build(groups(), {va: (name, 16) for va, name in SYMBOLS.items()}, DATA_NAMES)

    def test_each_unambiguous_compiler_name_binds_its_retail_name(self):
        self.assertEqual(self.rows(), [
            # a C++ owner's `symbol` binds the owner's address
            ("markRegistered__14InsightLibraryFv", 0x230f50, "InsightLibrary_MarkRegistered"),
            ("getClassMeta__10igRendererFv", 0x231010, "FUN_00231010"),
            ("arkRegisterInternal__10igRendererFv", 0x44c770, "igRenderer_Register"),
            ("setVisualContext__10igRendererFP15igVisualContext", 0x457ca0, "igRenderer_SetVisualContext"),
            ("_Meta__10igRenderer", 0x58c208, "g_igRenderer_metaObject"),
        ])

    def test_left_out(self):
        names = {row[0] for row in self.rows()}
        self.assertNotIn("__dt__6HolderFv", names)          # two units bind it to two functions
        self.assertNotIn("plain_member", names)             # symbols.txt holds it
        self.assertNotIn("g_plain", names)                  # not a compiler name

    def test_a_datum_without_a_recorded_name(self):
        rows = compiler_names.build(groups(), {va: (name, 16) for va, name in SYMBOLS.items()}, {})
        self.assertIn(("_Meta__10igRenderer", 0x58c208, "DAT_0058c208"), rows)

    def test_the_table_reads_back(self):
        text = compiler_names.render(self.rows())
        self.assertTrue(text.startswith("# compiler name"))
        self.assertEqual(compiler_names._parse(text, "map"),
                         {name: (va, retail) for name, va, retail in self.rows()})
        with self.assertRaises(ValueError):
            compiler_names._parse(text + "getClassMeta__10igRendererFv\t0x1\tx\n", "map")


class Command(unittest.TestCase):
    """--write writes the map beside symbols.txt and --check fails once the rows change."""

    def test_write_then_check(self):
        with tempfile.TemporaryDirectory() as d:
            symbols = os.path.join(d, "symbols.txt")
            Path(symbols).write_text("".join("%08x 000010 %s\n" % kv for kv in sorted(SYMBOLS.items())))
            Path(d, "data-names.tsv").write_text("0x0058c208\tg_igRenderer_metaObject\tglobal\n")
            rows = os.path.join(d, "unit-objects.json")
            Path(rows).write_text(json.dumps(ROWS))
            args = ["--symbols", symbols, "--unit-objects", rows]
            self.addCleanup(unitobjects.load.cache_clear)
            out = io.StringIO()
            with redirect_stdout(out), redirect_stderr(io.StringIO()):
                self.assertEqual(compiler_names.main(args + ["--check"]), 1)
                self.assertEqual(compiler_names.main(args + ["--write"]), 0)
                self.assertEqual(compiler_names.main(args + ["--check"]), 0)
            self.assertEqual(compiler_names.load(symbols)["arkRegisterInternal__10igRendererFv"],
                             (0x44c770, "igRenderer_Register"))
            changed = json.loads(json.dumps(ROWS))
            changed["0x%08x" % GUI]["emitted"]["arkRegisterInternal__10igRendererFv"] = "0x0044c780"
            Path(rows).write_text(json.dumps(changed))
            unitobjects.load.cache_clear()
            with redirect_stdout(io.StringIO()), redirect_stderr(io.StringIO()):
                self.assertEqual(compiler_names.main(args + ["--check"]), 1)

    def test_the_tree_map_is_current(self):
        unitobjects.load.cache_clear()
        self.addCleanup(unitobjects.load.cache_clear)
        with open(compiler_names.table_path()) as fh:
            self.assertEqual(fh.read(), compiler_names.generate())


class Resolvers(unittest.TestCase):
    MAP = {"arkRegisterInternal__10igRendererFv": (0x44c770, "igRenderer_Register"),
           "_Meta__10igRenderer": (0x58c208, "g_igRenderer_metaObject")}

    def test_sym_address_resolves_a_mapped_compiler_name(self):
        by_name, _ = verify.load_symbols(os.path.join(verify.ROOT, "config/SLUS-20836/symbols.txt"))
        with mock.patch.object(compiler_names, "load", return_value=self.MAP):
            self.assertEqual(verify.sym_address("arkRegisterInternal__10igRendererFv", by_name), 0x44c770)
            self.assertIsNone(verify.sym_address("arkRegister__10igRendererFv", by_name))

    def test_mapped_references_are_the_undefined_ones_the_rows_leave(self):
        syms = {"arkRegisterInternal__10igRendererFv": ("UND", 0, 0), "_Meta__10igRenderer": ("UND", 0, 0),
                "getClassMeta__10igRendererFv": (5, 0, 12), "other__Fv": ("UND", 0, 0)}
        with mock.patch.object(compiler_names, "load", return_value=self.MAP):
            self.assertEqual(verify.mapped_references(syms, "config/SLUS-20836/symbols.txt",
                                                      {"_Meta__10igRenderer": "DAT_0058c208"}),
                             {"arkRegisterInternal__10igRendererFv": 0x44c770})
        self.assertEqual(verify.retail_label(0x44c770, {0x44c770: ("igRenderer_Register", 112)}),
                         "igRenderer_Register")
        self.assertEqual(verify.retail_label(0x58c208, {}), "DAT_0058c208")


class RowWriter(unittest.TestCase):
    """whole_file_rows --cxx writes no row for a reference the map binds."""
    MAP = Resolvers.MAP

    def test_mapped_externals_and_undefined_data_go(self):
        syms = {"_Meta__10igRenderer": ("UND", 0, 0), "k_visualContext__10igRenderer": (7, 0, 4)}
        externals = {"arkRegisterInternal__10igRendererFv": 0x44c770, "lua_call__FP9lua_Stateii": 0x2a0000}
        data = {"_Meta__10igRenderer": 0x58c208, "k_visualContext__10igRenderer": 0x58c210, "g_x": 0x58c400}
        self.assertEqual(whole_file_rows.unmapped(externals, data, syms, self.MAP, "unit.o"),
                         ({"lua_call__FP9lua_Stateii": 0x2a0000},
                          {"k_visualContext__10igRenderer": 0x58c210, "g_x": 0x58c400}))

    def test_a_defined_datum_keeps_its_row(self):
        syms = {"_Meta__10igRenderer": (7, 0, 4)}
        self.assertEqual(whole_file_rows.unmapped({}, {"_Meta__10igRenderer": 0x58c208}, syms, self.MAP, "u.o")[1],
                         {"_Meta__10igRenderer": 0x58c208})

    def test_a_reference_the_map_places_elsewhere_stops_the_run(self):
        with self.assertRaises(SystemExit):
            whole_file_rows.unmapped({"arkRegisterInternal__10igRendererFv": 0x44c780}, {}, {}, self.MAP, "unit.o")

    def test_unit_row_and_source(self):
        with tempfile.TemporaryDirectory() as d:
            units = os.path.join(d, "units.tsv")
            Path(units).write_text("# header\n@compiler\tb52\tlocal/x.exe\n"
                                   "0x00100000\t0x00100100\tlib_Front\tb52\t-O4,p\toff\t-\twhole file\n"
                                   "0x00100100\t0x00100200\tlib_Single\tb52\t-O4,s\ton\t-\tfunction\n")
            self.assertEqual(whole_file_rows.unit_row(units, 0x100040),
                             (0x100000, 0x100100, "lib_Front", "b52", "-O4,p", "off"))
            with self.assertRaises(SystemExit):
                whole_file_rows.unit_row(units, 0x100140)
            with self.assertRaises(SystemExit):
                whole_file_rows.unit_row(units, 0x300000)
            src = Path(d, "src")
            (src / "a").mkdir(parents=True)
            (src / "a" / "Front.cpp").write_text("")
            (src / "a" / "ont.cpp").write_text("")
            self.assertEqual(whole_file_rows.unit_source("lib_Front", str(src)), str(src / "a" / "Front.cpp"))
            with self.assertRaises(SystemExit):
                whole_file_rows.unit_source("lib_Missing", str(src))


if __name__ == "__main__":
    unittest.main()
