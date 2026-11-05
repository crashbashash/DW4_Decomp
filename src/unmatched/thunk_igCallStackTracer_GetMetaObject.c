/* 0x002cc790 — thunk_igCallStackTracer_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCallStackTracer_GetMetaObject();

void thunk_igCallStackTracer_GetMetaObject(void) {
    igCallStackTracer_GetMetaObject();
}
