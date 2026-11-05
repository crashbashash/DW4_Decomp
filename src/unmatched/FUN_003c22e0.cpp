extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004cac40[4];
extern int DAT_00510d58[4];
extern int DAT_0058b560[4];
extern int DAT_0058b568[4];
int FUN_003c22e0(void);
}
int FUN_003c22e0(void) {
    if (DAT_0058b560[0] == 0) {
        DAT_0058b560[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004cac40[0], &DAT_0058b568[0], 1);
    }
    return DAT_0058b560[0];
}
