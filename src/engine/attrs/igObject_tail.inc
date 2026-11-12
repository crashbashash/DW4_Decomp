/* Default slot 21: constant 4. */
int Gap__Core__igObject__vfunc_21(void)
{
    return 4;
}

int FUN_00142bb0(struct L_142bb0 *arg0, unsigned *arg1) {
    int mid;
    int lo;
    int hi;
    unsigned b;
    unsigned a;
    int cnt;
    lo = 0;
    cnt = arg0->cnt;
    hi = cnt - 1;
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

