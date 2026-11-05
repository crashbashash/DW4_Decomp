extern "C" {
/* 0x00342310 — FUN_00342310. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_003424e0();

void FUN_00342310(int arg0) {
    FUN_003424e0();
    igMetaObject_CreateInstance(*(int *)0x587CB8, arg0);
}
}
