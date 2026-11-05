/* 0x001a3e60 — thunk_igCommonTraversal_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCommonTraversal_GetMetaObject();

void thunk_igCommonTraversal_GetMetaObject(void) {
    igCommonTraversal_GetMetaObject();
}
