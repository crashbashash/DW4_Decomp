/* 0x001a1200 — thunk_igFrustCullTraversal_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFrustCullTraversal_GetMetaObject();

void thunk_igFrustCullTraversal_GetMetaObject(void) {
    igFrustCullTraversal_GetMetaObject();
}
