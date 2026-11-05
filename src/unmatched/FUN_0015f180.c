/* 0x0015f180 — FUN_0015f180. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int Memory_FreeBuffer();

void FUN_0015f180(void *arg0) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;

    temp_a0 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 64);
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 64) = 0;
    }
    temp_a0_2 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 60);
    if (temp_a0_2 != 0) {
        Memory_FreeBuffer(temp_a0_2);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 60) = 0;
    }
    temp_a0_3 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 76);
    if (temp_a0_3 != 0) {
        Memory_FreeBuffer(temp_a0_3);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 76) = 0;
    }
}
