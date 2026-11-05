extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c2ff8[4];
extern int DAT_004c3008[4];
extern int DAT_005016f0[4];
extern int DAT_00587a60[4];
int FUN_0033f3b0(void) {
    if (DAT_00587a60[0] == 0) {
        DAT_00587a60[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c2ff8[0], &DAT_004c3008[0], 3);
    }
    return DAT_00587a60[0];
}
}
