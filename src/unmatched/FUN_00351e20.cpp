/* 0x00351e20 — FUN_00351e20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00351ff0();
void FUN_00351e20(int arg0);
}

void FUN_00351e20(int arg0) {
    FUN_00351ff0();
    igMetaObject_CreateInstance(*(int *)0x588AA8, arg0);
}
