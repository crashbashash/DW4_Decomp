/* 0x0034f8e0 — FUN_0034f8e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0034fa30();
void FUN_0034f8e0(int arg0);
}

void FUN_0034f8e0(int arg0) {
    FUN_0034fa30();
    igMetaObject_CreateInstance(*(int *)0x588800, arg0);
}
