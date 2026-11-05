/* 0x002c14c0 — thunk_igMediaFile_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMediaFile_GetMetaObject();

void thunk_igMediaFile_GetMetaObject(void) {
    igMediaFile_GetMetaObject();
}
