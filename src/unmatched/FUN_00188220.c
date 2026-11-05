/* 0x00188220 — FUN_00188220. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00188340();
int igMetaObject_CreateInstance(int, int);

void FUN_00188220(int arg0) {
    FUN_00188340();
    igMetaObject_CreateInstance(*(int *)0x560FC0, arg0);
}
