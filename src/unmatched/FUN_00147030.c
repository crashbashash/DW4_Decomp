int igMetaEnum_Create();
extern int DAT_00487580[4];
extern int DAT_004875a0[4];
extern int DAT_004d6e30[4];
extern int DAT_0055f758[4];
int FUN_00147030(void) {
    if (DAT_0055f758[0] == 0) {
        DAT_0055f758[0] = igMetaEnum_Create(&DAT_004d6e30[0], &DAT_00487580[0], &DAT_004875a0[0], 8);
    }
    return DAT_0055f758[0];
}
