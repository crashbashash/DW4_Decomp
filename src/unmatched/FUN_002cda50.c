/* 0x002cda50 — FUN_002cda50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_004c17e0[4];
extern int DAT_004c17f0[4];
extern int DAT_004f8b30[4];
extern int DAT_00586a80[4];
int FUN_002cda50(void) {
    if (DAT_00586a80[0] == 0) {
        DAT_00586a80[0] = igMetaEnum_Create(&DAT_004f8b30[0], &DAT_004c17e0[0], &DAT_004c17f0[0], 4);
    }
    return DAT_00586a80[0];
}
