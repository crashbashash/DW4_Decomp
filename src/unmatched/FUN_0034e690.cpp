extern "C" {
int FUN_001958f0(char *, int);
int FUN_00195970(int **, int);
int thunk_FUN_002ed460__002ff810(int **);
extern int DAT_00528dd0[4];
extern int DAT_005381b0[4];
int **FUN_0034e690(int **arg0, long long arg1);
}

int **FUN_0034e690(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_005381b0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_00528dd0[0];
            FUN_001958f0((char *)arg0 + 0x1C, -1);
            FUN_00195970(arg0, 0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
