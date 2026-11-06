extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c38b0[4];
extern int DAT_004c3910[4];
extern int DAT_00501a58[4];
extern int DAT_00587ea0[4];
int FUN_00344250(void) {
    if (DAT_00587ea0[0] == 0) {
        DAT_00587ea0[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c38b0[0], &DAT_004c3910[0], 0x17);
    }
    return DAT_00587ea0[0];
}
}
