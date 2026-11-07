extern "C" int StringChunk_ReleaseHeader(int, int *);
struct RecoveryString {
    int *p;
    RecoveryString() : p(0) {}
    ~RecoveryString() {
        int *q = p;
        if (q != 0) {
            int *t = (int *)((char *)q - 8);
            int v = t[1] - 1;
            t[1] = v;
            if (v == 0) StringChunk_ReleaseHeader(*t, t);
        }
    }
};
struct List { char pad[8]; int count; int pad2; int **data; };

extern "C" int FUN_0022cb80(List *arg0, int **arg1) {
    int *x;
    RecoveryString h;
    int lo = 0;
    int hi = arg0->count - 1;
    int mid;
    int **s0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        s0 = &arg0->data[mid];
        x = *s0;
        if (x) *(int *)((char *)x - 4) = *(int *)((char *)x - 4) + 1;
        {
            int *q = h.p;
            if (q) {
                int *t = (int *)((char *)q - 8);
                int v = t[1] - 1;
                t[1] = v;
                if (0 == v) StringChunk_ReleaseHeader(*t, t);
            }
        }
        h.p = *s0;
        unsigned a = (unsigned)((char *)*arg1 - (char *)8);
        unsigned b = (unsigned)((char *)h.p - (char *)8);
        if (b < a) {
            lo = mid + 1;
        } else if (a < b) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (arg0->count == 0) return 0;
    if ((unsigned)((char *)arg0->data[lo] - (char *)8) < (unsigned)((char *)*arg1 - (char *)8)) return 1 + lo;
    return lo;
}
