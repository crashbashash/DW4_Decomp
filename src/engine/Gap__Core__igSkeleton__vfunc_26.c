extern int DAT_004e0858[4];
int *Gap__Core__igSkeleton__vfunc_26(void *arg0, int arg1) {
    int *temp_v0;

    temp_v0 = (int *)(*(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 16) + (arg1 * 4)))) + 8));
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return &DAT_004e0858[0];
}
