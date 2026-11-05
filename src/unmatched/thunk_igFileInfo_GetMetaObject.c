/* 0x00229150 — thunk_igFileInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFileInfo_GetMetaObject();

void thunk_igFileInfo_GetMetaObject(void) {
    igFileInfo_GetMetaObject();
}
