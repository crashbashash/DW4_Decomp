/* 0x002b8850 — thunk_igSymbolTable_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igSymbolTable_GetMetaObject();

void thunk_igSymbolTable_GetMetaObject(void) {
    igSymbolTable_GetMetaObject();
}
