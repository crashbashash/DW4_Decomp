int _getMacroblockAddressIncrement();
int _ipuShowBits();
int _ipuFlushBits();
int FUN_00106df8();
int FUN_00106e78();
int _sceMpegErrorf();
int _sceMpegMessage();
extern int DAT_004d1ff8[4];
extern int DAT_004d2020[4];
int FUN_001058b8(void *arg0, int arg1, int *arg2, int *arg3, void *arg4) {
    int temp_s3;
    int temp_v0;
    int temp_v0_2;

    *(int *)((char *)(arg0) + 308) = 0;
    FUN_00106df8(arg0);
    temp_v0 = _ipuShowBits(arg0, 0x20);
    if ((unsigned int) (temp_v0 - 0x101) >= 0xAFU) {
        _sceMpegErrorf(arg0, &DAT_004d1ff8[0], temp_v0);
        return 2;
    }
    _ipuFlushBits(arg0, 0x20);
    temp_s3 = FUN_00106e78(arg0);
    temp_v0_2 = _getMacroblockAddressIncrement(arg0);
    *arg3 = temp_v0_2;
    if (*(int *)((char *)(arg0) + 308) != 0) {
        _sceMpegMessage(arg0, &DAT_004d2020[0], temp_v0_2);
        return 1;
    }
    *arg2 = (((((temp_s3 << 7) + (temp_v0 & 0xFF)) - 1) * *(int *)((char *)(arg0) + 324)) + temp_v0_2) - 1;
    *arg3 = 1;
    *(int *)((char *)(arg0) + 456) = 1;
    *(int *)((char *)(arg4) + 20) = 0;
    *(int *)((char *)(arg4) + 16) = 0;
    *(int *)((char *)(arg4) + 4) = 0;
    *(int *)((char *)(arg4) + 0) = 0;
    *(int *)((char *)(arg4) + 28) = 0;
    *(int *)((char *)(arg4) + 24) = 0;
    *(int *)((char *)(arg4) + 12) = 0;
    *(int *)((char *)(arg4) + 8) = 0;
    return 0;
}
