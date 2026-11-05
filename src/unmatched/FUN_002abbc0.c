/* 0x002abbc0 — FUN_002abbc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002abbc0(void *arg0) {
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    *(long long *)((char *)(arg0) + 0) = 0;
    *(long long *)((char *)(arg0) + 8) = 0;
    *(long long *)((char *)(arg0) + 16) = 0;
}
