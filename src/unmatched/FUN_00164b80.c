extern int DAT_005606e0[4];
extern int DAT_005606e4[4];
extern int DAT_005606e8[4];
extern int DAT_005606ec[4];
extern int DAT_005606f0[4];
extern int DAT_005606f4[4];
extern int DAT_005606f8[4];
extern int DAT_005606fc[4];
extern int DAT_005610a8[4];
extern int DAT_005610b8[4];
extern int DAT_005610c8[4];
extern int DAT_00586808[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
extern char GPR_00554b30;

int *FUN_00164b80(void) {
    if (GPR_00554b30 == 0) {
        DAT_005606e0[0] = DAT_00586808[0];
        GPR_00554b30 = 1;
        DAT_005606e4[0] = DAT_005610c8[0];
        DAT_005606e8[0] = DAT_005610b8[0];
        DAT_005606ec[0] = DAT_005610a8[0];
        DAT_005606f0[0] = DAT_00586898[0];
        DAT_005606f4[0] = DAT_00586818[0];
        DAT_005606f8[0] = DAT_00586830[0];
        DAT_005606fc[0] = DAT_00586840[0];
    }
    return &DAT_005606e0[0];
}
