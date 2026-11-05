/* 0x00285910 — FUN_00285910. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002855d8();
int FUN_0028b098();

void FUN_00285910(int arg0, int *arg1, int *arg2) {
    void *temp_s0;

    temp_s0 = (void *)(arg0 + 0x160);
    if (FUN_0028b098() != 0) {
        FUN_002855d8(0, 0xFF03020E);
        return;
    }
    *arg1 = *(int *)((char *)(temp_s0) + 208);
    *arg2 = *(int *)((char *)(temp_s0) + 212);
}
