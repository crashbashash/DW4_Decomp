struct L { char pad[8]; int cnt; int pad2; unsigned *items; };
int FUN_00142bb0(struct L *arg0, unsigned *arg1) {
    int cnt;
    int mid;
    unsigned a;
    unsigned b;
    int hi;
    int lo;
    cnt = arg0->cnt;
    lo = 0;
    hi = cnt - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        b = *arg1;
        a = arg0->items[mid];
        if (a < b) {
            lo = mid + 1;
        } else if (b < a) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (cnt == 0) {
        return 0;
    }
    return arg0->items[lo] < *arg1 ? lo + 1 : lo;
}
