/* 0x00457bc0 — FUN_00457bc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00457a10(int, int);

void FUN_00457bc0(void *arg0, void *arg1) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg1 + 8);
    if (temp_a1 == *(int *)0x58C280) {
        FUN_00457a10(*(int *)((char *)arg0 + 12), temp_a1);
    }
}
