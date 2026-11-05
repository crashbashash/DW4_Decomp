/* 0x0045d640 — thunk_igViewModel_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewModel_GetMetaObject();

void thunk_igViewModel_GetMetaObject(void) {
    igViewModel_GetMetaObject();
}
