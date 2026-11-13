"""Reviewed `start` and `data` rows and rule 6 (an unreferenced body in a gap of the code)."""
import os
import struct
import tempfile
import unittest

import split
from split import (CODE_HI, FILE_BASE, VADDR_BASE, add_reviewed_starts, apply_extent_overrides,
                   check_data_rows, data_rows, drop_data_rows, load_extent_overrides,
                   promote_code_bodies, promote_data_labels, promote_framed_bodies,
                   promote_j_thunks)

JR_RA, NOP, ERET = 0x03E00008, 0x00000000, 0x42000018
LW_V0 = 0x8C820008                      # lw v0,8(a0)
ADDIU_SP_M16, ADDIU_SP_P16 = 0x27BDFFF0, 0x27BD0010
SD_RA, LD_RA = 0xFFBF0000, 0xDFBF0000
FRAMED = (ADDIU_SP_M16, SD_RA, LD_RA, JR_RA, ADDIU_SP_P16)


def image(words, hi=CODE_HI + 0x100):
    """A zero image reaching `hi` (past CODE_HI) with `words` ({va: word}) written into it."""
    img = bytearray(FILE_BASE + hi - VADDR_BASE)
    for va, w in words.items():
        struct.pack_into("<I", img, va - VADDR_BASE + FILE_BASE, w)
    return bytes(img)


class ReviewedStarts(unittest.TestCase):
    fns = [(0x200000, 16, "before", None), (0x200040, 8, "after", None)]

    def test_row_in_a_gap_is_added(self):
        img = image({0x20000c: JR_RA, 0x200020: ERET})
        out = add_reviewed_starts(self.fns, img, {0x200020: (8, None, "start")})
        self.assertEqual([f[0] for f in out], [0x200000, 0x200020, 0x200040])
        self.assertEqual(out[1][2], "FUN_00200020")

    def test_row_overlapping_a_function_is_refused(self):
        img = image({0x200008: ERET})
        with self.assertRaises(ValueError):
            add_reviewed_starts(self.fns, img, {0x200008: (8, None, "start")})

    def test_row_running_into_the_next_function_is_refused(self):
        img = image({0x200020: ERET})
        with self.assertRaises(ValueError):
            add_reviewed_starts(self.fns, img, {0x200020: (0x40, None, "start")})

    def test_row_starting_on_padding_is_refused(self):
        with self.assertRaises(ValueError):
            add_reviewed_starts(self.fns, image({}), {0x200020: (8, None, "start")})


class CodeBodies(unittest.TestCase):
    def test_unreferenced_leaf_below_code_hi_is_promoted(self):
        img = image({0x200020: JR_RA, 0x200024: LW_V0})
        fns = [(0x200000, 16, "before", None), (0x200040, 8, "after", None)]
        out, added = promote_code_bodies(fns, img, [], set())
        self.assertEqual(added, [(0x200020, 8)])
        self.assertIn((0x200020, 8, "FUN_00200020", None), out)

    def test_body_above_code_hi_is_left_alone(self):
        va = CODE_HI + 0x20
        img = image({va: JR_RA, va + 4: LW_V0})
        fns = [(0x200000, 16, "before", None)]
        _, added = promote_code_bodies(fns, img, [], set())
        self.assertEqual(added, [])

    def test_code_hi_is_the_microcode_start(self):
        self.assertEqual(split.CODE_HI, 0x467120)


class DataRows(unittest.TestCase):
    fns = [(0x200000, 16, "before", None), (0x200040, 20, "blob", None), (0x200400, 8, "after", None)]
    data = [(0x200020, 0x200100)]

    def overrides(self, text):
        fh = tempfile.NamedTemporaryFile("w", suffix=".tsv", delete=False)
        fh.write(text)
        fh.close()
        self.addCleanup(os.remove, fh.name)
        return fh.name

    def test_rows_load_and_sort(self):
        path = self.overrides("0x00200100\t16\tsecond\tdata\n0x00200020\t224\tfirst\tdata\n"
                              "0x00200000\t16\tbefore\n")
        self.assertEqual(data_rows(load_extent_overrides(path)), [(0x200020, 0x200100), (0x200100, 0x200110)])

    def test_functions_inside_a_row_are_dropped(self):
        self.assertEqual([f[2] for f in drop_data_rows(self.fns, self.data)], ["before", "after"])

    def test_apply_drops_and_returns_the_rows(self):
        path = self.overrides("0x00200020\t224\tblob_data\tdata\n")
        out, cuts, data = apply_extent_overrides(self.fns, image({}), path)
        self.assertEqual(([f[2] for f in out], cuts, data), (["before", "after"], [], self.data))

    def test_a_function_crossing_a_row_edge_fails(self):
        with self.assertRaises(ValueError):
            drop_data_rows(self.fns, [(0x200050, 0x200100)])

    def test_overlapping_rows_fail(self):
        with self.assertRaises(ValueError):
            drop_data_rows(self.fns, [(0x200020, 0x200100), (0x2000f0, 0x200200)])

    def test_a_start_row_inside_a_row_fails(self):
        path = self.overrides("0x00200020\t224\tblob_data\tdata\n0x00200080\t8\tFUN_00200080\tstart\n")
        with self.assertRaises(ValueError):
            apply_extent_overrides(self.fns, image({0x200080: ERET}), path)

    def test_a_function_left_inside_a_row_fails(self):
        with self.assertRaises(ValueError):
            check_data_rows(self.fns, self.data)

    def test_rule_5_does_not_claim_a_framed_body_inside_a_row(self):
        img = image(dict(zip(range(0x200080, 0x200094, 4), FRAMED)), split.SECTION_HI)
        fns = drop_data_rows(self.fns, self.data)
        _, added = promote_framed_bodies(fns, img, [], set())
        self.assertEqual(added, [(0x200080, 20)])
        _, added = promote_framed_bodies(fns, img, [], set(), self.data)
        self.assertEqual(added, [])

    def test_rule_6_does_not_walk_into_a_row(self):
        img = image({0x200010: LW_V0, 0x200014: LW_V0, 0x200018: LW_V0, 0x200024: JR_RA})
        fns = [(0x200000, 16, "before", None), (0x200400, 8, "after", None)]
        _, added = promote_code_bodies(fns, img, [], set())
        self.assertEqual(added, [(0x200010, 0x1c)])
        _, added = promote_code_bodies(fns, img, [], set(), self.data)
        self.assertEqual(added, [])

    def test_a_referenced_leaf_label_inside_a_row_is_left_alone(self):
        img = image({0x200080: JR_RA, 0x200084: LW_V0, 0x200300: 0x200080})
        fns = drop_data_rows(self.fns, self.data)
        self.assertEqual(promote_data_labels(fns, img, [0x200080])[1], 1)
        self.assertEqual(promote_data_labels(fns, img, [0x200080], self.data)[1], 0)

    def test_a_thunk_inside_a_row_is_left_alone(self):
        img = image({0x200080: 0x08000000 | (0x200000 >> 2)})
        fns = drop_data_rows(self.fns, self.data)
        self.assertEqual(promote_j_thunks(fns, img, {0x200080})[1], 1)
        self.assertEqual(promote_j_thunks(fns, img, {0x200080}, data=self.data)[1], 0)


if __name__ == "__main__":
    unittest.main()
