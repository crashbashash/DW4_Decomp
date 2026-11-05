/* 0x002998d0 — FUN_002998d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00299f58();
void *FUN_00299f68();

void FUN_002998d0(void) {
    int (*temp_v0_3)(void *);
    int temp_v0_2;
    int temp_v1;
    void *temp_s0;
    void *temp_v0;

    temp_s0 = (void *)(FUN_00299f58());
    temp_v0 = (void *)(FUN_00299f68());
    if (temp_v0 != 0) {
        temp_v0_2 = *(int *)((char *)(temp_s0) + 4);
        temp_v1 = temp_v0_2 - 1;
        if (temp_v0_2 != 0) {
            *(int *)((char *)(temp_s0) + 4) = temp_v1;
            if (temp_v1 == 0) {
                temp_v0_3 = (int (*)(void *))(*(int *)((char *)(temp_v0) + 4));
                if (temp_v0_3 != 0) {
                    temp_v0_3(temp_v0);
                }
            }
        }
    }
}
