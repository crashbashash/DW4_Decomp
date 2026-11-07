int igMetaEnum_Create();
extern int DAT_00488f50[4];
extern int DAT_00488fb0[4];
extern int DAT_004dcbf0[4];
extern int DAT_0055fe30[4];
int FUN_0014e2a0(void) {
    if (DAT_0055fe30[0] == 0) {
        DAT_0055fe30[0] = igMetaEnum_Create(&DAT_004dcbf0[0], &DAT_00488f50[0], &DAT_00488fb0[0], 0x16);
    }
    return DAT_0055fe30[0];
}
