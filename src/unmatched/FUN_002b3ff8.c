/* 0x002b3ff8 — FUN_002b3ff8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002830a8();
int FUN_002b3c88();
int FUN_002b3e00();

void FUN_002b3ff8(int arg0, int arg1) {
    unsigned int temp_s0;

    temp_s0 = arg1 & 0xFF;
    FUN_002830a8(arg1);
    FUN_002b3c88(arg0, 0);
    FUN_002b3e00(arg0, 0, temp_s0 >> 1, temp_s0);
}
