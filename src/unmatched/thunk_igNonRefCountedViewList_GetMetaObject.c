/* 0x0044b9e0 — thunk_igNonRefCountedViewList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNonRefCountedViewList_GetMetaObject();

void thunk_igNonRefCountedViewList_GetMetaObject(void) {
    igNonRefCountedViewList_GetMetaObject();
}
