/* 0x0018a060 — FUN_0018a060. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0018a180();
int igMetaObject_CreateInstance(int, int);

void FUN_0018a060(int arg0) {
    FUN_0018a180();
    igMetaObject_CreateInstance(*(int *)0x5610B8, arg0);
}
