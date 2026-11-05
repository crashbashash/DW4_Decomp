/* 0x001a6af0 — FUN_001a6af0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_0048cf30[4];
extern int DAT_0048cf50[4];
extern int DAT_004e38f8[4];
extern int DAT_005620f0[4];
int FUN_001a6af0(void) {
    if (DAT_005620f0[0] == 0) {
        DAT_005620f0[0] = igMetaEnum_Create(&DAT_004e38f8[0], &DAT_0048cf30[0], &DAT_0048cf50[0], 6);
    }
    return DAT_005620f0[0];
}
