/* 0x002bc230 — thunk_igQueue_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igQueue_GetMetaObject();

void thunk_igQueue_GetMetaObject(void) {
    igQueue_GetMetaObject();
}
