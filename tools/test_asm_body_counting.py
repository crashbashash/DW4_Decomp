"""Asm bodies link from src/ but count as neither decompiled nor matched."""
import os
import tempfile
import unittest
from unittest import mock

import progress
import unitprofiles

BODY = """#pragma optimization_level 0
/* asm-body: reason=fixture tried=fixture */
asm void FUN_00100000(void) {
    jr ra
    nop
}
"""
INLINE = """void FUN_00100010(void) {
    asm { sync }
}
"""


class AsmBodyNames(unittest.TestCase):
    def write(self, text):
        handle, path = tempfile.mkstemp(suffix=".c")
        self.addCleanup(os.unlink, path)
        with os.fdopen(handle, "w") as fh:
            fh.write(text)
        return path

    def test_definition_under_the_pragma(self):
        path = self.write(BODY)
        self.assertEqual(unitprofiles.asm_body_names(path), {"FUN_00100000"})
        self.assertTrue(progress.is_asm_body("FUN_00100000", path))

    def test_inline_statement_is_c(self):
        path = self.write(INLINE)
        self.assertEqual(unitprofiles.asm_body_names(path), frozenset())
        self.assertFalse(unitprofiles.asm_body_source(path))

    def test_no_pragma_no_body(self):
        self.assertEqual(unitprofiles.asm_body_names(self.write(BODY.split("\n", 1)[1])), frozenset())


class Categories(unittest.TestCase):
    def test_asm_body_row_is_not_fully_verified(self):
        rows = {0x100000: ("asm-body", "-"), 0x100010: ("match", "-")}
        units = [(0x100000, 8, "FUN_00100000"), (0x100010, 16, "FUN_00100010")]
        with mock.patch.object(progress, "load_categories", return_value=rows):
            result = progress.categorise(units)
        self.assertTrue(result["recorded"])
        self.assertEqual(result["fully_verified"], {"functions": 1, "bytes": 16})
        self.assertEqual(result["by"]["asm-body"], {"functions": 1, "bytes": 8})

    def test_assembly_counts_as_matched_but_not_as_the_oracle_match_count(self):
        rows = {0x100000: ("assembly", "-"), 0x100010: ("match", "-"), 0x100020: ("asm-body", "-")}
        units = [(0x100000, 32, "memcpy"), (0x100010, 16, "FUN_00100010"), (0x100020, 16, "FUN_00100020")]
        paths = {name: "src/%s" % name for _va, _size, name in units}
        with mock.patch.object(progress, "load_categories", return_value=rows), \
                mock.patch.object(progress, "load_symbols", return_value=units), \
                mock.patch.object(progress, "have_src_paths", return_value=paths), \
                mock.patch.object(progress, "readable", return_value={"names": set()}), \
                mock.patch.object(progress, "region_of", return_value="newlib"):
            table = progress.region_table()
            result = progress.categorise(units)
        self.assertIn("| newlib | 0 KB | 75.0 % | 0.0 % |", table)
        self.assertEqual(result["fully_verified"], {"functions": 1, "bytes": 16})
        self.assertEqual(result["fully_matched"], {"functions": 2, "bytes": 48})


if __name__ == "__main__":
    unittest.main()
