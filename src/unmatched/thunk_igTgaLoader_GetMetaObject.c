/* 0x00150290 — thunk_igTgaLoader_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTgaLoader_GetMetaObject();

void thunk_igTgaLoader_GetMetaObject(void) {
    igTgaLoader_GetMetaObject();
}
