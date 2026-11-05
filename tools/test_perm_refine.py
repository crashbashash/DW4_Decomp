#!/usr/bin/env python3
"""Tests for tools/perm_refine.py: the facts read from a listing, the guard and the merge mechanics.
No compiler, permuter or game file is needed."""
import collections
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import perm_refine as pr

LISTING = """
build/x.o:     file format elf32-tradlittlemips

Disassembly of section .text:

00000000 <helper>:
   0:	03e00008 	jr	ra
   4:	00000000 	nop

00000008 <Subject>:
   8:	27bdfff0 	addiu	sp,sp,-16
   c:	ffbf0000 	sd	ra,0(sp)
  10:	0c000000 	jal	0 <helper>
			10: R_MIPS_26	Callee_One
  14:	ac850004 	sw	a1,4(a0)
  18:	10400003 	beqz	v0,28 <Subject+0x20>
  1c:	00000000 	nop
  20:	0c000000 	jal	0 <helper>
			20: R_MIPS_26	Callee_Two
  24:	a0800008 	sb	zero,8(a0)
  28:	dfbf0000 	ld	ra,0(sp)
  2c:	03e00008 	jr	ra
  30:	27bd0010 	addiu	sp,sp,16
"""


def facts(tokens, calls=(), stores=0):
    return pr.Facts(list(tokens), collections.Counter(calls), stores)


class Listing(unittest.TestCase):
    def test_only_the_named_function_is_read(self):
        got = pr.parse_listing(LISTING, "Subject")
        self.assertEqual(len(got.tokens), 11)
        self.assertEqual(got.calls, collections.Counter({"Callee_One": 1, "Callee_Two": 1}))

    def test_stores_to_the_stack_do_not_count(self):
        self.assertEqual(pr.parse_listing(LISTING, "Subject").stores, 2)      # sw 4(a0), sb 8(a0); not sd 0(sp)

    def test_a_call_is_compared_by_symbol_and_a_branch_without_its_address(self):
        tokens = pr.parse_listing(LISTING, "Subject").tokens
        self.assertIn("jal R_MIPS_26:Callee_One", tokens)
        self.assertIn("beqz v0,@", tokens)

    def test_a_missing_function_has_no_facts(self):
        self.assertEqual(pr.parse_listing(LISTING, "Absent").tokens, [])


class Guard(unittest.TestCase):
    target = facts(["a"] * 20, ["f", "g"], stores=4)
    base = facts(["a"] * 22, ["f", "g"], stores=3)

    def test_keeping_everything_is_acceptable(self):
        self.assertEqual(pr.loses_code(facts(["a"] * 21, ["f", "g"], 3), self.base, self.target), "")

    def test_dropping_a_call_the_target_makes_is_refused(self):
        self.assertIn("call", pr.loses_code(facts(["a"] * 21, ["f"], 3), self.base, self.target))

    def test_dropping_a_store_is_refused(self):
        self.assertIn("stores", pr.loses_code(facts(["a"] * 21, ["f", "g"], 2), self.base, self.target))

    def test_a_base_that_already_lacks_something_is_not_held_to_it(self):
        weak = facts(["a"] * 22, ["f"], stores=3)
        self.assertEqual(pr.loses_code(facts(["a"] * 21, ["f"], 3), weak, self.target), "")

    def test_shrinking_far_below_the_target_is_refused(self):
        self.assertIn("shrinks", pr.loses_code(facts(["a"] * 12, ["f", "g"], 4), self.base, self.target))

    def test_difference_is_zero_only_for_the_same_sequence(self):
        self.assertEqual(pr.difference(facts(["a", "b", "c"]), facts(["a", "b", "c"])), 0)
        self.assertEqual(pr.difference(facts(["a", "x", "c"]), facts(["a", "b", "c"])), 1)
        self.assertEqual(pr.difference(facts(["a", "c"]), facts(["a", "b", "c"])), 1)


class Merge(unittest.TestCase):
    base = ["int f(int a) {", "    int x = a;", "    x += 1;", "    g(x);", "    return x;", "}"]

    def test_each_edit_is_found_and_applies_alone(self):
        other = list(self.base)
        other[1] = "    int x = a + 0;"
        other[4] = "    return x + 0;"
        found = pr.changes_between(self.base, other, max_lines=3)
        self.assertEqual(len(found), 2)
        self.assertEqual(pr.apply_changes(self.base, found), other)
        self.assertEqual(pr.apply_changes(self.base, found[:1])[4], "    return x;")

    def test_a_long_rewrite_is_left_out(self):
        other = [self.base[0]] + ["    /* %d */" % i for i in range(8)] + [self.base[-1]]
        self.assertEqual(pr.changes_between(self.base, other, max_lines=3), [])

    def test_edits_that_touch_the_same_lines_do_not_stack(self):
        first = pr.Change(1, 3, ("    int x = a + 1;",))
        self.assertTrue(pr.overlaps(pr.Change(2, 3, ("    x++;",)), [first]))
        self.assertFalse(pr.overlaps(pr.Change(4, 5, ("    return x + 0;",)), [first]))
        self.assertTrue(pr.overlaps(pr.Change(3, 3, ("    h();",)), [pr.Change(3, 3, ("    k();",))]))


if __name__ == "__main__":
    unittest.main()
