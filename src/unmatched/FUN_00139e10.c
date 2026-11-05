/* 0x00139e10 — FUN_00139e10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00486a90[4];
extern int DAT_00486aa0[4];
extern int DAT_004d5b40[4];
extern int DAT_0055f3a8[4];
int FUN_00139e10(void) {
    if (DAT_0055f3a8[0] == 0) {
        DAT_0055f3a8[0] = igMetaEnum_Create(&DAT_004d5b40[0], &DAT_00486a90[0], &DAT_00486aa0[0], 3);
    }
    return DAT_0055f3a8[0];
}
