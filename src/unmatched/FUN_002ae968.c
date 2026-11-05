/* 0x002ae968 — FUN_002ae968. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ae968(int arg0, int *arg1, int *arg2) {
    void *temp_a0;

    temp_a0 = (void *)(arg0 + 0xD28);
    *arg1 = *(int *)((char *)(temp_a0) + 652);
    *arg2 = *(int *)((char *)(temp_a0) + 656);
    return 0;
}
