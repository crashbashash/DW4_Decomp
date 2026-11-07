int igMetaEnum_Create();
extern int DAT_004889c0[4];
extern int DAT_004889d0[4];
extern int DAT_004dc210[4];
extern int DAT_0055fbd8[4];
int FUN_0014c920(void) {
    if (DAT_0055fbd8[0] == 0) {
        DAT_0055fbd8[0] = igMetaEnum_Create(&DAT_004dc210[0], &DAT_004889c0[0], &DAT_004889d0[0], 3);
    }
    return DAT_0055fbd8[0];
}
