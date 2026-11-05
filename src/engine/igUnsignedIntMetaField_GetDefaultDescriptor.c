/* 0x002b7070 — igUnsignedIntMetaField_GetDefaultDescriptor. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igUnsignedIntMetaField_EnsureRegistered();
extern int DAT_00585740[4];
int igUnsignedIntMetaField_GetDefaultDescriptor(void) {
    if (DAT_00585740[0] == 0) {
        igUnsignedIntMetaField_EnsureRegistered();
    }
    return DAT_00585740[0];
}
