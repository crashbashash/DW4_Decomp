int FUN_00100610();
int FUN_00328e00();
extern int DAT_0052d8b0[4];
int **FUN_0032f2a0(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0052d8b0[0];
        FUN_00328e00(arg0, 0);
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
