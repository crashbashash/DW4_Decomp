int igProperty_FindInsertionIndex();
int igProperty_FindBySortedKey(void *arg0, void *arg1, int arg2) {
    int idx;
    int v;
    int t;
    if (arg1 == 0) {
        return 0;
    }
    idx = igProperty_FindInsertionIndex();
    if (idx >= *(int *)((char *)(arg0) + 8)) {
        return 0;
    }
    v = *(int *)(*(int *)((char *)(arg0) + 16) + (idx * 4));
    t = *(int *)(v + *(int *)((char *)(arg1) + 8));
    if (t != arg2) {
        return 0;
    }
    return v;
}
