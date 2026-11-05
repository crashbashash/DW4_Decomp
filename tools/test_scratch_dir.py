#!/usr/bin/env python3
"""The tools keep their temporary files in one private folder per process, so nothing piles up in /tmp."""
import os
import re
import subprocess
import sys
import threading
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import cc

TOOLS = ("verify.py", "check.py", "linkgen.py", "automatch.py", "m2c_batch.py", "m2c_one.py")


class ScratchDir(unittest.TestCase):
    def test_one_private_folder_per_process(self):
        seen = []
        threads = [threading.Thread(target=lambda: seen.append(cc.scratch_dir())) for _ in range(8)]
        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join()
        self.assertEqual(len(set(seen)), 1)
        self.assertTrue(os.path.isdir(seen[0]))

    def test_folder_and_contents_go_when_the_process_exits(self):
        code = ("import cc, os; d = cc.scratch_dir(); open(os.path.join(d, 'left.o'), 'w').close(); print(d)")
        folder = subprocess.run([sys.executable, "-c", code], cwd=HERE, capture_output=True, text=True,
                                check=True).stdout.strip()
        self.assertTrue(folder)
        self.assertFalse(os.path.exists(folder))

    def test_no_tool_writes_straight_to_tmp(self):
        for name in TOOLS:
            with open(os.path.join(HERE, name), encoding="utf-8") as handle:
                self.assertIsNone(re.search(r"""["']/tmp/""", handle.read()), name)


if __name__ == "__main__":
    unittest.main()
