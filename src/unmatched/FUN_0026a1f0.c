/* 0x0026a1f0 — FUN_0026a1f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025f2d0();
int FUN_0025f2e8();
int FUN_0026a178();

int FUN_0026a1f0(void *arg0, int arg1) {
    FUN_0025f2d0();
    FUN_0026a178(arg0);
    *(int *)((char *)(arg0) + 92) = arg1;
    FUN_0025f2e8();
    return 1;
}
