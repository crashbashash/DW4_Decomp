/* 0x0027cc88 — FUN_0027cc88. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027b2b0();
int FUN_0027b2c8();
int FUN_0027ccd0();

int FUN_0027cc88(int arg0, int arg1) {
    int temp_s0;

    FUN_0027b2b0();
    temp_s0 = FUN_0027ccd0(arg0, arg1);
    FUN_0027b2c8();
    return temp_s0;
}
