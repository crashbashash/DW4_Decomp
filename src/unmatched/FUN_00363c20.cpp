/* 0x00363c20 — FUN_00363c20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363d60();
void FUN_00363c20(int arg0);
}

void FUN_00363c20(int arg0) {
    FUN_00363d60();
    igMetaObject_CreateInstance(*(int *)0x5897F8, arg0);
}
