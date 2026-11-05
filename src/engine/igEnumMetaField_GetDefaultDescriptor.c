/* 0x002c6380 — igEnumMetaField_GetDefaultDescriptor. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igEnumMetaField_EnsureRegistered();
extern int DAT_005865a0[4];
int igEnumMetaField_GetDefaultDescriptor(void) {
    if (DAT_005865a0[0] == 0) {
        igEnumMetaField_EnsureRegistered();
    }
    return DAT_005865a0[0];
}
