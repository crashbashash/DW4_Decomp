int FUN_0013a800();
int FUN_00194830();
int FUN_001948b0();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00528870[4];
extern int DAT_0052b870[4];
int **FUN_00194790(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0052b870[0];
        if (arg0 != 0) {
            *arg0 = &DAT_00528870[0];
            FUN_00194830((char *)arg0 + 20, -1);
            FUN_001948b0((char *)arg0 + 16, -1);
            FUN_0013a800((char *)arg0 + 12, -1);
            FUN_0013a800((char *)arg0 + 8, -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
