import os
import subprocess
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCRIPT = os.path.join(ROOT, "tools", "region_board.py")
SOURCE = os.path.join(ROOT, "src", "libgcc", "divdi3.c")
ARGS = ["--unit-va", "0x22e4b8", "--function", "__divdi3"]
LAST_IF = "    if (c)\n"


def toolchain_present():
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    try:
        import check
        import unitprofiles
    finally:
        sys.path.pop(0)
    if not os.path.exists(os.environ.get("DW4_ELF", os.path.join(ROOT, check.ELF_DEFAULT))):
        return False
    table = unitprofiles.load()
    unit = unitprofiles.unit_for(0x22e4b8, table)
    exe = table.compilers[unit.compiler][0]
    return os.path.exists(os.path.join(ROOT, exe))


@unittest.skipUnless(os.path.exists(SOURCE) and toolchain_present(), "needs the retail ELF and the compiler")
class RegionBoardTest(unittest.TestCase):
    def run_board(self, cand, *extra):
        r = subprocess.run([sys.executable, SCRIPT, *ARGS, "--cand", cand, *extra],
                           cwd=ROOT, capture_output=True, text=True)
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        return r.stdout

    def test_matched_function_all_exact(self):
        out = self.run_board(SOURCE)
        self.assertEqual(out.count("EXACT"), 8)  # seven regions and the total line
        self.assertIn("total: 0/421 words differ, 7/7 regions EXACT", out)

    def test_changed_branch_flags_one_region(self):
        with open(SOURCE) as fh:
            text = fh.read()
        self.assertIn(LAST_IF, text)
        with tempfile.TemporaryDirectory() as tmp:
            cand = os.path.join(tmp, "divdi3.c")
            with open(cand, "w") as fh:
                fh.write(text.replace(LAST_IF, "    if (!c)\n"))
            out = self.run_board(cand)
        self.assertEqual(out.count("EXACT"), 7)  # six regions and the total line
        self.assertIn("R6   0x600-0x693  1/37 words differ", out)
        self.assertIn("total: 1/421 words differ, 6/7 regions EXACT", out)

    def test_record_and_show(self):
        with tempfile.TemporaryDirectory() as board:
            out = self.run_board(SOURCE, "--record", "t", "--board-dir", board)
            self.assertIn("record: improved", out)
            self.assertTrue(os.path.exists(os.path.join(board, "__divdi3", "board.json")))
            shown = subprocess.run([sys.executable, SCRIPT, "--show", "__divdi3", "--board-dir", board],
                                   cwd=ROOT, capture_output=True, text=True).stdout
            self.assertEqual(shown.count("EXACT"), 7)


if __name__ == "__main__":
    unittest.main()
