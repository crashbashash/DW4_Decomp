/* 0x00150600 — thunk_igFileImagePng_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFileImagePng_GetMetaObject();

void thunk_igFileImagePng_GetMetaObject(void) {
    igFileImagePng_GetMetaObject();
}
