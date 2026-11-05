int FUN_00140c00(void *arg0, int arg1) {
    if (arg1 == 0) {
        return *(int *)((char *)(arg0) + 48);
    }
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 64)) + 16) + (arg1 * 4))) - 4);
}
