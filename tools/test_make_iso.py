#!/usr/bin/env python3
"""make_iso.py writes the image over the load segment of the boot file and nothing else."""
import os
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import make_iso
from extract_iso import build_test_iso


class MakeIso(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.disc = os.path.join(self.tmp.name, "disc.iso")
        self.out = os.path.join(self.tmp.name, "out", "new.iso")
        self.boot = b"H" * 16 + b"E" * 64 + b"T" * 16
        build_test_iso(self.disc, {"SYSTEM.CNF": b"BOOT2 = cdrom0:\\GAME.ELF;1\n", "GAME.ELF": self.boot})

    def test_only_the_load_segment_changes(self):
        before = open(self.disc, "rb").read()
        written = make_iso.build_iso(self.disc, self.out, b"N" * 64, "GAME.ELF", 16)
        self.assertEqual(written, b"H" * 16 + b"N" * 64 + b"T" * 16)
        self.assertEqual(open(self.disc, "rb").read(), before)
        after = open(self.out, "rb").read()
        self.assertEqual(len(after), len(before))
        self.assertEqual(sum(a != b for a, b in zip(before, after)), 64)

    def test_an_image_that_does_not_fit_is_refused(self):
        with self.assertRaises(SystemExit):
            make_iso.build_iso(self.disc, self.out, b"N" * 200, "GAME.ELF", 16)
        self.assertFalse(os.path.exists(self.out))

    def test_the_disc_is_never_the_output(self):
        with self.assertRaises(SystemExit):
            make_iso.build_iso(self.disc, self.disc, b"N" * 64, "GAME.ELF", 16)

    def test_a_disc_without_the_boot_file_is_refused(self):
        with self.assertRaises(SystemExit):
            make_iso.build_iso(self.disc, self.out, b"N" * 64, "OTHER.ELF", 16)


if __name__ == "__main__":
    unittest.main()
