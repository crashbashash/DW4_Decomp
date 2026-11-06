int igMetaEnum_Create();
extern int DAT_0048cf30[4];
extern int DAT_0048cf50[4];
extern int DAT_004e38f8[4];
extern int DAT_005620f0[4];
int FUN_001a6af0(void) {
    if (DAT_005620f0[0] == 0) {
        DAT_005620f0[0] = igMetaEnum_Create(&DAT_004e38f8[0], &DAT_0048cf30[0], &DAT_0048cf50[0], 6);
    }
    return DAT_005620f0[0];
}
