/* 0x0013b060 — thunk_igAttrList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAttrList_GetMetaObject();

void thunk_igAttrList_GetMetaObject(void) {
    igAttrList_GetMetaObject();
}
