/* 0x002bc650 — thunk_igPluginHelper_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPluginHelper_GetMetaObject();

void thunk_igPluginHelper_GetMetaObject(void) {
    igPluginHelper_GetMetaObject();
}
