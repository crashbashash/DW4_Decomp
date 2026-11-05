/* 0x00189000 — FUN_00189000. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001890d0();
int igMetaObject_CreateInstance(int, int);

void FUN_00189000(int arg0) {
    FUN_001890d0();
    igMetaObject_CreateInstance(*(int *)0x561040, arg0);
}
