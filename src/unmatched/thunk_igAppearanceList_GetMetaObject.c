/* 0x001a6140 — thunk_igAppearanceList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAppearanceList_GetMetaObject();

void thunk_igAppearanceList_GetMetaObject(void) {
    igAppearanceList_GetMetaObject();
}
