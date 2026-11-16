"""Tests for tools/dispatcher/regalloc.py: the instruction alignment (a missing delay-slot nop must not shift every later
pair into a difference) and the merge edit (the merged web keeps the lower id, as b52's coalescer does)."""
import os
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools", "dispatcher"))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import regalloc as ra  # noqa: E402


class Alignment(unittest.TestCase):
    def test_missing_nop_pairs_the_rest(self):
        ours = [("lw", "s1,0(v0)"), ("bnez", "s1,0x40"), ("lw", "s5,16(s5)"), ("move", "a0,s1"), ("jal", "0x0")]
        retail = [("lw", "s2,0(v0)"), ("bnez", "s2,0x44"), ("nop", ""), ("lw", "s5,16(s5)"), ("move", "a0,s2"),
                  ("jal", "0x2ff820")]
        self.assertEqual(ra.match_instructions(ours, retail), {0: 0, 1: 1, 2: 3, 3: 4, 4: 5})
        # a jump target is no information: only the registers differ
        self.assertEqual(ra.shape("bnez", "s1,0x40", True), ra.shape("bnez", "s1,0x44", True))
        self.assertNotEqual(ra.shape("bnez", "s1,0x40", True), ra.shape("bnez", "s2,0x40", True))


class WordReport(unittest.TestCase):
    def test_one_or_two_spaces_before_ours(self):
        # the function report prints two spaces, the emitted-unit report one
        report = "  [  0] retail 27bdff90  ours 27bdff90\n  [  1] retail 0c0f08b8 ours 0c000000\n"
        self.assertEqual(ra.parse_words(report), ([0x27bdff90, 0x0c000000], [0x27bdff90, 0x0c0f08b8]))


class Edits(unittest.TestCase):
    def test_merge_keeps_the_lower_id(self):
        adj = {2: [], 16: [], 32: [33], 33: [32], 34: []}
        merges = [(args, a2, idmap) for kind, args, a2, _c, idmap in
                  ra.candidate_edits(adj, {32: 1, 33: 1, 34: 1}, [32, 33, 34], {}, None, None) if kind == "merge"]
        self.assertEqual([m[0] for m in merges], [(32, 34), (33, 34)])        # 32 and 33 interfere: no merge
        args, a2, idmap = merges[0]
        self.assertNotIn(34, a2)
        self.assertEqual(idmap, {34: 32})


if __name__ == "__main__":
    unittest.main()
