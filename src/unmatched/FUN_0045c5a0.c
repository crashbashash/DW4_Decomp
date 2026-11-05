/* 0x0045c5a0 — FUN_0045c5a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_0045c680();

void FUN_0045c5a0(int arg0) {
    FUN_0045c680();
    igMetaObject_CreateInstance(*(int *)0x58CBF8, arg0);
}
