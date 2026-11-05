/* 0x00352140 — FUN_00352140. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003522b0();
void FUN_00352140(int arg0);
}

void FUN_00352140(int arg0) {
    FUN_003522b0();
    igMetaObject_CreateInstance(*(int *)0x588AD0, arg0);
}
