int strcmp(int, int);
struct E { int pad4; int rc; };
struct T { int pad[1]; unsigned int cnt; unsigned int n; int pad12; int *tab; };
int StringTable_SearchRetained(struct T *arg0, int arg1, int *arg2, unsigned int *arg3) {
    unsigned int lo;
    unsigned int n;
    unsigned int mid;
    struct E *e;
    int s;
    int r;
    lo = 0;
    for (n = arg0->n; n != 0; n >>= 1) {
        mid = lo + n;
        if (arg0->cnt >= mid) {
            e = (struct E *)arg0->tab[mid - 1];
            s = (int)e + 8;
            r = strcmp(arg1, s);
            if (r == 0) {
                e->rc = e->rc + 1;
                *arg2 = s;
                *arg3 = mid - 1;
                return 1;
            }
            if (r > 0) {
                lo = mid;
            }
        }
    }
    *arg3 = lo;
    return 0;
}
