int igMetaEnum_Create();
extern int DAT_00487990[4];
extern int DAT_004879a0[4];
extern int DAT_004d7c20[4];
extern int DAT_0055f888[4];
int FUN_00149860(void) {
    if (DAT_0055f888[0] == 0) {
        DAT_0055f888[0] = igMetaEnum_Create(&DAT_004d7c20[0], &DAT_00487990[0], &DAT_004879a0[0], 4);
    }
    return DAT_0055f888[0];
}
