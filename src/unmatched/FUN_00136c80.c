/* 0x00136c80 — FUN_00136c80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00486478[4];
extern int DAT_00486488[4];
extern int DAT_004d55c0[4];
extern int DAT_0055f110[4];
int FUN_00136c80(void) {
    if (DAT_0055f110[0] == 0) {
        DAT_0055f110[0] = igMetaEnum_Create(&DAT_004d55c0[0], &DAT_00486478[0], &DAT_00486488[0], 3);
    }
    return DAT_0055f110[0];
}
