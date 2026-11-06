int igMetaEnum_Create();
extern int DAT_004c17c0[4];
extern int DAT_004c17d0[4];
extern int DAT_004f89f8[4];
extern int DAT_00586a78[4];
int FUN_002cd9f0(void) {
    if (DAT_00586a78[0] == 0) {
        DAT_00586a78[0] = igMetaEnum_Create(&DAT_004f89f8[0], &DAT_004c17c0[0], &DAT_004c17d0[0], 4);
    }
    return DAT_00586a78[0];
}
