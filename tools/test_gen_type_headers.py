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


if __name__ == "__main__":
    unittest.main()
