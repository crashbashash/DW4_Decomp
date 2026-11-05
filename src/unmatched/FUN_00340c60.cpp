extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c3348[4];
extern int DAT_00501a58[4];
extern int DAT_00587be8[4];
extern int DAT_00587bf0[4];
int FUN_00340c60(void) {
    if (DAT_00587be8[0] == 0) {
        DAT_00587be8[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c3348[0], &DAT_00587bf0[0], 1);
    }
    return DAT_00587be8[0];
}
}
