/* 0x0016a7c0 — FUN_0016a7c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0016a7c0(void *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = *(int *)((char *)(arg0) + 1236);
    *arg2 = *(int *)((char *)(arg0) + 1240);
    *arg3 = *(int *)((char *)(arg0) + 1244);
    *arg4 = *(int *)((char *)(arg0) + 1248);
}
