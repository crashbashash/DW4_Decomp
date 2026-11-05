/* 0x002c25f0 — thunk_igLibrary_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLibrary_GetMetaObject();

void thunk_igLibrary_GetMetaObject(void) {
    igLibrary_GetMetaObject();
}
