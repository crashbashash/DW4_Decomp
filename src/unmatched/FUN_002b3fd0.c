void FUN_002b3fd0(void *arg0, int arg1, int arg2) {
    *(int *)((char *)(arg0) + 8) = (int)((int) (*(int *)((char *)(arg0) + 8) - arg1));
    *(int *)((char *)(arg0) + 0) = (int)((int) (*(int *)((char *)(arg0) + 0) + (arg1 * *(int *)((char *)(arg0) + 4)) + arg2));
}
