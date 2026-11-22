#!/usr/bin/env python3
"""apply_names.py renames a function's derived `thunk_<name>` everywhere its sources say it, and a member of a class
(`--member Class::old new`) in its declaration, definitions, calls and compiler name."""
import json
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import apply_names  # noqa: E402


class DerivedThunk(unittest.TestCase):
    def test_thunk_key_in_unit_objects_follows_its_target(self):
        with tempfile.TemporaryDirectory() as tree:
            config = os.path.join(tree, "config", "SLUS-20836")
            os.makedirs(os.path.join(config, "names"))
            os.makedirs(os.path.join(tree, "src", "engine"))
            with open(os.path.join(config, "symbols.txt"), "w") as f:
                f.write("00143140 000008 thunk_FUN_00143150\n00143150 000048 FUN_00143150\n")
            with open(os.path.join(config, "names", "Test.tsv"), "w") as f:
                f.write("0x00143150\tigWidget_GetMetaObject\tengine\n")
            with open(os.path.join(tree, "src", "engine", "Widget.c"), "w") as f:
                f.write("void FUN_00143150(void) {}\nvoid thunk_FUN_00143150(void) { FUN_00143150(); }\n")
            unit_objects = os.path.join(config, "unit-objects.json")
            with open(unit_objects, "w") as f:
                json.dump({"0x00143140": {"emitted": {"thunk_FUN_00143150": "0x00143140",
                                                      "FUN_00143150": "0x00143150"}}}, f)
            code = apply_names.main([
                "--names", os.path.join(config, "names"), "--symbols", os.path.join(config, "symbols.txt"),
                "--src", os.path.join(tree, "src"), "--asm", os.path.join(tree, "asm"), "--apply", "--no-regen"])
            self.assertEqual(code, 0)
            emitted = json.load(open(unit_objects))["0x00143140"]["emitted"]
            self.assertEqual(emitted, {"thunk_igWidget_GetMetaObject": "0x00143140",
                                       "igWidget_GetMetaObject": "0x00143150"})
            source = open(os.path.join(tree, "src", "engine", "Widget.c")).read()
            self.assertIn("void thunk_igWidget_GetMetaObject(void) { igWidget_GetMetaObject(); }", source)


class Documents(unittest.TestCase):
    def test_subject_documents_follow_the_rename_and_method_documents_are_left(self):
        # FUN_00163770 became igVertexArray2Helper_FloatToFixedPoint: docs/engine/igvertexarray2helper.md (a subject
        # document) follows it; member-conversion.md, a method document, names no function and was given the name
        sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "scripts"))
        import check_doc_function_names
        with tempfile.TemporaryDirectory() as tree:
            config = os.path.join(tree, "config", "SLUS-20836")
            os.makedirs(os.path.join(config, "names"))
            os.makedirs(os.path.join(tree, "src", "engine"))
            os.makedirs(os.path.join(tree, "docs", "engine"))
            with open(os.path.join(config, "symbols.txt"), "w") as f:
                f.write("00163770 000090 FUN_00163770\n")
            with open(os.path.join(config, "names", "EngineGFX.tsv"), "w") as f:
                f.write("0x00163770\tigVertexArray2Helper_FloatToFixedPoint\tengine\n")
            with open(os.path.join(tree, "src", "engine", "Helper.c"), "w") as f:
                f.write("int FUN_00163770(float value, unsigned int fractionBits) { return 0; }\n")
            with open(os.path.join(tree, "config", "doc-subjects.txt"), "w") as f:
                f.write("# subjects\ndocs/engine/igvertexarray2helper.md\n")
            subject = os.path.join(tree, "docs", "engine", "igvertexarray2helper.md")
            method = os.path.join(tree, "docs", "engine", "member-conversion.md")
            with open(subject, "w") as f:
                f.write("`FUN_00163770` is a private helper called only from slot 61.\n")
            with open(method, "w") as f:
                f.write("A fixed-point helper (FUN_00163770) stays a free function.\n")
            code = apply_names.main([
                "--names", os.path.join(config, "names"), "--symbols", os.path.join(config, "symbols.txt"),
                "--src", os.path.join(tree, "src"), "--asm", os.path.join(tree, "asm"), "--apply", "--no-regen"])
            self.assertEqual(code, 0)
            self.assertEqual(open(subject).read(),
                             "`igVertexArray2Helper_FloatToFixedPoint` is a private helper called only from slot 61.\n")
            self.assertEqual(open(method).read(), "A fixed-point helper (FUN_00163770) stays a free function.\n")
            # the check reads the result as before the batch: the subject document names a symbol, the method
            # document's placeholder is still its own finding
            findings = check_doc_function_names.check_tree(
                tree, check_doc_function_names.load_subjects(os.path.join(tree, "config", "doc-subjects.txt")),
                {"igVertexArray2Helper_FloatToFixedPoint"})
            self.assertEqual([f.split(":")[0] for f in findings], ["docs/engine/member-conversion.md"])


MEMBER_TREE = {
    "include/dw4/support/reflected.h": (
        "typedef struct igObject {\n    int _vtable;\n} igObject;\n"
        "#ifdef __cplusplus\ntypedef struct Widget : public igObject {\n#else\n"
        "typedef struct Widget {\n    int _vtable;\n#endif\n    int _count;\n} Widget;\n"),
    "include/dw4/game/Other.h": "struct Other {\n    int getCount();\n};\n",
    "src/game/Game.cpp": (
        "#include \"dw4/support/reflected.h\"\n#include \"dw4/game/Other.h\"\n"
        "/* Widget::getCount counts; Other::getCount is another class's */\n"
        "int Widget::getCount() {\n    return _count;\n}\n"
        "int Widget::twice() {\n    return getCount() * 2;\n}\n"
        "int Game_Sum(Widget *w, igObject *o, Other *x) {\n"
        "    return w->getCount() + ((Widget *)o)->getCount() + x->getCount() + Widget::twice();\n}\n"),
    "config/class-members.tsv": "# class\tdeclaration\nWidget\tint getCount();\nWidget\tint twice();\n",
    "config/SLUS-20836/symbols.txt": "00100000 000010 Widget_GetCount\n00100010 000010 Widget_Twice\n",
}
MEMBER_ROWS = {"0x00100000": {"whole_file": True, "symbol": "getCount__6WidgetFv",
                              "emitted": {"twice__6WidgetFv": "0x00100010"}},
               "0x00200000": {"whole_file": True, "externals": {"getCount__6WidgetFv": "0x00100000"}}}


class MemberRename(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.tree = self.tmp.name
        for rel, text in MEMBER_TREE.items():
            path = os.path.join(self.tree, rel)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as fh:
                fh.write(text)
        with open(self.path("config/SLUS-20836/unit-objects.json"), "w") as fh:
            json.dump(MEMBER_ROWS, fh)

    def tearDown(self):
        self.tmp.cleanup()

    def path(self, rel):
        return os.path.join(self.tree, rel)

    def read(self, rel):
        with open(self.path(rel)) as fh:
            return fh.read()

    def run_rename(self, *extra):
        return apply_names.main(["--member", "Widget::getCount", "count", "--src", self.path("src"),
                                 "--symbols", self.path("config/SLUS-20836/symbols.txt"), *extra])

    def test_declaration_definition_calls_and_compiler_name(self):
        self.assertEqual(self.run_rename("--apply"), 0)
        source = self.read("src/game/Game.cpp")
        self.assertIn("/* Widget::count counts; Other::getCount is another class's */", source)
        self.assertIn("int Widget::count() {", source)
        self.assertIn("return count() * 2;", source)
        self.assertIn("return w->count() + ((Widget *)o)->count() + x->getCount() + Widget::twice();", source)
        self.assertEqual(self.read("include/dw4/game/Other.h"), MEMBER_TREE["include/dw4/game/Other.h"])
        self.assertIn("Widget\tint count();\n", self.read("config/class-members.tsv"))
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        self.assertEqual(rows["0x00100000"]["symbol"], "count__6WidgetFv")
        self.assertEqual(rows["0x00200000"]["externals"], {"count__6WidgetFv": "0x00100000"})

    def test_a_call_whose_receiver_is_not_read_is_refused_when_another_class_has_the_name(self):
        with open(self.path("src/game/Game.cpp"), "a") as fh:
            fh.write("int Game_Any(Widget **list) {\n    return list[0]->getCount();\n}\n")
        before = self.read("src/game/Game.cpp")
        self.assertEqual(self.run_rename("--apply"), 2)
        self.assertEqual(before, self.read("src/game/Game.cpp"))

    def test_a_macro_member_is_refused(self):
        self.assertEqual(apply_names.main(["--member", "Widget::_Meta", "meta", "--src", self.path("src"),
                                           "--symbols", self.path("config/SLUS-20836/symbols.txt")]), 2)


if __name__ == "__main__":
    unittest.main()
