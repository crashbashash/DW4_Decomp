/* 0x003c2340 — FUN_003c2340. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c2490();
void FUN_003c2340(int arg0);
}

void FUN_003c2340(int arg0) {
    FUN_003c2490();
    igMetaObject_CreateInstance(*(int *)0x58B570, arg0);
}
