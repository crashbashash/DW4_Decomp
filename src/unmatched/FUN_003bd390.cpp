extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca410[4];
extern int DAT_004ca420[4];
extern int DAT_00510d58[4];
extern int DAT_0058b1d0[4];
int FUN_003bd390(void);
}
int FUN_003bd390(void) {
    if (DAT_0058b1d0[0] == 0) {
        DAT_0058b1d0[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca410[0], &DAT_004ca420[0], 4);
    }
    return DAT_0058b1d0[0];
}
