extern "C" {
/* 0x00343760 — FUN_00343760. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_003438b0();

void FUN_00343760(int arg0) {
    FUN_003438b0();
    igMetaObject_CreateInstance(*(int *)0x587E10, arg0);
}
}
