/* 0x0013b240 — FUN_0013b240. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0013b800();
int FUN_002fe490();
int FUN_0013b8a0();

void FUN_0013b240(void) {
    FUN_0013b800();
    FUN_002fe490(&FUN_0013b8a0);
}
