/* 0x00368710 — FUN_00368710. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003688d0();
void FUN_00368710(int arg0);
}

void FUN_00368710(int arg0) {
    FUN_003688d0();
    igMetaObject_CreateInstance(*(int *)0x589B80, arg0);
}
