/* 0x0026d158 — FUN_0026d158. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002670f0();

void FUN_0026d158(void *arg0, char arg1) {
    int temp_v0;

    *(char *)((char *)(arg0) + 152) = arg1;
    temp_v0 = *(int *)((char *)(arg0) + 4);
    if (temp_v0 != 0) {
        FUN_002670f0(temp_v0);
    }
}
