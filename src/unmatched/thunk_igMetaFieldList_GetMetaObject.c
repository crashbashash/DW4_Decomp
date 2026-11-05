/* 0x002c8c90 — thunk_igMetaFieldList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaFieldList_GetMetaObject();

void thunk_igMetaFieldList_GetMetaObject(void) {
    igMetaFieldList_GetMetaObject();
}
