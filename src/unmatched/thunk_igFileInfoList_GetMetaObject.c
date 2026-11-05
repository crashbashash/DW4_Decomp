/* 0x00228e50 — thunk_igFileInfoList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFileInfoList_GetMetaObject();

void thunk_igFileInfoList_GetMetaObject(void) {
    igFileInfoList_GetMetaObject();
}
