/* 0x0036dd30 — FUN_0036dd30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0036def0();
void FUN_0036dd30(int arg0);
}

void FUN_0036dd30(int arg0) {
    FUN_0036def0();
    igMetaObject_CreateInstance(*(int *)0x58A028, arg0);
}
