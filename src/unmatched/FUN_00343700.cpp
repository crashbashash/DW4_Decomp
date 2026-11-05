extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c3790[4];
extern int DAT_00501a58[4];
extern int DAT_00587e00[4];
extern int DAT_00587e08[4];
int FUN_00343700(void) {
    if (DAT_00587e00[0] == 0) {
        DAT_00587e00[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c3790[0], &DAT_00587e08[0], 1);
    }
    return DAT_00587e00[0];
}
}
