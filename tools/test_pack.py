import os
import subprocess
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCRIPT = os.path.join(ROOT, "tools", "pack.py")


class PackTest(unittest.TestCase):
    def run_pack(self, function, *extra):
        with tempfile.TemporaryDirectory() as out:
            r = subprocess.run([sys.executable, SCRIPT, "--function", function, "--out", out, *extra],
                               cwd=ROOT, capture_output=True, text=True)
            self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
            with open(os.path.join(out, "pack.md")) as fh:
                md = fh.read()
            with open(os.path.join(out, "pack.c")) as fh:
                return md, fh.read()

    def test_target_kept_others_elided(self):
        # src/cri/sjcrs.c holds six small matched functions in one unit
        md, c = self.run_pack("SJCRS_Lock", "--keep", "0")
        self.assertIn("{\n    SVM_Lock();\n}", c)
        self.assertNotIn("SVM_Unlock();\n}", c)
        self.assertEqual(c.count("body elided"), 5)
        self.assertIn("{ /* body elided: 20 B, MATCH */ }", c)
        self.assertIn("- function: `SJCRS_Lock` at 0x0027b2b0, 20 B", md)
        self.assertIn("- source: `src/cri/sjcrs.c`", md)

    def test_neighbours_kept(self):
        _md, c = self.run_pack("SJCRS_Lock", "--keep", "1")
        self.assertIn("SVM_Unlock();\n}", c)
        self.assertEqual(c.count("body elided"), 3)

    def test_notes_and_near_misses_optional(self):
        with tempfile.TemporaryDirectory() as notes:
            with open(os.path.join(notes, "SJCRS_Lock.md"), "w") as fh:
                fh.write("note\n")
            tsv = os.path.join(notes, "nm.tsv")
            with open(tsv, "w") as fh:
                fh.write("id\tname\taddr\tdiff\nr1\tSJCRS_Lock\t0x0027b2b0\t2\n")
            md, _c = self.run_pack("SJCRS_Lock", "--notes-dir", notes, "--near-misses", tsv)
            self.assertIn("SJCRS_Lock.md", md)
            self.assertIn("  - diff: 2", md)
        md, _c = self.run_pack("SJCRS_Lock")
        self.assertNotIn("note file", md)
        self.assertNotIn("near-miss", md)


if __name__ == "__main__":
    unittest.main()
