int igMetaEnum_Create();
extern int DAT_004c1268[4];
extern int DAT_004c1278[4];
extern int DAT_004f8348[4];
extern int DAT_00586708[4];
int FUN_002c7780(void) {
    if (DAT_00586708[0] == 0) {
        DAT_00586708[0] = igMetaEnum_Create(&DAT_004f8348[0], &DAT_004c1268[0], &DAT_004c1278[0], 3);
    }
    return DAT_00586708[0];
}
