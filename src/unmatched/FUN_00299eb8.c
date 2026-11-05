/* 0x00299eb8 — FUN_00299eb8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002998d0();
int FUN_002999f0();
int FUN_00299a90();
int FUN_00299f68();
int FUN_00299f88();
int FUN_0029a3b8();

void FUN_00299eb8(void *arg0) {
    int temp_s0;
    void **temp_s2;

    if (FUN_00299f88() == 1) {
        FUN_00299f68();
        temp_s0 = *(int *)((char *)(arg0) + 20);
        temp_s2 = (void **)(*(int *)((char *)(arg0) + 12));
        if (temp_s0 != 0) {
            FUN_0029a3b8();
            FUN_00299a90(temp_s0);
            *(int *)((char *)(arg0) + 0) = 0;
            FUN_002999f0(temp_s0);
            ((int (*)())*(int *)((char *)((*temp_s2)) + 12))(temp_s2);
            *(int *)((char *)(arg0) + 20) = 0;
            FUN_002998d0();
        }
    }
}
