"""Tests for tools/asmsources.py: an assembly source in src/ needs the owner's approval row."""
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import asmsources  # noqa: E402
import units  # noqa: E402

TWO = """\t.set\tnoreorder
/* first */
\t.globl\tone
one:
\tjr\t$31
\tnop
/* second, with a .globl in a comment: .globl one */
\t.globl\ttwo
two:
\tjr\t$31
\tnop
"""


class AssemblySources(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp()
        self.src = os.path.join(self.dir, "src")
        os.makedirs(self.src)
        self.path = os.path.join(self.src, "pair.S")
        open(self.path, "w").write(TWO)

    def test_definitions(self):
        self.assertEqual(asmsources.definitions(TWO), ["one", "two"])

    def test_unapproved_file_is_refused(self):
        with self.assertRaisesRegex(ValueError, "does not approve"):
            asmsources.approved_definitions(self.path, root=self.dir, table={})

    def test_row_for_another_file_is_refused(self):
        table = {"one": ("src/other.S", "#x"), "two": ("src/pair.S", "#x")}
        with self.assertRaisesRegex(ValueError, "approved .* for src/other.S"):
            asmsources.approved_definitions(self.path, root=self.dir, table=table)

    def test_approved_file(self):
        table = {"one": ("src/pair.S", "#x"), "two": ("src/pair.S", "#x")}
        self.assertEqual(asmsources.approved_definitions(self.path, root=self.dir, table=table), ["one", "two"])

    def test_extract_keeps_one_function_and_the_lines(self):
        out = asmsources.extract(TWO, "two")
        self.assertEqual(out.count("\n"), TWO.count("\n"))
        self.assertEqual(asmsources.definitions(out), ["two"])
        self.assertIn(".set\tnoreorder", out)

    def test_table_rows(self):
        table = os.path.join(self.dir, "t.tsv")
        open(table, "w").write("# comment\none\tsrc/pair.S\t#evidence\n")
        self.assertEqual(asmsources.load(table), {"one": ("src/pair.S", "#evidence")})
        open(table, "a").write("one\tsrc/pair.S\t#again\n")
        with self.assertRaisesRegex(ValueError, "listed twice"):
            asmsources.load(table)

    def test_scan_refuses_unapproved(self):
        with self.assertRaisesRegex(ValueError, "does not approve"):
            units.scan(self.src)


if __name__ == "__main__":
    unittest.main()
