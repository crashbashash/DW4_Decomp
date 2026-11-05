/* 0x001c59b0 — FUN_001c59b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001c59e0();

int FUN_001c59b0(void) {
    return FUN_001c59e0() == 1;
}
