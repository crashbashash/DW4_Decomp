"""Reviewed source/instruction preimages must agree before diagnostic repair."""
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("combat_repairs", ROOT / "scripts/repair_combat_draft.py")
repairs = importlib.util.module_from_spec(spec)
spec.loader.exec_module(repairs)


class DraftRepairs(unittest.TestCase):
    SOURCE = '''extern int DAT_004cf538[4];
extern int DAT_004cf558[4];
void Gap__Bec__beNDMWGameRam__vfunc_34(void) {
    void **var_v1;
    void **var_v1_2;
    void **var_v1_3;
    short *var_v1_5;
    var_v1 += 4;
    var_v1_2 += 4;
    var_v1_3 += 4;
    var_v1_5 += 2;
    if (*(int *)((char *)(temp_a2) + 16)) {}
    if (*(int *)((char *)(temp_a2_2) + 16)) {}
    if (*(int *)((char *)(FUN_00406dd0(temp_v0_74, 1)) + 8)) {}
    if (*(int *)(FUN_00406f00(temp_s2_8) + temp_s1_13) != 0) {}
    if (*(int *)(FUN_00406f00(temp_s2_8) + temp_s1_13) == 0) {}
    beMessenger_AppendBool(arg0, *(int *)(FUN_00406f00(temp_s2_8) + temp_s1_13));
    *(int *)(temp_s1_13 + FUN_00406f00(temp_s2_8)) = temp_s0_7;
    *(int *)(temp_s1_13 + FUN_00406f00(temp_s2_8)) = temp_s0_8;
    *DataList_GetData_003e9090(temp_v0_86) = temp_s1_55;
    temp_a0_9 = sp428 * 4;
    var_s2_12 = *(int *)(&DAT_004cf558[0] + temp_a0_9);
    var_s3_7 = *(int *)(&DAT_004cf538[0] + temp_a0_9);
}'''

    def image(self):
        words = repairs.WORDS | repairs.HIT_WORDS | repairs.RNG_WORDS | repairs.EFFECT_WORDS | repairs.TABLE_WORDS
        data = bytearray(max(words) - 0x100000 + 0x84)
        for address, word in words.items():
            struct.pack_into("<I", data, address - 0x100000 + 0x80, word)
        return data

    def test_reviewed_steps_and_widths(self):
        result, changes = repairs.repair(self.SOURCE, self.image())
        self.assertEqual(len(changes), 17)
        self.assertEqual(result.count("+= 1;"), 4)
        self.assertEqual(result.count("*(unsigned char *)"), 8)
        self.assertIn("var_v1_2 += 1;", result)
        self.assertIn("*(int *)DataList_GetData_003e9090", result)

    def test_changed_original_width_or_stride_is_rejected(self):
        for address in repairs.WORDS:
            with self.subTest(address=address):
                image = self.image()
                image[address - 0x100000 + 0x80] ^= 1
                with self.assertRaisesRegex(ValueError, "instruction guard"):
                    repairs.repair(self.SOURCE, image)

    def test_changed_cursor_type_or_duplicate_preimage_is_rejected(self):
        for source in [self.SOURCE.replace("void **var_v1;", "char *var_v1;"),
                       self.SOURCE.replace("var_v1 += 4;", "var_v1 += 4; var_v1 += 4;")]:
            with self.assertRaises(ValueError):
                repairs.repair(source, self.image())

    def test_partial_repair_or_different_function_is_rejected(self):
        for source in [self.SOURCE.replace("var_v1_5 += 2;", "var_v1_5 += 1;"),
                       self.SOURCE.replace(repairs.FUNCTION, "another_callback")]:
            with self.assertRaises(ValueError):
                repairs.repair(source, self.image())

    def test_byte_buffer_preimages_must_all_be_present(self):
        for old in [" != 0) {}", " == 0) {}", " + temp_s1_13));",
                    " = temp_s0_7;", " = temp_s0_8;"]:
            with self.subTest(preimage=old):
                with self.assertRaisesRegex(ValueError, "source preimage"):
                    repairs.repair(self.SOURCE.replace(old, "changed", 1), self.image())

    def test_table_guards_and_byte_offset_preimages(self):
        for address in repairs.TABLE_WORDS:
            with self.subTest(address=address):
                image = self.image()
                image[address - 0x100000 + 0x80] ^= 1
                with self.assertRaisesRegex(ValueError, "instruction guard"):
                    repairs.repair(self.SOURCE, image)
        for old, new in [("sp428 * 4", "sp428 * 16"),
                         ("extern int DAT_004cf538[4];", "extern short DAT_004cf538[4];"),
                         ("&DAT_004cf558[0] + temp_a0_9", "&DAT_004cf558[0] + another_offset")]:
            with self.subTest(preimage=old):
                with self.assertRaises(ValueError):
                    repairs.repair(self.SOURCE.replace(old, new), self.image())
        result, _ = repairs.repair(self.SOURCE, self.image())
        self.assertIn("extern int DAT_004cf538[];", result)
        self.assertIn("extern int DAT_004cf558[];", result)
        self.assertEqual(result.count("(char *)&DAT_004cf"), 2)

    def attack_source(self):
        declarations, statements = [], []
        for result, index, compared, _site in repairs.ATTACK_EFFECTS:
            declarations.append("    int " + result + ";")
            query = ("beDataBase_GetRecordString(FUN_00406ee0(&arg0->_dBEneatk), "
                     + index + ", &DAT_005191f0[0])")
            statements.extend(["    " + result + " = 0;",
                               "    if (igStrCmp(" + query + ", &" + compared
                               + "[0]) == 0) { keep_result(" + result + "); }"])
        return ("void " + repairs.FUNCTION + "(void) {\n" + "\n".join(declarations)
                + "\n" + "\n".join(statements) + "\n}")

    def test_attack_effect_lookup_precedes_initialization_without_duplicating_calls(self):
        source = self.attack_source()
        result = repairs.restore_attack_effect_order(source, self.image())
        self.assertEqual(result.count("beDataBase_GetRecordString("), 4)
        self.assertEqual(result.count("igStrCmp("), 4)
        self.assertEqual(result.count("const char *recovery_attack_effect;"), 1)
        cursor = 0
        for flag, index, compared, _site in repairs.ATTACK_EFFECTS:
            query = result.index("recovery_attack_effect = ", cursor)
            zero = result.index(flag + " = 0;", cursor)
            compare = result.index("if (igStrCmp(recovery_attack_effect, &" + compared, cursor)
            self.assertLess(query, zero)
            self.assertLess(zero, compare)
            self.assertIn("keep_result(" + flag + ");", result)
            cursor = compare + 1

    def test_attack_effect_original_words_reject_drift(self):
        for address in repairs.EFFECT_WORDS:
            with self.subTest(address=hex(address)):
                image = self.image()
                image[address - 0x100000 + 0x80] ^= 1
                with self.assertRaisesRegex(ValueError, "instruction guard"):
                    repairs.restore_attack_effect_order(self.attack_source(), image)

    def test_attack_effect_preimages_and_unescaped_result_are_required(self):
        source = self.attack_source()
        for changed in [source.replace("DAT_00519230", "DAT_00519238", 1),
                        source.replace("DAT_005191f0", "DAT_00519200", 1),
                        source.replace("int var_s1_17;", "short var_s1_17;", 1),
                        source.replace("var_s1_17 = 0;", "var_s1_17 = 0; side_effect();", 1),
                        source.replace("keep_result(var_s1_17)", "keep_result(&var_s1_17)", 1)]:
            with self.assertRaises(ValueError):
                repairs.restore_attack_effect_order(changed, self.image())

    def test_attack_effect_repeat_or_wrong_function_is_rejected(self):
        transformed = repairs.restore_attack_effect_order(self.attack_source(), self.image())
        for source in [transformed, self.attack_source().replace(repairs.FUNCTION, "another_callback")]:
            with self.assertRaises(ValueError):
                repairs.restore_attack_effect_order(source, self.image())

    def rng_source(self):
        declarations, statements = [], []
        for receiver, numerator, denominator, ratio, _site in repairs.RNG_SAMPLES:
            declarations.append("    void **" + receiver + ";")
            expression = ("((int (*)())*(int *)((char *)((*" + receiver
                          + ")) + 96))(" + receiver + ") % 10000U")
            statements.extend([
                "    " + receiver + " = (void **)(FUN_00406e50(arg0->_system + 0x30));",
                "    " + ratio + " = (((int) (" + numerator + " * 3) / (int) "
                + denominator + ") + 0x64) - ((int) " + denominator + " / 40);",
                "    if ((int) (" + expression + ") < " + ratio + ") { result(); }"])
        return ("void " + repairs.FUNCTION + "(void) {\n" + "\n".join(declarations)
                + "\n" + "\n".join(statements) + "\n}")

    def test_rng_samples_preserve_draws_and_precede_ratio_math(self):
        source = self.rng_source()
        result = repairs.restore_rng_samples(source, self.image())
        self.assertEqual(source.count("% 10000U"), result.count("% 10000U"))
        self.assertEqual(result.count("unsigned int recovery_roll_"), 3)
        for receiver, numerator, denominator, ratio, _site in repairs.RNG_SAMPLES:
            name = "recovery_roll_" + receiver
            capture = result.index(name + " = ")
            self.assertLess(result.index(receiver + " = "), capture)
            self.assertLess(capture, result.index(ratio + " = "))
            self.assertLess(result.index(ratio + " = "), result.index("if ((int) (" + name))
            self.assertEqual(result.count(")(" + receiver + ") % 10000U"), 1)

    def test_rng_samples_reject_original_call_or_division_drift(self):
        for address in repairs.RNG_WORDS:
            with self.subTest(address=hex(address)):
                image = self.image()
                image[address - 0x100000 + 0x80] ^= 1
                with self.assertRaisesRegex(ValueError, "instruction guard"):
                    repairs.restore_rng_samples(self.rng_source(), image)

    def test_rng_samples_reject_changed_sources_and_intervening_effects(self):
        source = self.rng_source()
        cases = [source.replace("% 10000U", "% 1000U", 1),
                 source.replace("temp_s5_11 * 3", "temp_s5_11 * 4", 1),
                 source.replace("    temp_s0_61 =", "    side_effect();\n    temp_s0_61 =", 1),
                 source.replace("void **temp_v0_81;", "void *temp_v0_81;", 1),
                 source.replace("    temp_s0_61 =", "    inspect(temp_v0_81);\n    temp_s0_61 =", 1)]
        for changed in cases:
            with self.assertRaises(ValueError):
                repairs.restore_rng_samples(changed, self.image())

    def test_rng_samples_reject_repeat_or_wrong_function(self):
        result = repairs.restore_rng_samples(self.rng_source(), self.image())
        for source in [result, self.rng_source().replace(repairs.FUNCTION, "other_callback")]:
            with self.assertRaises(ValueError):
                repairs.restore_rng_samples(source, self.image())

    def test_sparse_switch_keeps_arm_contents_and_evaluates_guard_once(self):
        source = '''void callback(void) {
            if ((temp_s0_9 / 10000) != 4) {
                regular_lookup();
                if (nested) { regular_result(); }
            } else {
                append_guaranteed_hit();
            }
}'''
        source = source.replace("callback", repairs.FUNCTION)
        result = repairs.restore_hit_switch(source, self.image())
        self.assertEqual(result.count("temp_s0_9 / 10000"), 1)
        self.assertEqual(result.count("regular_lookup();"), 1)
        self.assertEqual(result.count("regular_result();"), 1)
        self.assertEqual(result.count("append_guaranteed_hit();"), 1)
        self.assertLess(result.index("case 4:"), result.index("append_guaranteed_hit();"))
        self.assertLess(result.index("append_guaranteed_hit();"), result.index("default:"))
        self.assertLess(result.index("default:"), result.index("regular_lookup();"))

    def test_sparse_switch_rejects_opcode_drift_and_control_transfers(self):
        source = '''void callback(void) {
            if ((temp_s0_9 / 10000) != 4) { regular(); } else { magic(); }
}'''
        source = source.replace("callback", repairs.FUNCTION)
        image = self.image()
        image[0x3fdf28 - 0x100000 + 0x80] ^= 1
        with self.assertRaisesRegex(ValueError, "instruction guard"):
            repairs.restore_hit_switch(source, image)
        for statement in ["break;", "continue;", "label: regular();"]:
            with self.assertRaisesRegex(ValueError, "control transfers"):
                repairs.restore_hit_switch(source.replace("regular();", statement), self.image())


if __name__ == "__main__":
    unittest.main()
