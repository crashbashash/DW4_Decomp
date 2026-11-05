struct L { char pad[8]; int n; int pad2; int *d; };
typedef int (*Cmp)(int *, int);
extern "C" int FUN_002d6e60(L *l, int key, Cmp cmp) {
    int lo = 0; int hi = l->n - 1; int mid; int r;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        r = cmp(l->d + mid, key);
        if (r < 0) lo = mid + 1; else if (r > 0) hi = mid - 1; else return mid;
    }
    if (l->n == 0) return 0;
    if (cmp(l->d + lo, key) < 0) lo++;
    return lo;
}