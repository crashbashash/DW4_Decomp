extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004caa00[4];
extern int DAT_004caa40[4];
extern int DAT_005123d0[4];
extern int DAT_0058b420[4];
int FUN_003c04a0(void);
}
int FUN_003c04a0(void) {
    if (DAT_0058b420[0] == 0) {
        DAT_0058b420[0] = igMetaEnum_Create(&DAT_005123d0[0], &DAT_004caa00[0], &DAT_004caa40[0], 0x10);
    }
    return DAT_0058b420[0];
}
