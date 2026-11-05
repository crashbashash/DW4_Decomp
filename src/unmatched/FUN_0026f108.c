/* 0x0026f108 — FUN_0026f108. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();

void FUN_0026f108(void *arg0) {
    *(int *)((char *)(arg0) + 12) = 0;
    memset((char *)arg0 + 0x28, 0, 8);
}
