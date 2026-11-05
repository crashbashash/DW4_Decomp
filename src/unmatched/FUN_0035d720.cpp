extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c65a0[4];
extern int DAT_004c65c0[4];
extern int DAT_00501a58[4];
extern int DAT_00589348[4];
int FUN_0035d720(void);
}

int FUN_0035d720(void) {
    if (DAT_00589348[0] == 0) {
        DAT_00589348[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c65a0[0], &DAT_004c65c0[0], 5);
    }
    return DAT_00589348[0];
}
