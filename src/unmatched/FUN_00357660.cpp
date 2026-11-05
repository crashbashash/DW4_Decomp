/* 0x00357660 — FUN_00357660. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00357820();
void FUN_00357660(int arg0);
}

void FUN_00357660(int arg0) {
    FUN_00357820();
    igMetaObject_CreateInstance(*(int *)0x588F30, arg0);
}
