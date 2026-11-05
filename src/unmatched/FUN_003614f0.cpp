/* 0x003614f0 — FUN_003614f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00361610();
void FUN_003614f0(int arg0);
}

void FUN_003614f0(int arg0) {
    FUN_00361610();
    igMetaObject_CreateInstance(*(int *)0x589640, arg0);
}
