/* 0x00187890 — FUN_00187890. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001879b0();
int igMetaObject_CreateInstance(int, int);

void FUN_00187890(int arg0) {
    FUN_001879b0();
    igMetaObject_CreateInstance(*(int *)0x560F70, arg0);
}
