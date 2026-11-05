/* 0x002c8970 — thunk_igObjectListList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObjectListList_GetMetaObject();

void thunk_igObjectListList_GetMetaObject(void) {
    igObjectListList_GetMetaObject();
}
