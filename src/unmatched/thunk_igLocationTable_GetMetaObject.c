/* 0x002c2180 — thunk_igLocationTable_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLocationTable_GetMetaObject();

void thunk_igLocationTable_GetMetaObject(void) {
    igLocationTable_GetMetaObject();
}
