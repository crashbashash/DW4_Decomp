#!/usr/bin/env python3
"""A compiler-emitted function is judged by the member definition its unit-objects.json name points at."""
import os
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import progress  # noqa: E402

SOURCE = """#include "holder.h"
struct Guard { igObject *p; ~Guard() { igRelease(p); } };
template <int kind> struct Holder { igObject *p; ~Holder() { igObject *q = p; if (q) igRelease(q); } };
struct Bad { igObject *p; ~Bad() { FUN_00123456(p); } };
void beCamera_Update(int camera) {
    Guard g;
    Holder<3> r;
    FUN_00123456(camera);
}
"""
HEADER = """template <class T> struct igSmartPointer {
    T *p;
    ~igSmartPointer() { igRelease(p); }
};
"""


class DemangleMember(unittest.TestCase):
    def test_compiler_names(self):
        self.assertEqual(progress.demangle_member("__dt__9ObjRef<5>Fv"), ("ObjRef", "~ObjRef"))
        self.assertEqual(progress.demangle_member("__dt__25igSmartPointer<8igObject>Fv"),
                         ("igSmartPointer", "~igSmartPointer"))
        self.assertEqual(progress.demangle_member("__ct__14NewDataListRefFRC14AllocatorValue"),
                         ("NewDataListRef", "NewDataListRef"))
        self.assertEqual(progress.demangle_member("release__9StringRefFPPc"), ("StringRef", "release"))
        self.assertEqual(progress.demangle_member("igRelease__FP8igObject"), (None, "igRelease"))
        self.assertEqual(progress.demangle_member("__ct__Q33Gap3Bec12beLuaWrapperFv"),
                         ("beLuaWrapper", "beLuaWrapper"))

    def test_a_plain_symbol_is_no_member(self):
        self.assertIsNone(progress.demangle_member("FUN_00336440"))
        self.assertIsNone(progress.demangle_member("igSmartPointer_igObjectList_Destruct"))


class MethodShaped(unittest.TestCase):
    def test_a_function_defined_as_a_member_is_no_free_method(self):
        # igLuaState_RunString is defined as `Gap::Lua::igLuaState::runString` (its unit-objects.json name
        # runString__Q33Gap3Lua10igLuaStateFPCc); igTransform_CreateInstance is still a free function
        syms = [(0x246620, 0x54, "igLuaState_RunString"), (0x196150, 0x34, "igTransform_CreateInstance"),
                (0x13b900, 0x12c, "Gap__Attrs__igAttrDefaultManager__vfunc_23")]
        paths = {name: "src/engine/unit.cpp" for _va, _n, name in syms}
        self.assertEqual(progress.method_shaped(syms, paths, {"igLuaState", "igTransform"}), (1, 0x34, 1))

    def test_member_class(self):
        self.assertEqual(progress.member_class("setVisualContext__10igRendererFP15igVisualContext"), "igRenderer")
        self.assertIsNone(progress.member_class("igRelease__FP8igObject"))
        self.assertIsNone(progress.member_class("igRenderer_SetVisualContext"))


class EmittedFunctions(unittest.TestCase):
    def judge(self, symbol, compiler_names):
        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "beCamera.cpp")
            with open(path, "w") as fh:
                fh.write(SOURCE)
            with open(os.path.join(tmp, "holder.h"), "w") as fh:
                fh.write(HEADER)
            with mock.patch.object(progress, "_symbol_address", return_value=0x200000), \
                    mock.patch.object(progress, "_emitted_names", return_value=compiler_names), \
                    mock.patch.dict(progress._HEADER_TEXTS, clear=True):
                return progress.readable_failures(symbol, path, {})

    def test_a_member_in_the_file_is_judged_alone(self):
        self.assertEqual(self.judge("Guard_Destruct", ["__dt__5GuardFv"]), [])

    def test_a_template_member_is_judged_alone(self):
        self.assertEqual(self.judge("Holder_3_Destruct", ["__dt__9Holder<3>Fv"]), [])

    def test_a_member_in_an_included_header_is_judged_alone(self):
        self.assertEqual(self.judge("igSmartPointer_igObject_Destruct",
                                    ["__dt__25igSmartPointer<8igObject>Fv"]), [])

    def test_the_member_text_still_fails_on_its_own_terms(self):
        self.assertEqual(self.judge("Bad_Destruct", ["__dt__3BadFv"]), ["addresses", "references"])

    def test_an_unknown_member_falls_back_to_the_whole_file(self):
        self.assertIn("references", self.judge("Missing_Destruct", ["__dt__7MissingFv"]))
        self.assertIn("references", self.judge("Plain_Destruct", []))


if __name__ == "__main__":
    unittest.main()
