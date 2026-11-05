/* 0x0013c7e0 — FUN_0013c7e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0013b820();
int FUN_001931b0();

void FUN_0013c7e0(void *arg0) {
    FUN_0013b820();
    *(int *)((char *)(arg0) + 28) = FUN_001931b0((char *)arg0 + 0xC, 1);
}
