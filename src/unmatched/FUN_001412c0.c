/* 0x001412c0 — FUN_001412c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int Gap__Core__igObject__vfunc_09();

void FUN_001412c0(void *arg0) {
    Gap__Core__igObject__vfunc_09();
    *(int *)((char *)arg0 + 20) = 3;
    *(int *)((char *)arg0 + 24) = 0;
    *(int *)((char *)arg0 + 28) = 2;
    *(int *)((char *)arg0 + 36) = 2;
}
