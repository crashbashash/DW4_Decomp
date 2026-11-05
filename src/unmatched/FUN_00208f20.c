/* 0x00208f20 — FUN_00208f20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00208f20(int arg0) {
    int temp_a3;

    temp_a3 = *(int *)0x569330 * 2;
    *(int *)0x56B028 = (int) (*(int *)0x56B028 & ~(3 << temp_a3));
    *(int *)0x56B028 = (int) (*(int *)0x56B028 | ((arg0 & 3) << temp_a3));
}
