/* 0x0025b998 — FUN_0025b998. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0025b998(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 196) = arg1;
    *(int *)((char *)(arg0) + 200) = (int)((int) (arg1 / 1536));
}
