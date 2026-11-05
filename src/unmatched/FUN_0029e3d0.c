/* 0x0029e3d0 — FUN_0029e3d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0029e3d0(int arg0, int arg1, int arg2) {
    int temp_v0;
    void *temp_a0;

    temp_a0 = (void *)(arg0 + (arg1 * 0x74) + 0x1318);
    temp_v0 = *(int *)((char *)(temp_a0) + 36);
    if (temp_v0 >= 0) {
        *(int *)((char *)(temp_a0) + 36) = (int)((int) (temp_v0 + arg2));
    }
}
