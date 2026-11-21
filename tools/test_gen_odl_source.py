#!/usr/bin/env python3
"""Tests for the C++ class tables and generators: scripts/gen_type_headers.py (class-members.tsv,
typed-fields.tsv, converted-classes.tsv), tools/gen_odl_source.py (igen's boilerplate) and the
symbols.txt display column of tools/split.py."""
import json
import os
import sys
import tempfile
import types
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(ROOT, "scripts"))

import gen_odl_source as odl  # noqa: E402
import gen_type_headers  # noqa: E402
import split  # noqa: E402

REFLECTION = {"classes": {
    "0x1000": {"class": "igObject", "fields": []},
    "0x1010": {"class": "igRenderer", "fields": [
        {"name": "_visualContext", "offset": 8, "type": "igObjectRefMetaField"}]},
    "0x1020": {"class": "igClearRenderer", "fields": [
        {"name": "_buffersToClear", "offset": 12, "type": "igUnsignedIntMetaField"}]},
}}
HIERARCHY = "# class\tbase\nigRenderer\tigObject\nigClearRenderer\tigRenderer\n"
OVERLAY = ("igObject\t0\tigObjectRefMetaField\t_vtable\tvtable\n"
           "igObject\t4\tigUnsignedIntMetaField\t_refCount\tcount\n")
# the root's declarations as the repository's table gives them (constructor, delete, slots, getMeta, statics)
ROOT_ROWS = "".join(line for line in open(os.path.join(ROOT, "config", "class-members.tsv"))
                    if line.startswith("igObject\t"))


class Tree:
    """A minimal tree for gen_type_headers.py: reflection, hierarchy, overlay and the three tables."""

    def __init__(self, tmp, members="", typed="", converted=""):
        self.tmp = tmp
        os.makedirs(os.path.join(tmp, "data"))
        os.makedirs(os.path.join(tmp, "config", "SLUS-20836"))
        json.dump(REFLECTION, open(os.path.join(tmp, "data", "reflection.json"), "w"))
        open(os.path.join(tmp, "data", "class-hierarchy.tsv"), "w").write(HIERARCHY)
        open(os.path.join(tmp, "config", "SLUS-20836", "authoritative-fields.tsv"), "w").write(OVERLAY)
        for name, text in (("members", members), ("typed", typed), ("converted", converted)):
            open(os.path.join(tmp, name + ".tsv"), "w").write("# header\n" + text)

    def generate(self, out="reflected.h"):
        path = os.path.join(self.tmp, out)
        argv = ["--reflection", os.path.join(self.tmp, "data", "reflection.json"),
                "--hierarchy", os.path.join(self.tmp, "data", "class-hierarchy.tsv"),
                "--asm", os.path.join(self.tmp, "no-asm"), "--out", path,
                "--members", os.path.join(self.tmp, "members.tsv"),
                "--typed-fields", os.path.join(self.tmp, "typed.tsv"),
                "--converted", os.path.join(self.tmp, "converted.tsv")]
        old = sys.stdout
        sys.stdout = open(os.devnull, "w")
        try:
            gen_type_headers.main(argv)
        finally:
            sys.stdout.close()
            sys.stdout = old
        return open(path).read()


def baseline(tmp):
    """The header the same tree gives with no table files at all."""
    other = os.path.join(tmp, "plain")
    os.makedirs(other)
    tree = Tree(other)
    for name in ("members", "typed", "converted"):
        os.remove(os.path.join(other, name + ".tsv"))
    return tree.generate()


class TypeHeaderTables(unittest.TestCase):
    def test_header_only_tables_change_nothing(self):
        with tempfile.TemporaryDirectory() as tmp:
            text = Tree(tmp).generate()
            self.assertNotIn("igObjectMacros.h", text)
            self.assertNotIn("namespace", text)
            self.assertEqual(text, baseline(tmp))

    def test_members_and_typed_field_go_into_the_flat_struct_under_cplusplus(self):
        with tempfile.TemporaryDirectory() as tmp:
            text = Tree(tmp, members="igRenderer\tIG_ABSTRACT_OBJECT_DEFINE(igRenderer)\n",
                        typed="igRenderer\t_visualContext\tstruct igVisualContext *\n").generate()
            self.assertIn('#include "dw4/core/igObjectMacros.h"', text)
            body = text[text.index("typedef struct igRenderer"):text.index("} igRenderer;")]
            self.assertIn("#ifdef __cplusplus\n    struct igVisualContext *_visualContext;", body)
            self.assertIn("#else\n    int _visualContext;", body)
            self.assertIn("#ifdef __cplusplus\n    IG_ABSTRACT_OBJECT_DEFINE(igRenderer)\n#endif", body)

    def test_converted_classes_are_namespaced_and_polymorphic(self):
        with tempfile.TemporaryDirectory() as tmp:
            text = Tree(tmp, members=ROOT_ROWS + "igClearRenderer\tvirtual void draw();\n",
                        converted="igRenderer\tGui\nigClearRenderer\tGui\n").generate()
            cpp = text[text.index("The converted classes"):]
            self.assertIn("using Gui::igRenderer;", cpp)
            self.assertIn("using Core::igObject;", cpp)
            root = cpp[cpp.index("class igObject {"):]
            slots = [ln.strip() for ln in root[:root.index("};")].split("\n") if "virtual" in ln]
            self.assertEqual(len(slots), 21)       # 20 slots and the inline getMeta at slot 20
            self.assertTrue(slots[19].startswith("virtual igObject *cloneViaMetadata"))
            self.assertIn("getMeta() const", slots[20])
            # the slot declarations come before the reference count, which follows the vptr
            self.assertLess(root.index("getMeta() const"), root.index("_refCount;"))
            self.assertIn("class igRenderer : public Gap::Core::igObject {", cpp)
            clear = cpp[cpp.index("class igClearRenderer : public Gap::Gui::igRenderer {"):]
            clear = clear[:clear.index("};")]
            # own field only, at its offset after the parent's 12 bytes, then the members
            self.assertNotIn("_visualContext", clear)
            self.assertIn("unsigned int _buffersToClear;", clear)
            self.assertIn("virtual void draw();", clear)
            # the flat struct stays, without the members
            flat = text[text.index("typedef struct igClearRenderer"):text.index("} igClearRenderer;")]
            self.assertNotIn("draw", flat)

    def test_a_converted_class_needs_its_parent_converted(self):
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(SystemExit):
                Tree(tmp, converted="igClearRenderer\tGui\n").generate()

    def test_the_root_needs_its_rows(self):
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(SystemExit):
                Tree(tmp, converted="igRenderer\tGui\n").generate()

    def test_members_need_a_struct(self):
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(SystemExit):
                Tree(tmp, members="igNoSuchClass\tvoid f();\n").generate()


def mips(lines):
    """asm-split style instruction list from `va: text` lines."""
    out = []
    for line in lines:
        va, text = line.split(": ", 1)
        mn, _, ops = text.partition(" ")
        out.append((int(va, 16), mn, [o.strip() for o in ops.split(",")] if ops else []))
    return out


class FakeImage:
    gp = 0x560000

    def word(self, va):
        return {0x4d0000: 0x3f800000}.get(va, 0)


class Tracer(unittest.TestCase):
    def test_delay_slots_global_loads_and_stack_arguments(self):
        events = odl.trace(mips([
            "00100000: addiu sp,sp,-48",
            "00100004: lui v1,0x45",
            "00100008: addiu v1,v1,-14352",
            "0010000c: sd v1,0(sp)",
            "00100010: lui at,0x59",
            "00100014: lw s0,-15864(at)",
            "00100018: li a0,1",
            "0010001c: jal 0x2fe9c0",
            "00100020: move a1,s0",
            "00100024: jr ra",
            "00100028: addiu sp,sp,48",
        ]), FakeImage())
        call = events[0]
        self.assertEqual(call["target"], 0x2fe9c0)
        self.assertEqual(call["args"][0], ("k", 1))
        self.assertTrue(odl.is_global(call["args"][1], 0x58c208))      # set in the delay slot
        self.assertEqual(call["stack"][0], ("k", 0x44c7f0))

    def test_a_skipped_call_is_conditional(self):
        events = odl.trace(mips([
            "00100000: bnez v0,0x10000c",
            "00100004: nop",
            "00100008: jal 0x2ff820",
            "0010000c: jr ra",
            "00100010: nop",
        ]), FakeImage())
        self.assertTrue([e for e in events if e["k"] == "call"][0]["cond"])


class Names(unittest.TestCase):
    def test_mangled_member(self):
        classes = {"igRenderer": 1}
        self.assertEqual(odl.mangled_member("getClassTypeSafe__10igRendererFv", classes),
                         ("igRenderer", "getClassTypeSafe"))
        self.assertEqual(odl.mangled_member("_Meta__10igRenderer", classes), ("igRenderer", "_Meta"))
        self.assertEqual(odl.mangled_member("_Meta__Q33Gap3Gui10igRenderer", classes), ("igRenderer", "_Meta"))
        self.assertEqual(odl.mangled_member("__ct__10igRendererFv", classes), ("igRenderer", "__ct"))
        self.assertIsNone(odl.mangled_member("igRenderer_Register", classes))

    def test_param_type(self):
        self.assertEqual(odl.param_type("struct igMetaField *self"), "igMetaField *")
        self.assertEqual(odl.param_type("const int &value"), "const int &")
        self.assertEqual(odl.param_type("void x"), "void")

    def test_float_literal(self):
        self.assertEqual(odl.float_literal(0x3f800000), "1.0f")


class MembersTable(unittest.TestCase):
    def test_merge_replaces_generated_rows_and_keeps_the_rest(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "class-members.tsv")
            open(path, "w").write("# header\nigRenderer\tIG_OBJECT_DEFINE(igRenderer)\n"
                                  "igRenderer\tvoid setVisualContext(igVisualContext *context);\n")
            odl.merge_member_rows(path, [("igRenderer", "IG_ABSTRACT_OBJECT_DEFINE(igRenderer)"),
                                         ("igRenderer", "static igMetaField *k_visualContext;")],
                                  ["igRenderer"])
            rows = open(path).read().split("\n")
            self.assertEqual(rows[0], "# header")
            self.assertEqual(rows[1:4], ["igRenderer\tIG_ABSTRACT_OBJECT_DEFINE(igRenderer)",
                                         "igRenderer\tstatic igMetaField *k_visualContext;",
                                         "igRenderer\tvoid setVisualContext(igVisualContext *context);"])
            self.assertIn("igMetaObject\t" + odl.SUPPORT_ROWS[0][1], rows)

    def test_a_regenerated_field_handle_keeps_its_access(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "class-members.tsv")
            open(path, "w").write("igRenderer\tIG_ABSTRACT_OBJECT_DEFINE(igRenderer)\n"
                                  "igRenderer\tprotected: static igMetaField *k_visualContext;\n"
                                  "igRenderer\tvoid setVisualContext(igVisualContext *context);\n")
            odl.merge_member_rows(path, [("igRenderer", "IG_ABSTRACT_OBJECT_DEFINE(igRenderer)"),
                                         ("igRenderer", "static igMetaField *k_visualContext;")],
                                  ["igRenderer"])
            self.assertEqual(open(path).read().split("\n")[:3], [
                "igRenderer\tIG_ABSTRACT_OBJECT_DEFINE(igRenderer)",
                "igRenderer\tprotected: static igMetaField *k_visualContext;",
                "igRenderer\tvoid setVisualContext(igVisualContext *context);"])


class DisplayColumn(unittest.TestCase):
    def test_converted_members_get_their_demangled_name(self):
        fake = types.ModuleType("demangle")
        fake.demangle = lambda m: types.SimpleNamespace(qualified={
            "setVisualContext__Q33Gap3Gui10igRendererFPQ33Gap3Gfx15igVisualContext":
                "Gap::Gui::igRenderer::setVisualContext"}[m])
        sys.modules["demangle"] = fake
        try:
            with tempfile.TemporaryDirectory() as tmp:
                path = os.path.join(tmp, "compiler-names.tsv")
                open(path, "w").write("# header\nsetVisualContext__Q33Gap3Gui10igRendererFPQ33Gap3Gfx15"
                                      "igVisualContext\t0x00457ca0\tigRenderer_SetVisualContext\n")
                fns = [(0x457ca0, 0xb4, "igRenderer_SetVisualContext", "igRenderer_SetVisualContext"),
                       (0x457d60, 0x80, "igClearRenderer_InitializeDrawing", None)]
                out = split.apply_display_names(fns, path)
                self.assertEqual(out[0], (0x457ca0, 0xb4, "igRenderer_SetVisualContext",
                                          "Gap::Gui::igRenderer::setVisualContext"))
                self.assertEqual(out[1], fns[1])
        finally:
            del sys.modules["demangle"]

    def test_header_only_table_changes_nothing(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "compiler-names.tsv")
            open(path, "w").write("# header\n")
            fns = [(0x100000, 8, "f", None)]
            self.assertIs(split.apply_display_names(fns, path), fns)
            self.assertIs(split.apply_display_names(fns, os.path.join(tmp, "absent.tsv")), fns)


@unittest.skipUnless(os.path.exists(os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
                     and os.path.isdir(os.path.join(ROOT, "asm")), "needs the retail executable and asm/")
class RetailRoles(unittest.TestCase):
    """igRenderer's roles and fragment, read from the retail registrar (the prototype's form)."""

    @classmethod
    def setUpClass(cls):
        cls.lib = odl.Library()

    def test_roles(self):
        roles = self.lib.classes["igRenderer"]
        self.assertEqual(roles["meta"], 0x58c208)
        self.assertEqual(roles["getClassTypeSafe"], 0x44c710)
        self.assertEqual(roles["arkRegister"], 0x44c760)
        self.assertEqual(roles["arkRegisterInternal"], 0x44c770)
        self.assertEqual(roles["getClassMetaSafe"], 0x44c7e0)
        self.assertEqual(roles["arkRegisterInitialize"], 0x44c7f0)
        self.assertEqual(self.lib.library_of("igRenderer"), "Gui")

    def test_fragment(self):
        written, rows, failed, _w = odl.generate(
            self.lib, ["igRenderer"], os.path.join(ROOT, "config", "class-members.tsv"),
            os.path.join(ROOT, "config", "converted-classes.tsv"), None,
            os.path.join(ROOT, "include", "dw4", "support", "reflected.h"))
        self.assertEqual(failed, {})
        text = "\n".join(written[0][1])
        self.assertIn("static igMetaObjectCallback regFunctions[] = { igVisualContext_EnsureRegistered, 0 };",
                      text)
        self.assertIn("    GuiLibrary_MarkRegistered();\n    return igMetaObject_RegisterClass(\n        true,\n"
                      "        &_Meta,\n        Gap::Core::igObject::arkRegisterInternal,\n"
                      "        Gap::Core::igObject::getClassMeta,\n"
                      "        (igMetaObjectCallback)getClassMetaSafe,\n        \"igRenderer\",\n"
                      "        sizeof(igRenderer),\n        0,\n        &arkRegisterInitialize,\n        0,\n"
                      "        regFunctions\n    );", text)
        self.assertIn("metaField->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();", text)
        self.assertEqual(rows, [("igRenderer", "IG_ABSTRACT_OBJECT_DEFINE(igRenderer)"),
                                ("igRenderer", "static igMetaField *k_visualContext;")])

    def test_an_inherited_field_replaced_by_a_new_type(self):
        # igMemoryRefMetaField's adder replaces the inherited _resetMethod (a char field) by a new
        # igEnumMetaField: created, given the inherited name, handle and offset, set, put in place
        written, _rows, failed, _w = odl.generate(
            self.lib, ["igMemoryRefMetaField"], os.path.join(ROOT, "config", "class-members.tsv"),
            os.path.join(ROOT, "config", "converted-classes.tsv"),
            os.path.join(ROOT, "config", "SLUS-20836", "compiler-names.tsv"),
            os.path.join(ROOT, "include", "dw4", "support", "reflected.h"))
        self.assertEqual(failed, {})
        text = "\n".join(written[0][1])
        self.assertIn(
            "        __internalNonRefCountedObjectList *metaFields = (__internalNonRefCountedObjectList *)"
            "metaObject->_metaFields;\n"
            "        int metaIndex = ObjectPointerList_FindIndex(metaFields, "
            "(int)igMetaObject_FindFieldByName(metaObject, \"_resetMethod\"));\n"
            "        igEnumMetaField *metaField = (igEnumMetaField *)igEnumMetaField_Create(", text)
        self.assertIn("        metaField->setBasicProperties(\"_resetMethod\", &k_resetMethod, 36, metaObject);\n",
                      text)
        self.assertIn("        metaField->_externalEnumStorage = (int)&k_resetMethod;\n"
                      "        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, ", text)


class FlatCasts(unittest.TestCase):
    def test_a_converted_class_named_by_a_c_parameter_is_the_flat_struct(self):
        w = odl.Writer(None, set(), {"igMetaField": "Core"}, {}, {}, {}, None)
        self.assertEqual(w.cast_to("igMetaField *", "metaField", "igShortMetaField *"),
                         "(::igMetaField *)metaField")
        self.assertEqual(w.cast_to("igMetaObject *", "m", "int"), "(igMetaObject *)m")
        self.assertEqual(w.cast_to("igMetaField *", "f", "igMetaField *"), "f")

    def test_a_converted_class_is_released_as_the_flat_root(self):
        w = odl.Writer(None, set(), {"igObject": "Core", "igUnsignedShortMetaField": "Core"}, {}, {}, {}, None)
        self.assertEqual(w.cast_to("igObject *", "metaField", "igUnsignedShortMetaField *"),
                         "(::igObject *)metaField")


class MemberCalls(unittest.TestCase):
    def test_a_converted_class_member_is_called_on_its_receiver(self):
        lib = types.SimpleNamespace(role_at={}, parent={"igIntMetaField": "igMetaField"})
        rows = {"igIntMetaField": ["IG_BOOTSTRAP_OBJECT_DEFINE(igIntMetaField)", "void setDefault(int def);"],
                "igMetaField": ["protected: static igMetaField *_MetaField;", "void validate();"]}
        w = odl.Writer(lib, set(), {"igIntMetaField": "Core", "igMetaField": "Core"},
                       {0x1000: "setDefault__Q33Gap4Core14igIntMetaFieldFi",
                        0x2000: "validate__Q33Gap4Core11igMetaFieldFv"}, {}, {}, None, rows)
        ctx = {"cls": "igIntArrayMetaField", "names": {("ret", 0): "metaField"},
               "types": {("ret", 0): "igIntMetaField"}, "start": None}
        call = {"k": "call", "target": 0x1000, "args": [("ret", 0), ("k", 1)], "fargs": [], "stack": {}}
        self.assertEqual(w.call_expr(call, 1, [], ctx), "metaField->setDefault(1)")
        # a member inherited from the parent's rows: a subclass receiver as it is, another one cast
        call = {"k": "call", "target": 0x2000, "args": [("ret", 0)], "fargs": [], "stack": {}}
        self.assertEqual(w.call_expr(call, 1, [], ctx), "metaField->validate()")
        ctx["types"][("ret", 0)] = "igMetaObject"
        self.assertEqual(w.call_expr(call, 1, [], ctx), "((igMetaField *)metaField)->validate()")
        self.assertIsNone(w.member_signature("Gap::Core::igMetaField::_MetaField"))

    def test_a_macro_declared_member_is_handed_over_bare_in_its_class(self):
        lib = types.SimpleNamespace(role_at={}, parent={})
        w = odl.Writer(lib, set(), {"igIntArrayMetaField": "Core"},
                       {0x1000: "arkRegisterMetaValidate__Q33Gap4Core19igIntArrayMetaFieldFv"}, {}, {}, None, {})
        self.assertEqual(w.callback(0x1000, "igIntArrayMetaField", "igMetaObjectCallback", ("void", [])),
                         "arkRegisterMetaValidate")
        self.assertEqual(w.callback(0x1000, "igOther", "igMetaObjectCallback", ("void", [])),
                         "Gap::Core::igIntArrayMetaField::arkRegisterMetaValidate")

    def test_a_static_the_metafield_macro_declares_is_called(self):
        # IG_METAFIELD_SETUP declares getMetaField; no class-members.tsv row names it (igObjectList's adder)
        lib = types.SimpleNamespace(role_at={}, parent={})
        w = odl.Writer(lib, set(), {"igObjectRefMetaField": "Core", "igObjectList": "Core"},
                       {0x1000: "getMetaField__Q33Gap4Core20igObjectRefMetaFieldFv"}, {}, {}, None, {})
        call = {"k": "call", "target": 0x1000, "args": [], "fargs": [], "stack": {}}
        ctx = {"cls": "igObjectList", "names": {}, "types": {}, "start": None}
        self.assertEqual(w.call_expr(call, 1, [], ctx), "Gap::Core::igObjectRefMetaField::getMetaField()")
        self.assertEqual(w.returns(0x1000, "igObjectList"), "igObjectRefMetaField *")
        ctx["cls"] = "igObjectRefMetaField"
        self.assertEqual(w.call_expr(call, 1, [], ctx), "getMetaField()")

    def test_a_kit_vector_temporary_is_written_as_its_constructor(self):
        # setDefault(const igVec4f &) on a stack temporary: every word of it, not the first alone
        w = odl.Writer(None, set(), {}, {}, {}, {}, None, {})
        ctx = {"cls": "igFogAttr", "names": {}, "types": {}, "start": None}
        at = {"frame": {16: ("k", 0), 20: ("k", 0), 24: ("k", 0), 28: ("k", 0x3f800000)}}
        self.assertEqual(w.value(("sp", 16), "const igVec4f &", [], ctx, at), "igVec4f(0.0f, 0.0f, 0.0f, 1.0f)")
        with self.assertRaises(odl.Unsupported):
            w.value(("sp", 16), "const igMatrix44f &", [], ctx, {"frame": {}})


if __name__ == "__main__":
    unittest.main()
