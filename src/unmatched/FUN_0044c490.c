/* 0x0044c490 — FUN_0044c490. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int igRendererOrderedList_EnsureRegistered();

void FUN_0044c490(int arg0) {
    igRendererOrderedList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C200, arg0);
}
