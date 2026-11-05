int FUN_002d7e90();
typedef struct A { char p[8]; int n; } A;
typedef struct K { char p[8]; int f8; } K;
int FUN_002d86b0(A *arg0, K *arg1, unsigned arg2) {
    int n;
    int lo;
    int hi;
    int mid;
    unsigned v;
    if (arg1 == 0) return -1;
    n = arg0->n;
    hi = n - 1;
    if (n <= 0) return 0;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        v = *(unsigned *)((char *)FUN_002d7e90(arg0, mid) + arg1->f8);
        if (v < arg2) {
            lo = mid + 1;
        } else if (arg2 < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    v = *(unsigned *)((char *)FUN_002d7e90(arg0, lo) + arg1->f8);
    if (v < arg2) lo++;
    return lo;
}
