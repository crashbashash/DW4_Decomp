/* 0x0045c170 — FUN_0045c170. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_0045c330();

void FUN_0045c170(int arg0) {
    FUN_0045c330();
    igMetaObject_CreateInstance(*(int *)0x58CB88, arg0);
}
