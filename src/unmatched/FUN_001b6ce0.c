float FUN_00122d90(float);
float FUN_001234c0(float);
void FUN_001b6cd0(void *, float, float, float, float, float, float);

void FUN_001b6ce0(void *arg0, float fparg0, float fparg1, float fparg2, float fparg3, float fparg4) {
    float var_f23;
    float temp_f14;
    float temp_f23;
    float var_f22;

    var_f23 = 0.0174532924f * fparg0;
    var_f22 = 0.0174532924f * fparg1;
    if (fparg0 < 0.0f) {
        var_f23 = 2.0f * FUN_00122d90((fparg2 * (fparg3 * FUN_001234c0(0.5f * var_f22))) / fparg3);
    } else {
        var_f22 = 2.0f * FUN_00122d90(((fparg3 * FUN_001234c0(0.5f * var_f23)) / fparg2) / fparg3);
    }
    temp_f23 = fparg3 * -FUN_001234c0(0.5f * var_f23);
    temp_f14 = fparg3 * -FUN_001234c0(0.5f * var_f22);
    FUN_001b6cd0(arg0, temp_f23, -temp_f23, temp_f14, -temp_f14, fparg3, fparg4);
}
