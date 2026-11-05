/* 0x00349870 — FUN_00349870. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00349a40();
void FUN_00349870(int arg0);
}

void FUN_00349870(int arg0) {
    FUN_00349a40();
    igMetaObject_CreateInstance(*(int *)0x588270, arg0);
}
