/* 0x001a5f20 — thunk_igAttrSet_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAttrSet_GetMetaObject();

void thunk_igAttrSet_GetMetaObject(void) {
    igAttrSet_GetMetaObject();
}
