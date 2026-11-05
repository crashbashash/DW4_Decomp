/* 0x00267240 — FUN_00267240. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025dab0();

void FUN_00267240(void *arg0) {
    FUN_0025dab0(*(int *)((char *)(arg0) + 4));
}
