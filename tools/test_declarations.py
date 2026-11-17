#!/usr/bin/env python3
"""Declaration debt (tools/declarations.py) and the `declarations` readable check on a small tree."""
import os
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import declarations  # noqa: E402
import progress  # noqa: E402

TREE = {
    # a fixed-parameter function, declared `(...)` in a header
    "src/game/foo.c": "#include \"dw4/foo.h\"\nint Foo_Get(int index) { return index; }\n",
    "include/dw4/foo.h": "int Foo_Get(...);\nint Log_Printf(...);\nint Asm_Only(...);\n",
    # a variadic definition: `(...)` declarations of it are not debt
    "src/game/log.c": "#include \"dw4/foo.h\"\nint Log_Printf(const char *format, ...) { return 0; }\n",
    # a scalar declared as an array by a C++ unit that does not define it
    "src/game/pool.c": "int g_poolSize;\n",
    "src/game/main.cpp": "extern \"C\" int g_poolSize[4];\n"
                         "extern \"C\" void Main_Run(int);\n"
                         "void Main_Run(int count) { g_poolSize[0] = count; }\n"
                         "extern \"C\" void Main_Idle(void) { }\n",
    # a local extern of a symbol a header already declares
    "include/dw4/count.h": "extern int g_count;\nvoid Count_Reset(void);\n",
    "src/game/count.c": "#include \"dw4/count.h\"\nint g_count;\nvoid Count_Reset(void) { g_count = 0; }\n",
    "src/game/user.c": "#include \"dw4/count.h\"\nextern int g_count;\n"
                       "int Foo_Get();\n"
                       "extern int DAT_00401234;\nint FUN_00401300(int);\n"
                       "extern int g_asmTable;\nextern int g_asmShared;\n"
                       "int User_Read(void) { return g_count; }\n"
                       "void User_Clear(void) { Count_Reset(); }\n"
                       "int User_Placeholder(void) { return DAT_00401234 + g_asmTable; }\n",
    # two headers that disagree
    "include/dw4/a.h": "extern \"C\" int Shared_Get(int);\n",
    "include/dw4/b.h": "extern \"C\" short Shared_Get(int);\n",
    # an old-style definition and a fragment of a unity unit
    "src/game/old.c": "extern int g_asmShared;\n"
                      "int Old_Add(a, b)\n    int a;\n    int b;\n{\n    return a + b;\n}\n",
    "src/game/unity.cpp": "#include \"src/game/part.inc\"\nextern \"C\" int Part_Value(void) { return 1; }\n",
    "src/game/part.inc": "extern \"C\" int Part_Value(void);\nextern \"C\" int Part_Use(void) { return Part_Value(); }\n",
    # a library header only its unity unit includes: its own prototypes are not debt, a copy of
    # another unit's symbol is
    "src/engine/LibLibrary.h": "extern \"C\" int Lib_Own(void);\nextern \"C\" int Foreign_Get(void);\n",
    "src/engine/lib.cpp": "#include \"src/engine/LibLibrary.h\"\n"
                          "extern \"C\" int Lib_Own(void) { return Foreign_Get(); }\n",
    "src/engine/foreign.c": "int Foreign_Get(void) { return 2; }\n",
    # gcc's mode attribute: DItype is long long, so the header's long long declaration agrees and the
    # copy declaring int parameters does not
    "src/libgcc/mul.c": "typedef int DItype __attribute__((mode(DI)));\n"
                        "DItype __muldi3(DItype u, DItype v) { return u * v; }\n",
    "include/dw4/soft.h": "long long __muldi3(long long, long long);\n",
    "src/game/narrow.c": "int __muldi3(int, int);\nint Narrow_Mul(int a) { return __muldi3(a, a); }\n",
    # a home under include/ that only one unit includes so far is still a home, not that unit's text
    "include/dw4/pnglike.h": "int Png_Read(int);\n",
    "src/game/pnglib.c": "int Png_Read(int n) { return n; }\n",
    "src/game/reader.c": "#include \"dw4/pnglike.h\"\nint Reader_Go(void) { return Png_Read(1); }\n",
}


class Declarations(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.folder = tempfile.TemporaryDirectory()
        for rel, text in TREE.items():
            path = os.path.join(cls.folder.name, rel)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as fh:
                fh.write(text)
        cls.idx = declarations.Index(cls.folder.name)

    @classmethod
    def tearDownClass(cls):
        cls.folder.cleanup()

    def names(self, decls):
        return sorted((d.path, d.name) for d in decls)

    def test_varargs_counts_a_fixed_definition_and_an_assembly_symbol(self):
        # and a C `()` declaration of a function whose definition takes parameters
        self.assertEqual(self.names(self.idx.varargs),
                         [("include/dw4/foo.h", "Asm_Only"), ("include/dw4/foo.h", "Foo_Get"),
                          ("src/game/user.c", "Foo_Get")])

    def test_a_variadic_definition_is_not_varargs_debt(self):
        self.assertNotIn("Log_Printf", {d.name for d in self.idx.varargs + self.idx.conflicts})

    def test_array_against_scalar_is_a_conflict(self):
        # and a mode(DI) typedef's real type: only the int copy of __muldi3 disagrees with it
        self.assertEqual(self.names(self.idx.conflicts),
                         [("src/game/main.cpp", "g_poolSize"), ("src/game/narrow.c", "__muldi3")])

    def test_local_externs(self):
        # the C++ unit's extern "C" line for its own Main_Run, the fragment's line for its unit's
        # Part_Value and the library header's Lib_Own are linkage, not debt; FUN_/DAT_ placeholders and
        # g_asmTable (assembly, one consumer) stay where they are used; g_asmShared has two consumers
        self.assertEqual(self.names(self.idx.local),
                         [("src/engine/LibLibrary.h", "Foreign_Get"), ("src/game/main.cpp", "g_poolSize"),
                          ("src/game/narrow.c", "__muldi3"),
                          ("src/game/old.c", "g_asmShared"), ("src/game/user.c", "Foo_Get"),
                          ("src/game/user.c", "g_asmShared"), ("src/game/user.c", "g_count")])

    def test_header_conflicts(self):
        self.assertEqual(self.idx.header_conflicts, ["Shared_Get"])

    def test_a_one_includer_home_under_include_is_not_own_text(self):
        self.assertNotIn("Png_Read", {d.name for d in self.idx.local})

    def test_old_style_definition_is_a_definition(self):
        old = self.idx.definition["Old_Add"]
        self.assertEqual((old.ret, old.params), ("int", None))

    def test_counts(self):
        self.assertEqual(self.idx.counts(), {"decl.local_externs": 7, "decl.varargs": 3,
                                             "decl.type_conflicts": 2, "decl.header_conflicts": 1})

    def test_bad_names_per_unit(self):
        root = self.folder.name
        self.assertEqual(self.idx.bad_names(os.path.join(root, "src/game/user.c")),
                         {"g_count", "Foo_Get", "g_asmShared"})
        self.assertEqual(self.idx.bad_names(os.path.join(root, "src/engine/lib.cpp")), {"Foreign_Get"})
        self.assertEqual(self.idx.bad_names(os.path.join(root, "src/game/foo.c")),
                         {"Foo_Get", "Asm_Only"})
        self.assertEqual(self.idx.bad_names(os.path.join(root, "src/game/part.inc")), frozenset())

    def test_member_access_is_not_a_use(self):
        self.assertEqual(declarations.used_bad("{ return p->g_count + q.g_count; }", {"g_count"}), set())
        self.assertEqual(declarations.used_bad("{ return g_count; }", {"g_count"}), {"g_count"})

    def test_readable_check(self):
        root = self.folder.name
        with mock.patch.object(progress.declarations, "index", lambda _root: self.idx):
            cache = {}
            user = os.path.join(root, "src/game/user.c")
            self.assertIn("declarations", progress.readable_failures("User_Read", user, cache))
            self.assertNotIn("declarations", progress.readable_failures("User_Clear", user, cache))
            self.assertNotIn("declarations", progress.readable_failures("User_Placeholder", user, cache))
            main = os.path.join(root, "src/game/main.cpp")
            self.assertIn("declarations", progress.readable_failures("Main_Run", main, cache))
            self.assertNotIn("declarations", progress.readable_failures("Main_Idle", main, cache))


if __name__ == "__main__":
    unittest.main()
