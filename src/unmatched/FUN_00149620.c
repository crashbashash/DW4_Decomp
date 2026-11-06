int igMetaEnum_Create();
extern int DAT_00487850[4];
extern int DAT_00487858[4];
extern int DAT_004d7520[4];
extern int DAT_0055f858[4];
int FUN_00149620(void) {
    if (DAT_0055f858[0] == 0) {
        DAT_0055f858[0] = igMetaEnum_Create(&DAT_004d7520[0], &DAT_00487850[0], &DAT_00487858[0], 2);
    }
    return DAT_0055f858[0];
}
