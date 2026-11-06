extern "C" {
int FUN_003b2d10(int **, int);
int thunk_FUN_002ed460__002ff810(int **);
extern int DAT_0053daa0[4];
extern int DAT_0053f2c0[4];
int **FUN_003b6770(int **arg0, long long arg1);
}
int **FUN_003b6770(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0053f2c0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0053daa0[0];
            FUN_003b2d10(arg0, 0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
