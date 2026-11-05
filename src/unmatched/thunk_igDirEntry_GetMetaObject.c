/* 0x002c7980 — thunk_igDirEntry_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDirEntry_GetMetaObject();

void thunk_igDirEntry_GetMetaObject(void) {
    igDirEntry_GetMetaObject();
}
