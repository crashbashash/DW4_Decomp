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
    # the symbol map names 0x401300 (user.c spells it FUN_00401300); 0x401234 has no name yet
    "config/SLUS-20836/symbols.txt": "# va size name\n00401300 000010 Real_Named\n00401400 000010 FUN_00401400\n",
    "src/game/alias.c": "/* FUN_00401300 in a comment */\nvoid FUN_00401400(void) { }\n",
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
                                             "decl.type_conflicts": 2, "decl.header_conflicts": 1,
                                             "decl.named_placeholders": 1, "decl.member_conflicts": 0})

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

    def test_a_placeholder_for_a_named_address(self):
        self.assertEqual(self.idx.named_placeholders(), [("src/game/user.c", 5, "FUN_00401300", "Real_Named")])


class ApprovedLocalDeclarations(unittest.TestCase):
    """A `local-decl` row exempts the copies of its symbol, while the tree holds exactly its count."""

    @classmethod
    def setUpClass(cls):
        cls.folder = tempfile.TemporaryDirectory()
        for rel, text in TREE.items():
            path = os.path.join(cls.folder.name, rel)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as fh:
                fh.write(text)

    @classmethod
    def tearDownClass(cls):
        cls.folder.cleanup()

    def index(self, **rows):
        return declarations.Index(self.folder.name, {name: (count, "#why") for name, count in rows.items()})

    def local(self, idx):
        return sorted((d.path, d.name) for d in idx.local)

    def test_an_approved_copy_is_not_counted_or_bad(self):
        idx = self.index(g_count=1)
        self.assertNotIn(("src/game/user.c", "g_count"), self.local(idx))
        self.assertEqual(idx.counts()["decl.local_externs"], 6)
        user = os.path.join(self.folder.name, "src/game/user.c")
        self.assertEqual(idx.bad_names(user), {"Foo_Get", "g_asmShared"})

    def test_an_approved_copy_is_no_type_or_varargs_debt(self):
        # narrow.c's int copy of __muldi3 is a type conflict; user.c's `()` Foo_Get is varargs debt
        plain = declarations.Index(self.folder.name, {})
        approved = self.index(__muldi3=1, Foo_Get=1)
        self.assertEqual(plain.counts()["decl.type_conflicts"] - approved.counts()["decl.type_conflicts"], 1)
        self.assertEqual(plain.counts()["decl.varargs"] - approved.counts()["decl.varargs"], 1)
        narrow = os.path.join(self.folder.name, "src/game/narrow.c")
        self.assertIn("__muldi3", plain.bad_names(narrow))
        self.assertNotIn("__muldi3", approved.bad_names(narrow))

    def test_an_approved_copy_stays_listed(self):
        idx = self.index(g_count=1)
        listed = {(d.path, d.name): why for d, why in idx.local_listing}
        self.assertEqual(listed[("src/game/user.c", "g_count")], "#why")
        self.assertIsNone(listed[("src/game/user.c", "Foo_Get")])
        self.assertEqual(len(idx.local_listing), 7)

    def test_a_row_covers_every_copy_of_its_symbol(self):
        # g_asmShared is declared in two units
        idx = self.index(g_asmShared=2)
        self.assertEqual({n for _p, n in self.local(idx)} & {"g_asmShared"}, set())
        self.assertEqual(idx.counts()["decl.local_externs"], 5)

    def test_an_excess_copy_voids_the_approval(self):
        idx = self.index(g_asmShared=1)
        self.assertEqual([n for _p, n in self.local(idx)].count("g_asmShared"), 2)
        self.assertEqual(idx.counts()["decl.local_externs"], 7)

    def test_a_copy_gone_voids_the_approval(self):
        idx = self.index(g_count=2)
        self.assertIn(("src/game/user.c", "g_count"), self.local(idx))
        self.assertEqual(idx.local_declared["g_count"], 1)

    def test_a_row_does_not_approve_another_symbol(self):
        self.assertEqual(self.local(self.index(g_nothing=1)), self.local(declarations.Index(self.folder.name, {})))

    def test_readable_passes_only_with_the_row(self):
        user = os.path.join(self.folder.name, "src/game/user.c")
        for rows, expect in (({}, True), ({"g_count": 1}, False), ({"g_count": 2}, True)):
            idx = self.index(**rows)
            with mock.patch.object(progress.declarations, "index", lambda _root, idx=idx: idx):
                failed = progress.readable_failures("User_Read", user, {})
            self.assertEqual("declarations" in failed, expect, rows)


UNIT_VIEW_TREE = {
    # object-like macros the defining file states its parameters with (newlib's RARG)
    "include/dw4/m.h": "struct _reent;\n"
                       "void *M_Alloc(struct _reent *, unsigned);\n"
                       "int M_Info(struct _reent *);\n"
                       "int M_Short(int);\n"
                       "int M_Cond(int);\n"
                       "int M_Late(int);\n",
    "src/newlib/m.c": "#include \"dw4/m.h\"\n"
                      "#define RARG struct _reent *reent_ptr,\n"
                      "#define RONEARG struct _reent *reent_ptr\n"
                      "#define SHORTARG short n\n"
                      "#ifdef M_WIDE\n#define CONDARG int n\n#endif\n"
                      "void *M_Alloc(RARG unsigned n) { return 0; }\n"
                      "int M_Info(RONEARG) { return 0; }\n"
                      "int M_Short(SHORTARG) { return n; }\n"
                      "int M_Cond(CONDARG) { return 0; }\n"
                      "int M_Late(LATEARG) { return 0; }\n"
                      "#define LATEARG int n\n",
    # a macro standing for the whole list: a `()` copy states nothing of it, or nothing of nothing
    "src/newlib/n.c": "#define VOIDARG void\n#define TWOARGS int a, int b\n"
                      "int N_None(VOIDARG) { return 0; }\nint N_Two(TWOARGS) { return a + b; }\n",
    "src/newlib/user.c": "int N_None();\nint N_Two();\nint User_Go(void) { return N_None() + N_Two(1, 2); }\n",
    # a typedef name the tree gives two meanings (libgcc's FLO_type), each unit seeing one of them
    "include/dw4/dp.h": "typedef double FLO;\n",
    "include/dw4/sp.h": "typedef float FLO;\n",
    "include/dw4/soft.h": "double Dp_Add(double, double);\nfloat Sp_Add(float, float);\n"
                          "float Dp_Mul(float, float);\ndouble Dp_Sub(double, double);\nfloat Dp_Div(float, float);\n",
    "src/libgcc/dp.c": "#include \"dw4/dp.h\"\n#include \"dw4/soft.h\"\n"
                       "FLO Dp_Add(FLO a, FLO b) { return a + b; }\nFLO Dp_Mul(FLO a, FLO b) { return a * b; }\n",
    "src/libgcc/sp.c": "#include \"dw4/sp.h\"\n#include \"dw4/soft.h\"\n"
                       "FLO Sp_Add(FLO a, FLO b) { return a + b; }\n",
    # a definer that does not include the header: each side as the units reading it see it
    "src/libgcc/sub.c": "#include \"dw4/dp.h\"\n"
                        "FLO Dp_Sub(FLO a, FLO b) { return a - b; }\nFLO Dp_Div(FLO a, FLO b) { return a / b; }\n",
    # a calling-convention macro and a memory-model one, each defined under conditions the tool cannot
    # decide (libpng's PNGAPI, zlib's FAR): every definition only decorates, so the types agree
    "include/dw4/api.h": "typedef struct Api_State *Api_Ptr;\nvoid Api_Read(Api_Ptr);\nint Api_Wide(Api_Ptr);\n",
    "src/third_party/api/apiconf.h": "#ifdef _WIN32\n#define API __cdecl\n#define FAR far\n#else\n#define API\n"
                                     "#define FAR\n#endif\n#ifdef API_WIDE\n#define WIDE long long\n#endif\n",
    "src/third_party/api/api.c": "#include \"apiconf.h\"\n#include \"dw4/api.h\"\n"
                                 "typedef struct Api_State FAR *Api_Ptr;\n"
                                 "void API Api_Read(Api_Ptr p) { }\nWIDE Api_Wide(Api_Ptr p) { return 0; }\n",
}


class UnitView(unittest.TestCase):
    """A declaration is compared with its definition as the defining unit reads both: its object-like
    macros expanded and its own typedefs, where the tree's reading finds a difference."""

    @classmethod
    def setUpClass(cls):
        cls.folder = tempfile.TemporaryDirectory()
        for rel, text in UNIT_VIEW_TREE.items():
            path = os.path.join(cls.folder.name, rel)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as fh:
                fh.write(text)
        cls.idx = declarations.Index(cls.folder.name, {})
        cls.conflicts = {d.name for d in cls.idx.conflicts}
        cls.varargs = {d.name for d in cls.idx.varargs}

    @classmethod
    def tearDownClass(cls):
        cls.folder.cleanup()

    def test_a_macro_spelling_the_same_parameters_agrees(self):
        self.assertNotIn("M_Alloc", self.conflicts)
        self.assertNotIn("M_Info", self.conflicts)

    def test_a_macro_spelling_another_type_conflicts(self):
        self.assertIn("M_Short", self.conflicts)

    def test_a_macro_defined_under_an_undecided_condition_or_later_is_not_expanded(self):
        self.assertIn("M_Cond", self.conflicts)
        self.assertIn("M_Late", self.conflicts)

    def test_a_macro_list_against_an_unstated_one(self):
        self.assertNotIn("N_None", self.varargs)
        self.assertIn("N_Two", self.varargs)

    def test_a_typedef_reads_as_its_unit_defines_it(self):
        self.assertNotIn("Dp_Add", self.conflicts)
        self.assertNotIn("Sp_Add", self.conflicts)
        self.assertNotIn("Dp_Sub", self.conflicts)

    def test_a_typedef_with_another_meaning_in_its_unit_conflicts(self):
        self.assertIn("Dp_Mul", self.conflicts)
        self.assertIn("Dp_Div", self.conflicts)

    def test_a_decorating_macro_adds_nothing_to_a_type(self):
        self.assertNotIn("Api_Read", self.conflicts)

    def test_the_counts(self):
        self.assertEqual(sorted(self.conflicts), ["Api_Wide", "Dp_Div", "Dp_Mul", "M_Cond", "M_Late", "M_Short"])
        self.assertEqual(sorted(self.varargs), ["N_Two"])


MEMBER_TREE = {
    "include/dw4/core/macros.h": "#define OBJ_COMMON(C) \\\n    public: static int arkRegister(); \\\n"
                                 "    int getMeta() const;\n",
    "include/dw4/support/reflected.h": (
        "#ifdef __cplusplus\n#include \"dw4/core/macros.h\"\n#endif\n"
        "typedef struct igObject {\n    int _vtable;\n} igObject;\n"
        "#ifdef __cplusplus\ntypedef struct Widget : public igObject {\n#else\n"
        "typedef struct Widget {\n    int _vtable;\n#endif\n    int _count;\n"
        "#ifdef __cplusplus\n    OBJ_COMMON(Widget)\n    static int *k_count;\n    void set(int count);\n"
        "    unsigned int size() const;\n#endif\n} Widget;\n"),
    # agreeing out-of-class definitions: typedefs, parameter names and a namespace are spelling only
    "src/game/widget.cpp": (
        "#include \"dw4/support/reflected.h\"\ntypedef unsigned int u32;\n"
        "int *Widget::k_count;\nint Widget::arkRegister() { return 0; }\nint Widget::getMeta() const { return 0; }\n"
        "void Widget::set(int value) { _count = value; }\nu32 Widget::size() const { return 4; }\n"
        "namespace Gap { namespace Gui {\nclass Panel {\npublic:\n    void show();\n};\n"
        "void Panel::show() { }\n} }\n"),
    # a definition its class states otherwise, and a member no body of its class declares
    "src/game/broken.cpp": (
        "#include \"dw4/support/reflected.h\"\nstruct Helper {\n    void run(int);\n};\n"
        "void Helper::run(long n) { }\nint Widget::missing() { return 1; }\nlong Widget::k_count;\n"),
    # a class no body of the tree declares is not judged
    "src/game/loose.cpp": "void Unknown::go() { }\n",
}


class MemberDeclarations(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.folder = tempfile.TemporaryDirectory()
        for rel, text in MEMBER_TREE.items():
            path = os.path.join(cls.folder.name, rel)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as fh:
                fh.write(text)
        cls.idx = declarations.Index(cls.folder.name, approvals={})

    @classmethod
    def tearDownClass(cls):
        cls.folder.cleanup()

    def test_conflicts(self):
        found = sorted((d.path, d.cls, d.name) for d, _why in self.idx.member_conflicts())
        self.assertEqual(found, [("src/game/broken.cpp", "Helper", "run"),
                                 ("src/game/broken.cpp", "Widget", "k_count"),
                                 ("src/game/broken.cpp", "Widget", "missing")])
        self.assertEqual(self.idx.counts()["decl.member_conflicts"], 3)

    def test_the_reason_names_the_declaration(self):
        why = {d.name: reason for d, reason in self.idx.member_conflicts()}
        self.assertIn("void Helper::run(int)", why["run"])
        self.assertIn("no declaration of missing", why["missing"])
        self.assertIn("Widget::k_count", why["k_count"])


class FunctionMacros(unittest.TestCase):
    def test_a_call_of_another_arity_is_no_invocation(self):
        macros = declarations.function_macros(["#define unlink(a, b, c) _unlink_r(a, b, c)\n"])
        text = "void unlink(); x = unlink(p, q, r);"
        self.assertEqual(declarations.expand_function_macros(text, macros),
                         "void unlink(); x =  _unlink_r(p, q, r) ;")


if __name__ == "__main__":
    unittest.main()
