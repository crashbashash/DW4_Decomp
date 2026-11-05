/* 0x001a2e20 — thunk_igBlendListRecord_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBlendListRecord_GetMetaObject();

void thunk_igBlendListRecord_GetMetaObject(void) {
    igBlendListRecord_GetMetaObject();
}
