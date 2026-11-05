extern "C" {
/* 0x00332490 — FUN_00332490. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026bd20(int);

int FUN_00332490(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 44);
    if (temp_a0 == 0) {
        return -1;
    }
    return FUN_0026bd20(temp_a0);
}
}
