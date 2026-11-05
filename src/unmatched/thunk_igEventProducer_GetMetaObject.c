/* 0x001462e0 — thunk_igEventProducer_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igEventProducer_GetMetaObject();

void thunk_igEventProducer_GetMetaObject(void) {
    igEventProducer_GetMetaObject();
}
