/* 0x00299580 — FUN_00299580. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00277658();

void FUN_00299580(void *arg0) {
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 76);
    if (temp_v0 != 0) {
        FUN_00277658(temp_v0);
    }
}
