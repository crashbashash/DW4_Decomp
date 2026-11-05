/* 0x00352940 — FUN_00352940. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00352a10();
void FUN_00352940(int arg0);
}

void FUN_00352940(int arg0) {
    FUN_00352a10();
    igMetaObject_CreateInstance(*(int *)0x588B48, arg0);
}
