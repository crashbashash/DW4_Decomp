/* 0x001f6460 — FUN_001f6460. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int *FUN_001f6460(int *arg0, int *arg1) {
    *arg0 = *arg1;
    return arg0;
}
