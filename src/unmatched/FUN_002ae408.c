/* 0x002ae408 — FUN_002ae408. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002adc40();
int FUN_002ae458();
int FUN_002aefe0();

void FUN_002ae408(int arg0) {
    FUN_002ae458();
    if (FUN_002adc40(arg0, 0x47) == 1) {
        FUN_002aefe0(arg0);
    }
}
