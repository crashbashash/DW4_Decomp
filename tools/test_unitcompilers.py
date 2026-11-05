"""Compiler requirements must select exactly, or fail before compilation."""
import hashlib
import tempfile
import unittest
from pathlib import Path

import unitcompilers
import verify


class CompilerSelectionTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.compiler = self.root / "compiler.exe"
        self.compiler.write_bytes(b"compiler fixture")
        self.table = self.root / "units.tsv"
        self.digest = hashlib.sha256(self.compiler.read_bytes()).hexdigest()
        self.write_table(f"0x374cc0\tcompiler.exe\t{self.digest}\n")

    def write_table(self, text):
        self.table.write_text(text)
        unitcompilers.load.cache_clear()

    def select(self, address=0x374cc0):
        return unitcompilers.compiler_for(address, "global.exe", self.table, self.root)

    def test_selection_and_unlisted_default(self):
        self.assertEqual(self.select(), str(self.compiler))
        self.assertEqual(self.select(0x100008), "global.exe")
        self.assertEqual(unitcompilers.compiler_for(1, "global.exe",
                         self.root / "absent.tsv"), "global.exe")

    def test_missing_and_changed_executable_never_fall_back(self):
        self.select()  # Populate the digest cache, then replace the executable.
        self.compiler.write_bytes(b"different compiler fixture")
        with self.assertRaisesRegex(ValueError, "SHA-256 mismatch"):
            self.select()
        self.compiler.unlink()
        with self.assertRaisesRegex(ValueError, "required compiler missing"):
            self.select()

    def test_malformed_and_duplicate_entries_are_rejected(self):
        for row in ["broken", f"0x374cc0 ../compiler.exe {self.digest}",
                    f"0x374cc0 /compiler.exe {self.digest}",
                    "0x374cc0 compiler.exe bad",
                    (f"0x374cc0 compiler.exe {self.digest}\n" * 2)]:
            with self.subTest(row=row):
                self.write_table(row)
                with self.assertRaisesRegex(ValueError, "invalid compiler entry"):
                    self.select()

    def test_verifier_reports_requirement_failure_before_compiling(self):
        self.write_table(f"0x374cc0 compiler.exe {'0' * 64}\n")
        ok, report = verify.verify_one(0x374cc0, "absent-source.c",
                                      unit_compilers=str(self.table))
        self.assertFalse(ok)
        self.assertIn("compile failed: required compiler", report)


if __name__ == "__main__":
    unittest.main()
