/* 0x002ae248 — FUN_002ae248. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ae290();

void FUN_002ae248(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 0) = 0;
    FUN_002ae290((char *)arg0 + 4);
    *(int *)((char *)(arg0) + 36) = arg1;
    *(int *)((char *)(arg0) + 40) = 1;
}
