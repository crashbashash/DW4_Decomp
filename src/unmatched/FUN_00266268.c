/* 0x00266268 — FUN_00266268. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025b9b8();
int FUN_0025bc10();

void FUN_00266268(void *arg0) {
    FUN_0025bc10(*(int *)((char *)(arg0) + 4));
    FUN_0025b9b8(*(int *)((char *)(arg0) + 4));
}
