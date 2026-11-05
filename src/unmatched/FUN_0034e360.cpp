/* 0x0034e360 — FUN_0034e360. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0034e520();
void FUN_0034e360(int arg0);
}

void FUN_0034e360(int arg0) {
    FUN_0034e520();
    igMetaObject_CreateInstance(*(int *)0x5886E0, arg0);
}
