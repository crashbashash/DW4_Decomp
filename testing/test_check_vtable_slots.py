"""scripts/check_vtable_slots.py: a declared `vfunc_NN` must be the NN-th virtual (0-based, dummies counted).

Run: python3 -m unittest discover -s testing -p 'test_check_vtable_slots.py'   (also by `make vtable-slots-check`)
"""
import os
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "scripts"))
import check_vtable_slots as cvs  # noqa: E402


class CheckVtableSlots(unittest.TestCase):
    def test_correct_numbering_passes(self):
        text = "class V {\npublic:\n    virtual void vfunc_00();\n    virtual void vfunc_01();\n    virtual void vfunc_02(int);\n};\n"
        hits, skipped = cvs.check_text(text)
        self.assertEqual(hits, [])
        self.assertEqual(skipped, [])

    def test_dummies_count_as_slots(self):
        # 29 dummies place the next declared virtual at slot 29 (vtable +0x08 + 4*29 = +124)
        dummies = "".join("    virtual void d%d();\n" % i for i in range(29))
        text = "class igObjectSlotView {\npublic:\n" + dummies + "    virtual void vfunc_31();\n};\n"
        hits, _ = cvs.check_text(text, "pool.hpp")
        self.assertEqual(len(hits), 1)
        path, line, cls, name, declared, actual = hits[0]
        self.assertEqual((cls, name, declared, actual), ("igObjectSlotView", "vfunc_31", 31, 29))
        self.assertEqual(path, "pool.hpp")
        self.assertEqual(line, 1)

    def test_offset_by_two_reports_each_slot(self):
        text = "class P {\npublic:\n" + "".join("    virtual void vfunc_%02d();\n" % i for i in range(2, 36)) + "};\n"
        hits, _ = cvs.check_text(text)
        self.assertEqual(len(hits), 34)
        self.assertEqual((hits[-1][3], hits[-1][4], hits[-1][5]), ("vfunc_35", 35, 33))

    def test_unnumbered_virtuals_and_comments_are_ignored(self):
        text = ("/* virtual void vfunc_99(); in a comment */\n"
                "struct S { virtual void Update(); virtual void vfunc_01(); int x; };\n")
        hits, _ = cvs.check_text(text)
        self.assertEqual(hits, [])

    def test_derived_class_is_skipped_not_checked(self):
        text = "class D : public B {\npublic:\n    virtual void vfunc_05();\n};\n"
        hits, skipped = cvs.check_text(text, "d.cpp")
        self.assertEqual(hits, [])
        self.assertEqual(skipped, [("d.cpp", 1, "D")])

    def test_nested_bodies_do_not_leak_virtuals(self):
        text = ("struct Outer {\n    struct Inner { virtual void vfunc_00(); };\n"
                "    virtual void vfunc_00();\n    virtual void vfunc_01();\n};\n")
        hits, _ = cvs.check_text(text)
        self.assertEqual(hits, [])

    def test_tree_is_clean(self):
        # the repository itself must pass (what `make vtable-slots-check` gates)
        files = cvs.default_files(os.path.join(ROOT, "src"), os.path.join(ROOT, "include", "dw4"))
        hits = []
        for path in files:
            text = open(path, errors="replace").read()
            if "virtual" in text:
                hits += cvs.check_text(text, path)[0]
        self.assertEqual(hits, [])


if __name__ == "__main__":
    unittest.main()
