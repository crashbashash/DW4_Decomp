/* 0x003660d0 — FUN_003660d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00366290();
void FUN_003660d0(int arg0);
}

void FUN_003660d0(int arg0) {
    FUN_00366290();
    igMetaObject_CreateInstance(*(int *)0x589958, arg0);
}
