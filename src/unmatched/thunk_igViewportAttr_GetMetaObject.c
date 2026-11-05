/* 0x00130600 — thunk_igViewportAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewportAttr_GetMetaObject();

void thunk_igViewportAttr_GetMetaObject(void) {
    igViewportAttr_GetMetaObject();
}
