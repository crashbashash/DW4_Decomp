extern char DAT_00554b2c[4];
extern int DAT_005606c0[4];
extern int DAT_005606c4[4];
extern int DAT_005606c8[4];
extern int DAT_005606cc[4];
extern int DAT_005606d0[4];
extern int DAT_005610c8[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
int *FUN_00164b10(void) {
    if (DAT_00554b2c[0] == 0) {
        DAT_00554b2c[0] = 1;
        DAT_005606c0[0] = DAT_005610c8[0];
        DAT_005606c4[0] = DAT_00586898[0];
        DAT_005606c8[0] = DAT_00586818[0];
        DAT_005606cc[0] = DAT_00586830[0];
        DAT_005606d0[0] = DAT_00586840[0];
    }
    return &DAT_005606c0[0];
}
