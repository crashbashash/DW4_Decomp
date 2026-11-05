/* 0x00296818 — FUN_00296818. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00299580();
int FUN_0029b1a8();

void FUN_00296818(void *arg0, int arg1) {
    FUN_0029b1a8(*(int *)((char *)(arg0) + 68));
    FUN_00299580(arg0, arg1);
}
