/* 0x0044f0b0 — FUN_0044f0b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int igWindowSizeObserver_RunStaticInit();

void FUN_0044f0b0(int arg0) {
    igWindowSizeObserver_RunStaticInit();
    igMetaObject_CreateInstance(*(int *)0x58C3C0, arg0);
}
