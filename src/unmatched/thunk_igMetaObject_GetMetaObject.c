/* 0x002be7e0 — thunk_igMetaObject_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_GetMetaObject();

void thunk_igMetaObject_GetMetaObject(void) {
    igMetaObject_GetMetaObject();
}
