int igMetaEnum_Create();
extern int DAT_00487910[4];
extern int DAT_00487930[4];
extern int DAT_004d7a50[4];
extern int DAT_0055f878[4];
int FUN_001497a0(void) {
    if (DAT_0055f878[0] == 0) {
        DAT_0055f878[0] = igMetaEnum_Create(&DAT_004d7a50[0], &DAT_00487910[0], &DAT_00487930[0], 6);
    }
    return DAT_0055f878[0];
}
