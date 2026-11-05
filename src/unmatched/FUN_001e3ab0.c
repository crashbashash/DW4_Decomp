/* 0x001e3ab0 - FUN_001e3ab0. sorted-array lower bound; declaration order (cnt, mid, a, b, hi, lo) and the final increment as a conditional expression. Verified byte-identical by tools/verify.py. */
struct L { char pad[8]; int cnt; int pad2; int *items; };
int FUN_001e3ab0(struct L *arg0, int *arg1) {
    int cnt;
    int mid;
    int a;
    int b;
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
