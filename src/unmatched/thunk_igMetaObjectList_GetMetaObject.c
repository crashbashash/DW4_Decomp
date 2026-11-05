/* 0x002c8fb0 — thunk_igMetaObjectList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObjectList_GetMetaObject();

void thunk_igMetaObjectList_GetMetaObject(void) {
    igMetaObjectList_GetMetaObject();
}
