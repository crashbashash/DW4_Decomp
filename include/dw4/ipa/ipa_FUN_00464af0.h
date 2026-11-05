/* callee body compiled before its caller in the same unit: the compiler then knows which registers it leaves untouched (interprocedural register use). Verified as a duplicate of the real function at 0x00464af0. */
static void FUN_00464af0(float *arg0, float *arg1, float fparg0) {
    float temp_f1;
    float temp_f1_2;

    temp_f1 = *arg0;
    if (!(temp_f1 <= fparg0)) {
        *arg0 = temp_f1 - fparg0;
    } else if (temp_f1 < -fparg0) {
        *arg0 = temp_f1 + fparg0;
    } else {
        *arg0 = 0.0f;
    }
    temp_f1_2 = *arg1;
    if (!(temp_f1_2 <= fparg0)) {
        *arg1 = temp_f1_2 - fparg0;
        return;
    }
    if (temp_f1_2 < -fparg0) {
        *arg1 = temp_f1_2 + fparg0;
        return;
    }
    *arg1 = 0.0f;
}
