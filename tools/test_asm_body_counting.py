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


if __name__ == "__main__":
    unittest.main()
