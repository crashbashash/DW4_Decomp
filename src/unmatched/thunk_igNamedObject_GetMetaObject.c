/* 0x002be450 — thunk_igNamedObject_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNamedObject_GetMetaObject();

void thunk_igNamedObject_GetMetaObject(void) {
    igNamedObject_GetMetaObject();
}
