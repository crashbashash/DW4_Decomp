#!/usr/bin/env python3
"""Which local views scripts/check_struct_conflicts.py compares with the class a unit is named for."""
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "scripts"))
import check_struct_conflicts as csc  # noqa: E402


class Receivers(unittest.TestCase):
    def write(self, name, text):
        d = tempfile.mkdtemp()
        path = os.path.join(d, name)
        open(path, "w").write(text)
        return path

    def test_the_first_parameter_is_the_receiver(self):
        path = self.write("Gap__Bec__beThing__vfunc_21.cpp",
                          "struct Thing { int a; };\nstruct Other { int b; };\n"
                          "void Gap__Bec__beThing__vfunc_21(Thing *self, Other *o) { }\n")
        self.assertEqual(csc.receivers(path), {"Thing"})

    def test_a_const_reference_is_a_receiver(self):
        path = self.write("beThing_Update.cpp", "struct T { int a; };\nint beThing_Update(const T &t) { return t.a; }\n")
        self.assertEqual(csc.receivers(path), {"T"})

    def test_a_prototype_is_not_a_definition(self):
        path = self.write("beThing_Update.c", "struct T;\nint other(struct T *t);\nint beThing_Update(void) { return 0; }\n")
        self.assertEqual(csc.receivers(path), set())

    def test_a_vtable_builder_holds_the_class_itself(self):
        self.assertTrue(csc._builds_instance("src/x/beThing_GetVTable.cpp"))
        self.assertFalse(csc._builds_instance("src/x/beThing_InitFields.cpp"))


if __name__ == "__main__":
    unittest.main()
