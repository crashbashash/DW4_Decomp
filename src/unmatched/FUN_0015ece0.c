/* 0x0015ece0 - FUN_0015ece0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
float FUN_0015ece0(void *arg0, int arg1) {
    int a, idx, c;
    a = *(int *)((char *)arg0 + 8);
    idx = arg1 * 4;
    c = *(int *)(a + 76);
    return *(float *)(c + idx);
}
