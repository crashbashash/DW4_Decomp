/* 0x004524d0 — thunk_igBoxComponent_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBoxComponent_GetMetaObject();

void thunk_igBoxComponent_GetMetaObject(void) {
    igBoxComponent_GetMetaObject();
}
