/* 0x0014e520 — thunk_igTrackedElementMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTrackedElementMetaField_GetMetaObject();

void thunk_igTrackedElementMetaField_GetMetaObject(void) {
    igTrackedElementMetaField_GetMetaObject();
}
