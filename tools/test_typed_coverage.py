#!/usr/bin/env python3
"""What tools/typed_coverage.py attributes to a class."""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import typed_coverage as tc  # noqa: E402


class TemplateArguments(unittest.TestCase):
    def test_a_parameter_resolves_to_what_the_file_instantiates(self):
        text = "template <class T> struct Holder { T *p; };\nHolder<igProbe> held(0);\n"
        self.assertEqual(tc.template_arguments(text), {"T": ["igProbe"]})

    def test_struct_keyword_and_pointer_are_ignored(self):
        text = "template <class T> struct Holder { T *p; };\nHolder<struct igProbe *> held(0);\n"
        self.assertEqual(tc.template_arguments(text), {"T": ["igProbe"]})

    def test_the_template_itself_is_not_an_argument(self):
        text = "template <class T> struct Holder { Holder(const Holder<T> &o); T *p; };\n"
        self.assertEqual(tc.template_arguments(text), {"T": []})

    def test_a_file_without_templates_has_none(self):
        self.assertEqual(tc.template_arguments("struct S { int a; };\n"), {})


if __name__ == "__main__":
    unittest.main()
