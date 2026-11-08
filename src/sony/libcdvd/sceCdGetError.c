extern char DAT_00484740[];
int FUN_0010e2a8();
int FUN_00116d90();
int SignalSema();
extern int DAT_0048356c[4];
extern int DAT_004850c0[4];
int sceCdGetError(void) {
    int temp_s0;

    if (FUN_00116d90(3) == 0) {
        return -1;
    }
    if (FUN_0010e2a8(&DAT_004850c0[0], 4, 0, 0, 0, DAT_00484740, 4, 0, 0) < 0) {
        SignalSema(DAT_0048356c[0]);
        return -1;
    }
    temp_s0 = *(int *)((int)DAT_00484740 | 0x20000000);
    SignalSema(DAT_0048356c[0]);
    return temp_s0;
}
