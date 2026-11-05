/* 0x00364d30 — FUN_00364d30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364ea0();
void FUN_00364d30(int arg0);
}

void FUN_00364d30(int arg0) {
    FUN_00364ea0();
    igMetaObject_CreateInstance(*(int *)0x589888, arg0);
}
