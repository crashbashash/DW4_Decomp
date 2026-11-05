/* 0x0026f0e8 — FUN_0026f0e8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0026f0e8(void *arg0) {
    if (*(int *)((char *)(arg0) + 12) == 0) {
        *(int *)((char *)(arg0) + 16) = 0;
        *(int *)((char *)(arg0) + 12) = 1;
    }
}
