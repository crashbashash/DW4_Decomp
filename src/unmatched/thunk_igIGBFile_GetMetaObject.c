/* 0x002c3e70 — thunk_igIGBFile_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIGBFile_GetMetaObject();

void thunk_igIGBFile_GetMetaObject(void) {
    igIGBFile_GetMetaObject();
}
