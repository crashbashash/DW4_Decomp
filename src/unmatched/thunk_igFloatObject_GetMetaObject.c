/* 0x001e50d0 — thunk_igFloatObject_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFloatObject_GetMetaObject();

void thunk_igFloatObject_GetMetaObject(void) {
    igFloatObject_GetMetaObject();
}
