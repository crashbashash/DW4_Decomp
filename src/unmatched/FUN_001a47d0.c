/* 0x001a47d0 — FUN_001a47d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_0048ca98[4];
extern int DAT_0048caa0[4];
extern int DAT_004e32e8[4];
extern int DAT_00561ee0[4];
int FUN_001a47d0(void) {
    if (DAT_00561ee0[0] == 0) {
        DAT_00561ee0[0] = igMetaEnum_Create(&DAT_004e32e8[0], &DAT_0048ca98[0], &DAT_0048caa0[0], 2);
    }
    return DAT_00561ee0[0];
}
