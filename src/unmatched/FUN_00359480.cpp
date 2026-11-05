/* 0x00359480 — FUN_00359480. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00359640();
void FUN_00359480(int arg0);
}

void FUN_00359480(int arg0) {
    FUN_00359640();
    igMetaObject_CreateInstance(*(int *)0x5890C0, arg0);
}
