extern int DAT_004b1e00[4];
int FUN_0027a200(unsigned int arg0) {
    int var_v0;

    var_v0 = 0;
    if (arg0 < 2U) {
        var_v0 = *(int *)((char *)&DAT_004b1e00[0] + (arg0 * 4));
    }
    return var_v0;
}
