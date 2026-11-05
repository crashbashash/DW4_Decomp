/* 0x002b25a8 — FUN_002b25a8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b1980();
int FUN_002b1c20();

void FUN_002b25a8(void *arg0, int arg1) {
    int temp_s1;

    temp_s1 = *(int *)((char *)(arg0) + 4);
    if (FUN_002b1980() != 0) {
        FUN_002b1c20(temp_s1, arg1);
    }
}
