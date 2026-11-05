/* 0x0014ed60 — thunk_igCustomStateField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCustomStateField_GetMetaObject();

void thunk_igCustomStateField_GetMetaObject(void) {
    igCustomStateField_GetMetaObject();
}
