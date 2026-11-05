/* 0x00279128 — FUN_00279128. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00265068();
int FUN_00265080();
int FUN_0026bc60();
int FUN_00278738();
int FUN_002788c8();

void FUN_00279128(void *arg0) {
    int temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(*(int *)((char *)(*(int *)((char *)(arg0) + 4)) + 4));
    temp_s0 = *(int *)((char *)(temp_s1) + 232);
    if (temp_s0 == 0) {
        return;
    }
    FUN_0026bc60();
    FUN_00265068();
    FUN_002788c8(temp_s0);
    *(int *)((char *)(temp_s1) + 232) = 0;
    FUN_00278738(0);
    FUN_00265080();
}
