/* 0x00226740 — thunk_igLogInterface_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLogInterface_GetMetaObject();

void thunk_igLogInterface_GetMetaObject(void) {
    igLogInterface_GetMetaObject();
}
