int FUN_0010e2a8();
extern int DAT_004bb100;
extern int DAT_00570c00[];
extern int DAT_00571750[];
int FUN_00281a00(int cmd, int *args, int n, int size) {
    int i;
    if (DAT_004bb100 == 0) {
        DAT_004bb100 = 1;
        for (i = 0; i < n; i++) {
            DAT_00570c00[i] = *args++;
        }
        FUN_0010e2a8(DAT_00571750, cmd, 0, DAT_00570c00, n * 4, DAT_00570c00, size, 0, 0);
        DAT_004bb100 = 0;
        return DAT_00570c00[0];
    }
    return -0x100;
}
