/* 0x002bb700 — thunk_igRegistryValue_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRegistryValue_GetMetaObject();

void thunk_igRegistryValue_GetMetaObject(void) {
    igRegistryValue_GetMetaObject();
}
