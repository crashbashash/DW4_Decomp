/* 0x00170b20 — FUN_00170b20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00170b20(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 1336)) + 16) + (arg1 * 0xA0))) + 152);
}
