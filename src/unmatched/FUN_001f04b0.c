extern char DAT_00568f00[];
extern char DAT_00568f60[];
int FUN_001f04b0(int arg0, int arg1) {
    int temp_a2;
    int temp_a0;
    int var_v0;

    temp_a0 = arg0 * 4;
    temp_a2 = *(int *)(DAT_00568f60 + temp_a0);
    var_v0 = 0;
    if ((temp_a2 != 0) && (arg1 != 0) && (*(int *)(DAT_00568f00 + temp_a0) != temp_a2) && (arg1 != temp_a2)) {
        var_v0 = 1;
    }
    return var_v0;
}
