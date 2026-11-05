/* 0x16a330 — FUN_0016a330. Verified byte-identical by tools/verify.py (wave3 sweep). */
int FUN_0016a330(void *arg0) {
    int temp_a1;
    unsigned int temp_a0;

    temp_a1 = *(int *)((char *)(arg0) + 896);
    temp_a0 = (unsigned int)(temp_a1 & 0x80000000) >> 7;
    return (temp_a1 & 0xFFFFFF) | (temp_a0 + (((temp_a1 & 0xFF000000) - temp_a0) * 2));
}
