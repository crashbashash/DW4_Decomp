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
        # the C form's return type stays: memberize casts the uses the member's return type changes
        self.assertIn("int igFooMetaField_GetSize(X *self)\n{\n}\n\nvoid igFooMetaField_Other", text)

    def test_replace_member_and_fragment(self):
        text = ("namespace Gap {\nnamespace Core {\n\nint igFoo::size() const\n{\n    return 1;\n}\n\n"
                "void igFoo::other()\n{\n}\n}\n}\n")
        new, ok = cc.replace_member(text, "igFoo", "size", "int igFoo::size() const\n{\n    return 2;\n}\n")
        self.assertTrue(ok)
        self.assertIn("    return 2;\n}\n\nvoid igFoo::other()", new)
        self.assertEqual(cc.replace_member(text, "igFoo", "absent", "x"), (text, False))
        self.assertEqual(sorted(cc.fragment_pieces(text, "igFoo")), ["other", "size"])
        self.assertEqual(cc.fragment_pieces(text, "igFoo")["other"], "void igFoo::other()\n{\n}")

    def test_a_call_is_no_definition(self):
        # igPsx2VisualContext_tail5.inc after igImage's memberize: the call lines are not igImage::isIndexed's head
        calls = ("void FUN_0017b5f0(TexContext *context, TexEntry *entry)\n{\n    int format;\n\n"
                 "    if (Gap::Gfx::igImage::isIndexed((IG_GFX_TEXTURE_FORMAT)entry->format)) {\n"
                 "        format = DAT_0048acb0[entry->format - 0x10000];\n    } else {\n"
                 "        format = DAT_0048ac40[entry->format];\n    }\n"
                 "    format = igImage::k_count;\n    return igImage::isIndexed(format) ? 1 : 0;\n}\n")
        self.assertEqual(cc.replace_member(calls, "igImage", "isIndexed", "x"), (calls, False))
        self.assertEqual(cc.fragment_pieces(calls, "igImage"), {})
        self.assertEqual(cc.respell_data(calls, "igImage", ["static int k_count;"]), calls)
        definition = ("bool igImage::isIndexed(IG_GFX_TEXTURE_FORMAT fmt)\n{\n    return 0;\n}\n"
                      "Gap::Core::igObject *Gap::Gfx::igImage::make(int n) const\n{\n}\n")
        new, ok = cc.replace_member(definition, "igImage", "isIndexed", "bool igImage::isIndexed(IG_GFX_TEXTURE_FORMAT"
                                    " fmt)\n{\n    return 1;\n}")
        self.assertTrue(ok)
        self.assertTrue(new.startswith("bool igImage::isIndexed(IG_GFX_TEXTURE_FORMAT fmt)\n{\n    return 1;\n}\n"))
        self.assertEqual(sorted(cc.fragment_pieces(definition, "igImage")), ["isIndexed", "make"])

    def test_drop_file_tables(self):
        text = ("int x;\n\nstatic FieldFactory g_igFoo_ctorTable[] = {\n    igIntMetaField_Create,\n};\n"
                "static int g_igFoo_fieldOffsets[] = {\n    56,\n};\n\n\nint y;\n")
        self.assertEqual(cc.drop_file_tables(text, "igFoo"), "int x;\n\nint y;\n")

    def test_drop_file_tables_keeps_the_other_blank_lines(self):
        # igEventTracker_tail.inc names igSemaphore::, and igSemaphore's splice collapsed its run of 27 blank lines
        text = ("int a;\n\n\n\nint b;\n\nstatic FieldFactory g_igFoo_ctorTable[] = {\n    igIntMetaField_Create,\n};\n"
                "\nint y;\n\n\nint z;\n")
        self.assertEqual(cc.drop_file_tables(text, "igFoo"), "int a;\n\n\n\nint b;\n\nint y;\n\n\nint z;\n")
        self.assertEqual(cc.drop_file_tables("int a;\n\n\nint b;\n", "igFoo"), "int a;\n\n\nint b;\n")

    def test_a_table_between_two_blocks_leaves_one_block(self):
        # igResource.inc after igResource's memberize: the ctor table stood between the arkRegister and
        # arkRegisterInternal blocks; blocks no table separated keep their bounds
        block = "namespace Gap {\nnamespace Core {\n\nvoid igResource::%s()\n{\n}\n}\n}\n"
        text = (block % "a" + "\nstatic FieldFactory g_igResource_ctorTable[] = {\n    x,\n};\n\n" + block % "b"
                + "\n" + block % "c")
        self.assertEqual(cc.drop_file_tables(text, "igResource"),
                         "namespace Gap {\nnamespace Core {\n\nvoid igResource::a()\n{\n}\n\n"
                         "void igResource::b()\n{\n}\n}\n}\n\n" + block % "c")

    def test_respell_data(self):
        rows = ["private: static igMetaField *k_num;", "static int k_cell;", "inline int getNum() const { return 1; }"]
        self.assertEqual(cc.static_data(rows), {"k_num": "igMetaField *", "k_cell": "int "})
        text = "int igFoo::k_num;\nvoid *igFoo::k_cell;\nint igFoo::k_numOther;\n"
        self.assertEqual(cc.respell_data(text, "igFoo", rows),
                         "igMetaField *igFoo::k_num;\nint igFoo::k_cell;\nint igFoo::k_numOther;\n")

    def test_boot_keys(self):
        self.assertEqual(cc.boot_key("Core", "igFooMetaField", "__ct__", ["bool"]),
                         "__ct__Q33Gap4Core14igFooMetaFieldFb")
        body, member, params = cc.boot_bodies("igFooMetaField", "igMetaField")["CopyConstruct"]
        params = [p.format(C="igFooMetaField", L="Core") for p in params]
        self.assertEqual(cc.boot_key("Core", "igFooMetaField", member, params),
                         "__ct__Q33Gap4Core14igFooMetaFieldFRCQ33Gap4Core14igFooMetaField")
        self.assertIn("igFooMetaField(const igFooMetaField &other) : igMetaField(other)",
                      body.format(C="igFooMetaField", B="igMetaField"))

    def test_overloads_by_full_declaration(self):
        decl = "void removeInfo(const char *infoName);"
        self.assertEqual(cc.member_name(decl), "removeInfo")
        self.assertEqual(cc.param_types("const char *infoName, int"), ["const char*", "int"])
        self.assertEqual(cc.param_types("void"), [])
        self.assertEqual(cc.qualified_member("Gap::Core::igFoo", "private: " + decl),
                         "void Gap::Core::igFoo::removeInfo(const char *infoName)")
        self.assertEqual(cc.qualified_member("Gap::Core::igFoo", "removeInfo"), "Gap::Core::igFoo::removeInfo")
        self.assertEqual(cc.member_decl("igFoo", ["void removeInfo(igInfo *info);"], decl),
                         (False, "void", "const char *infoName"))
        text = ("void igFoo::removeInfo(igInfo *info)\n{\n    a();\n}\n\n"
                "void igFoo::removeInfo(const char * name)\n{\n    b();\n}\n")
        new, ok = cc.replace_member(text, "igFoo", decl, "void igFoo::removeInfo(const char *infoName)\n{\n}")
        self.assertTrue(ok)
        self.assertIn("    a();", new)
        self.assertNotIn("    b();", new)
        self.assertEqual(cc.replace_member(text, "igFoo", "void removeInfo(int);", "x"), (text, False))

    def test_a_member_overload_beside_a_static_one_behind_a_comment_naming_it(self):
        # igVertexArray2Helper_tail.inc after GfxVertex2's memberize: the comment before slot 25 names the static
        # getIndexCount with a parenthesis after it, and the splice reported MISSING for `getIndexCount()`
        text = ("unsigned int igVertexArray2Helper::getWeightCount()\n{\n}\n\n"
                "/* Same as slot 24 for the stream with component type 6, index 0: looks it up with\n"
                " * Gap::Gfx::igVertexArray2::findVertexData and passes it to "
                "Gap::Gfx::igVertexArray2Helper::getIndexCount (same shape as "
                "Gap::Gfx::igVertexArray2Helper::getWeightCount with\n"
                " * fewer data-list classes), whose component count is left in v0. The declared return type is "
                "void. */\n\n"
                "unsigned igVertexArray2Helper::getIndexCount()\n{\n}\n\n"
                "unsigned int igVertexArray2Helper::getIndexCount(const igVertexData *indexVertexData)\n{\n"
                "    return 0;\n}\n")
        member = "unsigned int getIndexCount()"
        static = "static unsigned int getIndexCount(const igVertexData *indexVertexData)"
        body = "unsigned int igVertexArray2Helper::getIndexCount()\n{\n    return getIndexCount(find());\n}"
        new, ok = cc.replace_member(text, "igVertexArray2Helper", member, body)
        self.assertTrue(ok)
        self.assertIn(" * fewer data-list classes), whose component count is left in v0. The declared return type "
                      "is void. */\n\n" + body + "\n\nunsigned int igVertexArray2Helper::getIndexCount(const "
                      "igVertexData *indexVertexData)\n{\n    return 0;\n}\n", new)
        static_body = ("unsigned int igVertexArray2Helper::getIndexCount(const igVertexData *indexVertexData)\n{\n"
                       "    return 3;\n}")
        new, ok = cc.replace_member(new, "igVertexArray2Helper", static, static_body)
        self.assertTrue(ok)
        self.assertTrue(new.endswith(body + "\n\n" + static_body + "\n"))
        self.assertEqual(sorted(cc.fragment_pieces(text, "igVertexArray2Helper")), ["getIndexCount", "getWeightCount"])

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
        spec = self.specs["igFooMetaField"]
        cc.stub(self.tree, "igFooMetaField", spec, cc.c_names(self.tree, "igFooMetaField", spec))
        self.assertIn("\nint igFooMetaField_GetSize(igFooMetaField *self)\n{\n}\n",
                      self.tree.read("src/engine/core/igFooMetaField.inc"))
        table, unmapped = cc.memberize_table(self.tree, ["igFooMetaField"], self.specs)
        self.assertEqual(table, [("igFooMetaField_GetSize", "Gap::Core::igFooMetaField::computeSize")])
        self.assertEqual(unmapped, ["igFooMetaField_Odd"])

    def test_a_gen_member_is_the_function_at_its_role(self):
        # igPsx2Image's field adder: symbols.txt calls it FUN_00153ef0, so no `<class>_InitFields` maps it
        self.tree.write(cc.SYMBOLS, self.tree.read(cc.SYMBOLS) + "00153ef0 000018 FUN_00153ef0\n")
        self.tree._symbols = None
        listing = ("igFooMetaField                           getClassTypeSafe=0x100010 "
                   "arkRegisterInitialize=0x153ef0\n1 classes, 1 written, 0 cannot be written\n")
        self.tree.run = lambda args: listing
        roles = cc.generator_roles(self.tree, ["igFooMetaField"], self.specs)
        self.assertEqual(roles, {"igFooMetaField": {"getClassTypeSafe": 0x100010, "arkRegisterInitialize": 0x153ef0}})
        table, _unmapped = cc.memberize_table(self.tree, ["igFooMetaField"], self.specs, roles)
        self.assertIn(("FUN_00153ef0", "Gap::Core::igFooMetaField::arkRegisterInitialize"), table)
        # a role whose member a C name maps already is not derived again; one at another mapped function is a clash
        spec = dict(self.specs["igFooMetaField"], map={"GetSize": "getClassTypeSafe"})
        self.assertEqual(cc.c_names(self.tree, "igFooMetaField", spec, roles["igFooMetaField"]),
                         [("igFooMetaField_GetSize", "getClassTypeSafe"), ("FUN_00153ef0", "arkRegisterInitialize")])
        with self.assertRaisesRegex(cc.ConvError, "getClassTypeSafe"):
            cc.c_names(self.tree, "igFooMetaField", self.specs["igFooMetaField"], {"getClassTypeSafe": 0x100000})
        with self.assertRaisesRegex(cc.ConvError, "arkRegisterInitialize"):
            cc.c_names(self.tree, "igFooMetaField", self.specs["igFooMetaField"], {"arkRegisterInitialize": 0x200000})

    def test_a_body_no_c_function_becomes_is_an_error(self):
        # igGeometrySetAttr's spec named FUN_0013e6e0 under `map` (a `<class>_<suffix>`), so nothing became
        # createRenderList
        spec = dict(self.specs["igFooMetaField"], map={"GetSize": "computeSize", "FUN_00100030": "createRenderList"},
                    bodies={"createRenderList": "bool {C}::createRenderList()\n{\n}"})
        pairs = cc.c_names(self.tree, "igFooMetaField", spec)
        self.assertEqual(cc.unbacked_members(self.tree, "igFooMetaField", spec, pairs), ["createRenderList"])
        spec["extra"] = {"igFooMetaFieldList_X": "createRenderList"}
        pairs = cc.c_names(self.tree, "igFooMetaField", spec)
        self.assertEqual(cc.unbacked_members(self.tree, "igFooMetaField", spec, pairs), [])
        # a member the class defines already (added to a converted class) needs none
        del spec["extra"]
        self.tree.write("src/engine/core/igFooMetaField.inc", "bool igFooMetaField::createRenderList()\n{\n}\n")
        self.assertEqual(cc.unbacked_members(self.tree, "igFooMetaField", spec, pairs), [])

    def test_a_constructor_and_destructor_with_hand_bodies_map_from_their_c_names(self):
        # VisualCtx: igVisualContext's out-of-line constructor (FUN_001510e0) and destructor (FUN_00150af0) are hand
        # bodies; no spec key reached them, so both were written by hand and their C forms deleted by hand
        self.tree.write("config/class-members.tsv", self.tree.read("config/class-members.tsv") +
                        "igVisualContext\tprotected: igVisualContext();\nigVisualContext\tvirtual ~igVisualContext();\n")
        self.tree.write("src/engine/core/igVisualContext.inc",
                        "igVisualContext *FUN_001510e0(igVisualContext *self) {\n    self->_vt = 1;\n    return self;\n}\n\n"
                        "igVisualContext *FUN_00150af0(igVisualContext *self, short flag) {\n    if (flag > 0)\n"
                        "        Memory_Free(self);\n    return self;\n}\n")
        spec_file = os.path.join(self.tree.root, "spec.py")
        with open(spec_file, "w") as f:
            f.write("SPECS = %r\n" % {"igVisualContext": dict(
                gen=[], extra={"FUN_001510e0": "ctor", "FUN_00150af0": "dtor"},
                bodies={"ctor": "{C}::{C}()\n{\n    _timer = 0;\n}", "dtor": "{C}::~{C}()\n{\n    releaseAll();\n}"})})
        specs = cc.load_specs(spec_file)
        spec = specs["igVisualContext"]
        pairs = cc.c_names(self.tree, "igVisualContext", spec)
        self.assertEqual(cc.unbacked_members(self.tree, "igVisualContext", spec, pairs), [])
        cc.stub(self.tree, "igVisualContext", spec, pairs)
        # the C forms are emptied to their receivers, the destructor's delete flag gone
        self.assertEqual(self.tree.read("src/engine/core/igVisualContext.inc"),
                         "igVisualContext *FUN_001510e0(igVisualContext *self)\n{\n}\n\n"
                         "igVisualContext *FUN_00150af0(igVisualContext *self)\n{\n}\n")
        table, _unmapped = cc.memberize_table(self.tree, ["igVisualContext"], specs)
        self.assertEqual(table, [("FUN_001510e0", "Gap::Core::igVisualContext::igVisualContext"),
                                 ("FUN_00150af0", "Gap::Core::igVisualContext::~igVisualContext")])
        # memberize writes `C::C()` and `C::~C()` over the stubs; the splice writes the hand bodies over those
        self.tree.write("src/engine/core/igVisualContext.inc",
                        "namespace Gap {\nnamespace Core {\n\nigVisualContext::igVisualContext()\n{\n}\n\n"
                        "igVisualContext::~igVisualContext()\n{\n}\n}\n}\n")
        cc.splice_class(self.tree, "igVisualContext", spec, "")
        self.assertEqual(self.tree.read("src/engine/core/igVisualContext.inc"),
                         "namespace Gap {\nnamespace Core {\n\nigVisualContext::igVisualContext()\n{\n"
                         "    _timer = 0;\n}\n\nigVisualContext::~igVisualContext()\n{\n    releaseAll();\n}\n}\n}\n")

    def test_splice_writes_the_definition_only(self):
        os.makedirs(self.tree.path("src/engine/gfx"))
        definition = "namespace Gap {\nnamespace Gfx {\n\nbool igImage::isIndexed(int fmt)\n{\n    return 0;\n}\n}\n}\n"
        call = ("void FUN_0017b5f0(TexEntry *entry)\n{\n    if (Gap::Gfx::igImage::isIndexed(entry->format)) {\n"
                "        entry->format = 0;\n    }\n}\n")
        self.tree.write("src/engine/gfx/igGenericCapabilityManager_tail.inc", definition)
        self.tree.write("src/engine/gfx/igPsx2VisualContext_tail5.inc", call)
        spec = dict(lib="Gfx", rows=["static bool isIndexed(int fmt);"], gen=[],
                    bodies={"isIndexed": "bool {C}::isIndexed(int fmt)\n{\n    return fmt >= 0x10000;\n}"})
        cc.splice_class(self.tree, "igImage", spec, "")
        self.assertEqual(self.tree.read("src/engine/gfx/igPsx2VisualContext_tail5.inc"), call)
        self.assertIn("bool igImage::isIndexed(int fmt)\n{\n    return fmt >= 0x10000;\n}\n}\n}\n",
                      self.tree.read("src/engine/gfx/igGenericCapabilityManager_tail.inc"))

    def test_a_failed_run_restores_the_tree(self):
        root = self.tree.root
        self.tree.write(cc.SYMBOLS, self.tree.read(cc.SYMBOLS) + "00100040 000018 FUN_00100040\n")
        tools = {"tools/gen_odl_source.py": "print('igFooMetaField arkRegisterInitialize=0x100040')\n",
                 "scripts/gen_type_headers.py": "open('include/reflected.h', 'w').write('// regenerated\\n')\n",
                 # memberize writes some of its texts, then fails
                 "tools/memberize.py": "open('config/class-members.tsv', 'a').write('igFooMetaField\\tvoid x();\\n')\n"
                                       "open('src/engine/core/new.inc', 'w').write('x')\nraise SystemExit(1)\n"}
        for rel, text in tools.items():
            os.makedirs(os.path.dirname(os.path.join(root, rel)), exist_ok=True)
            self.tree.write(rel, text)
        os.makedirs(os.path.join(root, "include"))
        self.tree.write("include/reflected.h", "// as it was\n")
        spec = os.path.join(root, "spec.py")
        with open(spec, "w") as f:
            f.write("SPECS = %r\n" % self.specs)
        before = self.tree.snapshot()
        self.assertEqual(cc.main([spec, "all", "--root", root]), 1)
        self.assertEqual(self.tree.snapshot(), before)

    def test_add_members_to_a_converted_class(self):
        # igFile's statics, added after igFile was converted (CoreFiles' statics.tsv)
        self.tree.write("config/converted-classes.tsv", "# class\tlibrary\nigObject\tCore\nigFile\tCore\n")
        self.tree.write("config/class-members.tsv", "igFile\tIG_OBJECT_DEFINE(igFile)\nigFile\tvirtual int open();\n"
                                                    "igFolder\tIG_OBJECT_DEFINE(igFolder)\n")
        self.tree.write(cc.SYMBOLS, "00300000 000010 igFile_Open\n00300010 000010 FilePath_IsAbsolute\n")
        self.tree._symbols = None
        specs = {"igFile": dict(add=True, rows=["IG_OBJECT_DEFINE(igFile)",
                                                "static bool isAbsolutePath(const char *path);",
                                                "virtual int open();", "static void setSearchPath(const char *p);"],
                                extra={"FilePath_IsAbsolute": "isAbsolutePath"})}
        cc.step_tables(self.tree, ["igFile"], specs)
        members = ("igFile\tIG_OBJECT_DEFINE(igFile)\nigFile\tstatic bool isAbsolutePath(const char *path);\n"
                   "igFile\tvirtual int open();\nigFile\tstatic void setSearchPath(const char *p);\n"
                   "igFolder\tIG_OBJECT_DEFINE(igFolder)\n")
        self.assertEqual(self.tree.read("config/class-members.tsv"), members)
        cc.step_tables(self.tree, ["igFile"], specs)
        self.assertEqual(self.tree.read("config/class-members.tsv"), members)
        self.assertEqual(cc.gen_of(specs["igFile"]), [])
        self.assertEqual(cc.memberize_table(self.tree, ["igFile"], specs),
                         ([("FilePath_IsAbsolute", "Gap::Core::igFile::isAbsolutePath")], []))
        with self.assertRaises(cc.ConvError):
            cc.step_tables(self.tree, ["igFile"], {"igFile": dict(specs["igFile"], add=False)})
        with self.assertRaises(cc.ConvError):
            cc.step_tables(self.tree, ["igFolder"], {"igFolder": dict(add=True, rows=[])})

    def test_adding_a_row_the_table_has_under_another_label(self):
        # CoreFiles2's igFolder spec repeats getPathToFile without the `public:` the table's row carries
        table = ("igFolder\tIG_OBJECT_DEFINE(igFolder)\nigFolder\tprotected: static igMetaField *k_folderName;\n"
                 "igFolder\tpublic: virtual igStringObjRef getPathToFile(const char *fileName) const;\n"
                 "igFolder\tvirtual igSmartPointer<igStringRefList> getFiles() const;\n")
        self.tree.write("config/class-members.tsv", table)
        rows = ["IG_OBJECT_DEFINE(igFolder)",
                "protected: static igMetaField *k_folderName;",
                "public: inline void setFolderName(const char *folderNameParam) { _folderName = folderNameParam; }",
                "inline const char *getFolderName() const { return _folderName.p; }",
                "void appendRelativePath(const char *subdir);",
                "virtual igStringObjRef  getPathToFile(const char *fileName) const;"]
        self.assertEqual(self.tree.add_rows("config/class-members.tsv", "igFolder", rows), rows[2:5])
        lines = self.tree.read("config/class-members.tsv").splitlines()
        self.assertEqual(lines, table.splitlines()[:2] + ["igFolder\t" + r for r in rows[2:5]]
                         + table.splitlines()[2:])
        self.assertEqual(self.tree.add_rows("config/class-members.tsv", "igFolder", rows), [])

    def test_overload_keys_match_their_rows_by_signature(self):
        # igGeometryAttr's two intersectRay overloads (GeomAttr's geom15.py): a key had to repeat its row's text, or
        # the stub was skipped, the splice reported it MISSING and an `add` spec duplicated the row
        isect4 = ("virtual bool intersectRay(const igRay *ray, igVec3f &intersectPoint, igVec3f &norm, "
                  "ISET_SIDES whichFaces = FRONT_SIDE);")
        isect7 = ("virtual bool intersectRay(const igRay *ray, igVec3f &intersectPoint, igVec3f &norm, int &primIndex, "
                  "int &polyIndex, ISET_SIDES whichFaces = FRONT_SIDE, bool findNextIntersection = false) = 0;")
        table = "igGeometryAttr\t%s\nigGeometryAttr\tpublic: %s\n" % (isect4, isect7)
        self.tree.write("config/converted-classes.tsv", "igObject\tCore\nigGeometryAttr\tAttrs\n")
        self.tree.write("config/class-members.tsv", table)
        os.makedirs(self.tree.path("src/engine/attrs"))
        self.tree.write("src/engine/attrs/igGeometryAttr.inc",
                        "int FUN_0013cf80(igGeometryAttr *self, igRay *ray, float *p, float *n, int sides) {\n"
                        "    return 0;\n}\n")
        key = "bool intersectRay(const igRay* r, igVec3f &p, igVec3f& n, ISET_SIDES sides)"
        body = ("bool {C}::intersectRay(const igRay *ray, igVec3f &intersectPoint, igVec3f &norm, "
                "ISET_SIDES whichFaces)\n{\n    return 1;\n}")
        spec = dict(add=True, lib="Attrs", gen=[], extra={"FUN_0013cf80": key}, bodies={isect4: body},
                    rows=["public: virtual bool intersectRay(const igRay *r, igVec3f &p, igVec3f &n, ISET_SIDES s);"])
        cc.step_tables(self.tree, ["igGeometryAttr"], {"igGeometryAttr": spec})
        self.assertEqual(self.tree.read("config/class-members.tsv"), table)
        cc.check_keys(self.tree, "igGeometryAttr", spec)
        cc.stub(self.tree, "igGeometryAttr", spec, cc.c_names(self.tree, "igGeometryAttr", spec))
        self.assertEqual(self.tree.read("src/engine/attrs/igGeometryAttr.inc"),
                         "int FUN_0013cf80(igGeometryAttr *self, const igRay *ray, igVec3f &intersectPoint, "
                         "igVec3f &norm, ISET_SIDES whichFaces)\n{\n}\n")
        self.assertEqual(cc.memberize_table(self.tree, ["igGeometryAttr"], {"igGeometryAttr": spec})[0],
                         [("FUN_0013cf80", "virtual bool Gap::Attrs::igGeometryAttr::intersectRay(const igRay *ray, "
                                           "igVec3f &intersectPoint, igVec3f &norm, ISET_SIDES whichFaces)")])
        defs = ("bool igGeometryAttr::intersectRay(const igRay *ray, igVec3f &intersectPoint, igVec3f &norm, "
                "int &primIndex, int &polyIndex, ISET_SIDES whichFaces, bool findNextIntersection)\n{\n}\n\n"
                "bool igGeometryAttr::intersectRay(const igRay *ray, igVec3f &intersectPoint, igVec3f &norm, "
                "ISET_SIDES whichFaces)\n{\n}\n")
        new, ok = cc.replace_member(defs, "igGeometryAttr", isect4, body.replace("{C}", "igGeometryAttr"))
        self.assertTrue(ok)
        self.assertTrue(new.endswith("ISET_SIDES whichFaces)\n{\n    return 1;\n}\n"))
        # a bare name of two overloads is ambiguous
        with self.assertRaises(cc.ConvError):
            cc.check_keys(self.tree, "igGeometryAttr", dict(spec, bodies={"intersectRay": body}))

    def test_rekey_finds_the_unit_and_keeps_the_order(self):
        self.tree.write(cc.UNIT_OBJECTS, json.dumps({"0x00100000": {"emitted": collections.OrderedDict(
            [("a", "0x1"), ("igFooMetaField_Init", "0x00100000"), ("c", "0x3")])}}))
        self.assertEqual(self.tree.rekey([("igFooMetaField_Init", "__ct__Q33Gap4Core14igFooMetaFieldFv"),
                                          ("absent", "x")]), ["absent"])
        row = json.loads(self.tree.read(cc.UNIT_OBJECTS))["0x00100000"]
        self.assertEqual(list(row["emitted"].items()), [("a", "0x1"), ("__ct__Q33Gap4Core14igFooMetaFieldFv",
                                                                       "0x00100000"), ("c", "0x3")])

    def test_the_rekey_step_runs_memberize_rekey(self):
        # IGBFile's run left 0x2b5d50's stripped __dt__10ScopedLockFv and __dt__33igSmartPointer<15igSemaphoreView>Fv
        # for a hand edit: the conversion's last step is memberize's one renaming of the rows from the objects
        root = self.tree.root
        for rel, text in {"tools/memberize.py": "import sys\nopen('argv.txt', 'w').write(' '.join(sys.argv[1:]))\n",
                          "scripts/gen_type_headers.py": ""}.items():
            os.makedirs(os.path.dirname(os.path.join(root, rel)), exist_ok=True)
            self.tree.write(rel, text)
        spec = os.path.join(root, "spec.py")
        with open(spec, "w") as f:
            f.write("SPECS = %r\n" % self.specs)
        self.assertEqual(cc.main([spec, "rekey", "--root", root]), 0)
        self.assertEqual(self.tree.read("argv.txt"), "--rekey --apply")

    def test_boot_names_for_c_names_of_another_stem(self):
        # a bootstrap class whose C names are not its own (__internalNonRefCountedObjectList's ObjectPointerList_*)
        self.tree.write(cc.UNIT_OBJECTS, json.dumps({"0x00100000": {"emitted": {"FooList_Init": "0x00100000"}}}))
        self.tree.write("src/engine/core/FooList.inc", "void *FooList_Init(igFooMetaField *self) {\n    return self;\n}\n")
        spec = dict(self.specs["igFooMetaField"], base="igMetaField", boot_names={"Init": "FooList_Init"})
        self.assertEqual(cc.boot_cnames(self.tree, "igFooMetaField", spec), {"Init": "FooList_Init"})
        cc.splice_boot(self.tree, "igFooMetaField", spec)
        self.assertIn("igFooMetaField::igFooMetaField()\n{\n}\n", self.tree.read("src/engine/core/FooList.inc"))
        row = json.loads(self.tree.read(cc.UNIT_OBJECTS))["0x00100000"]
        self.assertEqual(row["emitted"], {"__ct__Q33Gap4Core14igFooMetaFieldFv": "0x00100000"})

    def test_a_boot_body_joins_the_block_before_it_and_keeps_the_blank_lines(self):
        self.tree.write(cc.UNIT_OBJECTS, json.dumps({"0x00100000": {"emitted": {"FooList_Init": "0x00100000"}}}))
        self.tree.write("src/engine/core/FooList.inc",
                        "namespace Gap {\nnamespace Core {\n\nvoid igFooMetaField::a()\n{\n}\n}\n}\n\n"
                        "void *FooList_Init(igFooMetaField *self) {\n    return self;\n}\n\n\nint after;\n")
        spec = dict(self.specs["igFooMetaField"], base="igMetaField", boot_names={"Init": "FooList_Init"})
        cc.splice_boot(self.tree, "igFooMetaField", spec)
        self.assertEqual(self.tree.read("src/engine/core/FooList.inc"),
                         "namespace Gap {\nnamespace Core {\n\nvoid igFooMetaField::a()\n{\n}\n\n"
                         "igFooMetaField::igFooMetaField()\n{\n}\n}\n}\n\n\nint after;\n")

    def test_a_splice_keeps_the_blank_lines_of_the_files_naming_the_class(self):
        text = "void f()\n{\n    igFooMetaField::g();\n}\n\n\n\n\nint after;\n"
        self.tree.write("src/engine/core/igEventTracker_tail.inc", text)
        cc.splice_class(self.tree, "igFooMetaField", dict(gen=[], add=True), "")
        self.assertEqual(self.tree.read("src/engine/core/igEventTracker_tail.inc"), text)

    def test_empty_fragment_goes_with_its_include(self):
        self.tree.write("src/engine/core/igFooMetaField_tail.inc", "\n")
        self.tree.write("src/engine/core/CoreLibrary.cpp", '#include "src/engine/core/igFooMetaField.inc"\n'
                        '#include "src/engine/core/igFooMetaField_tail.inc"\n')
        self.assertEqual(cc.drop_empty_fragments(self.tree, "Core"), ["src/engine/core/igFooMetaField_tail.inc"])
        self.assertFalse(os.path.exists(self.tree.path("src/engine/core/igFooMetaField_tail.inc")))
        self.assertEqual(self.tree.read("src/engine/core/CoreLibrary.cpp"),
                         '#include "src/engine/core/igFooMetaField.inc"\n')
        self.assertEqual(cc.drop_empty_fragments(self.tree, "Core"), [])

    def test_spec_file(self):
        path = os.path.join(self.tmp.name, "spec.py")
        with open(path, "w") as f:
            f.write("import classconv\nSPECS = {'igBarArrayMetaField': classconv.array_spec("
                    "'igBarArrayMetaField', 'igBarMetaField', 'int', 'all')}\n")
        specs = cc.load_specs(path)
        self.assertEqual(specs["igBarArrayMetaField"]["map"]["SetDefaultAll"], "setDefault")


if __name__ == "__main__":
    unittest.main()
