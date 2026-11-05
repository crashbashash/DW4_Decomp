/* 0x002265c0 — thunk_igMessageBase_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMessageBase_GetMetaObject();

void thunk_igMessageBase_GetMetaObject(void) {
    igMessageBase_GetMetaObject();
}
