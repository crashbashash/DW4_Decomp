"""Section census of the last relink: every section name is accounted for in tools/verify.py.

Scans every object `make link` wrote under build/link/ (u_*.o) and requires each section
name to be in exactly one of verify.COMPARED_SECTIONS (compared with retail or
deliberately ignored, with its reason) or verify.DEBT_SECTIONS (known, not yet compared).
An unknown name fails naming the object and section; a `.data`/`.bss` with content fails
too (ee-gcc emits them empty; a filled one would be an unowned allocated section).

Needs a prior `make link`: without build/link/ the scan is skipped with a message. The
scan parses ~36k section header tables and takes a few seconds.
"""
import glob
import os
import unittest

import verify

OBJECTS = os.path.join(verify.ROOT, "build", "link", "u_*.o")


class Tables(unittest.TestCase):
    def test_tables_are_disjoint_and_explained(self):
        for key, reason in verify.COMPARED_SECTIONS.items():
            self.assertTrue(reason and len(reason.splitlines()) == 1, key)
        compared = {k if isinstance(k, str) else k.pattern for k in verify.COMPARED_SECTIONS}
        debt = {k if isinstance(k, str) else k.pattern for k in verify.DEBT_SECTIONS}
        self.assertFalse(compared & debt)
        self.assertEqual(verify.DEBT_SECTIONS, {}, "no section is knowingly left uncompared today")

    def test_roles(self):
        self.assertEqual(verify.section_role(".text"), "compared")
        self.assertEqual(verify.section_role(".rodata.dw4_004ffb80"), "compared")
        self.assertEqual(verify.section_role(".rel.rodata.dw4_004ffb80"), "compared")
        self.assertIsNone(verify.section_role(".sdata"))
        self.assertIsNone(verify.section_role(".rodata.str1.4"))


class LastRelink(unittest.TestCase):
    def test_every_section_of_every_object_is_accounted_for(self):
        objects = sorted(glob.glob(OBJECTS))
        if not objects:
            self.skipTest("build/link/ has no objects: run `make link` first, then this census")
        counts, unknown, filled = verify.section_census(objects)
        self.assertEqual(unknown, [], "sections outside COMPARED_SECTIONS/DEBT_SECTIONS (object, name): %r"
                         % [(os.path.basename(p), n) for p, n in unknown[:10]])
        self.assertEqual(filled, [], "empty-only sections with content: %r"
                         % [(os.path.basename(p), n, s) for p, n, s in filled[:10]])
        self.assertEqual(counts[".text"], len(objects))
        self.assertIn(".exceptix", counts)


if __name__ == "__main__":
    unittest.main()
