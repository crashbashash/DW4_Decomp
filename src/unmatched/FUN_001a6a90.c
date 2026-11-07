int igMetaEnum_Create();
extern int DAT_0048cf10[4];
extern int DAT_0048cf20[4];
extern int DAT_004e38a0[4];
extern int DAT_005620e8[4];
int FUN_001a6a90(void) {
    if (DAT_005620e8[0] == 0) {
        DAT_005620e8[0] = igMetaEnum_Create(&DAT_004e38a0[0], &DAT_0048cf10[0], &DAT_0048cf20[0], 4);
    }
    return DAT_005620e8[0];
}
