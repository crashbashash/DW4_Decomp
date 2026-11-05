/* 0x00207420 — FUN_00207420. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00207420(int arg0) {
    return arg0 != *(short *)0x568E14;
}
