/* 0x001a9320 — thunk_igAnimation_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAnimation_GetMetaObject();

void thunk_igAnimation_GetMetaObject(void) {
    igAnimation_GetMetaObject();
}
