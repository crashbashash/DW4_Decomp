int FUN_00147450(void *arg0, int arg1) {
    int i;
    int *list;

    for (i = 0; i < 0x20; i++) {
        if (arg1 == *(int *)(*(int *)((char *)(arg0) + 8) + (i * 4))) {
            return i;
        }
    }
    return -1;
}
