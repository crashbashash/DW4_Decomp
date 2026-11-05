/* 0x00109178 — FUN_00109178. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00109178(void *arg0) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 64));
    temp_v0 = (void *)(*(int *)((char *)(temp_v1) + 464));
    if (temp_v0 != 0) {
        *(int *)((char *)(temp_v0) + 40) = 0;
    }
    temp_v0_2 = (void *)(*(int *)((char *)(temp_v1) + 480));
    if (temp_v0_2 != 0) {
        *(int *)((char *)(temp_v0_2) + 40) = 0;
    }
    temp_v0_3 = (void *)(*(int *)((char *)(temp_v1) + 496));
    if (temp_v0_3 != 0) {
        *(int *)((char *)(temp_v0_3) + 40) = 0;
    }
    temp_v0_4 = (void *)(*(int *)((char *)(temp_v1) + 468));
    if (temp_v0_4 != 0) {
        *(int *)((char *)(temp_v0_4) + 40) = 0;
    }
    temp_v0_5 = (void *)(*(int *)((char *)(temp_v1) + 484));
    if (temp_v0_5 != 0) {
        *(int *)((char *)(temp_v0_5) + 40) = 0;
    }
    temp_v0_6 = (void *)(*(int *)((char *)(temp_v1) + 500));
    if (temp_v0_6 != 0) {
        *(int *)((char *)(temp_v0_6) + 40) = 0;
    }
    return 1;
}
