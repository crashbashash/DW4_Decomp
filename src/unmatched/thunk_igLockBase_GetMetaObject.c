/* 0x00226c50 — thunk_igLockBase_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLockBase_GetMetaObject();

void thunk_igLockBase_GetMetaObject(void) {
    igLockBase_GetMetaObject();
}
