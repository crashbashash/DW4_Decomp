/* 0x00299528 — FUN_00299528. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00277528();

void FUN_00299528(void *arg0) {
    FUN_00277528(*(int *)((char *)(arg0) + 76));
}
