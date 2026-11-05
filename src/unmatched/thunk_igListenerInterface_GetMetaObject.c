/* 0x00226ec0 — thunk_igListenerInterface_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igListenerInterface_GetMetaObject();

void thunk_igListenerInterface_GetMetaObject(void) {
    igListenerInterface_GetMetaObject();
}
