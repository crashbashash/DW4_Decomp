/* 0x0017c5e0 — FUN_0017c5e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0017c5e0(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + (arg1 * 0x88))) + 8);
}
