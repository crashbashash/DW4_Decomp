/* 0x001a4ef0 — thunk_igBitMask_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBitMask_GetMetaObject();

void thunk_igBitMask_GetMetaObject(void) {
    igBitMask_GetMetaObject();
}
