/* 0x0013aea0 — thunk_igNonRefCountedAttrList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNonRefCountedAttrList_GetMetaObject();

void thunk_igNonRefCountedAttrList_GetMetaObject(void) {
    igNonRefCountedAttrList_GetMetaObject();
}
