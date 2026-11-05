/* 0x0044c020 — thunk_igTextElement_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTextElement_GetMetaObject();

void thunk_igTextElement_GetMetaObject(void) {
    igTextElement_GetMetaObject();
}
