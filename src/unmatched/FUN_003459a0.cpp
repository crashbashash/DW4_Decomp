extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c3b40[4];
extern int DAT_004c3b60[4];
extern int DAT_005016f0[4];
extern int DAT_00587f90[4];
int FUN_003459a0(void) {
    if (DAT_00587f90[0] == 0) {
        DAT_00587f90[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c3b40[0], &DAT_004c3b60[0], 7);
    }
    return DAT_00587f90[0];
}
}
