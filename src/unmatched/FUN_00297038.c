/* 0x00297038 — FUN_00297038. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ad950();

void FUN_00297038(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg0) + 64);
    if (arg1 == 1) {
        FUN_002ad950(temp_a0, 0x27, 1);
        return;
    }
    FUN_002ad950(temp_a0, 0x27, 0);
}
