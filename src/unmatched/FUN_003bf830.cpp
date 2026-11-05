extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca820[4];
extern int DAT_004ca840[4];
extern int DAT_00512120[4];
extern int DAT_0058b3a0[4];
int FUN_003bf830(void);
}
int FUN_003bf830(void) {
    if (DAT_0058b3a0[0] == 0) {
        DAT_0058b3a0[0] = igMetaEnum_Create(&DAT_00512120[0], &DAT_004ca820[0], &DAT_004ca840[0], 7);
    }
    return DAT_0058b3a0[0];
}
