int igMetaEnum_Create();
extern int DAT_0048cf68[4];
extern int DAT_0048cf78[4];
extern int DAT_004e3928[4];
extern int DAT_005620f8[4];
int FUN_001a6b50(void) {
    if (DAT_005620f8[0] == 0) {
        DAT_005620f8[0] = igMetaEnum_Create(&DAT_004e3928[0], &DAT_0048cf68[0], &DAT_0048cf78[0], 3);
    }
    return DAT_005620f8[0];
}
