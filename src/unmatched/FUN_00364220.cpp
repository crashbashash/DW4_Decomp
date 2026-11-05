/* 0x00364220 — FUN_00364220. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364390();
void FUN_00364220(int arg0);
}

void FUN_00364220(int arg0) {
    FUN_00364390();
    igMetaObject_CreateInstance(*(int *)0x589848, arg0);
}
