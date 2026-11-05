/* 0x00267c60 — FUN_00267c60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00267c60(void *arg0, short arg1, short arg2) {
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    *(short *)((char *)(arg0) + 8) = arg1;
    *(short *)((char *)(arg0) + 10) = arg2;
}
