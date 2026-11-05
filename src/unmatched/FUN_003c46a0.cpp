extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004cb710[4];
extern int DAT_004cb730[4];
extern int DAT_00510d58[4];
extern int DAT_0058bac0[4];
int FUN_003c46a0(void);
}
int FUN_003c46a0(void) {
    if (DAT_0058bac0[0] == 0) {
        DAT_0058bac0[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004cb710[0], &DAT_004cb730[0], 8);
    }
    return DAT_0058bac0[0];
}
