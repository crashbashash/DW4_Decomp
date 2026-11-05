/* 0x00363210 — FUN_00363210. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363480();
void FUN_00363210(int arg0);
}

void FUN_00363210(int arg0) {
    FUN_00363480();
    igMetaObject_CreateInstance(*(int *)0x589790, arg0);
}
