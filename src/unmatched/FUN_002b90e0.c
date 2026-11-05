/* 0x002b90e0 — FUN_002b90e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b9200();
int igMetaObject_CreateInstance(int, int);

void FUN_002b90e0(int arg0) {
    FUN_002b9200();
    igMetaObject_CreateInstance(*(int *)0x5858D8, arg0);
}
