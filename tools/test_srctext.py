"""Unity-built units: tools read a unit's `#include "src/..."` fragments as the compiler does."""
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import srctext  # noqa: E402
import units  # noqa: E402


def write(root, rel, text):
    path = os.path.join(root, rel)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as fh:
        fh.write(text)
    return path


class Expansion(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = self.tmp.name
        write(self.root, "src/engine/lib/Lib.h", 'int shared(void);\n#include "dw4/reflected.h"\n')
        write(self.root, "src/engine/lib/First.inc", "int first(void) { return 1; }\n")
        write(self.root, "src/engine/lib/Second.inc",
              '#include "src/engine/lib/Nested.inc"\nint second(void) { return 2; }\n')
        write(self.root, "src/engine/lib/Nested.inc", "static int nested(void) { return 3; }\n")
        self.unit = write(self.root, "src/engine/lib/Lib.cpp",
                          '#include "src/engine/lib/Lib.h"\n#include "src/engine/lib/First.inc"\n'
                          '#include "src/engine/lib/Second.inc"\n')

    def tearDown(self):
        self.tmp.cleanup()

    def test_expands_repository_includes_in_order(self):
        text = srctext.read(self.unit, root=self.root)
        self.assertLess(text.index("first"), text.index("nested"))
        self.assertLess(text.index("nested"), text.index("second"))
        self.assertNotIn('#include "src/', text)

    def test_keeps_other_includes(self):
        self.assertIn('#include "dw4/reflected.h"', srctext.read(self.unit, root=self.root))

    def test_definitions_seen_through_fragments(self):
        names = [n for n, _s, _e in units.definitions(srctext.read(self.unit, root=self.root))]
        self.assertEqual(names, ["first", "nested", "second"])

    def test_included_lists_every_fragment(self):
        self.assertEqual(srctext.included(self.unit, root=self.root),
                         ["src/engine/lib/Lib.h", "src/engine/lib/First.inc",
                          "src/engine/lib/Second.inc", "src/engine/lib/Nested.inc"])

    def test_plain_file_unchanged(self):
        path = write(self.root, "src/engine/Plain.c", "int plain(void) { return 0; }\n")
        self.assertEqual(srctext.read(path, root=self.root), "int plain(void) { return 0; }\n")

    def test_self_include_refused(self):
        loop = write(self.root, "src/engine/lib/Loop.inc", '#include "src/engine/lib/Loop.inc"\n')
        with self.assertRaises(ValueError):
            srctext.read(loop, root=self.root)


class ScanThroughUnits(unittest.TestCase):
    def test_scan_maps_fragment_functions_to_the_unit(self):
        with tempfile.TemporaryDirectory() as root:
            write(root, "src/engine/lib/A.inc", "int fragment_a(void) { return 1; }\n")
            unit = write(root, "src/engine/lib/Lib.cpp", '#include "src/engine/lib/A.inc"\n')
            empty = write(root, "unit-objects.json", "{}")
            old = srctext.ROOT
            srctext.ROOT = root
            try:
                table = units.scan(os.path.join(root, "src"), symbols=os.devnull, unit_objects=empty)
            finally:
                srctext.ROOT = old
            self.assertEqual(table.get("fragment_a"), unit)


if __name__ == "__main__":
    unittest.main()
