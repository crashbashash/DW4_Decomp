/* 0x002cd5c0 — FUN_002cd5c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_004c16b0[4];
extern int DAT_004c16c0[4];
extern int DAT_004f89f8[4];
extern int DAT_00586a28[4];
int FUN_002cd5c0(void) {
    if (DAT_00586a28[0] == 0) {
        DAT_00586a28[0] = igMetaEnum_Create(&DAT_004f89f8[0], &DAT_004c16b0[0], &DAT_004c16c0[0], 4);
    }
    return DAT_00586a28[0];
}
