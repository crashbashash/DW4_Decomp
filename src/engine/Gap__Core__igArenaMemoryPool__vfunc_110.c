int Gap__Core__igArenaMemoryPool__vfunc_110(void *arg0) {
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg0) + 124);
    if (temp_v1 != 0) {
        return temp_v1 + *(int *)((char *)(arg0) + 160);
    }
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2064);
}
