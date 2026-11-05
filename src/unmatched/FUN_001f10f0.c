/* 0x001f10f0 — FUN_001f10f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001f10f0(int arg0, int arg1, int arg2, int arg3) {
    *(int *)0x5692A8 = arg0;
    *(int *)0x5692B0 = arg1;
    *(int *)0x5692C0 = arg3;
    *(int *)0x569300 = arg2;
}
