/* 0x0022bbd0 — FUN_0022bbd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int Gap__Core__igObject__vfunc_11();

void FUN_0022bbd0(void *arg0) {
    Gap__Core__igObject__vfunc_11();
    *(int *)((char *)(arg0) + 8) = (int)(arg0);
}
