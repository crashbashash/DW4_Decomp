/* 0x00278918 — FUN_00278918. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00278610();
int FUN_00278628();
int FUN_00278948();

void FUN_00278918(int arg0) {
    FUN_00278610();
    FUN_00278948(arg0);
    FUN_00278628();
}
