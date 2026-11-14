"""Tests for tools/listing.py: the masked shape and b52's `-g` records."""
import os
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import cc  # noqa: E402
import listing  # noqa: E402
import verify  # noqa: E402

B52 = os.path.join(listing.ROOT, "local", "mwcps2", "3.0b52-030722", "mwccps2.exe")
CORE_FLAGS = "-O4,s -sdatathreshold 2 -RTTI off -inline level=8,bottomup -Cpp_exceptions off"


class Shape(unittest.TestCase):
    def test_a_zero_extension_is_not_a_field_mask(self):
        # `dsll32 x,a0,0; dsrl32 x,x,0` widens a 32-bit value; the same pair by 9 keeps a 23-bit count
        widen = [listing.Insn(0, "dsll32", "s0,a0,0x0", None, None), listing.Insn(4, "dsrl32", "s0,s0,0x0", None, None)]
        mask = [listing.Insn(0, "dsll32", "v1,v1,0x9", None, None), listing.Insn(4, "dsrl32", "v1,v1,0x9", None, None)]
        self.assertNotEqual(listing.shape(widen), listing.shape(mask))
        self.assertEqual(listing.shape(widen), ["dsll32/0", "dsrl32/0"])


@unittest.skipUnless(os.path.exists(B52) and os.path.exists(verify.WIBO_DEFAULT), "b52 compiler unavailable")
class DebugRecords(unittest.TestCase):
    SOURCE = "extern void take(int *);\nint probe(int a) {\n    int kept = a;\n    take(&kept);\n    return kept;\n}\n"

    def compile(self, folder, extra):
        src = os.path.join(folder, "probe.c")
        with open(src, "w") as fh:
            fh.write(self.SOURCE)
        out = os.path.join(folder, "probe%s.o" % extra.strip())
        subprocess.run(cc.compile_argv(verify.WIBO_DEFAULT, B52, (CORE_FLAGS + " " + extra).strip(), src, out),
                       cwd=folder, check=True, capture_output=True)
        return out

    def test_g_names_the_frame_slot_without_changing_the_code(self):
        with tempfile.TemporaryDirectory(prefix="dw4-listing-") as folder:
            plain, debug = self.compile(folder, ""), self.compile(folder, "-g")
            self.assertEqual(listing.body(plain, "probe"), listing.body(debug, "probe"))
            records = listing.debug_records(debug, "probe")
            kept = {v.name: v for v in records.variables}["kept"]
            self.assertEqual(kept.location[0], "sp")
            stored = [listing.memory_operand(x) for x in listing.object_listing(plain, "probe")]
            self.assertIn((kept.location[1], "sp"), stored)
            self.assertEqual(records.lines[0][0], 0)       # the line table starts at the function's first word


if __name__ == "__main__":
    unittest.main()
