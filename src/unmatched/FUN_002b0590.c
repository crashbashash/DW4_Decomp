/* 0x002b0590 — FUN_002b0590. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002b0590(void *arg0, int arg1) {
    if (arg1 > 0) {
        *(int *)((char *)(arg0) + 16) = arg1;
    }
}
