/* 0x0014ad60 — FUN_0014ad60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00488580[4];
extern int DAT_00488590[4];
extern int DAT_004dbb40[4];
extern int DAT_0055fa08[4];
int FUN_0014ad60(void) {
    if (DAT_0055fa08[0] == 0) {
        DAT_0055fa08[0] = igMetaEnum_Create(&DAT_004dbb40[0], &DAT_00488580[0], &DAT_00488590[0], 4);
    }
    return DAT_0055fa08[0];
}
