/* 0x002c5f70 — thunk_igErrorHandler_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igErrorHandler_GetMetaObject();

void thunk_igErrorHandler_GetMetaObject(void) {
    igErrorHandler_GetMetaObject();
}
