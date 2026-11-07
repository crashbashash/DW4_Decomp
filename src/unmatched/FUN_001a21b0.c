int igMetaEnum_Create();
extern int DAT_0048c360[4];
extern int DAT_0048c380[4];
extern int DAT_004e1448[4];
extern int DAT_00561b98[4];
int FUN_001a21b0(void) {
    if (DAT_00561b98[0] == 0) {
        DAT_00561b98[0] = igMetaEnum_Create(&DAT_004e1448[0], &DAT_0048c360[0], &DAT_0048c380[0], 5);
    }
    return DAT_00561b98[0];
}
