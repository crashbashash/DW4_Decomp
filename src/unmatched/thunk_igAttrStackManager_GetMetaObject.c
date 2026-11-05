/* 0x001a56d0 — thunk_igAttrStackManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAttrStackManager_GetMetaObject();

void thunk_igAttrStackManager_GetMetaObject(void) {
    igAttrStackManager_GetMetaObject();
}
