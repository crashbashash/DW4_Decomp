/* 0x002338b0 — thunk_igInfoManagerList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInfoManagerList_GetMetaObject();

void thunk_igInfoManagerList_GetMetaObject(void) {
    igInfoManagerList_GetMetaObject();
}
