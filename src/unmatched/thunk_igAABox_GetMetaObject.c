/* 0x0018a810 — thunk_igAABox_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAABox_GetMetaObject();

void thunk_igAABox_GetMetaObject(void) {
    igAABox_GetMetaObject();
}
