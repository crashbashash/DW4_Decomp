/* 0x0016fd40 — thunk_memcpy. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memcpy();

void thunk_memcpy(void) {
    memcpy();
}
