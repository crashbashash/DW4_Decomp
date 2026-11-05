/* 0x001ae1a0 — FUN_001ae1a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001ae1a0(void *arg0, float fparg0, float fparg1, float fparg2) {
    *(float *)((char *)(arg0) + 0) = fparg0;
    *(float *)((char *)(arg0) + 4) = fparg1;
    *(float *)((char *)(arg0) + 8) = fparg2;
}
