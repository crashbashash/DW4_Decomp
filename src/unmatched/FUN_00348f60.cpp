extern "C" {
/* 0x00348f60 — FUN_00348f60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00349100();

void FUN_00348f60(int arg0) {
    FUN_00349100();
    igMetaObject_CreateInstance(*(int *)0x588220, arg0);
}
}
