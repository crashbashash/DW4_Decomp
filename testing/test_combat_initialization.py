"""Retail instruction proof and counterfactuals for incoming combat registers."""
from pathlib import Path
import os
import shutil
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import verify_combat_initialization as proof

ELF = Path(os.environ.get("DW4_ELF", ROOT / "orig/SLUS-20836/SLUS_208.36"))


@unittest.skipUnless(ELF.exists() and shutil.which("mipsel-linux-gnu-objdump"),
                     "private retail ELF and MIPS binutils required")
class CombatInitialization(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.image = ELF.read_bytes()

    def changed_word(self, address, value):
        image = bytearray(self.image)
        struct.pack_into("<I", image, address - 0x100000 + 0x80, value)
        return image

    def test_retail_incoming_s0_is_not_read(self):
        result = proof.check(self.image)
        self.assertEqual(result["reads"], [])
        self.assertEqual(result["maximum_level_cap"], 9876)
        self.assertEqual(result["final_skill_threshold"], 10000)
        self.assertTrue(result["all_valid_level_caps_covered"])

    def test_nonzero_zero_damage_path_exposes_incoming_skill(self):
        # Change only the no-damage assignment, without touching the image file.
        # It now reaches the critical bonus with incoming s0 still undefined.
        image = self.changed_word(0x3FEA70, 0x24120001)  # li s2,1, formerly move s2,zero
        result = proof.check(image)
        self.assertIn("0x003fec9c", result["reads"])
        self.assertIn("0x003fed5c", result["reads"])

    def test_valid_level_caps_follow_original_arithmetic(self):
        flow = proof.Flow(self.image)
        for level in range(1, 1000):
            expected = (30 * level if level < 37 else 20 * level + 360 if level < 108
                        else 10 * level + 1430 if level < 228 else 8 * level + 1884)
            self.assertEqual(flow.level_cap(level), expected, level)

    def test_lowered_terminal_threshold_breaks_coverage(self):
        image = bytearray(self.image)
        struct.pack_into("<h", image, 0x4CF590 + 20 * 2 - 0x100000 + 0x80, 9000)
        self.assertFalse(proof.check(image)["all_valid_level_caps_covered"])

    def test_changed_switch_guard_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "switch sequence"):
            proof.Flow(self.changed_word(0x3FDE90, 0x2C410017))

    def test_unreviewed_opcode_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "unsupported instruction"):
            proof.Flow(self.changed_word(0x3FCAA4, 0x0002107F))  # dsra32, absent from retail body


if __name__ == "__main__":
    unittest.main()
