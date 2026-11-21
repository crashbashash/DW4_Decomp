#!/usr/bin/env python3
"""Tests for tools/classconv.py: the text steps of a batch conversion, on literal sources and a scratch tree."""
import collections
import json
import os
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import classconv as cc  # noqa: E402

C_SOURCE = '''int g_igFooMetaField_count;

/* the factory */
int igFooMetaField_GetSize(igFooMetaField *self) {
    const char *brace = "}";
    return self->_num * 4; /* } */
}

void igFooMetaField_Other(void) {
}
'''


class TextTest(unittest.TestCase):
    def test_block_end_skips_literals_and_comments(self):
        text = "{ '}' \"}\" /* } */ // }\n }tail"
        self.assertEqual(text[cc.block_end(text, 0):], "tail")

    def test_find_c_def(self):
        s, e = cc.find_c_def(C_SOURCE, "igFooMetaField_GetSize")
        self.assertTrue(C_SOURCE[s:].startswith("int igFooMetaField_GetSize("))
        self.assertTrue(C_SOURCE[:e].endswith("/* } */\n}"))
        self.assertIsNone(cc.find_c_def(C_SOURCE, "igFooMetaField_Missing"))

    def test_decl_of_and_stub(self):
        rows = ["IG_OBJECT_DEFINE(igFooMetaField)", "private: static igMetaField *k_num;",
                "virtual unsigned short computeSize();", "static igFooMetaField *getMetaField();",
                "void setDefault(unsigned int index, char val);"]
        self.assertEqual(cc.decl_of(rows, "computeSize"), (False, "unsigned short", ""))
        self.assertEqual(cc.decl_of(rows, "getMetaField"), (True, "igFooMetaField *", ""))
        self.assertIsNone(cc.decl_of(rows, "missing"))
        head = cc.stub_head("igFooMetaField", "igFooMetaField_SetDefault", cc.decl_of(rows, "setDefault"))
        self.assertEqual(head, "void igFooMetaField_SetDefault(igFooMetaField *self, unsigned int index, char val)")
        self.assertEqual(cc.stub_head("igFooMetaField", "igFooMetaField_Get", cc.decl_of(rows, "getMetaField")),
                         "igFooMetaField * igFooMetaField_Get(void)")
        text, ok = cc.stub_text(C_SOURCE, "igFooMetaField_GetSize", "unsigned short igFooMetaField_GetSize(X *self)")
        self.assertTrue(ok)
        self.assertIn("unsigned short igFooMetaField_GetSize(X *self)\n{\n}\n\nvoid igFooMetaField_Other", text)

    def test_replace_member_and_fragment(self):
        text = ("namespace Gap {\nnamespace Core {\n\nint igFoo::size() const\n{\n    return 1;\n}\n\n"
                "void igFoo::other()\n{\n}\n}\n}\n")
        new, ok = cc.replace_member(text, "igFoo", "size", "int igFoo::size() const\n{\n    return 2;\n}\n")
        self.assertTrue(ok)
        self.assertIn("    return 2;\n}\n\nvoid igFoo::other()", new)
        self.assertEqual(cc.replace_member(text, "igFoo", "absent", "x"), (text, False))
        self.assertEqual(sorted(cc.fragment_pieces(text, "igFoo")), ["other", "size"])
        self.assertEqual(cc.fragment_pieces(text, "igFoo")["other"], "void igFoo::other()\n{\n}")

    def test_drop_file_tables(self):
        text = ("int x;\n\nstatic FieldFactory g_igFoo_ctorTable[] = {\n    igIntMetaField_Create,\n};\n"
                "static int g_igFoo_fieldOffsets[] = {\n    56,\n};\n\n\nint y;\n")
        self.assertEqual(cc.drop_file_tables(text, "igFoo"), "int x;\n\nint y;\n")

    def test_respell_data(self):
        rows = ["private: static igMetaField *k_num;", "static int k_cell;", "inline int getNum() const { return 1; }"]
        self.assertEqual(cc.static_data(rows), {"k_num": "igMetaField *", "k_cell": "int "})
        text = "int igFoo::k_num;\nvoid *igFoo::k_cell;\nint igFoo::k_numOther;\n"
        self.assertEqual(cc.respell_data(text, "igFoo", rows),
                         "igMetaField *igFoo::k_num;\nint igFoo::k_cell;\nint igFoo::k_numOther;\n")

    def test_rekey_row_keeps_order(self):
        row = {"emitted": collections.OrderedDict([("a", "0x1"), ("igFoo_Init", "0x2"), ("c", "0x3")])}
        self.assertTrue(cc.rekey_row(row, "igFoo_Init", "__ct__Q33Gap4Core5igFooFv"))
        self.assertEqual(list(row["emitted"]), ["a", "__ct__Q33Gap4Core5igFooFv", "c"])
        self.assertFalse(cc.rekey_row(row, "absent", "x"))

    def test_boot_keys(self):
        self.assertEqual(cc.boot_key("Core", "igFooMetaField", "__ct__", ["bool"]),
                         "__ct__Q33Gap4Core14igFooMetaFieldFb")
        body, member, params = cc.boot_bodies("igFooMetaField", "igMetaField")["CopyConstruct"]
        params = [p.format(C="igFooMetaField", L="Core") for p in params]
        self.assertEqual(cc.boot_key("Core", "igFooMetaField", member, params),
                         "__ct__Q33Gap4Core14igFooMetaFieldFRCQ33Gap4Core14igFooMetaField")
        self.assertIn("igFooMetaField(const igFooMetaField &other) : igMetaField(other)",
                      body.format(C="igFooMetaField", B="igMetaField"))

    def test_array_spec(self):
        spec = cc.array_spec("igCharArrayMetaField", "igCharMetaField", "char", "index")
        self.assertIn("void setDefault(unsigned int index, char val);", spec["rows"])
        self.assertEqual(spec["map"]["SetDefaultElement"], "setDefault")
        self.assertIn("getNum() * sizeof(char)", spec["bodies"]["computeSize"])
        self.assertIn("igCharMetaField::getMetaField()->endianSwapMemory", spec["bodies"]["endianSwapMemory"])
        self.assertNotIn("setDefault", cc.array_spec("igLongArrayMetaField", "igLongMetaField", "long long")["bodies"])

    def test_leftover_declarations(self):
        report = ("src/a.h:12: igFoo_Init: C-name declaration no longer needed: no unconverted code names it\n"
                  "src/a.h:3: g_igFoo_vtable: C-name declaration no longer needed: x\n"
                  "memberize --check: 2 C-name declarations no longer needed\n")
        self.assertEqual(dict(cc.leftover_declarations(report)), {"src/a.h": {3, 12}})


class TreeTest(unittest.TestCase):
    """The steps that read and write the tree, on a scratch repository."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = self.tmp.name
        for d in ("config/SLUS-20836", "src/engine/core"):
            os.makedirs(os.path.join(root, d))
        files = {
            "config/converted-classes.tsv": "# class\tlibrary\nigObject\tCore\n",
            "config/class-members.tsv": "igObject\tvirtual void a();\nigMetaField\tvirtual void b();\n",
            "config/typed-fields.tsv": "",
            cc.SYMBOLS: "00100000 000010 igFooMetaField_GetSize\n00100010 000010 igFooMetaField_Odd\n"
                        "00100020 000010 igFooMetaField_Create\n00100030 000010 igFooMetaFieldList_X\n",
            cc.UNIT_OBJECTS: json.dumps({"0x00100000": {"emitted": {"igFooMetaField_Init": "0x00100000"}}}),
            "src/engine/core/igFooMetaField.inc": C_SOURCE,
        }
        for rel, text in files.items():
            with open(os.path.join(root, rel), "w") as f:
                f.write(text)
        self.tree = cc.Tree(root)
        self.specs = {"igFooMetaField": dict(rows=["IG_OBJECT_DEFINE(igFooMetaField)",
                                                   "virtual unsigned short computeSize();"],
                                             typed=[("_ref", "igSmartPointer<igObject>")],
                                             map={"GetSize": "computeSize"}, keep=("Create",),
                                             bodies={"computeSize": "unsigned short {C}::computeSize()\n{\n}"})}

    def tearDown(self):
        self.tmp.cleanup()

    def test_symbols_are_the_class_own(self):
        self.assertEqual(self.tree.symbols("igFooMetaField"), ["GetSize", "Odd", "Create"])

    def test_tables(self):
        cc.step_tables(self.tree, ["igFooMetaField"], self.specs)
        self.assertTrue(self.tree.read("config/converted-classes.tsv").endswith("igFooMetaField\tCore\n"))
        self.assertTrue(self.tree.read("config/class-members.tsv").endswith(
            "igFooMetaField\tvirtual unsigned short computeSize();\n"))
        self.assertEqual(self.tree.read("config/typed-fields.tsv"), "igFooMetaField\t_ref\tigSmartPointer<igObject>\n")
        with self.assertRaises(cc.ConvError):
            cc.step_tables(self.tree, ["igFooMetaField"], self.specs)

    def test_rows_go_after_the_class_last_row(self):
        self.tree.append_rows("config/class-members.tsv", "igObject", ["void c();"])
        self.assertEqual(self.tree.read("config/class-members.tsv"),
                         "igObject\tvirtual void a();\nigObject\tvoid c();\nigMetaField\tvirtual void b();\n")

    def test_stub_and_table(self):
        cc.stub(self.tree, "igFooMetaField", self.specs["igFooMetaField"])
        self.assertIn("unsigned short igFooMetaField_GetSize(igFooMetaField *self)\n{\n}\n",
                      self.tree.read("src/engine/core/igFooMetaField.inc"))
        table, unmapped = cc.memberize_table(self.tree, ["igFooMetaField"], self.specs)
        self.assertEqual(table, [("igFooMetaField_GetSize", "Gap::Core::igFooMetaField::computeSize")])
        self.assertEqual(unmapped, ["igFooMetaField_Odd"])

    def test_rekey_finds_the_unit(self):
        self.assertEqual(self.tree.rekey([("igFooMetaField_Init", "__ct__Q33Gap4Core14igFooMetaFieldFv"),
                                          ("absent", "x")]), ["absent"])
        row = json.loads(self.tree.read(cc.UNIT_OBJECTS))["0x00100000"]
        self.assertEqual(row["emitted"], {"__ct__Q33Gap4Core14igFooMetaFieldFv": "0x00100000"})

    def test_spec_file(self):
        path = os.path.join(self.tmp.name, "spec.py")
        with open(path, "w") as f:
            f.write("import classconv\nSPECS = {'igBarArrayMetaField': classconv.array_spec("
                    "'igBarArrayMetaField', 'igBarMetaField', 'int', 'all')}\n")
        specs = cc.load_specs(path)
        self.assertEqual(specs["igBarArrayMetaField"]["map"]["SetDefaultAll"], "setDefault")


if __name__ == "__main__":
    unittest.main()
