/* 0x0025dfc0 — FUN_0025dfc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026f0b8();
int FUN_0026f0e8();

void FUN_0025dfc0(void *arg0, int arg1) {
    int temp_a3;
    int temp_s0;
    void *temp_v1;

    temp_v1 = (void *)((char *)arg0 + 0x48);
    temp_s0 = *(int *)((char *)(arg0) + 8);
    temp_a3 = *(int *)((char *)(temp_v1) + 20) + (*(int *)((char *)(temp_v1) + 32) * 2);
    FUN_0026f0b8(temp_s0, *(int *)((char *)(arg0) + 72), arg1, temp_a3, temp_a3 + (*(int *)((char *)(temp_v1) + 28) * 2));
    FUN_0026f0e8(temp_s0);
}
