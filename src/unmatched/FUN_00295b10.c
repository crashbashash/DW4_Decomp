/* 0x00295b10 — FUN_00295b10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029b390();
int FUN_002ac498();

void FUN_00295b10(void *arg0) {
    int temp_s0;
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 68);
    temp_s0 = *(int *)((char *)(arg0) + 64);
    if ((temp_v0 != 0) && (FUN_0029b390(temp_v0) == 3)) {
        FUN_002ac498(temp_s0);
    }
}
