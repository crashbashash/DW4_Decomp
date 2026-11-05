/* 0x001c47a0 — FUN_001c47a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001904f0();

void FUN_001c47a0(void *arg0, int arg1, int arg2) {
    FUN_001904f0((char *)arg0 + 0x1DC);
    *(int *)((char *)(arg0) + 540) = arg1;
    *(int *)((char *)(arg0) + 544) = arg2;
}
