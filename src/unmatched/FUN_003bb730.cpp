/* 0x003bb730 - FUN_003bb730. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca090[4];
extern int DAT_004ca0b0[4];
extern int DAT_00510d58[4];
extern int DAT_0058b020[4];
int FUN_003bb730(void);
}
int FUN_003bb730(void) {
    if (DAT_0058b020[0] == 0) {
        DAT_0058b020[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca090[0], &DAT_004ca0b0[0], 7);
    }
    return DAT_0058b020[0];
}
