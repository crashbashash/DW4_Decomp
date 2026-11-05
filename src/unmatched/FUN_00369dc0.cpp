/* 0x00369dc0 — FUN_00369dc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00369f80();
void FUN_00369dc0(int arg0);
}

void FUN_00369dc0(int arg0) {
    FUN_00369f80();
    igMetaObject_CreateInstance(*(int *)0x589D10, arg0);
}
