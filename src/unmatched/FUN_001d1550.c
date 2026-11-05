/* 0x001d1550 — FUN_001d1550. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001d0c90(void *);
int FUN_001d1a80(int, void *, int);

void FUN_001d1550(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 68);
    if (temp_a0 != 0) {
        FUN_001d1a80(temp_a0, arg0, arg1);
    }
    if (*(int *)((char *)arg0 + 64) != 0) {
        FUN_001d0c90(arg0);
    }
}
