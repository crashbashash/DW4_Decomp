/* 0x00139e70 — FUN_00139e70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00486ab0[4];
extern int DAT_00486ac0[4];
extern int DAT_004d5bc0[4];
extern int DAT_0055f3b0[4];
int FUN_00139e70(void) {
    if (DAT_0055f3b0[0] == 0) {
        DAT_0055f3b0[0] = igMetaEnum_Create(&DAT_004d5bc0[0], &DAT_00486ab0[0], &DAT_00486ac0[0], 3);
    }
    return DAT_0055f3b0[0];
}
