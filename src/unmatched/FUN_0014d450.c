int igMetaEnum_Create();
extern int DAT_00488cb0[4];
extern int DAT_00488cc0[4];
extern int DAT_004dc640[4];
extern int DAT_0055fcf8[4];
int FUN_0014d450(void) {
    if (DAT_0055fcf8[0] == 0) {
        DAT_0055fcf8[0] = igMetaEnum_Create(&DAT_004dc640[0], &DAT_00488cb0[0], &DAT_00488cc0[0], 4);
    }
    return DAT_0055fcf8[0];
}
