/* 0x001a5c20 — thunk_igAttrStack_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAttrStack_GetMetaObject();

void thunk_igAttrStack_GetMetaObject(void) {
    igAttrStack_GetMetaObject();
}
