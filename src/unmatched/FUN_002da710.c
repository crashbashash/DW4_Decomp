/* 0x002da710 — FUN_002da710. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002dab80(void *, int);
int FUN_0030b3c0(int, int);

int FUN_002da710(void *arg0, int arg1, int arg2) {
    if (arg1 == 0) {
        return 0;
    }
    FUN_0030b3c0(*(int *)((char *)arg0 + 36), arg2);
    FUN_002dab80(arg0, arg1);
    return 1;
}
