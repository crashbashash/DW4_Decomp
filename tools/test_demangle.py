#!/usr/bin/env python3
"""tools/demangle.py: MWCC 3.0b52 compiler names read and written."""
import json
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import demangle as dm  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# the member-study prototype's compiler names (trial/map.tsv and the converted unit rows), in their kit form
PROTOTYPE = [
    "getClassTypeSafe__10igRendererFv", "arkRegister__10igRendererFv", "arkRegisterInternal__10igRendererFv",
    "getClassMetaSafe__10igRendererFv", "arkRegisterInitialize__10igRendererFv",
    "setVisualContext__10igRendererFP15igVisualContext", "getClassMeta__10igRendererFv",
    "getMeta__10igRendererCFv", "_Meta__10igRenderer", "k_visualContext__10igRenderer",
    "getClassTypeSafe__Q33Gap3Gui10igRendererFv", "retrieveVTablePointer__Q33Gap3Gui15igClearRendererFv",
    "setVisualContext__Q33Gap3Gui10igRendererFPQ33Gap3Gfx15igVisualContext", "__dt__Q33Gap3Gui10igRendererFv",
    "getMeta__Q33Gap3Gui10igRendererCFv", "__vt__Q33Gap3Gui10igRenderer", "__vt__Q33Gap3Gui15igClearRenderer",
    "_Meta__Q33Gap3Gui10igRenderer", "ArkCore__Q23Gap4Core", "__ct__Q33Gap4Core8igObjectFv",
]


def unit_object_names():
    with open(os.path.join(ROOT, "config", "SLUS-20836", "unit-objects.json")) as fh:
        rows = json.load(fh)
    names = set()
    for row in rows.values():
        for field in ("emitted", "duplicates", "externals", "data"):
            names.update(row.get(field) or {})
        names.update(row.get("stripped") or [])
        if row.get("symbol"):
            names.add(row["symbol"])
    return names


class Demangle(unittest.TestCase):
    def test_member_function(self):
        d = dm.demangle("setVisualContext__Q33Gap3Gui10igRendererFPQ33Gap3Gfx15igVisualContext")
        self.assertEqual((d.namespaces, d.class_name, d.name, d.params, d.const, d.special, d.data),
                         (("Gap", "Gui"), "igRenderer", "setVisualContext", ("Gap::Gfx::igVisualContext *",),
                          False, None, False))
        self.assertEqual(d.qualified, "Gap::Gui::igRenderer::setVisualContext")
        self.assertEqual(d.signature, "Gap::Gui::igRenderer::setVisualContext(Gap::Gfx::igVisualContext *)")

    def test_const_member_and_specials(self):
        self.assertEqual(dm.demangle("getMeta__10igRendererCFv").signature, "igRenderer::getMeta() const")
        d = dm.demangle("__dt__25igSmartPointer<8igObject>Fv")
        self.assertEqual((d.class_name, d.class_base, d.name, d.special),
                         ("igSmartPointer<igObject>", "igSmartPointer", "~igSmartPointer", "dtor"))
        d = dm.demangle("__ct__Q23Gap13BecLuaWrapperFv")
        self.assertEqual((d.namespaces, d.class_name, d.name, d.special), (("Gap",), "BecLuaWrapper",
                                                                           "BecLuaWrapper", "ctor"))
        d = dm.demangle("__vt__Q33Gap3Gui10igRenderer")
        self.assertEqual((d.qualified, d.special, d.data), ("Gap::Gui::igRenderer::__vt", "vt", True))
        self.assertEqual(dm.demangle("__dl__FPv").signature, "operator delete(void *)")
        self.assertEqual(dm.demangle("__as__9HitRecordFRC9HitRecord").signature,
                         "HitRecord::operator=(const HitRecord &)")

    def test_data_and_namespaces(self):
        d = dm.demangle("_Meta__10igRenderer")
        self.assertEqual((d.qualified, d.data, d.params), ("igRenderer::_Meta", True, ()))
        d = dm.demangle("__new_handler__3std")
        self.assertEqual((d.namespaces, d.class_name, d.qualified), (("std",), None, "std::__new_handler"))
        d = dm.demangle("__ct__Q43Gap3Lua9igLuaGlue5ClassFPCcPCcPFP9lua_State_iPFP9lua_State_iPFP9lua_State_i"
                        "PFP9lua_State_iPFP9lua_State_i")
        self.assertEqual((d.namespaces, d.class_name), (("Gap", "Lua"), "igLuaGlue::Class"))
        self.assertEqual(d.params[:3], ("const char *", "const char *", "int (*)(lua_State *)"))

    def test_types(self):
        self.assertEqual(dm.demangle("luaL_findstring__FPCcPCPCc").params, ("const char *", "const char *const *"))
        self.assertEqual(dm.demangle("__ct__14LuaStartupHookFPFv_PQ43Gap3Lua9igLuaGlue5Classi").params,
                         ("Gap::Lua::igLuaGlue::Class *(*)()", "int"))
        self.assertEqual(dm.demangle("__dt__36Hashed<Q43Gap3Lua9igLuaGlue5Class,7>Fv").class_name,
                         "Hashed<Gap::Lua::igLuaGlue::Class, 7>")
        self.assertEqual(dm.demangle("luaL_verror__FP9lua_StatePCce").params, ("lua_State *", "const char *", "..."))
        self.assertEqual(dm.demangle("posrelat__FlUi").params, ("long", "unsigned int"))

    def test_name_with_double_underscore(self):
        self.assertEqual(dm.demangle("luaB__ALERT__FP9lua_State").name, "luaB__ALERT")
        self.assertEqual(dm.demangle("__dt__26__partial_array_destructorFv").class_name, "__partial_array_destructor")

    def test_not_compiler_names(self):
        for name in ("FUN_00231010", "Gap__Attrs__igAttrDefaultManager__vfunc_23", "igRenderer_SetVisualContext",
                     "thunk_FUN_001592c0__0016e390", "igVertexArray2__FindVertexData", "@183", "watchNames$14",
                     "@STRING@what__Q23std9exceptionCFv", "__FindExceptionTable", "", "__dt__0Fv"):
            self.assertIsNone(dm.demangle(name), name)


class Mangle(unittest.TestCase):
    def test_contract_forms(self):
        self.assertEqual(dm.mangle("Gap::Gui::igRenderer::setVisualContext", ["Gap::Gfx::igVisualContext *"]),
                         "setVisualContext__Q33Gap3Gui10igRendererFPQ33Gap3Gfx15igVisualContext")
        self.assertEqual(dm.mangle("Gap::Gui::igRenderer::getMeta", [], const=True),
                         "getMeta__Q33Gap3Gui10igRendererCFv")
        self.assertEqual(dm.mangle("Gap::Gui::igRenderer::igRenderer", []), "__ct__Q33Gap3Gui10igRendererFv")
        self.assertEqual(dm.mangle("Gap::Gui::igRenderer::~igRenderer", ["void"]), "__dt__Q33Gap3Gui10igRendererFv")
        self.assertEqual(dm.mangle("Gap::Gui::igRenderer::__vt", None), "__vt__Q33Gap3Gui10igRenderer")
        self.assertEqual(dm.mangle("igRenderer::_Meta", None), "_Meta__10igRenderer")
        self.assertEqual(dm.mangle("igSmartPointer<igObject>::~igSmartPointer", []),
                         "__dt__25igSmartPointer<8igObject>Fv")
        self.assertEqual(dm.mangle("ObjRef<5>::~ObjRef", []), "__dt__9ObjRef<5>Fv")
        self.assertEqual(dm.mangle("igRelease", ["igObject *"]), "igRelease__FP8igObject")
        self.assertEqual(dm.mangle("operator delete", ["void*"]), "__dl__FPv")
        self.assertEqual(dm.mangle("plain_c_datum", None), "plain_c_datum")

    def test_spellings(self):
        for spelling, code in [("unsigned", "Ui"), ("long unsigned int", "Ul"), ("struct igObject*", "P8igObject"),
                               ("char*const*", "PCPc"), ("int(*)(lua_State*)", "PFP9lua_State_i"),
                               ("void (*)(void)", "PFv_v"), ("const Gap::Gfx::igVisualContext &",
                                                             "RCQ33Gap3Gfx15igVisualContext"),
                               ("igSmartPointer<igSmartPointer<igObject>>",
                                "43igSmartPointer<25igSmartPointer<8igObject>>"),
                               ("int (*)[3]", "PA3_i"), ("signed char", "Sc"), ("long double", "r")]:
            self.assertEqual(dm.encode_type(spelling), code, spelling)
            self.assertEqual(dm.encode_type(dm.format_type(dm.parse_type(spelling))), code, spelling)

    def test_refusals(self):
        for args in [("Foo::~Bar", []), ("igRenderer::get", ["frob int"]), ("f", [], True),
                     ("x::operator ?", [])]:
            with self.assertRaises(dm.MangleError, msg=args):
                dm.mangle(*args)


class RoundTrip(unittest.TestCase):
    def test_every_unit_object_and_prototype_name(self):
        """Each compiler name the rows hold reads back to itself: mangle(demangle(x)) == x."""
        names = unit_object_names() | set(PROTOTYPE)
        read = 0
        for name in sorted(names):
            d = dm.demangle(name)
            if d is None:
                continue
            read += 1
            self.assertEqual(dm.mangle(d.qualified, None if d.data else d.params, d.const), name)
            for param in d.params:
                self.assertEqual(dm.format_type(dm.parse_type(param)), param)
        for name in PROTOTYPE:
            self.assertIsNotNone(dm.demangle(name), name)
        self.assertGreater(read, 1000)


if __name__ == "__main__":
    unittest.main()
