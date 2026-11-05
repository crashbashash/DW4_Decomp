/* 0x002b3530 — FUN_002b3530. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b3548();

void FUN_002b3530(void *arg0) {
    FUN_002b3548(*(int *)((char *)(arg0) + 64));
}
