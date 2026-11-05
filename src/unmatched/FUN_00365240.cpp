/* 0x00365240 — FUN_00365240. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003653b0();
void FUN_00365240(int arg0);
}

void FUN_00365240(int arg0) {
    FUN_003653b0();
    igMetaObject_CreateInstance(*(int *)0x5898A8, arg0);
}
