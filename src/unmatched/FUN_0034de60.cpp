/* 0x0034de60 — FUN_0034de60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0034df30();
void FUN_0034de60(int arg0);
}

void FUN_0034de60(int arg0) {
    FUN_0034df30();
    igMetaObject_CreateInstance(*(int *)0x5886B0, arg0);
}
