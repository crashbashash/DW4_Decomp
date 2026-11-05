/* 0x0035eb30 - FUN_0035eb30. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c6850[4];
extern int DAT_004c6870[4];
extern int DAT_00501a58[4];
extern int DAT_00589458[4];
int FUN_0035eb30(void);
}

int FUN_0035eb30(void) {
    if (DAT_00589458[0] == 0) {
        DAT_00589458[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c6850[0], &DAT_004c6870[0], 5);
    }
    return DAT_00589458[0];
}
