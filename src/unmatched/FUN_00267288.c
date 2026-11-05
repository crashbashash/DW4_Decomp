/* 0x00267288 — FUN_00267288. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025db20();

void FUN_00267288(void *arg0) {
    FUN_0025db20(*(int *)((char *)(arg0) + 4));
}
