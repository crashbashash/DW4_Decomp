/* 0x002c4540 — thunk_igFolder_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFolder_GetMetaObject();

void thunk_igFolder_GetMetaObject(void) {
    igFolder_GetMetaObject();
}
