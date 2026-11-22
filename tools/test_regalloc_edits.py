"""Tests for tools/dispatcher/regalloc.py: the instruction alignment (a missing delay-slot nop must not shift every later
pair into a difference), the merge edit (the merged web keeps the lower id, as b52's coalescer does), the register
constraints, the id search widened to the involved nodes' neighbours, and a candidate that defines the function as a
member."""
import json
import os
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools", "dispatcher"))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import regalloc as ra  # noqa: E402
import regalloc_sim as sim  # noqa: E402
import unitobjects  # noqa: E402


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


class Constraints(unittest.TestCase):
    def test_a_load_ties_its_base_by_colour(self):
        # FUN_001dc610's `lw v1,116(s2)`, retail `lw v1,116(s1)`: the IR lists the sorter (32, colour s2) before the
        # loaded value (68, colour v1), so mapping by position asked 68 for s1
        fin = {32: ra.REGNUM["s2"], 68: ra.REGNUM["v1"]}
        self.assertEqual(ra.tie([32, 68], ["v1", "s2"], ["v1", "s1"], [("s2", "s1")], fin), [(32, "s1")])
        self.assertEqual(ra.tie([68, 32], ["v1", "s2"], ["v1", "s1"], [("s2", "s1")], fin), [(32, "s1")])


# FUN_001dc610 before its fix (each package-list append through a helper that takes the list): the graph of the pass the
# tool replays, cut to the nodes that keep its behaviour. 32 is the sorter (a parameter), 36, 38 and 40 the three lists
# (ours s1, retail s2), 44, 45 and 46 each append's count, the rest temporaries; CALL the registers a call clobbers.
CALL = [0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 31]
EDGES = {32: CALL + [36, 37, 38, 39, 40, 41, 44, 45, 46, 73, 74, 75, 79, 80, 86, 87, 88, 92, 93, 98, 99, 100, 104, 105, 106],
         36: CALL + [37, 44, 73, 74, 75, 79], 37: CALL + [44, 73, 74, 75, 79, 80],
         38: CALL + [39, 45, 86, 87, 88, 92], 39: CALL + [45, 86, 87, 88, 92, 93],
         40: CALL + [41, 46, 98, 99, 100, 104], 41: CALL + [46, 98, 99, 100, 104, 105, 106],
         44: CALL + [73, 74, 75], 45: CALL + [86, 87, 88], 46: CALL + [98, 99, 100],
         73: [0, 2], 74: [0, 2], 75: [0, 2], 79: [0, 2, 80], 80: [0, 2], 86: [0, 2], 87: [0, 2], 88: [0, 2],
         92: [0, 2, 93], 93: [0, 2], 98: [0, 2], 99: [0, 2], 100: [0, 2], 104: [0, 2, 105], 105: [0, 2], 106: [0, 2]}
COST = {32: 19, 36: 7, 38: 7, 40: 7, 44: 4, 45: 4, 46: 4}
WANT = {32: 17, 36: 18, 37: 16, 38: 18, 39: 16, 40: 18, 41: 16, 44: 19, 45: 19, 46: 19, 73: 3, 74: 3, 75: 3, 79: 4, 80: 3,
        86: 3, 87: 3, 88: 3, 92: 4, 93: 3, 98: 3, 99: 3, 100: 3, 104: 4, 105: 3, 106: 3}
INVOLVED = [32, 36, 38, 40]


def graph():
    adj = {n: set() for n in CALL}
    for x, nbs in EDGES.items():
        adj.setdefault(x, set()).update(nbs)
        for y in nbs:
            adj.setdefault(y, set()).add(x)
    return {n: sorted(v) for n, v in adj.items()}, {n: COST.get(n, 2) for n in EDGES}


class NeighbourSearch(unittest.TestCase):
    def setUp(self):
        sim.K = 25
        self.adj, self.cost = graph()

    def test_each_count_below_its_list_is_an_edit(self):
        base, total, edits = ra.edit_search(self.adj, self.cost, WANT, INVOLVED, fixed={32})
        self.assertLess(base, total)
        full = [steps for score, steps in edits if score == total]
        self.assertEqual(full[0], [("renumber each", (((44, 36), (45, 38), (46, 40)), -1))])

    def test_the_permuted_ids_take_the_neighbours(self):
        near = ra.neighbours(self.adj, self.cost, INVOLVED)[:4]
        self.assertEqual(near[:3], [44, 45, 46])
        pool = sorted(INVOLVED + near)
        sols, _total = ra.search(self.adj, self.cost, WANT, pool)
        best = ra.rank_orders(sols, pool, {32})[0]
        self.assertEqual([n for n in best if n in (32, 36, 38, 40, 44, 45, 46)], [32, 44, 36, 45, 38, 46, 40])


class Members(unittest.TestCase):
    def test_a_member_is_found_by_its_qualified_name(self):
        names = ["FUN_001dc500", "endCompoundRenderPackage__7XSorterFv", "count__21igTDataList<P8igObject>CFv"]
        self.assertEqual(ra.member_names("XSorter::endCompoundRenderPackage", names), [names[1]])
        self.assertEqual(ra.member_names("XSorter::endCompoundRenderPackage()", names), [names[1]])
        self.assertEqual(ra.member_names("endCompoundRenderPackage__7XSorterFv", names), [names[1]])
        self.assertEqual(ra.member_names("Sorter::endCompoundRenderPackage", names), [])

    def test_the_function_is_compared_on_its_own_under_the_candidates_name(self):
        va, name, _size, _member = ra.resolve("0x1dc610")
        group = unitobjects.group_for(va, None)
        table, symbols = ra.standalone_inputs(va, name, "endCompoundRenderPackage__7XSorterFv")
        with open(table) as fh:
            self.assertNotIn(group.owner, [int(k, 0) for k in json.load(fh)])
        with open(symbols) as fh:
            self.assertIn("001dc610 000204 endCompoundRenderPackage__7XSorterFv\n", fh.read())
        self.assertTrue(os.path.exists(os.path.join(os.path.dirname(symbols), "compiler-names.tsv")))


if __name__ == "__main__":
    unittest.main()
