/* 0x00278780 — FUN_00278780. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00278610();
int FUN_00278628();
int FUN_002787c8();

int FUN_00278780(int arg0, int arg1) {
    int temp_s0;

    FUN_00278610();
    temp_s0 = FUN_002787c8(arg0, arg1);
    FUN_00278628();
    return temp_s0;
}
