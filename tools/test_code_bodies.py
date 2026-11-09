"""Reviewed `start` rows and rule 6 (an unreferenced body in a gap of the code)."""
import struct
import unittest

import split
from split import CODE_HI, FILE_BASE, VADDR_BASE, add_reviewed_starts, promote_code_bodies

JR_RA, NOP, ERET = 0x03E00008, 0x00000000, 0x42000018
LW_V0 = 0x8C820008                      # lw v0,8(a0)


def image(words):
    """A zero image reaching past CODE_HI with `words` ({va: word}) written into it."""
    img = bytearray(FILE_BASE + CODE_HI + 0x100 - VADDR_BASE)
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


if __name__ == "__main__":
    unittest.main()
