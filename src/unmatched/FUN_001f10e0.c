/* 0x001f10e0 — FUN_001f10e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001f10e0(int arg0) {
    *(int *)0x569308 = arg0;
}
