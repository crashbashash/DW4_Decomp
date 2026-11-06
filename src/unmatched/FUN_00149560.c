int igMetaEnum_Create();
extern int DAT_00487810[4];
extern int DAT_00487820[4];
extern int DAT_004d7450[4];
extern int DAT_0055f848[4];
int FUN_00149560(void) {
    if (DAT_0055f848[0] == 0) {
        DAT_0055f848[0] = igMetaEnum_Create(&DAT_004d7450[0], &DAT_00487810[0], &DAT_00487820[0], 3);
    }
    return DAT_0055f848[0];
}
