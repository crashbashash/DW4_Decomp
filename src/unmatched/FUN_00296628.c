/* 0x00296628 — FUN_00296628. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a1060();

void FUN_00296628(void *arg0) {
    FUN_002a1060(*(int *)((char *)(arg0) + 64));
}
