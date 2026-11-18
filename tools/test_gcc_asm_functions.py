"""An EE GCC unit's assembly function: a file-scope `__asm__` block approved by an `asm-function` row."""
import os
import shutil
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import asmsources  # noqa: E402
import sourceapprovals as sa  # noqa: E402
import unitprofiles  # noqa: E402
import units  # noqa: E402


def block(*names, labelled=True):
    lines = ['__asm__(\n    "\\t.section .text.%s,\\"ax\\",@progbits\\n"\n' % (names[0] if names else "x")]
    for name in names:
        lines.append('    "\\t.globl %s\\n"\n' % name)
        if labelled:
            lines.append('    "%s:\\n"\n' % name)
        lines.append('    "\\tjr $31\\n"\n    "\\tnop\\n"\n')
    lines.append('    "\\t.previous\\n");\n')
    return "".join(lines)


UNIT = "int before(int a) { return a; }\n\n" + block("asm_fn") + "\nint after(int a) { return a + 1; }\n"
ROW = {("asm-function", "asm_fn"): (1, "#x")}


class GccAsmFunctions(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp(dir=os.path.join(sa.ROOT, "build"))
        self.addCleanup(shutil.rmtree, self.dir)

    def write(self, name, text):
        path = os.path.join(self.dir, name)
        with open(path, "w") as fh:
            fh.write(text)
        return path

    def test_the_block_defines_its_one_function(self):
        found = asmsources.gcc_functions(UNIT)
        self.assertEqual([name for name, _s, _e in found], ["asm_fn"])
        _name, start, end = found[0]
        self.assertTrue(UNIT[start:].startswith("__asm__("))
        self.assertTrue(UNIT[:end].endswith(");"))

    def test_the_scan_files_it_under_its_unit(self):
        path = self.write("unit.c", UNIT)
        index = units.scan(self.dir)
        self.assertEqual({name: index[name] for name in ("before", "asm_fn", "after")},
                         {"before": path, "asm_fn": path, "after": path})

    def test_an_approved_function_is_counted_as_an_asm_function(self):
        path = self.write("unit.c", UNIT)
        self.assertTrue(sa.defines(path, "asm_fn"))
        self.assertEqual(sa.uses(path, "asm_fn"), {"asm": 0, "volatile": 0, "asm-function": 1})
        self.assertTrue(sa.approved_asm_function(path, "asm_fn", ROW))
        self.assertIsNone(sa.problem(path, "asm_fn", ROW))
        self.assertEqual(len(sa.approved_statements([path], ROW)), 1)

    def test_an_unapproved_function_is_rejected(self):
        path = self.write("unit.c", UNIT)
        self.assertFalse(sa.approved_asm_function(path, "asm_fn", {}))
        self.assertEqual(sa.problem(path, "asm_fn", {}), "1 asm-function without an approval row")
        self.assertEqual(sa.approved_statements([path], {}), set())
        # a row for another kind approves nothing
        self.assertIsNotNone(sa.problem(path, "asm_fn", {("asm", "asm_fn"): (1, "#x")}))

    def test_the_c_around_it_is_unaffected(self):
        path = self.write("unit.c", UNIT)
        for name in ("before", "after"):
            self.assertEqual(sa.uses(path, name), {"asm": 0, "volatile": 0, "asm-function": 0}, name)
            self.assertIsNone(sa.problem(path, name, {}), name)
            self.assertFalse(sa.approved_asm_function(path, name, {("asm-function", name): (1, "#x")}), name)

    def test_the_unit_keeps_its_compiler(self):
        path = self.write("unit.c", UNIT)
        profile = unitprofiles.Profile("local/ee-gcc2.96/bin/ee-gcc", "-O2 -G0 -ffunction-sections", "off")
        self.assertFalse(unitprofiles.asm_body_source(path))
        self.assertIs(unitprofiles.for_source(profile, path, "-O4,p", "local/mwcc/mwccps2.exe"), profile)

    def test_a_block_defining_two_functions_or_none_is_refused(self):
        for text in (block("one", "two"), block("unlabelled", labelled=False), block()):
            with self.assertRaises(ValueError, msg=text):
                asmsources.gcc_functions("int f(void) { return 0; }\n" + text)
            self.write("bad.c", text)
            with self.assertRaises(ValueError, msg=text):
                units.scan(self.dir)

    def test_an_indented_statement_inside_a_function_is_no_block(self):
        text = 'void f(void) {\n    __asm__("sync");\n}\n'
        self.assertEqual(asmsources.gcc_functions(text), ())

    def test_the_shipped_block_is_approved(self):
        path = os.path.join(sa.ROOT, "src", "cri", "sfxz.c")
        self.assertIn("sfxzmv_GetZfrmInf", asmsources.gcc_function_names(path))
        self.assertTrue(sa.approved_asm_function(path, "sfxzmv_GetZfrmInf"))
        self.assertIsNone(sa.problem(path, "sfxzmv_GetZfrmInf"))


if __name__ == "__main__":
    unittest.main()
