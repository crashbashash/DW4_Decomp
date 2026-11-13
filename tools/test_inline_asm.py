#!/usr/bin/env python3
"""What tools/inline_asm.py counts as a statement, and which ones C cannot spell."""
import os
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import inline_asm  # noqa: E402


class Statements(unittest.TestCase):
    def bodies(self, text):
        return [body for _s, _e, body in inline_asm.statements(text)]

    def test_each_spelling_is_found(self):
        text = 'void f(void) { asm { nop } __asm__ volatile ("sync"); asm("nop"); }'
        self.assertEqual(self.bodies(text), ["nop", "sync", "nop"])

    def test_a_comment_is_not_a_statement(self):
        self.assertEqual(self.bodies("/* asm { nop } */\n// asm(\"nop\");\nint x;\n"), [])

    def test_an_empty_barrier_counts(self):
        self.assertEqual(self.bodies('void f(void) { __asm__ volatile (""); }'), [""])

    def test_a_trailing_semicolon_goes_with_the_statement(self):
        start, end, _body = inline_asm.statements('asm("nop"); int x;')[0]
        self.assertEqual('asm("nop"); int x;'[start:end], 'asm("nop");')

    def test_a_temporary_split_is_not_a_source(self):
        with tempfile.TemporaryDirectory() as root:
            os.mkdir(os.path.join(root, "src"))
            for name in ("unit.c", "dw4u_123_0.c"):
                open(os.path.join(root, "src", name), "w").close()
            with mock.patch.object(inline_asm, "ROOT", root):
                found = [os.path.basename(path) for path in inline_asm.sources()]
        self.assertEqual(found, ["unit.c"])

    def test_only_sync_and_ei_have_no_c_spelling(self):
        self.assertTrue(inline_asm.is_hardware("sync"))
        self.assertTrue(inline_asm.is_hardware("ei"))
        self.assertFalse(inline_asm.is_hardware("nop"))
        self.assertFalse(inline_asm.is_hardware("dmove a0,a1"))

    def test_a_statement_of_only_sync_and_ei_has_no_c_spelling(self):
        self.assertTrue(inline_asm.is_hardware(self.bodies('__asm__ __volatile__("sync\\nei\\n");')[0]))
        self.assertFalse(inline_asm.is_hardware(self.bodies('__asm__ __volatile__("sync\\nnop\\n");')[0]))


if __name__ == "__main__":
    unittest.main()
