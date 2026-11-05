/* 0x002b9c60 — FUN_002b9c60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStringMetaField_EnsureRegistered();
extern int DAT_00585910[4];
int FUN_002b9c60(void) {
    if (DAT_00585910[0] == 0) {
        igStringMetaField_EnsureRegistered();
    }
    return DAT_00585910[0];
}
