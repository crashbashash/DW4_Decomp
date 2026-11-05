/* 0x002be050 — thunk_igNamedObjectInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNamedObjectInfo_GetMetaObject();

void thunk_igNamedObjectInfo_GetMetaObject(void) {
    igNamedObjectInfo_GetMetaObject();
}
