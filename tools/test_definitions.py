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


if __name__ == "__main__":
    unittest.main()
