int igMetaEnum_Create();
extern int DAT_004c1a10[4];
extern int DAT_004c1a20[4];
extern int DAT_004f89f8[4];
extern int DAT_00586b78[4];
int FUN_002ce1b0(void) {
    if (DAT_00586b78[0] == 0) {
        DAT_00586b78[0] = igMetaEnum_Create(&DAT_004f89f8[0], &DAT_004c1a10[0], &DAT_004c1a20[0], 4);
    }
    return DAT_00586b78[0];
}
