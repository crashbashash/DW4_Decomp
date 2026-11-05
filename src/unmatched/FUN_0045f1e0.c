/* 0x0045f1e0 — FUN_0045f1e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0045f1e0(void *arg0, float fparg0, float fparg1) {
    *(float *)((char *)(arg0) + 0) = fparg0;
    *(float *)((char *)(arg0) + 4) = fparg1;
}
