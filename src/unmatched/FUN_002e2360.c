int FUN_002e2360(void *arg0) {
    int i;
    for (i = 0; i < 0x10; i++) {
        if (!(*(int *)((char *)(arg0) + 80) & (3 << (i * 2)))) {
            return i;
        }
    }
    return 0;
}
