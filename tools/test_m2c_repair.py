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

    def test_a_declared_prototype_follows_the_definition(self):
        src = 'extern "C" {\nvoid f(int arg1);\n}\nvoid f(int arg1) {\n    g(arg1);\n}\n'
        out = m2c_batch.argument_variants(src, "")
        self.assertTrue(any("void f(int arg0, int arg1);" in x for x in out))

    def test_a_word_widened_for_a_shift_is_loaded_as_a_word(self):
        src = "void f(void *p) {\n    if (((long long) *(long long *)((char *)(p) + 4) << 0x29) == 0) {\n    }\n}\n"
        self.assertTrue(any("*(int *)((char *)(p) + 4) << 0x29" in x for x in m2c_batch.argument_variants(src, "")))

    def test_a_released_global_is_read_once(self):
        src = ("void f(void) {\n    *(int *)((char *)(D[0]) + 4) = (int)((int) (*(int *)((char *)(D[0]) + 4) - 1));\n"
               "    if (((long long) *(long long *)((char *)(D[0]) + 4) << 0x29) == 0) {\n"
               "        igObject_Destroy(D[0]);\n    }\n}\n")
        out = m2c_batch.argument_variants(src, "")
        self.assertTrue(any("void *held = (void *)D[0];" in x and "igObject_Destroy(held);" in x for x in out))

    def test_a_rotated_loop_becomes_a_while(self):
        src = "void f(int a) {\nloop_2:\n    if (a < 3) {\n        a += 1;\n        goto loop_2;\n    }\n}\n"
        self.assertEqual(m2c_batch.unrotate_loops(src), "void f(int a) {\n    while (a < 3) {\n        a += 1;\n    }\n}\n")

    def test_arguments_go_in_the_registers_retail_sets(self):
        asm = "/* 0 */ move $a3, $zero\n/* 4 */ jal g\n/* 8 */ nop\n"
        out = m2c_batch.place_arguments("void f(void) {\n    g(0);\n}\n", asm)
        self.assertIn("g(arg0, arg1, arg2, 0);", out)
        self.assertIn("void f(int arg0, int arg1, int arg2) {", out)

    def test_a_passed_through_first_argument_is_kept(self):
        asm = "/* 0 */ addiu $a1, $s1, 1\n/* 4 */ jal g\n/* 8 */ li $a2, 4\n"
        out = m2c_batch.place_arguments("void f(void *arg0) {\n    g(x + 1, 4);\n}\n", asm)
        self.assertIn("g(arg0, x + 1, 4);", out)

    def test_locals_are_reversed_for_b52(self):
        src = "void f(void) {\n    int a;\n    char *b;\n    void *c;\n\n    a = 1;\n}\n"
        self.assertEqual(m2c_batch.reverse_locals(src), "void f(void) {\n    void *c;\n    char *b;\n    int a;\n\n    a = 1;\n}\n")

    def test_an_unused_middle_parameter_comes_back(self):
        out = m2c_batch.argument_variants("void f(void *arg0, int arg2) {\n    g(arg0, arg2);\n}\n", "")
        self.assertTrue(any("void f(void *arg0, int arg1, int arg2) {" in x for x in out))

    def test_a_byte_offset_on_an_int_pointer_is_not_scaled_twice(self):
        src = "void f(int a) {\n    x = *(int *)(&D[0] + (a * 4));\n    p = (int *)(a);\n    p += 4;\n}\n"
        out = m2c_batch.argument_variants(src, "")
        self.assertTrue(any("((char *)&D[0] + (a * 4))" in x and "p += 1;" in x for x in out))

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


class TailCallDrafts(unittest.TestCase):
    @staticmethod
    def drafts(*lines):
        return m2c_batch.tail_call_drafts("f", "".join("/* 0 */ %s\n" % x for x in lines))

    def test_arguments_swapped_through_a_scratch_register(self):
        out = self.drafts("move $v0,$a0", "move $a0,$a1", "j g", "move $a1,$v0")
        self.assertTrue(any("g(arg1, arg0);" in x for x in out))

    def test_a_delay_slot_load_keeps_its_field_type(self):
        out = self.drafts("move $v0,$a0", "move $a0,$a1", "j g", "lbu $a1,12($v0)")
        self.assertTrue(any("void g(int, unsigned char);" in x for x in out))

    def test_a_short_parameter_is_narrowed_at_its_use(self):
        out = self.drafts("dsll32 $v0,$a1,0x10", "dsra32 $v0,$v0,0x10", "j g", "sw $v0,16($a0)")
        self.assertTrue(any("short arg1" in x and "= arg1;" in x for x in out))

    def test_the_fifth_integer_argument_is_a4(self):
        out = self.drafts("j g", "li $a4,1")
        self.assertTrue(any("g(arg0, arg1, arg2, arg3, 1);" in x for x in out))

    def test_a_float_constant_comes_from_its_bits(self):
        out = self.drafts("lui $v0,0x3f00", "mtc1 $v0,$f0", "j g", "mul.s $f12,$f0,$f12")
        self.assertTrue(any("g((0.5f * farg0));" in x for x in out))

    def test_a_branch_or_an_unread_register_gives_no_draft(self):
        self.assertEqual(self.drafts("beq $a0,$zero,.L1", "nop", "j g", "nop"), [])
        self.assertEqual(self.drafts("j g", "move $a0,$s0"), [])


if __name__ == "__main__":
    unittest.main()
