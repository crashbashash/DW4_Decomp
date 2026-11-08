extern char DAT_00554b28;
extern int DAT_005606a0[4];
extern int DAT_005606a4[4];
extern int DAT_005606a8[4];
extern int DAT_005606ac[4];
extern int DAT_005606b0[4];
extern int DAT_005610b8[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
int *FUN_00164aa0(void) {
    if (DAT_00554b28 == 0) {
        DAT_00554b28 = 1;
        DAT_005606a0[0] = DAT_005610b8[0];
        DAT_005606a4[0] = DAT_00586898[0];
        DAT_005606a8[0] = DAT_00586818[0];
        DAT_005606ac[0] = DAT_00586830[0];
        DAT_005606b0[0] = DAT_00586840[0];
    }
    return &DAT_005606a0[0];
}
