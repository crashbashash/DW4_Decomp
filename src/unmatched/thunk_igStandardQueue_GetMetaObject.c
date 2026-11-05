/* 0x002bc2f0 — thunk_igStandardQueue_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStandardQueue_GetMetaObject();

void thunk_igStandardQueue_GetMetaObject(void) {
    igStandardQueue_GetMetaObject();
}
