/* 0x002c9120 — thunk_igPointerListList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPointerListList_GetMetaObject();

void thunk_igPointerListList_GetMetaObject(void) {
    igPointerListList_GetMetaObject();
}
