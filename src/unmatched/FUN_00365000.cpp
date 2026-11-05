/* 0x00365000 — FUN_00365000. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00365120();
void FUN_00365000(int arg0);
}

void FUN_00365000(int arg0) {
    FUN_00365120();
    igMetaObject_CreateInstance(*(int *)0x589898, arg0);
}
