int igMetaEnum_Create();
extern int DAT_0048ad10[4];
extern int DAT_0048ad30[4];
extern int DAT_004e0960[4];
extern int DAT_00560f00[4];
int FUN_001869e0(void) {
    if (DAT_00560f00[0] == 0) {
        DAT_00560f00[0] = igMetaEnum_Create(&DAT_004e0960[0], &DAT_0048ad10[0], &DAT_0048ad30[0], 8);
    }
    return DAT_00560f00[0];
}
