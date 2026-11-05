/* 0x00294d90 — FUN_00294d90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002967b8();

void FUN_00294d90(float *arg0) {
    FUN_002967b8(0, 0x1B, (int) *arg0);
    FUN_002967b8(0, 7, 1);
}
