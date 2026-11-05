/* 0x002c5120 — thunk_igExternalInfoEntry_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igExternalInfoEntry_GetMetaObject();

void thunk_igExternalInfoEntry_GetMetaObject(void) {
    igExternalInfoEntry_GetMetaObject();
}
