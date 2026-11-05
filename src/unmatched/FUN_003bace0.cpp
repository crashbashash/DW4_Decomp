/* 0x003bace0 — FUN_003bace0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003badf0();
void FUN_003bace0(int arg0);
}

void FUN_003bace0(int arg0) {
    FUN_003badf0();
    igMetaObject_CreateInstance(*(int *)0x58AF88, arg0);
}
