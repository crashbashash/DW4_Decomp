/* 0x0014f150 — thunk_igCustomStateCollection_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCustomStateCollection_GetMetaObject();

void thunk_igCustomStateCollection_GetMetaObject(void) {
    igCustomStateCollection_GetMetaObject();
}
