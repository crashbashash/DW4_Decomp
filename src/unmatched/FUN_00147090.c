/* 0x00147090 — FUN_00147090. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001471b0();
int igMetaObject_CreateInstance(int, int);

void FUN_00147090(int arg0) {
    FUN_001471b0();
    igMetaObject_CreateInstance(*(int *)0x55F760, arg0);
}
