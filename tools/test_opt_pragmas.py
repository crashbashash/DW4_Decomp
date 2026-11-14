#!/usr/bin/env python3
"""opt_pragma.statements: what b52 ignores is not counted, and a scoped readonly_strings is allowed by rule."""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import progress  # noqa: E402

count = progress.count_opt_pragmas


class OptPragmas(unittest.TestCase):
    def test_names_b52_ignores_are_not_counted(self):
        self.assertEqual(count("#pragma scheduling off\n#pragma opt_peephole off\n#pragma longlong_enums on\n"), 0)

    def test_code_generation_and_data_pragmas_are_counted(self):
        self.assertEqual(count("#pragma push\n#pragma schedule off\n#pragma inline_depth(0)\n"
                               "#pragma pool_strings on\n#pragma pop\n"), 3)

    def test_readonly_strings_counts_only_outside_a_closed_push(self):
        self.assertEqual(count("#pragma push\n#pragma readonly_strings on\nvoid f(void) {}\n#pragma pop\n"), 0)
        self.assertEqual(count("#pragma readonly_strings on\n"), 1)
        self.assertEqual(count("#pragma push\n#pragma readonly_strings on\nvoid f(void) {}\n"), 1)


if __name__ == "__main__":
    unittest.main()
