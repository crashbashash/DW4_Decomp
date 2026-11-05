/* 0x002b0560 — FUN_002b0560. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002b0560(void *arg0, void *arg1) {
    *(long long *)((char *)(arg0) + 344) = (long long) *(long long *)((char *)(arg1) + 0);
    *(long long *)((char *)(arg0) + 352) = (long long) *(long long *)((char *)(arg1) + 8);
}
