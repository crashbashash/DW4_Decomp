/* 0x002c8e00 — thunk_igMetaObjectListList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObjectListList_GetMetaObject();

void thunk_igMetaObjectListList_GetMetaObject(void) {
    igMetaObjectListList_GetMetaObject();
}
