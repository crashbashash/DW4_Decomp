#!/usr/bin/env python3
"""What tools/typed_coverage.py attributes to a class."""
import json
import os
import sys
import tempfile
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


class MemberFunctions(unittest.TestCase):
    def test_a_member_head_is_a_function_of_its_class(self):
        text = ("int igFoo_Get(igFoo *self) {\n    return self->_n;\n}\n"
                "void igRenderer::setVisualContext(igVisualContext *context) {\n    _visualContext = context;\n}\n"
                "igMetaObject *Gap::Gui::igRenderer::getMeta() const {\n    return _Meta;\n}\n")
        names = [n for n, _args, _s, _e in tc.split_functions(text)]
        self.assertEqual(names, ["igFoo_Get", "igRenderer::setVisualContext", "Gap::Gui::igRenderer::getMeta"])
        self.assertEqual([tc.class_of(n) for n in names], ["igFoo", "igRenderer", "igRenderer"])

    def test_locals_and_parameters_hide_fields(self):
        body = "{\n    int _count = 1;\n    igVisualContext *old;\n    return _count;\n}\n"
        self.assertEqual(tc.local_names("igVisualContext *context, int n", body), {"context", "n", "_count", "old"})
        self.assertNotIn("_count", tc.local_names("void", "{\n    return _count;\n}\n"))

    def test_bare_field_reads_in_a_member_are_recovered(self):
        with tempfile.TemporaryDirectory() as tree:
            os.makedirs(os.path.join(tree, "data"))
            os.makedirs(os.path.join(tree, "src", "gui"))
            with open(os.path.join(tree, "data", "reflection.json"), "w") as fh:
                json.dump({"classes": {"0x1": {"class": "igRenderer", "fields": [
                    {"offset": 8, "name": "_visualContext", "type": "igObjectRefMetaField"}]}}}, fh)
            with open(os.path.join(tree, "src", "gui", "r.cpp"), "w") as fh:
                fh.write("void igRenderer::setVisualContext(igVisualContext *context) {\n"
                         "    if (_visualContext != context)\n        _visualContext = context;\n"
                         "    other->_visualContext = 0;\n}\n"
                         "void igRenderer::hide(int _visualContext) {\n    _visualContext = 0;\n"
                         "    this->_visualContext = 0;\n}\n")
            stats = tc.measure(os.path.join(tree, "data", "reflection.json"), os.path.join(tree, "src"))
        # two bare reads, `this->_visualContext` and (as for any function of the class) a pointer of unread type
        # reaching a field of the class's name; the parameter of that name hides the field
        self.assertEqual(stats["recovered"], 4)
        self.assertEqual(stats["by_class"], {"igRenderer": 4})


if __name__ == "__main__":
    unittest.main()
