#!/usr/bin/env python3
"""Tests for tools/kpatch.py: the table, the patch source directory and its place outside the censuses."""
import os
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import kpatch  # noqa: E402
import srctree  # noqa: E402
import units  # noqa: E402


class TableTest(unittest.TestCase):
    def test_rows(self):
        rows = kpatch.parse("# comment\n"
                            "tlbsrc\tsrc/sony/libkernl/kpatch/tlbsrc.c\t0x80075000\towner\t-\ttlbsrc\t816\n"
                            "eenull\t-\t0x00082000\towner\tee-gcc-2.9-as210\teenull\t40\n")
        self.assertEqual(rows[0].sources, ("src/sony/libkernl/kpatch/tlbsrc.c",))
        self.assertEqual((rows[0].run, rows[0].size), (0x80075000, 816))
        self.assertEqual(rows[1].sources, ())
        self.assertEqual((rows[0].compiler, rows[1].compiler), (None, "ee-gcc-2.9-as210"))

    def test_source_outside_the_patch_directory(self):
        with self.assertRaises(ValueError):
            kpatch.parse("tlbsrc\tsrc/sony/libkernl/tlbfunc.c\t0x80075000\towner\t-\ttlbsrc\t816\n")

    def test_repeated_name(self):
        row = "tlbsrc\t-\t0x80075000\towner\t-\ttlbsrc\t816\n"
        with self.assertRaises(ValueError):
            kpatch.parse(row + row)

    def test_committed_table(self):
        names = [p.name for p in kpatch.load()]
        self.assertEqual(sorted(names), ["eenull", "osdsrc", "srcfile", "tlbsrc"])

    def test_sourceless_row_does_not_build(self):
        with self.assertRaises(ValueError):
            kpatch.build(kpatch.Patch("eenull", (), 0x82000, "owner", None, "eenull", 40))


class CensusTest(unittest.TestCase):
    def test_patch_sources_are_not_units(self):
        index = units.scan(os.path.join(kpatch.ROOT, "src"))
        self.assertNotIn("kPutTLBEntry", index)
        self.assertFalse(any(kpatch.is_patch_source(p) for p in index.values()))
        self.assertFalse(any(kpatch.is_patch_source(p) for p in srctree.index(os.path.join(kpatch.ROOT, "src")).values()))

    def test_functions_keyed_apart_when_patches_share_a_name(self):
        with tempfile.TemporaryDirectory(dir=kpatch.PATCH_DIR) as tmp:
            for name in ("a", "b"):
                with open(os.path.join(tmp, name + ".c"), "w") as fh:
                    fh.write("int kGetEntryAddress(int n)\n{\n    return n;\n}\nint only_%s(void)\n{\n    return 0;\n}\n" % name)
            rel = os.path.relpath(tmp, kpatch.ROOT)
            patches = [kpatch.Patch(name, (os.path.join(rel, name + ".c"),), 0, "owner", None, name, 0)
                       for name in ("a", "b")]
            found = kpatch.functions(patches)
        self.assertEqual(sorted(found), ["kGetEntryAddress_a", "kGetEntryAddress_b", "only_a", "only_b"])
        self.assertEqual(found["kGetEntryAddress_b"][1], "kGetEntryAddress")


class IncludeTest(unittest.TestCase):
    def test_source_without_a_patch(self):
        with tempfile.NamedTemporaryFile("w", suffix=".c") as fh:
            fh.write('#include "other.inc"\nint x;\n')
            fh.flush()
            self.assertIsNone(kpatch.include_dir_for(fh.name))


if __name__ == "__main__":
    unittest.main()
