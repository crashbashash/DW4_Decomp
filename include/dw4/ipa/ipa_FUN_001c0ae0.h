/* callee body compiled before its caller in the same unit: the compiler then knows which registers it leaves untouched (interprocedural register use). Verified as a duplicate of the real function at 0x001c0ae0. */
static int FUN_001c0ae0(float *arg0, float fparg0, float fparg1) {
    float var_f1;
    int temp_f0;

    if (DAT_005626e8[0] == fparg0 && fparg1 == DAT_005626f0[0]) {
        *arg0 = DAT_00562700[0];
        return DAT_005626f8[0];
    }
    temp_f0 = (int)(fparg0 / fparg1);
    DAT_005626e8[0] = fparg0;
    var_f1 = fparg0 - ((float)temp_f0 * fparg1);
    DAT_005626f0[0] = fparg1;
    DAT_00562700[0] = var_f1;
    var_f1 = (var_f1 > 0.0f) ? var_f1 : 0.0f;
    DAT_00562700[0] = var_f1;
    *arg0 = var_f1;
    DAT_005626f8[0] = temp_f0;
    return temp_f0;
}
