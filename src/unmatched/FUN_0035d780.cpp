/* 0x0035d780 — FUN_0035d780. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0035da30();
void FUN_0035d780(int arg0);
}

void FUN_0035d780(int arg0) {
    FUN_0035da30();
    igMetaObject_CreateInstance(*(int *)0x589350, arg0);
}
