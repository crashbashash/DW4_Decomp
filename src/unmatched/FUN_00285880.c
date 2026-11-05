/* 0x00285880 — FUN_00285880. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002855d8();
int FUN_0028b098();

void FUN_00285880(int arg0, int *arg1, int *arg2, int *arg3) {
    void *temp_s0;

    temp_s0 = (void *)(arg0 + 0x160);
    if (FUN_0028b098() != 0) {
        FUN_002855d8(0, 0xFF03020F);
        return;
    }
    *arg1 = *(int *)((char *)(temp_s0) + 728) << 0xB;
    *arg2 = *(int *)((char *)(temp_s0) + 228);
    *arg3 = -1;
}
