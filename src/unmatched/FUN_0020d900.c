/* 0x0020d900 — FUN_0020d900. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0020d900(float arg0) {
    *(float *)0x56C2D8 = arg0;
}
