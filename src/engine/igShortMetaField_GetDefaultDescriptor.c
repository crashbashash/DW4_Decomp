/* 0x002ba2e0 — igShortMetaField_GetDefaultDescriptor. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igShortMetaField_EnsureRegistered();
extern int DAT_00585950[4];
int igShortMetaField_GetDefaultDescriptor(void) {
    if (DAT_00585950[0] == 0) {
        igShortMetaField_EnsureRegistered();
    }
    return DAT_00585950[0];
}
