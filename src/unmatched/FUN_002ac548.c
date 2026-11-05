/* 0x002ac548 — FUN_002ac548. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002b0338();
extern int (*DAT_004beb24)(void *, int);

int FUN_002ac548(void *arg0, int *arg1) {
    int temp_s2;
    int temp_v0;

    *arg1 = 0;
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000136, 0xB, arg1, 0);
    }
    temp_s2 = FUN_002b0338(arg0, 6, 0xB, arg1, 0);
    temp_v0 = *arg1;
    if (temp_v0 != 0) {
        *(int *)((char *)(arg0) + 2408) = 1;
    }
    if (DAT_004beb24 != 0) {
        DAT_004beb24(arg0, temp_v0);
    }
    return temp_s2;
}
