/* 0x00137d20 — thunk_igFogStateAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFogStateAttr_GetMetaObject();

void thunk_igFogStateAttr_GetMetaObject(void) {
    igFogStateAttr_GetMetaObject();
}
