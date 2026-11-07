int igMetaEnum_Create();
extern int DAT_004c1248[4];
extern int DAT_004c1258[4];
extern int DAT_004f8330[4];
extern int DAT_00586700[4];
int FUN_002c7720(void) {
    if (DAT_00586700[0] == 0) {
        DAT_00586700[0] = igMetaEnum_Create(&DAT_004f8330[0], &DAT_004c1248[0], &DAT_004c1258[0], 3);
    }
    return DAT_00586700[0];
}
