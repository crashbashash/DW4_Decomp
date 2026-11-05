/* 0x00137eb0 — thunk_igFogAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFogAttr_GetMetaObject();

void thunk_igFogAttr_GetMetaObject(void) {
    igFogAttr_GetMetaObject();
}
