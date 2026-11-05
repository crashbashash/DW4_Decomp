/* 0x002badd0 — thunk_igResource_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igResource_GetMetaObject();

void thunk_igResource_GetMetaObject(void) {
    igResource_GetMetaObject();
}
