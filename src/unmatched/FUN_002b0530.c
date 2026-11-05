/* Returns the first copied value so it holds v0 and the second takes v1. */
long long FUN_002b0530(void *arg0, void *arg1) {
    long long r = *(long long *)((char *)(arg1) + 0);
    *(long long *)((char *)(arg0) + 312) = r;
    *(long long *)((char *)(arg0) + 320) = *(long long *)((char *)(arg1) + 8);
    return r;
}
