extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca940[4];
extern int DAT_004ca970[4];
extern int DAT_00512258[4];
extern int DAT_0058b410[4];
int FUN_003c03e0(void);
}
int FUN_003c03e0(void) {
    if (DAT_0058b410[0] == 0) {
        DAT_0058b410[0] = igMetaEnum_Create(&DAT_00512258[0], &DAT_004ca940[0], &DAT_004ca970[0], 0xA);
    }
    return DAT_0058b410[0];
}
