/* 0x00139990 — FUN_00139990. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00139ab0();
int igMetaObject_CreateInstance(int, int);

void FUN_00139990(int arg0) {
    FUN_00139ab0();
    igMetaObject_CreateInstance(*(int *)0x55F360, arg0);
}
