/* 0x0014d910 — thunk_igIndexArray_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIndexArray_GetMetaObject();

void thunk_igIndexArray_GetMetaObject(void) {
    igIndexArray_GetMetaObject();
}
