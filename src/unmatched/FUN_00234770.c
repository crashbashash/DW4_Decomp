int FUN_002345b0();
int igStrCmp();
extern int DAT_004e95f8[4];
extern int DAT_004e96b0[4];
int FUN_00234770(int arg0, int arg1, int arg2, char *arg3) {
    int sp2C;
    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) == 0) {
        return 0;
    }
    *arg3 = 0;
    if (igStrCmp(sp2C, &DAT_004e96b0[0]) == 0) {
        *arg3 = 1;
    } else if (igStrCmp(sp2C, &DAT_004e95f8[0]) == 0) {
        *arg3 = 1;
    }
    return 1;
}
