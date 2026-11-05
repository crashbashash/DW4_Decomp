/* 0x003689f0 — FUN_003689f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00368bc0();
void FUN_003689f0(int arg0);
}

void FUN_003689f0(int arg0) {
    FUN_00368bc0();
    igMetaObject_CreateInstance(*(int *)0x589B90, arg0);
}
