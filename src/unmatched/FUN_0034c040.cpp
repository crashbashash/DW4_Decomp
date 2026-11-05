/* 0x0034c040 — FUN_0034c040. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0034c230();
void FUN_0034c040(int arg0);
}

void FUN_0034c040(int arg0) {
    FUN_0034c230();
    igMetaObject_CreateInstance(*(int *)0x5884C8, arg0);
}
