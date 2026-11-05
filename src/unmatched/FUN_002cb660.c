/* 0x002cb660 — FUN_002cb660. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002cb7c0();
int igMetaObject_CreateInstance(int, int);

void FUN_002cb660(int arg0) {
    FUN_002cb7c0();
    igMetaObject_CreateInstance(*(int *)0x5868C8, arg0);
}
