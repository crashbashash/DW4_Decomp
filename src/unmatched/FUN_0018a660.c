/* 0x0018a660 — FUN_0018a660. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0018a780();
int igMetaObject_CreateInstance(int, int);

void FUN_0018a660(int arg0) {
    FUN_0018a780();
    igMetaObject_CreateInstance(*(int *)0x5610E0, arg0);
}
