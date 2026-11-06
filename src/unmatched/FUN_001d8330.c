int FUN_001d8330(void *arg0, unsigned int arg1) {
    return ((1 << (arg1 & 0x1F)) & *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 52)) + 16) + ((arg1 >> 5) * 4))) != 0;
}
