/* 0x00207440 — FUN_00207440. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00207440(void) {
    *(int *)0x56BFC8 = 1;
}
