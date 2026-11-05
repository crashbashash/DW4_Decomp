"""scripts/check_struct_conflicts.py: the local-view parser and its three reports on small fixtures.

Run: python3 -m unittest discover -s testing -p 'test_check_struct_conflicts.py'   (also by `make struct-report`)
"""
import os
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "scripts"))
import check_struct_conflicts as csc  # noqa: E402

REFLECTED = {
    "igIntList": {"size": 20, "fields": {0: ("_vtable", "int", 4), 4: ("_refCount", "unsigned int", 4),
                                         8: ("_count", "int", 4), 12: ("_capacity", "int", 4), 16: ("_data", "int", 4)}},
}


def views_of(text, path):
    local = {}
    out = []
    for kind, name, base, body, line in csc.bodies(csc.strip_comments(text)):
        v = csc.parse_view(kind, name, base, body, local, REFLECTED, path, line)
        local[name] = (v.size, 4)
        out.append(v)
    return out


class Parser(unittest.TestCase):
    def test_layout_with_padding_arrays_and_pointers(self):
        v = views_of("typedef struct IntList { char p0[8]; int count; int cap; int *data; } IntList;", "a.c")[0]
        self.assertEqual([(m.name, m.offset, m.size) for m in v.members],
                         [("p0", 0, 8), ("count", 8, 4), ("cap", 12, 4), ("data", 16, 4)])
        self.assertEqual(v.size, 20)

    def test_unsigned_and_bitfields_and_virtuals(self):
        v = views_of("struct R { int vt; unsigned refs; unsigned char lo : 7; unsigned char hi : 1; };", "a.c")[0]
        self.assertEqual([(m.name, m.offset) for m in v.members], [("vt", 0), ("refs", 4), ("lo", 8), ("hi", 8)])
        v = views_of("class V { virtual void a(); virtual void b(); int x; };", "a.cpp")[0]
        self.assertEqual(v.nvirtual, 2)
        self.assertEqual([(m.name, m.offset) for m in v.members], [("<vptr>", 0), ("x", 4)])

    def test_preprocessor_lines_are_not_members(self):
        v = views_of("struct S {\n#define X 1\n    int a;\n};", "a.c")[0]
        self.assertEqual([m.name for m in v.members], ["a"])


class Reports(unittest.TestCase):
    def test_a_agreeing_views_are_not_reported(self):
        vs = (views_of("typedef struct IntList { char p0[8]; int count; int cap; int *data; } IntList;", "a.c")
              + views_of("typedef struct IntList { int vt; unsigned refs; int count; int cap; int *data; } IntList;", "b.cpp")
              + views_of("typedef struct IntList { int _unk00[2]; int count; int capacity; int *data; } IntList;", "c.c"))
        out = []
        self.assertEqual(csc.report_a(vs, out), 0)
        self.assertEqual(out, [])

    def test_a_clash_at_same_offset_is_reported_once_per_name(self):
        vs = (views_of("struct Pool { int vt; int rc; int cap; };", "a.c")
              + views_of("struct Pool { int vt; int rc; short cap; short n; };", "b.c")
              + views_of("struct S { int a; };", "c.c") + views_of("struct S { short a; };", "d.c"))
        out = []
        self.assertEqual(csc.report_a(vs, out), 1)  # `S` is generic and ignored
        self.assertTrue(out[0].startswith("Pool: 2 definitions in 2 files"))
        self.assertTrue(any("+8:" in line for line in out))

    def test_b_receiver_view_vs_reflected(self):
        path = os.path.join("src", "unmatched", "igIntList_Append.c")
        vs = views_of("struct L { int vt; int rc; short count; short cap; int *data; int extra; int tail; };", path)
        out = []
        self.assertEqual(csc.report_b(vs, REFLECTED, out), 1)
        text = "\n".join(out)
        self.assertIn("short count@8 is 2 bytes, reflected int _count is 4", text)
        self.assertIn("int tail@20 is beyond the registered size 20", text)
        self.assertIn("sits inside reflected int _count@8", text)  # cap at +10

    def test_b_consistent_view_and_dummy_vtable_are_silent(self):
        path = os.path.join("src", "unmatched", "Gap__Core__igIntList__vfunc_12.cpp")
        vs = (views_of("struct L { int vt; unsigned rc; int count; int cap; int *data; };", path)
              + views_of("class V { virtual void d0(); virtual void vfunc_01(); };", path))
        out = []
        self.assertEqual(csc.report_b(vs, REFLECTED, out), 0)

    def test_c_offset_names(self):
        vs = views_of("struct O { int f0; int f4; short f8; short f10; int f0xc; int w20; int pad24; };", "a.c")
        out = []
        self.assertEqual(csc.report_c(vs, out), 1)
        self.assertEqual([line for line in out if "is at" in line], ["  a.c:1 (struct O): int w20 is at +16"])

    def test_class_of_unit(self):
        self.assertEqual(csc.class_of_unit("src/unmatched/Gap__Bec__beNDMWMdlPlayer__vfunc_38.cpp"), "beNDMWMdlPlayer")
        self.assertEqual(csc.class_of_unit("src/game/beNDMWLoadIntf2NameSel__Update.c"), "beNDMWLoadIntf2NameSel")
        self.assertEqual(csc.class_of_unit("src/unmatched/igMetaField_SetToDefault.c"), "igMetaField")
        self.assertIsNone(csc.class_of_unit("src/unmatched/memcpy.c"))


if __name__ == "__main__":
    unittest.main()
