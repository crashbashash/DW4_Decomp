"""Signed combat quotients: arithmetic proofs and decompiler regressions.

Requires the locally supplied m2c for AST/integration checks; the independent
integer proof does not require a retail image, compiler or emulator.
"""
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import m2c_compat


class ReciprocalArithmetic(unittest.TestCase):
    def test_all_reviewed_reciprocals_have_full_domain_error_bounds(self):
        self.assertEqual(sorted(m2c_compat.SIGNED_RECIPROCALS.values()),
                         [3, 5, 10, 20, 40, 50, 80, 100, 400, 1000, 10000])
        for (multiplier, shift), denominator in m2c_compat.SIGNED_RECIPROCALS.items():
            scale = 1 << (32 + shift)
            error = multiplier * denominator - scale
            # x=q*d+r. Maximize the monotone residual over feasible pairs:
            # completed quotient intervals and the final partial interval.
            # Positive inputs need residual < scale. For negative x=-n,
            # ceil(n*M/scale) needs 0 < residual <= scale. The equality occurs
            # for /3 at INT_MIN and is valid only on the negative side.
            def bound(maximum):
                quotient, remainder = divmod(maximum, denominator)
                return max((quotient - 1) * error + multiplier * (denominator - 1),
                           quotient * error + multiplier * remainder)
            self.assertGreater(error, 0)
            self.assertGreater(multiplier, 0)
            self.assertLess(bound((1 << 31) - 1), scale)
            self.assertLessEqual(bound(1 << 31), scale)
            samples = [-(1 << 31), (1 << 31) - 1, -1, 0, 1]
            samples += [sign * (denominator + offset) for sign in (-1, 1) for offset in (-1, 0, 1)]
            for value in samples:
                expected = -(abs(value) // denominator) if value < 0 else value // denominator
                self.assertEqual(((value * multiplier) >> (32 + shift)) + (value < 0), expected)

    def test_all_signed_32_bit_quotient_intervals(self):
        denominator, multiplier, shift = 10000, 0x68DB8BAD, 44
        low, high = -(1 << 31), (1 << 31) - 1

        def trunc(value):
            return -(abs(value) // denominator) if value < 0 else value // denominator

        def machine(value):
            return ((value * multiplier) >> shift) + (value < 0)

        # Each side of zero is monotone. Equality at both endpoints of every
        # interval where trunc(value / denominator) is constant proves equality
        # for every intervening integer, covering all 2**32 signed inputs.
        for quotient in range(trunc(low), trunc(high) + 1):
            if quotient < 0:
                start, end = (quotient - 1) * denominator + 1, quotient * denominator
            elif quotient > 0:
                start, end = quotient * denominator, (quotient + 1) * denominator - 1
            else:
                start, end = -denominator + 1, denominator - 1
            for value in (max(low, start), min(high, end)):
                if machine(value) != quotient:
                    self.fail(f"reciprocal differs at {value}: expected {quotient}")
        self.assertEqual(machine(0), 0)
        self.assertEqual(trunc(-10000) + ((-10000 & 0xFFFFFFFF) >> 31), 0)
        self.assertEqual(machine(-10000), -1)


@unittest.skipIf(m2c_compat._evaluate is None, "locally supplied m2c unavailable")
class SignedCategoryRecovery(unittest.TestCase):
    def setUp(self):
        self.ev = m2c_compat._evaluate
        self.B, self.L = self.ev.BinaryOp, self.ev.Literal
        self.x = self.ev.GlobalSymbol("input", self.ev.Type.s32())
        self.y = self.ev.GlobalSymbol("other", self.ev.Type.s32())

    def product(self, unsigned=False, swapped=False, multiplier=0x68DB8BAD):
        left, right = self.x, self.L(multiplier)
        if swapped:
            left, right = right, left
        return self.B.int(left, "MULTU_HI" if unsigned else "MULT_HI", right)

    def partial(self, product=None, shift=12):
        product = product if product is not None else self.product()
        return product if shift == 0 else self.B.sshift(product, ">>", self.L(shift))

    def test_complete_pattern_and_commuted_operands(self):
        for swapped in (False, True):
            product = self.ev.fold_divmod(self.product(swapped=swapped))
            partial = self.ev.fold_divmod(self.partial(product))
            correction = self.B.ushift(self.x, ">>", self.L(31))
            for left, right in ((partial, correction), (correction, partial)):
                result = self.ev.fold_divmod(self.B.int(left, "+", right))
                self.assertEqual(result.op, "/")
                self.assertEqual(self.ev.early_unwrap_ints(result.left), self.x)
                self.assertEqual(self.ev.early_unwrap_ints(result.right), self.L(10000))
                self.assertTrue(result.type.is_signed())

    def test_reviewed_patterns_and_subtractive_sign_corrections(self):
        for (multiplier, shift), denominator in m2c_compat.SIGNED_RECIPROCALS.items():
            product = self.ev.fold_divmod(self.product(multiplier=multiplier))
            partial = self.ev.fold_divmod(self.partial(product, shift=shift))
            logical = self.B.ushift(self.x, ">>", self.L(31))
            arithmetic = self.B.sshift(self.x, ">>", self.L(31))
            for expression, expected in [(self.B.int(partial, "+", logical), denominator),
                                         (self.B.int(partial, "-", arithmetic), denominator),
                                         (self.B.int(arithmetic, "-", partial), -denominator)]:
                result = self.ev.fold_divmod(expression)
                self.assertEqual(result.op, "/")
                self.assertEqual(self.ev.early_unwrap_ints(result.right), self.L(expected))
                self.assertTrue(result.type.is_signed())

    def test_partials_are_not_truncating_division(self):
        for expression in (self.product(), self.partial(), self.product(multiplier=0x55555556)):
            self.assertIs(self.ev.fold_divmod(expression), expression)

    def test_nearby_patterns_are_not_rewritten(self):
        patterns = [
            (self.partial(), self.B.ushift(self.y, ">>", self.L(31))),
            (self.partial(), self.B.sshift(self.x, ">>", self.L(31))),
            (self.partial(), self.B.ushift(self.x, ">>", self.L(30))),
            (self.partial(shift=11), self.B.ushift(self.x, ">>", self.L(31))),
            (self.partial(self.product(unsigned=True)), self.B.ushift(self.x, ">>", self.L(31))),
            (self.partial(), self.B.u64(self.x, ">>", self.L(31))),
            (self.B.s64(self.product(), ">>", self.L(12)), self.B.ushift(self.x, ">>", self.L(31))),
        ]
        for product, correction in patterns:
            result = self.ev.fold_divmod(self.B.int(product, "+", correction))
            self.assertEqual(result.op, "+")

    def test_unshifted_third_rejects_unsigned_wide_and_wrong_corrections(self):
        product = self.product(multiplier=0x55555556)
        logical = self.B.ushift(self.x, ">>", self.L(31))
        wide = self.ev.GlobalSymbol("wide_input", self.ev.Type.s64())
        for partial, correction in [
            (self.product(unsigned=True, multiplier=0x55555556), logical),
            (self.B.s64(self.x, "MULT_HI", self.L(0x55555556)), logical),
            (self.B.int(wide, "MULT_HI", self.L(0x55555556)),
             self.B.ushift(wide, ">>", self.L(31))),
            (self.partial(product, shift=1), logical),
            (product, self.B.ushift(self.y, ">>", self.L(31))),
        ]:
            self.assertEqual(self.ev.fold_divmod(self.B.int(partial, "+", correction)).op, "+")

    def test_synthetic_instruction_pipeline(self):
        import m2c_batch
        for (multiplier, shift), denominator in m2c_compat.SIGNED_RECIPROCALS.items():
            name = f"signed_div{denominator}"
            assembly = f"""glabel {name}
lui $v1, 0x{multiplier >> 16:x}
ori $v1, $v1, 0x{multiplier & 65535:x}
mult $v1, $a0
srl $v0, $a0, 31
mfhi $v1
{f'sra $v1, $v1, {shift}' if shift else ''}
jr $ra
addu $v0, $v1, $v0
"""
            with tempfile.TemporaryDirectory() as directory:
                result = m2c_batch.run_m2c(assembly, name, str(Path(directory) / "input.s"))
            self.assertIn(f"/ {denominator}", result)
            self.assertNotIn("MULT_HI", result)
            self.assertNotIn(">>", result)
            if denominator == 3:
                self.assertIn("(s32) arg0 / 3", result)


if __name__ == "__main__":
    unittest.main()
