int igMetaEnum_Create();
extern int DAT_00489240[4];
extern int DAT_00489248[4];
extern int DAT_004dcfb0[4];
extern int DAT_0055ff80[4];
int FUN_00150710(void) {
    if (DAT_0055ff80[0] == 0) {
        DAT_0055ff80[0] = igMetaEnum_Create(&DAT_004dcfb0[0], &DAT_00489240[0], &DAT_00489248[0], 2);
    }
    return DAT_0055ff80[0];
}
