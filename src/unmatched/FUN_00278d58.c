/* 0x00278d58 — FUN_00278d58. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00278610();
int FUN_00278628();
int FUN_00278da8();

void FUN_00278d58(int arg0, int arg1, int arg2) {
    FUN_00278610();
    FUN_00278da8(arg0, arg1, arg2);
    FUN_00278628();
}
