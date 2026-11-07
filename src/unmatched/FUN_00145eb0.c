int igMetaEnum_Create();
extern int DAT_00486dd0[4];
extern int DAT_00486f80[4];
extern int DAT_004d64d8[4];
extern int DAT_0055f5e0[4];
int FUN_00145eb0(void) {
    if (DAT_0055f5e0[0] == 0) {
        DAT_0055f5e0[0] = igMetaEnum_Create(&DAT_004d64d8[0], &DAT_00486dd0[0], &DAT_00486f80[0], 0x69);
    }
    return DAT_0055f5e0[0];
}
