int FUN_0027e1c0();
int FUN_0027e1d8();
extern int (*DAT_00570bb8)();

int FUN_0027eca8(int *arg0) {
    int temp_v0;
    int var_s0;

    if (DAT_00570bb8 != 0) {
        var_s0 = (int)(DAT_00570bb8());
    } else {
        FUN_0027e1c0();
        temp_v0 = *arg0;
        *arg0 = 1;
        var_s0 = temp_v0 != 1;
        FUN_0027e1d8();
    }
    return var_s0;
}
