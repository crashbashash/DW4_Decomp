/* 0x00366910 — FUN_00366910. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00366b20();
void FUN_00366910(int arg0);
}

void FUN_00366910(int arg0) {
    FUN_00366b20();
    igMetaObject_CreateInstance(*(int *)0x5899C8, arg0);
}
