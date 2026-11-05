extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c2958[4];
extern int DAT_004c2968[4];
extern int DAT_00500478[4];
extern int DAT_005877a0[4];
int FUN_00336140(void) {
    if (DAT_005877a0[0] == 0) {
        DAT_005877a0[0] = igMetaEnum_Create(&DAT_00500478[0], &DAT_004c2958[0], &DAT_004c2968[0], 3);
    }
    return DAT_005877a0[0];
}
}
