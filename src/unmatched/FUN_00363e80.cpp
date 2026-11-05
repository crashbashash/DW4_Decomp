/* 0x00363e80 — FUN_00363e80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363fa0();
void FUN_00363e80(int arg0);
}

void FUN_00363e80(int arg0) {
    FUN_00363fa0();
    igMetaObject_CreateInstance(*(int *)0x589838, arg0);
}
