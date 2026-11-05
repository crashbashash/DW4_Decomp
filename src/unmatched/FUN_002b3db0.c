/* 0x002b3db0 — FUN_002b3db0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b4498();

void FUN_002b3db0(void *arg0, void *arg1) {
    FUN_002b4498(*(int *)((char *)(arg0) + 40), *(int *)((char *)(arg1) + 76));
}
