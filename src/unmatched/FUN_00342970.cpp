extern "C" {
/* 0x00342970 — FUN_00342970. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00342b00();

void FUN_00342970(int arg0) {
    FUN_00342b00();
    igMetaObject_CreateInstance(*(int *)0x587CE8, arg0);
}
}
