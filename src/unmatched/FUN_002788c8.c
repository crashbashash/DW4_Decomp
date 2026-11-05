/* 0x002788c8 — FUN_002788c8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00278610();
int FUN_00278628();
int FUN_002788f8();

void FUN_002788c8(int arg0) {
    FUN_00278610();
    FUN_002788f8(arg0);
    FUN_00278628();
}
