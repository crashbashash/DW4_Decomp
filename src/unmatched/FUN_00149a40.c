int igMetaEnum_Create();
extern int DAT_00487c30[4];
extern int DAT_00487c40[4];
extern int DAT_004d88f0[4];
extern int DAT_0055f8b0[4];
int FUN_00149a40(void) {
    if (DAT_0055f8b0[0] == 0) {
        DAT_0055f8b0[0] = igMetaEnum_Create(&DAT_004d88f0[0], &DAT_00487c30[0], &DAT_00487c40[0], 3);
    }
    return DAT_0055f8b0[0];
}
