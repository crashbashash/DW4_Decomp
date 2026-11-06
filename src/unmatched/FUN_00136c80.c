int igMetaEnum_Create();
extern int DAT_00486478[4];
extern int DAT_00486488[4];
extern int DAT_004d55c0[4];
extern int DAT_0055f110[4];
int FUN_00136c80(void) {
    if (DAT_0055f110[0] == 0) {
        DAT_0055f110[0] = igMetaEnum_Create(&DAT_004d55c0[0], &DAT_00486478[0], &DAT_00486488[0], 3);
    }
    return DAT_0055f110[0];
}
