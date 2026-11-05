/* 0x002b0548 — FUN_002b0548. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002b0548(void *arg0, void *arg1) {
    *(long long *)((char *)(arg0) + 328) = (long long) *(long long *)((char *)(arg1) + 0);
    *(long long *)((char *)(arg0) + 336) = (long long) *(long long *)((char *)(arg1) + 8);
}
