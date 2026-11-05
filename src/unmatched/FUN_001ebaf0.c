/* 0x001ebaf0 — FUN_001ebaf0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001ebaf0(int arg0) {
    int temp_v1;

    temp_v1 = arg0 != 0;
    *(int *)0x568E40 = temp_v1;
    *(short *)0x568E0E = (short) temp_v1;
}
