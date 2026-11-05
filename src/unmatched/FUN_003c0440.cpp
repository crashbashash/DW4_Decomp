extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca9a0[4];
extern int DAT_004ca9d0[4];
extern int DAT_005122d0[4];
extern int DAT_0058b418[4];
int FUN_003c0440(void);
}
int FUN_003c0440(void) {
    if (DAT_0058b418[0] == 0) {
        DAT_0058b418[0] = igMetaEnum_Create(&DAT_005122d0[0], &DAT_004ca9a0[0], &DAT_004ca9d0[0], 0xB);
    }
    return DAT_0058b418[0];
}
