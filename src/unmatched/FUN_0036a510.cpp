/* 0x0036a510 — FUN_0036a510. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0036a630();
void FUN_0036a510(int arg0);
}

void FUN_0036a510(int arg0) {
    FUN_0036a630();
    igMetaObject_CreateInstance(*(int *)0x589D78, arg0);
}
