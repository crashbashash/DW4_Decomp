int igMetaEnum_Create();
extern int DAT_00487290[4];
extern int DAT_00487360[4];
extern int DAT_004d6bc8[4];
extern int DAT_0055f6a8[4];
int FUN_00146850(void) {
    if (DAT_0055f6a8[0] == 0) {
        DAT_0055f6a8[0] = igMetaEnum_Create(&DAT_004d6bc8[0], &DAT_00487290[0], &DAT_00487360[0], 0x31);
    }
    return DAT_0055f6a8[0];
}
