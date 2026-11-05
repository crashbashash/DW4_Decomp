extern "C" {
/* 0x00342630 — FUN_00342630. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_003427f0();

void FUN_00342630(int arg0) {
    FUN_003427f0();
    igMetaObject_CreateInstance(*(int *)0x587CD0, arg0);
}
}
