/* 0x002b94f0 — thunk_igStringObjList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStringObjList_GetMetaObject();

void thunk_igStringObjList_GetMetaObject(void) {
    igStringObjList_GetMetaObject();
}
