/* 0x002bfa60 — FUN_002bfa60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryRefMetaField_EnsureRegistered();
extern int DAT_00585d88[4];
int FUN_002bfa60(void) {
    if (DAT_00585d88[0] == 0) {
        igMemoryRefMetaField_EnsureRegistered();
    }
    return DAT_00585d88[0];
}
