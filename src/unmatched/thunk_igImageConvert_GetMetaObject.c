/* 0x0014dc30 — thunk_igImageConvert_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igImageConvert_GetMetaObject();

void thunk_igImageConvert_GetMetaObject(void) {
    igImageConvert_GetMetaObject();
}
