/* 0x002d18c0 — FUN_002d18c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002d18c0(int arg0) {
    *(int *)0x586DE0 = arg0;
}
