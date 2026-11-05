/* 0x0044e990 — FUN_0044e990. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int igActiveComponentsObserver_RunStaticInit();

void FUN_0044e990(int arg0) {
    igActiveComponentsObserver_RunStaticInit();
    igMetaObject_CreateInstance(*(int *)0x58C360, arg0);
}
