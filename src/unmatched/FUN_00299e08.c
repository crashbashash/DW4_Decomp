/* 0x00299e08 — FUN_00299e08. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00299a90();
int FUN_00299f68();
int FUN_00299f88();
int FUN_002a0f98();

void FUN_00299e08(void *arg0) {
    int temp_s0_2;
    int temp_s2;
    int temp_s3;
    void **temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((char *)arg0 + 0x294);
    temp_s3 = *(int *)((char *)(arg0) + 64);
    FUN_00299f68();
    temp_s2 = *(int *)((char *)(temp_s0) + 20);
    temp_s1 = (void **)(*(int *)((char *)(temp_s0) + 12));
    temp_s0_2 = *(int *)((char *)(temp_s0) + 16);
    if (FUN_00299f88(temp_s0) != 1) {
        return;
    }
    if (temp_s2 != 0) {
        FUN_00299a90(temp_s2);
    }
    ((int (*)())*(int *)((char *)((*temp_s1)) + 20))(temp_s1);
    FUN_002a0f98(temp_s3, temp_s0_2 + 0xC0, temp_s1, 0, 0);
}
