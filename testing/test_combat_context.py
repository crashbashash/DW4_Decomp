"""Check the retail skill-growth table and its decompiler address units."""
from pathlib import Path
import os
import struct
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "scripts")]
import gen_combat_context

ELF = Path(os.environ.get("DW4_ELF", ROOT / "orig/SLUS-20836/SLUS_208.36"))


class GrowthContext(unittest.TestCase):
    @unittest.skipUnless(ELF.exists(), "private retail ELF required")
    def test_retail_growth_labels_and_word_index(self):
        image = ELF.read_bytes()
        def word(address):
            return struct.unpack_from("<I", image, address - 0x100000 + 0x80)[0]
        labels = []
        for i in range(6):
            offset = word(0x4CF5C0 + i * 4) - 0x100000 + 0x80
            labels.append(image[offset:image.index(b"\0", offset)].decode("ascii"))
        self.assertEqual(labels, ["BLUNT_GROW", "SLASH_GROW", "STAB_GROW",
                                  "BASH_GROW", "SHOT_GROW", "CRUSH_GROW"])
        self.assertEqual(word(0x3FF574), 0x00153080)  # sll a2,s5,2
        self.assertEqual(word(0x3FF580), 0x00661021)  # addu v0,v1,a2
        self.assertEqual(word(0x3FF584), 0x8C460000)  # lw a2,0(v0)

    @unittest.skipUnless(ELF.exists(), "private retail ELF required")
    def test_retail_technique_groups_follow_the_reviewed_order(self):
        image = ELF.read_bytes()
        # Paired equality tests for 40/45, 55/60 and 50/-50, then the
        # single-value groups 65, 80 and 75. These are interior branches.
        words = {0x405218: 0x24020028, 0x40522C: 0x12A20004,
                 0x405234: 0x2402002D, 0x405238: 0x16A200D5,
                 0x405590: 0x24020037, 0x405594: 0x12A20004,
                 0x40559C: 0x2402003C, 0x4055A0: 0x16A2010D,
                 0x4059D8: 0x24020032, 0x4059DC: 0x12A20004,
                 0x4059E4: 0x2402FFCE, 0x4059E8: 0x16A2005D,
                 0x405B60: 0x24020041, 0x405B64: 0x16A20164,
                 0x4060F8: 0x24020050, 0x4060FC: 0x16A2013E,
                 0x4065F8: 0x2402004B, 0x4065FC: 0x16A2012A}
        for address, expected in words.items():
            with self.subTest(address=hex(address)):
                actual = struct.unpack_from("<I", image, address - 0x100000 + 0x80)[0]
                self.assertEqual(actual, expected)

    @unittest.skipUnless((ROOT / "local/m2c").exists(), "private m2c dependency required")
    def test_context_retains_element_index_through_cleanup(self):
        import m2c_batch
        assembly = """glabel growth_lookup
lui $v1, %hi(DAT_004cf5c0)
sll $a0, $a0, 2
addiu $v1, $v1, %lo(DAT_004cf5c0)
addu $v0, $v1, $a0
jr $ra
lw $v0, 0($v0)
"""
        with tempfile.TemporaryDirectory() as directory:
            context = Path(directory) / "context.c"
            context.write_text(gen_combat_context.generate())
            output = m2c_batch.run_m2c(assembly, "growth_lookup",
                                     str(Path(directory) / "input.s"), context=str(context))
        cleaned = m2c_batch.clean(output)
        self.assertIn("return DAT_004cf5c0[arg0];", cleaned)
        self.assertNotIn("* 4", cleaned)
        self.assertIn("char *growth_lookup", cleaned)


if __name__ == "__main__":
    unittest.main()
