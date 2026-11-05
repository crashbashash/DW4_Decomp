/* 0x0025b8a8 — FUN_0025b8a8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025b618();

void FUN_0025b8a8(void *arg0) {
    if (*(char *)((char *)(arg0) + 1) == 2) {
        FUN_0025b618();
    }
}
