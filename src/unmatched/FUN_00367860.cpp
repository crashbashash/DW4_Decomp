/* 0x00367860 — FUN_00367860. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00367b20();
void FUN_00367860(int arg0);
}

void FUN_00367860(int arg0) {
    FUN_00367b20();
    igMetaObject_CreateInstance(*(int *)0x589AD8, arg0);
}
