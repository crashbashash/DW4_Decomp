/* 0x002bbda0 — igRawRefMetaField_GetDefaultDescriptor. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRawRefMetaField_EnsureRegistered();
extern int DAT_00585a88[4];
int igRawRefMetaField_GetDefaultDescriptor(void) {
    if (DAT_00585a88[0] == 0) {
        igRawRefMetaField_EnsureRegistered();
    }
    return DAT_00585a88[0];
}
