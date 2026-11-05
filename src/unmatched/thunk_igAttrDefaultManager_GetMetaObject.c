/* 0x0013abc0 — thunk_igAttrDefaultManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAttrDefaultManager_GetMetaObject();

void thunk_igAttrDefaultManager_GetMetaObject(void) {
    igAttrDefaultManager_GetMetaObject();
}
