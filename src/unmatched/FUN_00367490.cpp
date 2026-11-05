/* 0x00367490 — FUN_00367490. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003675b0();
void FUN_00367490(int arg0);
}

void FUN_00367490(int arg0) {
    FUN_003675b0();
    igMetaObject_CreateInstance(*(int *)0x589AB0, arg0);
}
