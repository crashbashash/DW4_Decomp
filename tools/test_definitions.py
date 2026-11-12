"""units.definitions on K&R definitions, the style of the stock libraries."""
import unittest

import units


def names(text):
    return [name for name, _start, _end in units.definitions(text)]


class KAndR(unittest.TestCase):
    def test_parameter_declarations_before_the_body(self):
        text = "#define local static\nint first(a, b)\n  int a;\n  char *b;\n{\n  return a;\n}\n"
        (name, start, end), = units.definitions(text)
        self.assertEqual(name, "first")
        self.assertEqual(text[start:start + 9], "int first")
        self.assertEqual(text[end - 1], "}")

    def test_macros_and_pointers_in_the_head(self):
        text = "uLong ZEXPORT sum(adler, buf, len)\n  uLong adler;\n  const Bytef *buf;\n  uInt len;\n{ }\n"
        self.assertEqual(names(text), ["sum"])

    def test_after_declarations_and_other_definitions(self):
        text = ("static int table[4];\nint proto(int);\nlocal int one(a)\nint a;\n{ }\n"
                "int two(void) { }\nint three(b)\nint b;\n{ if (b) { } }\n")
        self.assertEqual(names(text), ["one", "two", "three"])

    def test_extract_keeps_only_the_named_definition(self):
        text = "int one(a)\nint a;\n{ return 1; }\nint two(b)\nint b;\n{ return 2; }\n"
        kept = units.extract(text, "two")
        self.assertIn("return 2", kept)
        self.assertNotIn("return 1", kept)

    def test_prototypes_and_bare_blocks_are_not_definitions(self):
        self.assertEqual(names("int f(a, b);\nint x;\nstruct s { int y; };\n"), [])

    def test_extract_keeps_an_inline_helper(self):
        text = "static inline int one(void) { return 1; }\nint two(void) { return one(); }\nint three(void) { }\n"
        kept = units.extract(text, "two")
        self.assertIn("return 1", kept)
        self.assertNotIn("three", kept)

    def test_one_line_macros_with_braces_are_not_definitions(self):
        text = ("#define ADD(x) do { (x)++; } while (0)\n#define DROP(x) do { (x)--; } while (0)\n"
                "#define LONG(x) do { \\\n (x) = 0; } while (0)\nint f(int a) { ADD(a); DROP(a); return a; }\n")
        self.assertEqual(names(text), ["f"])
        kept = units.extract(text, "f")
        self.assertIn("#define DROP(x) do { (x)--; }", kept)


class SpecialMembers(unittest.TestCase):
    def test_constructor_with_initialisers_and_destructor_are_named_by_class(self):
        text = ("struct Holder { Holder(int *w); ~Holder(); int *a; int *b; };\n"
                "Holder::Holder(int *w)\n    : a(make(0)), b(w) {\n}\n"
                "Holder::~Holder() {\n    a = 0;\n}\n"
                "void Holder_use(Holder *h) { h->a = 0; }\n")
        self.assertEqual(names(text), ["Holder::Holder", "Holder::~Holder", "Holder_use"])

    def test_a_qualified_ordinary_member_keeps_its_own_name(self):
        self.assertEqual(names("int Holder::count(int n) { return n; }\n"), ["count"])

    def test_mangled_constructor_and_destructor_name_the_definition(self):
        import unitobjects
        self.assertEqual(unitobjects.special_member("__ct__11ViewerSetupFP8igObject"), "ViewerSetup::ViewerSetup")
        self.assertEqual(unitobjects.special_member("__dt__6HolderFv"), "Holder::~Holder")
        self.assertIsNone(unitobjects.special_member("luaA_index__FP9lua_Statei"))
        self.assertIsNone(unitobjects.special_member("__ct__99ShortFv"))

    def test_an_owner_written_as_a_constructor_gets_its_source(self):
        import json, os, tempfile, unitobjects
        with tempfile.TemporaryDirectory() as tmp:
            symbols = os.path.join(tmp, "symbols.txt")
            rows = os.path.join(tmp, "unit-objects.json")
            with open(symbols, "w") as fh:
                fh.write("00100000 000040 FUN_00100000\n00100040 000040 FUN_00100040\n")
            with open(rows, "w") as fh:
                json.dump({"0x00100000": {"whole_file": True, "symbol": "__ct__6HolderFPi",
                                          "emitted": {"__dt__6HolderFv": "0x00100040"}}}, fh)
            unitobjects.load.cache_clear()
            try:
                index = unitobjects.augment_sources({"Holder::Holder": "src/x.cpp"}, symbols, rows)
            finally:
                unitobjects.load.cache_clear()
        self.assertEqual(index["FUN_00100000"], "src/x.cpp")
        self.assertEqual(index["FUN_00100040"], "src/x.cpp")


if __name__ == "__main__":
    unittest.main()
