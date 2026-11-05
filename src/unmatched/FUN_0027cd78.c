/* 0x0027cd78 — FUN_0027cd78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027b2b0();
int FUN_0027b2c8();
int FUN_0027cdd8();

void FUN_0027cd78(int arg0, int arg1, int arg2, int arg3) {
    FUN_0027b2b0();
    FUN_0027cdd8(arg0, arg1, arg2, arg3);
    FUN_0027b2c8();
}
