int igMetaEnum_Create();
extern int DAT_004878b0[4];
extern int DAT_004878e0[4];
extern int DAT_004d78d0[4];
extern int DAT_0055f870[4];
int FUN_00149740(void) {
    if (DAT_0055f870[0] == 0) {
        DAT_0055f870[0] = igMetaEnum_Create(&DAT_004d78d0[0], &DAT_004878b0[0], &DAT_004878e0[0], 0xB);
    }
    return DAT_0055f870[0];
}
