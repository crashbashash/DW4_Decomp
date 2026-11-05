/* 0x002c35a0 — thunk_igInfoList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInfoList_GetMetaObject();

void thunk_igInfoList_GetMetaObject(void) {
    igInfoList_GetMetaObject();
}
