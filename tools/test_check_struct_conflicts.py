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

    def test_a_later_parameter_of_the_units_class_is_the_receiver(self):
        path = self.write("igThing_tail.inc",
                          "struct Shader { int a; };\nstruct igThing;\n"
                          "void igThing_DrawShader(Shader *self, igThing *thing) { }\n"
                          "void igThing_Update(Other *o) { }\n")
        self.assertEqual(csc.receivers(path), {"Other"})

    def test_a_vtable_builder_holds_the_class_itself(self):
        self.assertTrue(csc._builds_instance("src/x/beThing_GetVTable.cpp"))
        self.assertFalse(csc._builds_instance("src/x/beThing_InitFields.cpp"))


class SourcedNames(unittest.TestCase):
    def test_a_member_a_source_names_is_not_offset_named(self):
        path = os.path.join(tempfile.mkdtemp(), "filt.c")
        open(path, "w").write("struct Filt { short k0; short k1; short d0; short d1; short f6; };\n")
        views = csc.collect([path], {})
        flagged = []
        csc.report_c(views, flagged, sourced=set())
        self.assertTrue(any(" d0 " in line for line in flagged))
        kept = []
        self.assertEqual(csc.report_c(views, kept, sourced={("Filt", "d0"), ("Filt", "d1")}), 1)
        self.assertFalse(any(" d0 " in line or " d1 " in line for line in kept))
        self.assertTrue(any(" f6 " in line for line in kept))


if __name__ == "__main__":
    unittest.main()
