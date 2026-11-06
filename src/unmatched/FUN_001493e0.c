int igMetaEnum_Create();
extern int DAT_00487768[4];
extern int DAT_00487770[4];
extern int DAT_004d70e0[4];
extern int DAT_0055f828[4];
int FUN_001493e0(void) {
    if (DAT_0055f828[0] == 0) {
        DAT_0055f828[0] = igMetaEnum_Create(&DAT_004d70e0[0], &DAT_00487768[0], &DAT_00487770[0], 2);
    }
    return DAT_0055f828[0];
}
