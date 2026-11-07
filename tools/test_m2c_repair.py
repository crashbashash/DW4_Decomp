#!/usr/bin/env python3
"""The draft repairs in m2c_batch.py: each turns a spelling the compilers refuse into one they take."""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m2c_batch  # noqa: E402


class Repair(unittest.TestCase):
    def test_a_loaded_word_is_called_through_a_function_pointer(self):
        out = m2c_batch.repair("    x = *(int *)((a * 4) + b)(c, d);\n")
        self.assertIn("((int (*)())*(int *)((a * 4) + b))(c, d)", out)

    def test_a_double_dereference_casts_to_a_pointer_pointer(self):
        self.assertIn("**(int **)(", m2c_batch.repair("    f(**(int *)((char *)(a) + 8));\n"))

    def test_annotations_become_c(self):
        self.assertNotIn("unaligned", m2c_batch.repair("    f((unaligned int) x);\n"))
        out = m2c_batch.repair("    return (bitwise float) ((bitwise int) x & 1);\n")
        self.assertNotIn("(bitwise ", out)
        self.assertIn("bitwise_float((", out)

    def test_a_typed_stack_slot_wins_over_its_placeholder(self):
        out = m2c_batch.repair("    int sp5C;\n    void **sp5C;\n")
        self.assertEqual(out.count("sp5C"), 1)

    def test_a_wrapper_regains_the_arguments_it_left_in_registers(self):
        out = m2c_batch.repair("void f(void) {\n    memset(0, 0x48);\n}\n")
        self.assertIn("void f(int a) {", out)
        self.assertIn("memset(a, 0, 0x48);", out)

    def test_a_blamed_comparison_casts_both_sides(self):
        src = "void f(void) {\n    if (a == b) {\n    }\n}\n"
        rep = "compile failed: 3:     if (a == b) { | illegal operand"
        self.assertIn("(int)(a) == (int)(b)", m2c_batch.repair_error(src, rep))

    def test_a_report_without_a_safe_change_gives_up(self):
        self.assertIsNone(m2c_batch.repair_error("x\n", "compile failed: 2: x | illegal use of keyword"))


if __name__ == "__main__":
    unittest.main()
