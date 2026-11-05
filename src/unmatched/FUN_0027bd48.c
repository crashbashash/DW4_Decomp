/* 0x0027bd48 — FUN_0027bd48. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027b2b0();
int FUN_0027b2c8();
int FUN_0027bda0();

int FUN_0027bd48(int arg0, int arg1, int arg2) {
    int temp_s0;

    FUN_0027b2b0();
    temp_s0 = FUN_0027bda0(arg0, arg1, arg2);
    FUN_0027b2c8();
    return temp_s0;
}
