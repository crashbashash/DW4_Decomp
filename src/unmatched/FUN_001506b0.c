/* 0x001506b0 — FUN_001506b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00489230[4];
extern int DAT_00489238[4];
extern int DAT_004dcf30[4];
extern int DAT_0055ff78[4];
int FUN_001506b0(void) {
    if (DAT_0055ff78[0] == 0) {
        DAT_0055ff78[0] = igMetaEnum_Create(&DAT_004dcf30[0], &DAT_00489230[0], &DAT_00489238[0], 2);
    }
    return DAT_0055ff78[0];
}
