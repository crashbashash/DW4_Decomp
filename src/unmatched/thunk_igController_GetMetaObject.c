/* 0x00146980 — thunk_igController_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igController_GetMetaObject();

void thunk_igController_GetMetaObject(void) {
    igController_GetMetaObject();
}
