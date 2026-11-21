#!/usr/bin/env python3
"""scripts/gen_type_headers.py writes class-members.tsv rows into the class bodies with the kit's access."""
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "scripts"))
import gen_type_headers as gth  # noqa: E402

LAYOUTS = {
    "igObject": (0x587198, 2, "sizeof 8", 8, [(0, 4, "    int _vtable;"), (4, 4, "    unsigned int _refCount;")]),
    "igRenderer": (0x1, 1, "sizeof 12", 12, [(8, 4, "    int _visualContext;")]),
}


class Access(unittest.TestCase):
    def test_a_label_opens_the_declaration_and_none_is_public(self):
        self.assertEqual(gth.split_access("protected: igObject();"), ("protected", "igObject();"))
        self.assertEqual(gth.split_access("private:static int k;"), ("private", "static int k;"))
        self.assertEqual(gth.split_access("virtual void draw();"), ("public", "virtual void draw();"))

    def test_sections_follow_the_table_order(self):
        lines, access = gth.member_lines(["protected: A();", "protected: A(bool b);", "void f();",
                                          "protected: static int _Meta;", "static void g();"], "public")
        self.assertEqual(lines, ["protected:", "    A();", "    A(bool b);", "public:", "    void f();",
                                 "protected:", "    static int _Meta;", "public:", "    static void g();"])
        self.assertEqual(access, "public")

    def test_the_root_opens_with_its_first_rows_access_and_keeps_its_fields_public(self):
        members = {"igObject": ["protected: igObject();", "virtual void destruct();", "protected: static int *_Meta;"],
                   "igRenderer": ["IG_ABSTRACT_OBJECT_DEFINE(igRenderer)", "protected: static int *k_visualContext;",
                                  "void setVisualContext(int *context);"]}
        out = gth.converted_classes({"igObject": "Core", "igRenderer": "Gui"}, {"igRenderer": "igObject"}, LAYOUTS,
                                    members)
        root = out[out.index("class igObject {"):]
        self.assertEqual(root[:9], ["class igObject {", "protected:", "    igObject();", "public:",
                                    "    virtual void destruct();", "protected:", "    static int *_Meta;", "public:",
                                    "    unsigned int _refCount;"])
        sub = out[out.index("class igRenderer : public Gap::Core::igObject {"):]
        self.assertEqual(sub[:8], ["class igRenderer : public Gap::Core::igObject {", "public:",
                                   "    int _visualContext;", "    IG_ABSTRACT_OBJECT_DEFINE(igRenderer)", "protected:",
                                   "    static int *k_visualContext;", "public:",
                                   "    void setVisualContext(int *context);"])

    def test_a_table_without_labels_writes_one_public_section(self):
        members = {"igObject": ["igObject();", "virtual void destruct();"]}
        out = gth.converted_classes({"igObject": "Core"}, {}, LAYOUTS, members)
        root = out[out.index("class igObject {"):]
        self.assertEqual(root[:5], ["class igObject {", "public:", "    igObject();", "    virtual void destruct();",
                                    "    unsigned int _refCount;"])

    def test_the_kits_reference_union_takes_the_place_of_the_word(self):
        union = ("protected: union { mutable unsigned int _both; struct { mutable unsigned int _refCount : 23; "
                 "unsigned int _memPoolIndex : 9; } _either; } _refAndMemPool;")
        members = {"igObject": ["virtual void destruct();", union]}
        out = gth.converted_classes({"igObject": "Core"}, {}, LAYOUTS, members)
        root = out[out.index("class igObject {"):]
        self.assertEqual(root[:6], ["class igObject {", "public:", "    virtual void destruct();", "protected:",
                                    "    " + union.split(": ", 1)[1], "};"])


class FlatView(unittest.TestCase):
    def test_a_flat_view_row_is_declared_in_the_struct_and_defined_after_the_gap_class(self):
        decl, body = gth.split_inline("inline void release() const { ((const Gap::Core::igObject *)this)->release(); }",
                                      "igObject")
        self.assertEqual(decl, "inline void release() const;")
        self.assertEqual(body, "inline void igObject::release() const { ((const Gap::Core::igObject *)this)->release(); }")
        decl, body = gth.split_inline("static inline void ref(const igObject *obj) { if (obj != 0) obj->ref(); }",
                                      "igObject")
        self.assertEqual(decl, "static inline void ref(const igObject *obj);")
        self.assertEqual(body, "inline void igObject::ref(const igObject *obj) { if (obj != 0) obj->ref(); }")

    def test_the_definitions_follow_the_converted_classes(self):
        members = {"igObject": ["virtual void destruct();"],
                   "::igObject": ["inline void ref() const { ((const Gap::Core::igObject *)this)->ref(); }"]}
        out = gth.converted_classes({"igObject": "Core"}, {}, LAYOUTS, members)
        self.assertEqual(out[-3:], ["inline void igObject::ref() const { ((const Gap::Core::igObject *)this)->ref(); }",
                                    "#endif", ""])


class SmartPointerInclude(unittest.TestCase):
    def test_the_template_is_read_once_the_root_is_complete(self):
        layouts = dict(LAYOUTS, igRenderer=(0x1, 1, "sizeof 12", 12,
                                            [(8, 4, "    igSmartPointer<igVisualContext> _visualContext;")]))
        members = {"igObject": ["virtual void destruct();"], "igRenderer": ["void setVisualContext(int *context);"]}
        out = gth.converted_classes({"igObject": "Core", "igRenderer": "Gui"}, {"igRenderer": "igObject"}, layouts,
                                    members)
        include = out.index("#include \"dw4/core/igSmartPointer.h\"")
        self.assertEqual(out.count("#include \"dw4/core/igSmartPointer.h\""), 1)
        # after the root's closing braces, before the first class holding a smart pointer
        self.assertEqual(out[include - 3:include], ["};", "}", "}"])
        self.assertLess(out.index("class igObject {"), include)
        self.assertLess(include, out.index("class igRenderer : public Gap::Core::igObject {"))

    def test_no_smart_pointer_member_no_include(self):
        out = gth.converted_classes({"igObject": "Core", "igRenderer": "Gui"}, {"igRenderer": "igObject"}, LAYOUTS,
                                    {"igObject": ["virtual void destruct();"]})
        self.assertNotIn("#include \"dw4/core/igSmartPointer.h\"", out)


if __name__ == "__main__":
    unittest.main()
