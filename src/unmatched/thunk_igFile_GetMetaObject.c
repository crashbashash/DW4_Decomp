/* 0x002c09d0 — thunk_igFile_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFile_GetMetaObject();

void thunk_igFile_GetMetaObject(void) {
    igFile_GetMetaObject();
}
