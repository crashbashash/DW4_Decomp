int FUN_001b40f0(void *arg0, int arg1) {
    if (arg1 >= 8) {
        return 0;
    }
    return *(unsigned char *)((char *)(arg0) + 64) & (1 << arg1) & 0xFF;
}
