extern char DAT_004835c0[];
int FUN_0010e2a8();
int FUN_00116a78();
int SignalSema();
extern int DAT_00483568[4];
extern int DAT_00484710[4];
int FUN_00116be8(void) {
    int temp_s0;

    if (FUN_00116a78(2) == 0) {
        return 0;
    }
    if (FUN_0010e2a8(&DAT_00484710[0], 0xE, 0, 0, 0, DAT_004835c0, 4, 0, 0) < 0) {
        SignalSema(DAT_00483568[0]);
        return 0;
    }
    temp_s0 = *(int *)((int)DAT_004835c0 | 0x20000000);
    SignalSema(DAT_00483568[0]);
    return temp_s0;
}
