extern "C" {
/* 0x00348170 — FUN_00348170. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00348530();

void FUN_00348170(int arg0) {
    FUN_00348530();
    igMetaObject_CreateInstance(*(int *)0x5881D8, arg0);
}
}
