/* 0x002bf220 — thunk_igMetaEnum_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_GetMetaObject();

void thunk_igMetaEnum_GetMetaObject(void) {
    igMetaEnum_GetMetaObject();
}
