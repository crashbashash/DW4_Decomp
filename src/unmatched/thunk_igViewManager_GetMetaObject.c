/* 0x0045d380 — thunk_igViewManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewManager_GetMetaObject();

void thunk_igViewManager_GetMetaObject(void) {
    igViewManager_GetMetaObject();
}
