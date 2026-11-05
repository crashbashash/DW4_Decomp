/* 0x001aaae0 — thunk_igActor_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igActor_GetMetaObject();

void thunk_igActor_GetMetaObject(void) {
    igActor_GetMetaObject();
}
