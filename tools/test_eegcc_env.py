#!/usr/bin/env python3
"""ee-as always runs with the heap setting that keeps its output the same on every C library (#3897)."""
import os
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import eegcc_compile


class AssemblerEnv(unittest.TestCase):
    def test_setting_is_present_and_the_environment_is_kept(self):
        with patch.dict(os.environ, {"DW4_MARK": "1"}):
            env = eegcc_compile.assembler_env()
        self.assertEqual(env["GLIBC_TUNABLES"], "glibc.cpu.hwcaps=-SSSE3:glibc.malloc.mmap_threshold=0")
        self.assertEqual(env["DW4_MARK"], "1")

    def test_the_assembler_is_run_with_it(self):
        calls = []

        class Done:
            returncode, stdout, stderr = 0, "", ""

        def run(cmd, **kwargs):
            calls.append((cmd, kwargs))
            return Done()

        with patch.object(eegcc_compile.subprocess, "run", run), patch.object(eegcc_compile, "fix_symtab_info"):
            self.assertEqual(eegcc_compile.main(["/x/ee-gcc", "-O2", "-G0", "a.c", "a.o"]), 0)
        assembler = [kwargs for cmd, kwargs in calls if cmd[0].endswith("ee-as")]
        self.assertEqual(len(assembler), 1)
        self.assertEqual(assembler[0]["env"]["GLIBC_TUNABLES"], "glibc.cpu.hwcaps=-SSSE3:glibc.malloc.mmap_threshold=0")


if __name__ == "__main__":
    unittest.main()
