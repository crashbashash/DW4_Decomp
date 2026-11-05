/* 0x00307650 — FUN_00307650. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00307650(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8);
}
