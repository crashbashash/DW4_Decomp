int igMetaEnum_Create();
extern int DAT_00487870[4];
extern int DAT_00487890[4];
extern int DAT_004d76a0[4];
extern int DAT_0055f868[4];
int FUN_001496e0(void) {
    if (DAT_0055f868[0] == 0) {
        DAT_0055f868[0] = igMetaEnum_Create(&DAT_004d76a0[0], &DAT_00487870[0], &DAT_00487890[0], 8);
    }
    return DAT_0055f868[0];
}
