/* 0x002d0550 — FUN_002d0550. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d0550(void *arg0) {
    return *(int *)((char *)(arg0) + 180);
}
