/* 0x001e5d60 — thunk_igBoolObject_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBoolObject_GetMetaObject();

void thunk_igBoolObject_GetMetaObject(void) {
    igBoolObject_GetMetaObject();
}
