int ADXM_IsSetupThrd();
int FUN_0029aa78();
int FUN_0029ac78();

int FUN_0029aa10(int arg0) {
    int temp_v0;
    int var_s2;

    var_s2 = 0;
    temp_v0 = ADXM_IsSetupThrd();
    if ((temp_v0 == 1) && (FUN_0029aa78() != temp_v0)) {
        var_s2 = FUN_0029ac78(arg0);
    }
    return var_s2;
}
