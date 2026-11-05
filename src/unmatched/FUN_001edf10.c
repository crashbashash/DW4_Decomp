/* 0x001edf10 — FUN_001edf10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001edf10(int arg0) {
    *(int *)0x490B68 = arg0;
}
