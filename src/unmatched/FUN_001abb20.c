/* 0x001abb20 - FUN_001abb20. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int FUN_001abb20(void *arg0) {
    return (*(unsigned char *)((char *)(arg0) + 72) & 8) ? *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 8) : 0;
}
