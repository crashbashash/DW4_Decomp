/* 0x002b80a0 — thunk_igThread_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igThread_GetMetaObject();

void thunk_igThread_GetMetaObject(void) {
    igThread_GetMetaObject();
}
