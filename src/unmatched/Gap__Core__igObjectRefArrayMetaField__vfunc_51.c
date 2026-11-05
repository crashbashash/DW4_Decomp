int Gap__Core__igObjectRefMetaField__vfunc_51();

int Gap__Core__igObjectRefArrayMetaField__vfunc_51(void *arg0, int arg1, char *arg2, int arg3, int arg4) {
    int i;
    int start;
    int cur;
    int *p;
    p = (int *)arg1;
    cur = (int)arg2;
    start = cur;
    for (i = 0; i < *(int *)((char *)arg0 + 68); i++) {
        cur += Gap__Core__igObjectRefMetaField__vfunc_51(arg0, p, cur, arg3, arg4);
        p++;
    }
    return cur - start;
}
