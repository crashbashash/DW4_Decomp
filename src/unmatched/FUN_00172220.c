/* 0x00172220 — FUN_00172220. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00172220(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 1344)) + 84);
}
