int igProperty_FindInsertionIndex(void *arg0, void *arg1, unsigned int arg2) {
    int n;
    int lo;
    int hi;
    int mid;
    unsigned int key;
    int e;
    if (arg1 == 0) {
        return -1;
    }
    n = *(int *)((char *)(arg0) + 8);
    if (n <= 0) {
        return 0;
    }
    hi = n - 1;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        e = *(int *)(*(int *)((char *)(arg0) + 16) + (mid * 4));
        key = *(unsigned int *)(e + *(int *)((char *)(arg1) + 8));
        if (key < arg2) {
            lo = mid + 1;
        } else if (arg2 < key) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    e = *(int *)(*(int *)((char *)(arg0) + 16) + (lo * 4));
    if (*(unsigned int *)(e + *(int *)((char *)(arg1) + 8)) < arg2) {
        return lo + 1;
    }
    return lo;
}
