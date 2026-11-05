/* 0x002bec30 — thunk_igMetaFieldInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaFieldInfo_GetMetaObject();

void thunk_igMetaFieldInfo_GetMetaObject(void) {
    igMetaFieldInfo_GetMetaObject();
}
