/* 0x00226aa0 — thunk_igLockInterface_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLockInterface_GetMetaObject();

void thunk_igLockInterface_GetMetaObject(void) {
    igLockInterface_GetMetaObject();
}
