/* 0x002be260 — thunk_igNamedObjectList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNamedObjectList_GetMetaObject();

void thunk_igNamedObjectList_GetMetaObject(void) {
    igNamedObjectList_GetMetaObject();
}
