/* 0x003bc940 — FUN_003bc940. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bca60();
void FUN_003bc940(int arg0);
}

void FUN_003bc940(int arg0) {
    FUN_003bca60();
    igMetaObject_CreateInstance(*(int *)0x58B0D0, arg0);
}
