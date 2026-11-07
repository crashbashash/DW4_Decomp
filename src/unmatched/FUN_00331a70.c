typedef struct L { char pad[8]; int count; int pad2; unsigned int *data; } L;
int FUN_00331a70(L *arg0, unsigned int *arg1) {
    unsigned int v;
    int lo;
    int hi;
    int mid;
    unsigned int k;
    int n;
    lo = 0;
    n = arg0->count;
    hi = n - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        k = *arg1;
        v = arg0->data[mid];
        if (v < k) {
            lo = 1 + mid;
        } else if (k < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!n) return 0;
    lo = (arg0->data[lo] < *arg1) ? lo + 1 : lo;
    return lo;
}
