"""Tests for tools/sourceapprovals.py: inline asm and volatile need the owner's approval row."""
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import sourceapprovals as sa  # noqa: E402


class SourceApprovals(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp(dir=os.path.join(sa.ROOT, "build"))

    def write(self, name, text):
        path = os.path.join(self.dir, name)
        with open(path, "w") as fh:
            fh.write(text)
        return path

    def test_plain_function_needs_nothing(self):
        path = self.write("a.c", "int f(int *p) { return *p; }\n")
        self.assertIsNone(sa.problem(path, "f", {}))

    def test_volatile_needs_a_row(self):
        path = self.write("a.c", "int f(int *p) { return *(volatile int *)p; }\n")
        self.assertIn("1 volatile", sa.problem(path, "f", {}))
        self.assertIsNone(sa.problem(path, "f", {("volatile", "f"): (1, "#x")}))

    def test_a_new_use_voids_the_row(self):
        path = self.write("a.c", "int f(int *p) { return *(volatile int *)p + *(volatile int *)p; }\n")
        self.assertIn("covers 1", sa.problem(path, "f", {("volatile", "f"): (1, "#x")}))

    def test_asm_needs_a_row_but_sync_does_not(self):
        path = self.write("a.c", 'void f(void) { asm("nop"); }\n')
        self.assertIn("1 asm", sa.problem(path, "f", {}))
        path = self.write("b.c", 'void f(void) { asm("sync"); }\n')
        self.assertIsNone(sa.problem(path, "f", {}))

    def test_comments_and_strings_do_not_count(self):
        path = self.write("a.c", '/* volatile */ char *f(void) { return "volatile"; } // asm("nop")\n')
        self.assertIsNone(sa.problem(path, "f", {}))

    def test_another_functions_use_does_not_reach(self):
        path = self.write("a.c", "int f(int *p) { return *p; }\nint g(int *p) { return *(volatile int *)p; }\n")
        self.assertIsNone(sa.problem(path, "f", {}))
        self.assertIn("volatile", sa.problem(path, "g", {}))

    def test_inline_helper_reaches_only_its_callers(self):
        path = self.write("a.c", "static inline int h(int *p) { return *(volatile int *)p; }\n"
                                 "int f(int *p) { return h(p); }\nint g(int *p) { return *p; }\n")
        self.assertIn("volatile", sa.problem(path, "f", {}))
        self.assertIsNone(sa.problem(path, "g", {}))

    def test_file_scope_declaration_reaches_every_function(self):
        path = self.write("a.c", "struct S { volatile int v; };\nint f(struct S *s) { return s->v; }\nint g(void) { return 1; }\n")
        self.assertIn("volatile", sa.problem(path, "g", {}))

    def test_project_header_counts(self):
        self.write("h.h", '#define M(x) asm("multu %1,%1" : : "d"(x))\n')
        path = self.write("a.c", '#include "h.h"\nvoid f(int x) { M(x); }\n')
        self.assertIn("1 asm", sa.problem(path, "f", {}))

    def test_table_rows_are_checked(self):
        path = self.write("t.tsv", "volatile\tf\t1\t#x\n")
        self.assertEqual(sa.load(path), {("volatile", "f"): (1, "#x")})
        for bad in ("nop\tf\t1\t#x\n", "volatile\tf\t0\t#x\n", "volatile\tf\t1\n", "volatile\tf\t1\t#x\nvolatile\tf\t1\t#y\n"):
            with self.assertRaises(ValueError):
                sa.load(self.write("t.tsv", bad))

    def test_the_shipped_table_has_no_stale_row(self):
        self.assertEqual(sa.stale(), [])


if __name__ == "__main__":
    unittest.main()
