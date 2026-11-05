/* 0x0014f890 — thunk_igDisableExt_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDisableExt_GetMetaObject();

void thunk_igDisableExt_GetMetaObject(void) {
    igDisableExt_GetMetaObject();
}
