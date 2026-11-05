/* 0x0036c030 — FUN_0036c030. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0036c1f0();
void FUN_0036c030(int arg0);
}

void FUN_0036c030(int arg0) {
    FUN_0036c1f0();
    igMetaObject_CreateInstance(*(int *)0x589E90, arg0);
}
