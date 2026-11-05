/* 0x002c0690 — FUN_002c0690. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c0890();
int igMetaObject_CreateInstance(int, int);

void FUN_002c0690(int arg0) {
    FUN_002c0890();
    igMetaObject_CreateInstance(*(int *)0x585F18, arg0);
}
