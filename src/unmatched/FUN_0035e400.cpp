/* 0x0035e400 — FUN_0035e400. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0035e520();
void FUN_0035e400(int arg0);
}

void FUN_0035e400(int arg0) {
    FUN_0035e520();
    igMetaObject_CreateInstance(*(int *)0x5893E8, arg0);
}
