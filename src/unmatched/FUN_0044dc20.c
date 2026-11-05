/* 0x0044dc20 — FUN_0044dc20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int igHotKeyBinding_RunStaticInit();

void FUN_0044dc20(int arg0) {
    igHotKeyBinding_RunStaticInit();
    igMetaObject_CreateInstance(*(int *)0x58C2C0, arg0);
}
