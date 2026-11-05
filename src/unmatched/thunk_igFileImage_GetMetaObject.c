/* 0x0014df60 — thunk_igFileImage_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFileImage_GetMetaObject();

void thunk_igFileImage_GetMetaObject(void) {
    igFileImage_GetMetaObject();
}
