#!/usr/bin/env python3
"""A static initialiser's dotted compiler name (`__sinit_<file>`) through split, lookup and progress."""
import json
import os
import shutil
import subprocess
import tempfile
import unittest

import progress
import split
import unitobjects
import units

NAME = "__sinit_fixture.cpp"
SOURCE = """
struct Holder { int value; Holder(int v) : value(v) {} };
Holder g_holder(1);
%s
extern "C" void fixture_owner(void) { extern int DAT_00500000; DAT_00500000 = g_holder.value; }
"""


class StaticInitialiserNames(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="dw4-sinit-")
        self.addCleanup(temp.cleanup)
        self.root = temp.name
        self.symbols = os.path.join(self.root, "symbols.txt")
        with open(self.symbols, "w") as fh:
            fh.write("00180000 000010 fixture_owner\n0051fd00 000008 %s\n" % NAME)
        self.registry = os.path.join(self.root, "objects.json")
        with open(self.registry, "w") as fh:
            json.dump({"0x180000": {"whole_file": True, "emitted": {NAME: "0x0051fd00"}}}, fh)
        unitobjects.load.cache_clear()
        self.addCleanup(unitobjects.load.cache_clear)
        self.src = os.path.join(self.root, "src")
        os.makedirs(self.src)
        self.source = os.path.join(self.src, "fixture.cpp")

    def write(self, globals_=""):
        with open(self.source, "w") as fh:
            fh.write(SOURCE % globals_)

    def test_sanitize_keeps_only_an_initialisers_dot(self):
        self.assertEqual(split.sanitize(NAME), NAME)
        self.assertEqual(split.sanitize("__sinit"), "__sinit")
        self.assertEqual(split.sanitize("Gap::Foo.bar"), "Gap__Foo_bar")

    def test_the_asm_unit_assembles_under_the_dotted_label(self):
        if not (shutil.which("mipsel-linux-gnu-as") and shutil.which("mipsel-linux-gnu-nm")):
            self.skipTest("GNU MIPS tools unavailable")
        va = split.VADDR_BASE
        table = {va: (0x03e00008, "jr ra"), va + 4: (0, "nop")}
        path = split.emit_asm(table, bytes(split.FILE_BASE + 8), va, 8, NAME, self.root)
        self.assertEqual(os.path.basename(path), NAME + ".s")
        obj = os.path.join(self.root, "unit.o")
        subprocess.run(["mipsel-linux-gnu-as", "-o", obj, path], check=True, capture_output=True)
        nm = subprocess.run(["mipsel-linux-gnu-nm", obj], check=True, capture_output=True, text=True).stdout
        self.assertIn("T " + NAME, nm)

    def test_the_initialiser_maps_to_its_owner_and_reads_its_globals(self):
        self.write()
        index = units.scan(self.src, symbols=self.symbols, unit_objects=self.registry)
        self.assertEqual(index[NAME], self.source)
        # the function body's DAT_ reference is the function's, not the initialiser's
        self.assertEqual(progress.readable_failures(NAME, self.source, {}), [])
        self.assertIn("references", progress.readable_failures("fixture_owner", self.source, {}))
        self.write("extern int DAT_00500010;")
        self.assertEqual(progress.readable_failures(NAME, self.source, {}), ["addresses", "references"])


if __name__ == "__main__":
    unittest.main()
