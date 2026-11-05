/* 0x0027d3c8 — FUN_0027d3c8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027b2b0();
int FUN_0027b2c8();
int FUN_0027d400();

int FUN_0027d3c8(int arg0) {
    int temp_s0;

    FUN_0027b2b0();
    temp_s0 = FUN_0027d400(arg0);
    FUN_0027b2c8();
    return temp_s0;
}
