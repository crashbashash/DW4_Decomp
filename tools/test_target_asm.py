"""objdiff's target takes the compiled spelling of a word only when it relocates to retail."""
import struct
import unittest

import target_asm

LUI, LW = 0x3c010000, 0x8c240000


def pack(*words):
    return struct.pack("<%dI" % len(words), *words)


class Spellings(unittest.TestCase):
    def spell(self, raw, relocs, addresses, retail):
        words = struct.unpack("<%dI" % (len(raw) // 4), raw)
        self.assertEqual(len(words), len(retail))
        return target_asm.spellings(raw, relocs, addresses.get, 0, lambda off: retail[off // 4])

    def test_alias_that_relocates_to_retail_keeps_the_compiled_name(self):
        relocs = [(".text", 0, 5, "s_TEXT_0051b3c0", 0), (".text", 4, 6, "s_TEXT_0051b3c0", 0)]
        found = self.spell(pack(LUI, LW), relocs, {"s_TEXT_0051b3c0": 0x51b3c0}, [LUI | 0x52, LW | 0xb3c0])
        self.assertEqual(found[0], (("R_MIPS_HI16", "s_TEXT_0051b3c0"), LUI))
        self.assertEqual(found[4], (("R_MIPS_LO16", "s_TEXT_0051b3c0"), LW))

    def test_gp_relative_keeps_its_type(self):
        word = 0x8f820000
        found = target_asm.spellings(pack(word), [(".text", 0, 7, "GPR_00500010", 0)],
                                     {"GPR_00500010": 0x500010}.get, 0x500000, lambda off: word | 0x10)
        self.assertEqual(found[0], (("R_MIPS_GPREL16", "GPR_00500010"), word))

    def test_wrong_address_is_left_to_objdiff(self):
        relocs = [(".text", 0, 5, "DAT_00520000", 0), (".text", 4, 6, "DAT_00520000", 0)]
        found = self.spell(pack(LUI, LW), relocs, {"DAT_00520000": 0x520000}, [LUI | 0x52, LW | 0xb3c0])
        self.assertNotIn(4, found)

    def test_unresolved_symbol_is_not_taken(self):
        relocs = [(".text", 0, 4, "@183", 0)]
        self.assertEqual(self.spell(pack(0x0c000000), relocs, {}, [0x0c000000]), {})

    def test_literal_equal_to_retail_stays_a_literal(self):
        self.assertEqual(self.spell(pack(LUI | 0x49), [], {}, [LUI | 0x49]), {0: (None, LUI | 0x49)})

    def test_different_word_is_not_taken(self):
        self.assertEqual(self.spell(pack(LUI | 0x49), [], {}, [LUI | 0x57]), {})


if __name__ == "__main__":
    unittest.main()
