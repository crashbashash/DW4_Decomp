/* 0x0027b640 — FUN_0027b640. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027b2b0();
int FUN_0027b2c8();
int FUN_0027b690();

void FUN_0027b640(int arg0, int arg1, int arg2) {
    FUN_0027b2b0();
    FUN_0027b690(arg0, arg1, arg2);
    FUN_0027b2c8();
}
