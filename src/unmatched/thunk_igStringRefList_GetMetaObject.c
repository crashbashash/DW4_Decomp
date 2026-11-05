/* 0x002b9280 — thunk_igStringRefList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStringRefList_GetMetaObject();

void thunk_igStringRefList_GetMetaObject(void) {
    igStringRefList_GetMetaObject();
}
