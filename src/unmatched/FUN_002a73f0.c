/* 0x002a73f0 — FUN_002a73f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memcpy();

void FUN_002a73f0(void *arg0, void *arg1) {
    memcpy(*(int *)((char *)(arg0) + 0), *(int *)((char *)(arg1) + 0), *(int *)((char *)(arg1) + 4));
    *(int *)((char *)(arg0) + 4) = (int)((int) *(int *)((char *)(arg1) + 4));
}
