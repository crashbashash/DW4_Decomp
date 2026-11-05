/* 0x002adf78 — FUN_002adf78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();
int FUN_002a0dd8();

int FUN_002adf78(void *arg0, void **arg1, int *arg2) {
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF00011C);
    }
    if (*(int *)((char *)(arg0) + 120) != 0) {
        *arg1 = (char *)arg0 + 0x10C;
        *arg2 = *(int *)((char *)(arg0) + 264);
    } else {
        *arg1 = 0;
        *arg2 = 0;
    }
    return 0;
}
