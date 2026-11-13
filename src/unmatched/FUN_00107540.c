int FUN_001064c8();
int FUN_001064f8();
int FUN_00106c88();
int _sceMpegMessage();
extern int DAT_004d20e0[4];
extern int DAT_004d2108[4];
void FUN_00107540(void *arg0) {
    int temp_v0;
    int temp_v0_2;

    temp_v0 = FUN_00106c88(arg0, 1);
    *(int *)((char *)(arg0) + 2136) = temp_v0;
    if (temp_v0 != 0) {
        FUN_001064f8(arg0);
        FUN_001064c8(arg0, 0x50000000);
        FUN_001064f8(arg0);
    }
    temp_v0_2 = FUN_00106c88(arg0, 1);
    *(int *)((char *)(arg0) + 2140) = temp_v0_2;
    if (temp_v0_2 != 0) {
        FUN_001064f8(arg0);
        FUN_001064c8(arg0, 0x58000000);
        FUN_001064f8(arg0);
    }
    if (FUN_00106c88(arg0, 1) != 0) {
        _sceMpegMessage(arg0, &DAT_004d20e0[0]);
    }
    if (FUN_00106c88(arg0, 1) != 0) {
        _sceMpegMessage(arg0, &DAT_004d2108[0]);
    }
}
