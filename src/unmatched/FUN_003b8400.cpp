/* 0x003b8400 — FUN_003b8400. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b8510();
void FUN_003b8400(int arg0);
}

void FUN_003b8400(int arg0) {
    FUN_003b8510();
    igMetaObject_CreateInstance(*(int *)0x58ADE8, arg0);
}
