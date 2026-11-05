/* 0x002cc9f0 — thunk_igCallStackTable_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCallStackTable_GetMetaObject();

void thunk_igCallStackTable_GetMetaObject(void) {
    igCallStackTable_GetMetaObject();
}
