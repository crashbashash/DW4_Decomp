/* 0x002b96a0 — thunk_igStringObj_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStringObj_GetMetaObject();

void thunk_igStringObj_GetMetaObject(void) {
    igStringObj_GetMetaObject();
}
