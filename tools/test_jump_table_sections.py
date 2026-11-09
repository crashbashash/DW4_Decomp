#!/usr/bin/env python3
"""How tools/verify.py pairs an object's .rodata sections with the recorded tables and pools."""
import os
import sys
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import verify  # noqa: E402


def headers(*sizes):
    return [(".text", (0, 0, 6, 0, 0, 16))] + [(".rodata", (0, 0, 2, 0, 0, s)) for s in sizes]


class Sections(unittest.TestCase):
    def pair(self, sizes, tables):
        with mock.patch.object(verify, "elf_section_headers", return_value=headers(*sizes)):
            return verify.jump_table_sections("x.o", tables)

    def test_a_whole_table(self):
        self.assertEqual(self.pair([12], [(0x1000, 3)]), [(1, 0x1000, 12)])

    def test_a_pool_ending_inside_its_last_word(self):
        self.assertEqual(self.pair([2], [(0x1000, 1)]), [(1, 0x1000, 2)])

    def test_a_pool_a_whole_word_short_is_refused(self):
        with self.assertRaises(ValueError):
            self.pair([4], [(0x1000, 2)])

    def test_a_section_larger_than_recorded_is_refused(self):
        with self.assertRaises(ValueError):
            self.pair([6], [(0x1000, 1)])


if __name__ == "__main__":
    unittest.main()
