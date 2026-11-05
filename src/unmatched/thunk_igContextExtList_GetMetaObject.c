/* 0x002cb4a0 — thunk_igContextExtList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igContextExtList_GetMetaObject();

void thunk_igContextExtList_GetMetaObject(void) {
    igContextExtList_GetMetaObject();
}
