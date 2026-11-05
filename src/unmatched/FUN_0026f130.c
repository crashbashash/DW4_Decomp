/* 0x0026f130 — FUN_0026f130. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0026f130(void *arg0) {
    if (*(int *)((char *)(arg0) + 12) == 3) {
        *(int *)((char *)(arg0) + 12) = 0;
    }
}
