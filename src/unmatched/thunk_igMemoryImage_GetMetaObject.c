/* 0x0014de80 — thunk_igMemoryImage_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryImage_GetMetaObject();

void thunk_igMemoryImage_GetMetaObject(void) {
    igMemoryImage_GetMetaObject();
}
