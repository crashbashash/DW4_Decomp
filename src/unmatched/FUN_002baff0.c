/* 0x002baff0 — FUN_002baff0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002bb200();
int igMetaObject_CreateInstance(int, int);

void FUN_002baff0(int arg0) {
    FUN_002bb200();
    igMetaObject_CreateInstance(*(int *)0x585A08, arg0);
}
