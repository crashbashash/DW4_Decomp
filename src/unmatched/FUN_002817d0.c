int FUN_00281a00();
extern int DAT_00570c00[];
void FUN_002817d0(int *arg0, int *arg1) {
    int i;
    FUN_00281a00(0xFE00, 0, 0, 0x80);
    for (i = 0; i < 32; i++) {
        *arg0++ = DAT_00570c00[i];
        *arg1++ = DAT_00570c00[i + 32];
    }
}
