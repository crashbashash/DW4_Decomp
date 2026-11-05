/* 0x00228aa0 — thunk_igInterfaced_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInterfaced_GetMetaObject();

void thunk_igInterfaced_GetMetaObject(void) {
    igInterfaced_GetMetaObject();
}
