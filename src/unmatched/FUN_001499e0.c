int igMetaEnum_Create();
extern int DAT_00487a50[4];
extern int DAT_00487b40[4];
extern int DAT_004d8870[4];
extern int DAT_0055f8a8[4];
int FUN_001499e0(void) {
    if (DAT_0055f8a8[0] == 0) {
        DAT_0055f8a8[0] = igMetaEnum_Create(&DAT_004d8870[0], &DAT_00487a50[0], &DAT_00487b40[0], 0x3B);
    }
    return DAT_0055f8a8[0];
}
