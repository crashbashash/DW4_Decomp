/* 0x00233c00 — thunk_igFlushRenderer_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFlushRenderer_GetMetaObject();

void thunk_igFlushRenderer_GetMetaObject(void) {
    igFlushRenderer_GetMetaObject();
}
