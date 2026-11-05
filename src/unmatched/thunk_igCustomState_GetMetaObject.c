/* 0x0014f2b0 — thunk_igCustomState_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCustomState_GetMetaObject();

void thunk_igCustomState_GetMetaObject(void) {
    igCustomState_GetMetaObject();
}
