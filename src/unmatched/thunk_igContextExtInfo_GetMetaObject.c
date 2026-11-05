/* 0x002cb850 — thunk_igContextExtInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igContextExtInfo_GetMetaObject();

void thunk_igContextExtInfo_GetMetaObject(void) {
    igContextExtInfo_GetMetaObject();
}
