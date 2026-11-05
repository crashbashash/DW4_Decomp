"""Guard the vendored `m2c` against recovery errors this pipeline can trigger.

`m2c` is fetched under `local/m2c/` and is **not** committed (see
[`../docs/engine/m2c-bulk.md`](../docs/engine/m2c-bulk.md)), so a fix cannot live in its
source. Importing this module puts `local/m2c` on `sys.path` (unless `DW4_M2C_DIR` says
otherwise) and patches the upstream bugs described below.

**The bug.** `m2c/evaluate.py:fold_shift_bgez` simplifies a `bgez`/`bltz` whose operand is
`x << n` (or `x * 2**n`) to `!(x & (1 << (31 - n)))` — with no bounds on `n`. A shift of
32 or more makes `31 - n` negative and Python raises `ValueError: negative shift count`,
which aborts the whole decompile. It is a *simplification*, so not folding an
out-of-range shift is always sound: `handle_bgez` falls back to `expr >= 0`, the same
condition it started from.

The pipeline triggered it 4 times before finding #349 and **133 more** after it, because
naming a `%hi` base makes m2c fold a register to a constant it previously left symbolic
(a `bltz` on the result then reaches the buggy folder). Guarding it is what keeps the
`%lo` register-lifetime fix usable.

Combat quotients use signed multiply-high and an arithmetic shift, followed by
the input's sign correction. Upstream folds the partial product/shift into
division too early and retains an extra correction. Preserve the partial until
the complete reviewed sequence is present. The finite pattern list below comes
from the dispatcher; other reciprocals remain outside this rule. The independent
integer bounds in testing/test_m2c_compat.py prove every signed input for each.

The scoped `materialize_function_calls` helper is an opt-in diagnostic projection.
It exposes nonvoid call results as temporaries and restores the translator after
one serial invocation; ordinary rendering stays unchanged.
"""
from contextlib import contextmanager
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.environ.get("DW4_M2C_DIR", os.path.join(ROOT, "local", "m2c")))

try:
    import m2c.evaluate as _evaluate
except Exception:                                   # noqa: BLE001
    _evaluate = None

if _evaluate is not None and not getattr(_evaluate.fold_shift_bgez, "_dw4_guarded", False):
    _original = _evaluate.fold_shift_bgez

    def fold_shift_bgez(expr):
        try:
            return _original(expr)
        except ValueError:
            return None

    fold_shift_bgez._dw4_guarded = True
    _evaluate.fold_shift_bgez = fold_shift_bgez


SIGNED_RECIPROCALS = {
    (0x10624DD3, 6): 1000,
    (0x55555556, 0): 3,
    (0x51EB851F, 4): 50,
    (0x51EB851F, 5): 100,
    (0x51EB851F, 7): 400,
    (0x66666667, 1): 5,
    (0x66666667, 2): 10,
    (0x66666667, 3): 20,
    (0x66666667, 4): 40,
    (0x66666667, 5): 80,
    (0x68DB8BAD, 12): 10000,
}
_SIGNED_MULTIPLIERS = frozenset(multiplier for multiplier, _shift in SIGNED_RECIPROCALS)


def _signed_reciprocal_product(expr):
    """(Input, multiplier) of a reviewed signed multiply-high, or None."""
    expr = _evaluate.early_unwrap_ints(expr)
    if not isinstance(expr, _evaluate.BinaryOp) or expr.op != "MULT_HI":
        return None
    left = _evaluate.early_unwrap_ints(expr.left)
    right = _evaluate.early_unwrap_ints(expr.right)
    if isinstance(left, _evaluate.Literal) and left.value in _SIGNED_MULTIPLIERS:
        return right, left.value
    if isinstance(right, _evaluate.Literal) and right.value in _SIGNED_MULTIPLIERS:
        return left, right.value
    return None


def _signed_reciprocal_partial(expr):
    """(Input, denominator) of a reviewed arithmetic-shifted product, or None."""
    expr = _evaluate.early_unwrap_ints(expr)
    product = _signed_reciprocal_product(expr)
    # MULT_HI itself selects signed multiplication. With no SRA, inferred
    # signedness can be ambiguous or unsigned because of the logical sign-bit
    # correction; the word width and opcode remain authoritative.
    if product is not None and expr.type.get_size_bits() in (None, 32):
        numerator, multiplier = product
        if numerator.type.get_size_bits() not in (None, 8, 16, 32):
            return None
        denominator = SIGNED_RECIPROCALS.get((multiplier, 0))
        if denominator is not None:
            return numerator, denominator
    if (isinstance(expr, _evaluate.BinaryOp) and expr.op == ">>"
            and expr.type.is_signed() and expr.type.get_size_bits() == 32
            and isinstance(_evaluate.early_unwrap_ints(expr.right), _evaluate.Literal)):
        product = _signed_reciprocal_product(expr.left)
        if product is not None:
            numerator, multiplier = product
            if numerator.type.get_size_bits() not in (None, 8, 16, 32):
                return None
            shift = _evaluate.early_unwrap_ints(expr.right).value
            denominator = SIGNED_RECIPROCALS.get((multiplier, shift))
            if denominator is not None:
                return numerator, denominator
    return None


if _evaluate is not None and not getattr(_evaluate.fold_divmod, "_dw4_category_guarded", False):
    _original_divmod = _evaluate.fold_divmod

    def fold_divmod(expr):
        # Folding either partial into truncating division loses the distinction
        # between the shifted floor-product and the corrected signed quotient.
        if (_signed_reciprocal_product(expr) is not None
                or _signed_reciprocal_partial(expr) is not None):
            return expr
        if expr.op in ("+", "-"):
            orientations = ((expr.left, expr.right, False), (expr.right, expr.left, True))
            for product, correction, reversed_operands in orientations:
                partial = _signed_reciprocal_partial(product)
                correction = _evaluate.early_unwrap_ints(correction)
                if (partial is not None and isinstance(correction, _evaluate.BinaryOp)
                        and correction.op == ">>"
                        and correction.type.get_size_bits() == 32
                        and _evaluate.early_unwrap_ints(correction.right) == _evaluate.Literal(31)):
                    numerator, denominator = partial
                    valid = ((expr.op == "+" and correction.type.is_unsigned())
                             or (expr.op == "-" and correction.type.is_signed()))
                    if valid and _evaluate.early_unwrap_ints(correction.left) == numerator:
                        if expr.op == "-" and reversed_operands:
                            denominator = -denominator
                        return _evaluate.BinaryOp.sint(numerator, "/", _evaluate.Literal(denominator))
        return _original_divmod(expr)

    fold_divmod._dw4_category_guarded = True
    _evaluate.fold_divmod = fold_divmod
    # arch_mips imports this function by value. Cover both import orders:
    # m2c_run imports us before main, while an interactive driver may import later.
    import m2c.arch_mips as _arch_mips
    _arch_mips.fold_divmod = fold_divmod


@contextmanager
def materialize_function_calls(*, direct_only=False, remainders=False):
    """Keep nonvoid call results in explicit temporaries for one serial run.

    This opt-in source projection preserves call placement instead of nesting
    calls in later expressions. It does not establish source types or a match.
    direct_only retains named function results, leaving indirect calls nested.
    remainders additionally captures modulo values where MIPS reads HI.
    Counters include m2c inference passes, not distinct retail call sites.
    """
    from m2c import evaluate, translate

    original = translate.NodeState._eval_once
    stats = {"materialized": 0}
    if remainders:
        stats["remainders"] = 0

    def materialized(self, expr, **kwargs):
        result = original(self, expr, **kwargs)
        value = evaluate.early_unwrap_ints(expr)
        if isinstance(value, translate.FuncCall) and not value.type.is_void():
            named = True
            if direct_only:
                target = translate.late_unwrap(value.function)
                if isinstance(target, translate.AddressOf):
                    target = target.expr
                named = isinstance(target, translate.GlobalSymbol) and target.type.is_function()
            if named:
                result.force()
                stats["materialized"] += 1
        elif remainders and isinstance(value, translate.BinaryOp) and value.op == "%":
            instruction = getattr(kwargs.get("source"), "instruction", None)
            if getattr(instruction, "mnemonic", None) == "mfhi":
                result.force()
                stats["remainders"] += 1
        return result

    translate.NodeState._eval_once = materialized
    try:
        yield stats
    finally:
        translate.NodeState._eval_once = original
