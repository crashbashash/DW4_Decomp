/* 0x002b3660 — FUN_002b3660. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00284dc8();

void FUN_002b3660(void *arg0) {
    FUN_00284dc8(*(int *)((char *)(arg0) + 64));
}
