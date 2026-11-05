/* 0x0019ca20 — thunk_igNonRefCountedNodeList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNonRefCountedNodeList_GetMetaObject();

void thunk_igNonRefCountedNodeList_GetMetaObject(void) {
    igNonRefCountedNodeList_GetMetaObject();
}
