/* 0x00453360 — thunk_igAction_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAction_GetMetaObject();

void thunk_igAction_GetMetaObject(void) {
    igAction_GetMetaObject();
}
