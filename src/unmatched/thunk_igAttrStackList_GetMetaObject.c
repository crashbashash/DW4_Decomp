/* 0x001a5a60 — thunk_igAttrStackList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAttrStackList_GetMetaObject();

void thunk_igAttrStackList_GetMetaObject(void) {
    igAttrStackList_GetMetaObject();
}
