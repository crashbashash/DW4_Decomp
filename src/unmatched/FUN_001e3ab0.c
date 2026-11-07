struct L { char pad[8]; int cnt; int pad2; int *items; };
int FUN_001e3ab0(struct L *arg0, int *arg1) {
    int lo;
    int hi;
    int mid;
    int b;
    int cnt;
    int a;
    cnt = arg0->cnt;
    hi = cnt - 1;
    lo = 0;
    while (lo < hi) {
        b = *arg1;
        mid = (lo + hi) >> 1;
        a = arg0->items[mid];
        if (a < b) {
            lo = mid + 1;
        } else if (b < a) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!cnt) {
        return 0;
    }
    return arg0->items[lo] < *arg1 ? 1 + lo : lo;
}
