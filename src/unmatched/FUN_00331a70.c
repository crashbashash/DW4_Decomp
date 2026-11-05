typedef struct L { char pad[8]; int count; int pad2; unsigned int *data; } L;
int FUN_00331a70(L *arg0, unsigned int *arg1) {
    int n;
    unsigned int k;
    int hi;
    int lo;
    int mid;
    unsigned int v;
    n = arg0->count;
    lo = 0;
    hi = n - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        k = *arg1;
        v = arg0->data[mid];
        if (v < k) {
            lo = mid + 1;
        } else if (k < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (n == 0) return 0;
    lo = (arg0->data[lo] < *arg1) ? lo + 1 : lo;
    return lo;
}
