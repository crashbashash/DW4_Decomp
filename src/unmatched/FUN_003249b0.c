/* 0x003249b0 — FUN_003249b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_003249b0(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 120) = arg1;
}
