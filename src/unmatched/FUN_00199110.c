int igMetaEnum_Create();
extern int DAT_0048b650[4];
extern int DAT_0048b660[4];
extern int DAT_004e1c00[4];
extern int DAT_00561520[4];
int FUN_00199110(void) {
    if (DAT_00561520[0] == 0) {
        DAT_00561520[0] = igMetaEnum_Create(&DAT_004e1c00[0], &DAT_0048b650[0], &DAT_0048b660[0], 4);
    }
    return DAT_00561520[0];
}
