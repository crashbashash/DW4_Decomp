/* 0x0030b5c0 — FUN_0030b5c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0012a8c8(int);

void FUN_0030b5c0(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 8);
    if (temp_a0 != 0) {
        FUN_0012a8c8(temp_a0);
    }
}
