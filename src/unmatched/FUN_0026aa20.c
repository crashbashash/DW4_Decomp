/* 0x0026aa20 — FUN_0026aa20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00270280();

void FUN_0026aa20(void *arg0, int *arg1) {
    *arg1 = FUN_00270280(*(int *)((char *)(arg0) + 8));
}
