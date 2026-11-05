extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c3780[4];
extern int DAT_004c3788[4];
extern int DAT_005016f0[4];
extern int DAT_00587df0[4];
int FUN_00343430(void) {
    if (DAT_00587df0[0] == 0) {
        DAT_00587df0[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c3780[0], &DAT_004c3788[0], 2);
    }
    return DAT_00587df0[0];
}
}
