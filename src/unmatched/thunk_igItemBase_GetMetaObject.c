/* 0x002289c0 — thunk_igItemBase_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igItemBase_GetMetaObject();

void thunk_igItemBase_GetMetaObject(void) {
    igItemBase_GetMetaObject();
}
