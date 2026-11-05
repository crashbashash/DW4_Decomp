/* 0x00298420 — FUN_00298420. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00298468();
int FUN_00298618();

void FUN_00298420(void *arg0) {
    if (*(int *)((char *)(arg0) + 400) == 0) {
        return;
    }
    FUN_00298468();
    FUN_00298618(arg0);
}
