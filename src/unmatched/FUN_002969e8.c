/* 0x002969e8 — FUN_002969e8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ad950();

void FUN_002969e8(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg0) + 64);
    if (arg1 == 0) {
        FUN_002ad950(temp_a0, 0xF, 0);
        return;
    }
    if (*(int *)((char *)(arg0) + 12) == 1) {
        FUN_002ad950(temp_a0, 0xF, 2);
        return;
    }
    FUN_002ad950(temp_a0, 0xF, 1);
}
