int igMetaEnum_Create();
extern int DAT_00488cd0[4];
extern int DAT_00488ce0[4];
extern int DAT_004dc710[4];
extern int DAT_0055fd00[4];
int FUN_0014d4b0(void) {
    if (DAT_0055fd00[0] == 0) {
        DAT_0055fd00[0] = igMetaEnum_Create(&DAT_004dc710[0], &DAT_00488cd0[0], &DAT_00488ce0[0], 3);
    }
    return DAT_0055fd00[0];
}
