"""Tests for tools/mwcc_irdump/gdb_cse_compare.py's log, on what the script recorded from the first IRO_CommonSubs call
of FUN_001c16a0's 9-word draft: the four `index << 2` shifts 93, 183, 229 and 389 are one group, yet 183 and 229 end
up in a temporary of their own. The old log listed only rejected pairs, so the four looked as if 183 and 229 had never
been compared with 93."""
import os
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools", "mwcc_irdump"))
import gdb_cse_compare as cse  # noqa: E402

SHIFT, OTHER = (3, 17), (3, 15)
# the shift group (6), a later group of the same shape (26), one of another shape (8)
SHAPES = {93: SHIFT, 183: SHIFT, 229: SHIFT, 389: SHIFT, 296: SHIFT, 318: SHIFT, 97: OTHER, 215: OTHER}
JOINS = [(93, 6), (97, 8), (183, 6), (215, 8), (229, 6), (296, 26), (318, 26), (389, 6)]
COMPARES = [(97, 6, 93), (183, 6, 93), (215, 6, 183), (215, 8, 97), (229, 6, 183), (296, 6, 229), (296, 8, 215),
            (318, 6, 229), (318, 8, 215), (318, 26, 296), (389, 6, 229)]
SHIFTS = [dict(node=93, flow=6, group=6, role=2, entry=0, sources=[], temp=0x6c23e238),
          dict(node=183, flow=12, group=6, role=2, entry=1, sources=[93, 93], temp=0x6c23e438),
          dict(node=229, flow=12, group=6, role=0, entry=0, sources=[183], temp=0),
          dict(node=389, flow=24, group=6, role=2, entry=1, sources=[93], temp=0)]


class Grouping(unittest.TestCase):
    def test_a_later_group_meets_only_the_latest_member(self):
        # 296 and 318 are compared with group 6 when 229 is its latest member: never with 93, 183 or 389
        self.assertEqual(cse.never_met(26, JOINS, SHAPES, COMPARES), [93, 183, 389])
        self.assertEqual(cse.never_met(6, JOINS, SHAPES, COMPARES), [])


class Sharing(unittest.TestCase):
    def test_a_reached_computation_with_reusers_keeps_its_own_temporary(self):
        self.assertEqual(cse.value_sets(SHIFTS), [[93, 389], [183, 229]])
        self.assertEqual(cse.apart(SHIFTS[1], SHIFTS, [], 6), ("own temporary", [93], [229]))


if __name__ == "__main__":
    unittest.main()
