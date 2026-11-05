#!/usr/bin/env python3
"""ee-as always runs with the heap setting that keeps its output the same on every C library (#3897)."""
import os
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import eegcc_compile


class AssemblerEnv(unittest.TestCase):
    def test_setting_is_present_and_the_environment_is_kept(self):
        with patch.dict(os.environ, {"DW4_MARK": "1"}):
            env = eegcc_compile.assembler_env()
        self.assertEqual(env["GLIBC_TUNABLES"], "glibc.cpu.hwcaps=-SSSE3,-SSE2:glibc.malloc.mmap_threshold=0")
        self.assertEqual(env["DW4_MARK"], "1")

    def test_a_named_shim_is_preloaded(self):
        with tempfile.NamedTemporaryFile() as shim, patch.dict(os.environ, {"DW4_EE_AS_SHIM": shim.name}):
            self.assertEqual(eegcc_compile.assembler_env()["LD_PRELOAD"], shim.name)

    def test_a_missing_shim_stops_the_build(self):
        with patch.dict(os.environ, {"DW4_EE_AS_SHIM": "/nonexistent/shim.so"}):
            with self.assertRaises(SystemExit):
                eegcc_compile.assembler_env()

    def test_no_shim_by_default(self):
        with patch.dict(os.environ):
            os.environ.pop("DW4_EE_AS_SHIM", None)
            self.assertNotIn("LD_PRELOAD", eegcc_compile.assembler_env())

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
        self.assertEqual(assembler[0]["env"]["GLIBC_TUNABLES"], "glibc.cpu.hwcaps=-SSSE3,-SSE2:glibc.malloc.mmap_threshold=0")


if __name__ == "__main__":
    unittest.main()
