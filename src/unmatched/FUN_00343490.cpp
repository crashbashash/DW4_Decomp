extern "C" {
/* 0x00343490 — FUN_00343490. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00343650();

void FUN_00343490(int arg0) {
    FUN_00343650();
    igMetaObject_CreateInstance(*(int *)0x587DF8, arg0);
}
}
