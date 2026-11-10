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

    def test_a_statement_with_a_row_is_approved(self):
        path = self.write("a.c", 'void f(void) { asm("nop"); }\n')
        self.assertEqual(len(sa.approved_statements([path], {("asm", "f"): (1, "#x")})), 1)
        self.assertEqual(sa.approved_statements([path], {}), set())

    def test_a_voided_row_approves_nothing(self):
        path = self.write("a.c", 'void f(void) { asm("nop"); asm("nop"); }\n')
        self.assertEqual(sa.approved_statements([path], {("asm", "f"): (1, "#x")}), set())

    def test_hardware_is_not_an_approval(self):
        path = self.write("a.c", 'void f(void) { asm("sync"); }\n')
        self.assertEqual(sa.approved_statements([path], {("asm", "f"): (1, "#x")}), set())

    def test_an_inline_helper_needs_every_caller_approved(self):
        path = self.write("a.c", 'static inline void h(void) { asm("nop"); }\n'
                                 "void f(void) { h(); }\nvoid g(void) { h(); }\n")
        self.assertEqual(sa.approved_statements([path], {("asm", "f"): (1, "#x")}), set())
        rows = {("asm", "f"): (1, "#x"), ("asm", "g"): (1, "#x")}
        self.assertEqual(len(sa.approved_statements([path], rows)), 1)

    def test_a_helper_nothing_calls_is_not_approved(self):
        path = self.write("a.c", 'static inline void h(void) { asm("nop"); }\nvoid f(void) { }\n')
        self.assertEqual(sa.approved_statements([path], {("asm", "f"): (1, "#x")}), set())

    def test_a_header_needs_every_including_function_approved(self):
        header = self.write("h.h", 'static inline void h(void) { asm("nop"); }\n')
        one = self.write("a.c", '#include "h.h"\nvoid f(void) { h(); }\n')
        two = self.write("b.c", '#include "h.h"\nvoid g(void) { h(); }\n')
        paths = [header, one, two]
        self.assertEqual(sa.approved_statements(paths, {("asm", "f"): (1, "#x")}), set())
        rows = {("asm", "f"): (1, "#x"), ("asm", "g"): (1, "#x")}
        self.assertEqual({path for path, _start in sa.approved_statements(paths, rows)}, {header})

    def test_an_asm_function_needs_an_asm_function_row(self):
        path = self.write("a.cpp", "asm void f(void) {\n    jr ra\n    nop\n}\n")
        self.assertEqual(sa.uses(path, "f")["asm-function"], 1)
        self.assertFalse(sa.approved_asm_function(path, "f", {}))
        self.assertTrue(sa.approved_asm_function(path, "f", {("asm-function", "f"): (1, "#x")}))

    def test_an_asm_function_row_does_not_approve_c(self):
        path = self.write("a.c", "int f(int a) { return a; }\n")
        self.assertEqual(sa.uses(path, "f")["asm-function"], 0)
        self.assertFalse(sa.approved_asm_function(path, "f", {("asm-function", "f"): (1, "#x")}))

    def test_an_asm_function_is_found_without_the_pragma(self):
        path = self.write("a.cpp", "asm void f(void) {\n    nop\n}\n")
        self.assertIn("f", sa.unitprofiles.asm_body_names(path))

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

    def test_file_scope_declaration_reaches_the_functions_that_use_it(self):
        path = self.write("a.c", "struct S { volatile int v; };\nint f(struct S *s) { return s->v; }\nint g(void) { return 1; }\n")
        self.assertIn("1 volatile", sa.problem(path, "f", {}))
        self.assertIsNone(sa.problem(path, "g", {}))

    def test_a_volatile_global_reaches_only_its_users(self):
        path = self.write("a.c", "extern volatile int a;\nextern volatile int b;\nextern int c;\n"
                                 "int f(void) { return a + b; }\nint g(void) { return c; }\n"
                                 "int h(void) { return a; }\n")
        self.assertIn("2 volatile", sa.problem(path, "f", {}))
        self.assertIsNone(sa.problem(path, "g", {}))
        self.assertIn("1 volatile", sa.problem(path, "h", {}))

    def test_a_type_reached_through_another_type_counts(self):
        path = self.write("a.c", "typedef struct { volatile int n; } Q;\ntypedef struct { Q *q; } D;\n"
                                 "int f(D *d) { return d->q->n; }\nint g(void) { return 0; }\n")
        self.assertIn("1 volatile", sa.problem(path, "f", {}))
        self.assertIsNone(sa.problem(path, "g", {}))

    def test_defines_tells_a_member_from_an_emitted_copy(self):
        path = self.write("a.c", "int f(void) { return 0; }\nint g(void) { return 1; }\n")
        self.assertTrue(sa.defines(path, "g"))
        self.assertFalse(sa.defines(path, "h"))

    def test_a_shared_keyword_is_not_a_use(self):
        path = self.write("a.c", "extern volatile unsigned int a;\nunsigned int g(unsigned int x) { return x; }\n")
        self.assertIsNone(sa.problem(path, "g", {}))

    def test_a_single_function_file_follows_the_same_rule(self):
        path = self.write("a.c", "extern volatile int a;\nint g(int x) { return x; }\n")
        self.assertIsNone(sa.problem(path, "g", {}))

    def test_strings_do_not_shift_the_statements(self):
        path = self.write("a.c", 'char *s = "a;b{c";\nextern volatile int a;\nint f(void) { return a; }\n'
                                 "int g(void) { return 0; }\n")
        self.assertIn("1 volatile", sa.problem(path, "f", {}))
        self.assertIsNone(sa.problem(path, "g", {}))

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
