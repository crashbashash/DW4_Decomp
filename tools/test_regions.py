#!/usr/bin/env python3
"""check_regions.py fails on the kinds of mistake it exists to catch."""
import os
import struct
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_regions as cr  # noqa: E402
import regions  # noqa: E402

ROW = "0x%08x\t0x%08x\t%s\tlabel\tGame\t%s\tCore\t%s\thigh\tevidence\n"
JAL_LATCH = 0x0C000000 | (0x100040 >> 2)
SQ_S0 = (0x1F << 26) | (29 << 21) | (16 << 16)
SD_S0 = (0x3F << 26) | (29 << 21) | (16 << 16)


def table(*rows):
    fh = tempfile.NamedTemporaryFile("w", suffix=".tsv", delete=False)
    fh.writelines(ROW % r for r in rows)
    fh.close()
    return fh.name


def image(words):
    return lambda va: words.get(va, 0)


class Regions(unittest.TestCase):
    def test_a_gap_between_rows_fails(self):
        path = table((0x100000, 0x200000, "a", "mwcc", "-"), (0x200010, cr.IMAGE_END, "b", "mwcc", "-"))
        self.assertTrue(cr.check_tiling(regions.load(path)))

    def test_rows_that_tile_pass(self):
        path = table((0x100000, 0x200000, "a", "mwcc", "-"), (0x200000, cr.IMAGE_END, "b", "mwcc", "-"))
        self.assertEqual(cr.check_tiling(regions.load(path)), [])

    def test_a_moved_anchor_fails(self):
        path = table((0x100000, cr.IMAGE_END, "a", "mwcc", "start"))
        self.assertTrue(cr.check_anchors(regions.load(path), [(0x100010, 16, "start")]))

    def test_gcc_saves_in_an_mwcc_row_fail(self):
        path = table((0x100000, cr.IMAGE_END, "a", "mwcc", "-"))
        got = cr.check_build(regions.load(path), [(0x110000, 16, "f")], image({0x110000: SD_S0}), path)
        self.assertTrue(got)

    def test_mwcc_may_mix_sd_with_sq(self):
        path = table((0x100000, cr.IMAGE_END, "a", "mwcc", "-"))
        words = {0x110000: SD_S0, 0x110004: SQ_S0}
        self.assertEqual(cr.check_build(regions.load(path), [(0x110000, 16, "f")], image(words), path), [])

    def test_an_unaligned_function_in_an_mwcc_row_fails(self):
        path = table((0x100000, cr.IMAGE_END, "a", "mwcc", "-"))
        self.assertTrue(cr.check_build(regions.load(path), [(0x110008, 16, "f")], image({}), path))

    def test_sq_in_a_gcc_row_fails(self):
        path = table((0x100000, cr.IMAGE_END, "a", "gcc", "-"))
        got = cr.check_build(regions.load(path), [(0x110000, 16, "f")], image({0x110000: SQ_S0}), path)
        self.assertTrue(got)

    def test_a_function_in_a_data_row_fails(self):
        path = table((0x100000, cr.IMAGE_END, "a", "data", "-"))
        self.assertTrue(cr.check_build(regions.load(path), [(0x110000, 16, "f")], image({}), path))

    def test_a_registrar_outside_its_latch_row_fails(self):
        path = table((0x100000, 0x200000, "a", "mwcc", "-"), (0x200000, cr.IMAGE_END, "b", "mwcc", "-"))
        symbols = [(0x100040, 24, "ALibrary_MarkRegistered"), (0x200000, 4, "registrar")]
        self.assertTrue(cr.check_latches(symbols, image({0x200000: JAL_LATCH}), path))

    def test_a_registrar_in_its_latch_row_passes(self):
        path = table((0x100000, cr.IMAGE_END, "a", "mwcc", "-"))
        symbols = [(0x100040, 24, "ALibrary_MarkRegistered"), (0x200000, 4, "registrar")]
        self.assertEqual(cr.check_latches(symbols, image({0x200000: JAL_LATCH}), path), [])

    def test_a_class_in_the_wrong_namespace_fails(self):
        path = table((0x100000, cr.IMAGE_END, "a", "mwcc", "-"))
        self.assertTrue(cr.check_namespaces([(0x110000, 4, "igX_Register")], {"igX": "Sg"}, path))

    def test_a_class_in_its_rows_namespace_passes(self):
        path = table((0x100000, cr.IMAGE_END, "a", "mwcc", "-"))
        self.assertEqual(cr.check_namespaces([(0x110000, 4, "igX_Register")], {"igX": "Core"}, path), [])

    def test_namespace_falls_back_to_gap_alone(self):
        self.assertEqual(regions.class_namespace("igX", {}, {}), "Gap")
        self.assertEqual(regions.class_namespace("igX", {"igX": ""}, {}), "Gap")
        self.assertEqual(regions.class_namespace("igX", {"igX": "Sg"}, {}), "Gap::Sg")


if __name__ == "__main__":
    unittest.main()
