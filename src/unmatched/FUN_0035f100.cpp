/* 0x0035f100 — FUN_0035f100. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0035f2b0();
void FUN_0035f100(int arg0);
}

void FUN_0035f100(int arg0) {
    FUN_0035f2b0();
    igMetaObject_CreateInstance(*(int *)0x589478, arg0);
}
