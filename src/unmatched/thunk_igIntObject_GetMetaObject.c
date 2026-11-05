/* 0x001e4f40 — thunk_igIntObject_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIntObject_GetMetaObject();

void thunk_igIntObject_GetMetaObject(void) {
    igIntObject_GetMetaObject();
}
