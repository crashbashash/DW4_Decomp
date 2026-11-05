/* 0x00351780 — FUN_00351780. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00351910();
void FUN_00351780(int arg0);
}

void FUN_00351780(int arg0) {
    FUN_00351910();
    igMetaObject_CreateInstance(*(int *)0x588A58, arg0);
}
