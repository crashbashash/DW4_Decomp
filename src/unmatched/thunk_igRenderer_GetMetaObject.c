/* 0x0044c7e0 — thunk_igRenderer_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRenderer_GetMetaObject();

void thunk_igRenderer_GetMetaObject(void) {
    igRenderer_GetMetaObject();
}
