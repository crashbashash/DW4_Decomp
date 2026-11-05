/* 0x00349270 — FUN_00349270. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00349430();
void FUN_00349270(int arg0);
}

void FUN_00349270(int arg0) {
    FUN_00349430();
    igMetaObject_CreateInstance(*(int *)0x588238, arg0);
}
