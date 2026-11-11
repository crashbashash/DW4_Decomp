"""verify.py keeps one readelf answer per object file, and asks again when the file changes."""
import os
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import verify  # noqa: E402


class ReadelfCache(unittest.TestCase):
    def setUp(self):
        verify._READELF_CACHE.clear()
        self.tmp = tempfile.TemporaryDirectory()
        self.obj = os.path.join(self.tmp.name, "a.o")
        with open(self.obj, "wb") as fh:
            fh.write(b"one")

    def tearDown(self):
        self.tmp.cleanup()

    def _run(self):
        calls = []

        def fake(cmd, **_kw):
            calls.append(cmd)
            return mock.Mock(stdout="out%d" % len(calls))
        return calls, fake

    def test_one_read_per_file_and_flag(self):
        calls, fake = self._run()
        with mock.patch.object(verify.subprocess, "run", fake):
            self.assertEqual(verify._readelf("-rW", self.obj), "out1")
            self.assertEqual(verify._readelf("-rW", self.obj), "out1")
            self.assertEqual(verify._readelf("-sW", self.obj), "out2")
        self.assertEqual(len(calls), 2)

    def test_recompiled_object_is_read_again(self):
        calls, fake = self._run()
        with mock.patch.object(verify.subprocess, "run", fake):
            verify._readelf("-rW", self.obj)
            with open(self.obj, "wb") as fh:
                fh.write(b"recompiled")
            os.utime(self.obj, ns=(1, 1))
            self.assertEqual(verify._readelf("-rW", self.obj), "out2")


class HeaderCache(unittest.TestCase):
    def test_callers_get_their_own_list(self):
        verify._HEADER_CACHE.clear()
        with tempfile.NamedTemporaryFile() as fh, \
                mock.patch.object(verify, "_elf_section_headers", return_value=[("x", (0,))]) as parse:
            first = verify.elf_section_headers(fh.name)
            first.append("changed")
            self.assertEqual(verify.elf_section_headers(fh.name), [("x", (0,))])
            self.assertEqual(parse.call_count, 1)


if __name__ == "__main__":
    unittest.main()
