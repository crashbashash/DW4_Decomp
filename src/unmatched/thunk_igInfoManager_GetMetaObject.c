/* 0x00233990 — thunk_igInfoManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInfoManager_GetMetaObject();

void thunk_igInfoManager_GetMetaObject(void) {
    igInfoManager_GetMetaObject();
}
