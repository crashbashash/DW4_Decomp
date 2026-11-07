int igMetaEnum_Create();
extern int DAT_00485bf0[4];
extern int DAT_00485c00[4];
extern int DAT_004d4d08[4];
extern int DAT_0055ed40[4];
int FUN_00131f80(void) {
    if (DAT_0055ed40[0] == 0) {
        DAT_0055ed40[0] = igMetaEnum_Create(&DAT_004d4d08[0], &DAT_00485bf0[0], &DAT_00485c00[0], 3);
    }
    return DAT_0055ed40[0];
}
