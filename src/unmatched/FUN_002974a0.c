int FUN_002963a8();
int FUN_002968c0();
int mwsfd_Error();
int FUN_002aa548();
extern int DAT_004f3fc8[4];
void FUN_002974a0(int arg0, float fparg0) {
    float temp_f1;
    int temp_a0;
    int temp_f0;
    int var_v1;

    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f3fc8[0]);
        return;
    }
    temp_a0 = FUN_002963a8(arg0);
    temp_f1 = (fparg0 * 1000.0f) + 0.5f;
    temp_f0 = (int)((int) temp_f1);
    var_v1 = 1;
    if (!(temp_f1 < (float) temp_f0)) {
        var_v1 = 0;
    }
    FUN_002aa548(temp_a0, temp_f0 - var_v1);
}
