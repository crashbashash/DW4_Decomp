/* 0x00452c40 — FUN_00452c40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCharMetricsMetaField_RunStaticInit();
extern int DAT_0058c650[4];
int FUN_00452c40(void) {
    if (DAT_0058c650[0] == 0) {
        igCharMetricsMetaField_RunStaticInit();
    }
    return DAT_0058c650[0];
}
