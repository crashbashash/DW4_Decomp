int igMetaEnum_Create();
extern int DAT_00487860[4];
extern int DAT_00487868[4];
extern int DAT_004d7580[4];
extern int DAT_0055f860[4];
int FUN_00149680(void) {
    if (DAT_0055f860[0] == 0) {
        DAT_0055f860[0] = igMetaEnum_Create(&DAT_004d7580[0], &DAT_00487860[0], &DAT_00487868[0], 2);
    }
    return DAT_0055f860[0];
}
