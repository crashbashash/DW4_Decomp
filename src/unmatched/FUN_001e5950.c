/* 0x001e5950 — FUN_001e5950. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001e5ab0();
int igMetaObject_CreateInstance(int, int);

void FUN_001e5950(int arg0) {
    FUN_001e5ab0();
    igMetaObject_CreateInstance(*(int *)0x562C20, arg0);
}
