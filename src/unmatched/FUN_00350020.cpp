/* 0x00350020 — FUN_00350020. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00350fb0();
void FUN_00350020(int arg0);
}

void FUN_00350020(int arg0) {
    FUN_00350fb0();
    igMetaObject_CreateInstance(*(int *)0x588888, arg0);
}
