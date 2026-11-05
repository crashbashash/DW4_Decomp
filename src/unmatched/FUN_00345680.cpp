extern "C" {
/* 0x00345680 — FUN_00345680. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00345830();

void FUN_00345680(int arg0) {
    FUN_00345830();
    igMetaObject_CreateInstance(*(int *)0x587F60, arg0);
}
}
