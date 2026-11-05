/* 0x00278b58 — FUN_00278b58. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00278610();
int FUN_00278628();
int FUN_00278bb8();

void FUN_00278b58(int arg0, int arg1, int arg2, int arg3) {
    FUN_00278610();
    FUN_00278bb8(arg0, arg1, arg2, arg3);
    FUN_00278628();
}
