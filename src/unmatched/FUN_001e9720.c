/* 0x001e9720 — FUN_001e9720. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001e9720(int arg0) {
    *(int *)0x562D58 = arg0;
}
