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


class ArgumentVariants(unittest.TestCase):
    def test_an_unused_first_parameter_comes_back(self):
        out = m2c_batch.argument_variants("int f(int arg1, int arg2) {\n    return g(arg1, arg2);\n}\n", "")
        self.assertTrue(any("int f(int arg0, int arg1, int arg2) {" in x for x in out))

    def test_a_value_left_in_a_register_reaches_the_callee(self):
        out = m2c_batch.argument_variants("void f(void) {\n    g(0xFF);\n}\n", "")
        self.assertTrue(any("void f(int p0) {" in x and "g(p0, 0xFF);" in x for x in out))

    def test_a_tail_call_keeps_its_delay_slot_argument(self):
        asm = "/* 0 */ j g\n/* 4 */ lw $a0, 52($a0)\n"
        out = m2c_batch.argument_variants("void f(void) {\n    g();\n}\n", asm)
        self.assertTrue(any("g(*(int *)((char *)arg0 + 52));" in x and "void *arg0" in x for x in out))

    def test_a_word_stored_narrower_is_loaded_whole(self):
        src = "void f(void *a) {\n    *(short *)a = (short) *(short *)((char *)a + 4);\n}\n"
        self.assertTrue(any("(short) *(int *)" in x for x in m2c_batch.argument_variants(src, "")))


if __name__ == "__main__":
    unittest.main()
