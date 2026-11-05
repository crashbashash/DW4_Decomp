/* 0x00303700 — FUN_00303700. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObject_ResetFields(int);

void FUN_00303700(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)(arg1 + *(int *)((char *)arg0 + 8));
    if (temp_a0 != 0) {
        igObject_ResetFields(temp_a0);
    }
}
