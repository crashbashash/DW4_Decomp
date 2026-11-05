/* 0x00240370 — FUN_00240370. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00240370(void *arg0) {
    *(int *)((char *)(arg0) + 4) = (int) *(int *)((char *)(*(int *)((char *)(arg0) + 4)) + 4);
    return arg0;
}
