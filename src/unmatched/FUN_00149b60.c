int igMetaEnum_Create();
extern int DAT_00487cb0[4];
extern int DAT_00487fc0[4];
extern int DAT_004db0b0[4];
extern int DAT_0055f8c8[4];
int FUN_00149b60(void) {
    if (DAT_0055f8c8[0] == 0) {
        DAT_0055f8c8[0] = igMetaEnum_Create(&DAT_004db0b0[0], &DAT_00487cb0[0], &DAT_00487fc0[0], 0xC3);
    }
    return DAT_0055f8c8[0];
}
