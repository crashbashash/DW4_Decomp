/* 0x0034fd00 — FUN_0034fd00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0034fe80();
void FUN_0034fd00(int arg0);
}

void FUN_0034fd00(int arg0) {
    FUN_0034fe80();
    igMetaObject_CreateInstance(*(int *)0x588860, arg0);
}
