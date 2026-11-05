/* 0x0020e3c0 — FUN_0020e3c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0020e3c0(float arg0) {
    *(float *)0x56C650 = arg0;
}
