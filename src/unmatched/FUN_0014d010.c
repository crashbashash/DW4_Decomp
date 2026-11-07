int igMetaEnum_Create();
extern int DAT_00488b80[4];
extern int DAT_00488b90[4];
extern int DAT_004dc4c0[4];
extern int DAT_0055fc98[4];
int FUN_0014d010(void) {
    if (DAT_0055fc98[0] == 0) {
        DAT_0055fc98[0] = igMetaEnum_Create(&DAT_004dc4c0[0], &DAT_00488b80[0], &DAT_00488b90[0], 4);
    }
    return DAT_0055fc98[0];
}
